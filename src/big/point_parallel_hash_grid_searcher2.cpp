#include "point_parallel_hash_grid_searcher2.h"
#include "constants.h"
#include "parallel.h"
#include "bout.h"
#include "logging.h"
namespace big
{

    PointParallelHashGridSearcher2::PointParallelHashGridSearcher2(const Size2 &resolution, double gridSpacing)
        : PointParallelHashGridSearcher2(resolution.x, resolution.y, gridSpacing)
    {
    }

    PointParallelHashGridSearcher2::PointParallelHashGridSearcher2(std::size_t resolutionX, std::size_t resolutionY, double gridSpacing)
        : _gridSpacing(gridSpacing)
    {
        _resolution.x = std::max(static_cast<ssize_t>(resolutionX), kOneSSize);
        _resolution.y = std::max(static_cast<ssize_t>(resolutionY), kOneSSize);

        _startIndexTable.resize(_resolution.x * _resolution.y, kMaxSize);
        _endIndexTable.resize(_resolution.x * _resolution.y, kMaxSize);
    }

    PointParallelHashGridSearcher2::PointParallelHashGridSearcher2(const PointParallelHashGridSearcher2 &other)
    {
        set(other);
    }

    void PointParallelHashGridSearcher2::set(const PointParallelHashGridSearcher2 &other)
    {
        _gridSpacing = other._gridSpacing;
        _resolution = other._resolution;
        _points = other._points;
        _keys = other._keys;
        _startIndexTable = other._startIndexTable;
        _endIndexTable = other._endIndexTable;
        _sortedIndices = other._sortedIndices;
    }

    void PointParallelHashGridSearcher2::build(const ConstArrayAccessor1<Vector2D> &points)
    {
        _points.clear();
        _keys.clear();
        _startIndexTable.clear();
        _endIndexTable.clear();
        _sortedIndices.clear();

        /// Allocate memory chuncks.
        std::size_t numberOfPoints = points.size();
        std::vector<std::size_t> tempKeys(numberOfPoints);

        _startIndexTable.resize(_resolution.x * _resolution.y, kMaxSize); // 为什么开这么大的空间呢？
        _endIndexTable.resize(_resolution.x * _resolution.y, kMaxSize);

        _keys.resize(numberOfPoints);
        _sortedIndices.resize(numberOfPoints);
        _points.resize(numberOfPoints);

        if (numberOfPoints == 0)
        {
            return;
        }

        // Initialize indices array and generate hash key for each point.
        parallelFor(kZeroSize,
                    numberOfPoints,
                    [&](std::size_t i)
                    {
                        _sortedIndices[i] = i;
                        _points[i] = points[i];
                        tempKeys[i] = this->getHashKeyFromPosition(points[i]);
                    }); // get the hashKey of each point.

        // Sort index based on hash key.
        parallelSort(_sortedIndices.begin(),
                     _sortedIndices.end(),
                     [&tempKeys](std::size_t indexA, std::size_t indexB)
                     {
                         return tempKeys[indexA] < tempKeys[indexB];
                     });

        // Re-order point and key arrays.
        // Sothat the _points and _keys are sorted by the magnitude of hashkey from small to large.
        parallelFor(kZeroSize,
                    numberOfPoints,
                    [&](std::size_t i)
                    {
                        _points[i] = points[_sortedIndices[i]];
                        _keys[i] = tempKeys[_sortedIndices[i]];
                    });
        // bout(_keys);

        _startIndexTable[_keys[0]] = 0;
        _endIndexTable[_keys[numberOfPoints - 1]] = numberOfPoints;

        parallelFor(kOneSize,
                    numberOfPoints,
                    [&](std::size_t i)
                    {
                        if (_keys[i] > _keys[i - 1])
                        {
                            _startIndexTable[_keys[i]] = i;
                            _endIndexTable[_keys[i - 1]] = i;
                        }
                    });
        ///  points : {{1, 2}, {2, 3}, {3, 4}, {-4,-3}, {5, 6}, {1, 3.0}, {2, 5}, {5, 1},{2, 7}}
        ///  tempKeys: 100 101 201 9898 302 100 201 2 301

        /// sorted:

        /// _sortedIndices : 7 5 0 1 6 2 8 4 3
        /// _keys : 2 100 100 101 201 201 301 302 9898

        /// _startIndexTable: 0 1 1 3 4 4 6 7 8
        /// _endIndexTable  : 1 3 3 4 6 6 7 8 9

        std::size_t sumNumberOfPointsPerBucket = 0;
        std::size_t maxNumberOfPointsPerBucket = 0;
        std::size_t numberOfNonEmptyBucket = 0;

        for (std::size_t i = 0; i < _startIndexTable.size(); ++i)
        {
            if (_startIndexTable[i] != kMaxSize)
            {
                std::size_t numberOfPointInBucket = _endIndexTable[i] - _startIndexTable[i];
                sumNumberOfPointsPerBucket += numberOfPointInBucket;
                maxNumberOfPointsPerBucket = std::max(maxNumberOfPointsPerBucket, numberOfPointInBucket);
                ++numberOfNonEmptyBucket;
            }
        }
        BIG_INFO << sumNumberOfPointsPerBucket << " "<< maxNumberOfPointsPerBucket <<" " << numberOfNonEmptyBucket;
    }

    std::size_t PointParallelHashGridSearcher2::getHashKeyFromPosition(const Vector2D &position) const
    {
        Point2I bucketIndex = getBucketIndex(position);
        return getHashKeyFromBucketIndex(bucketIndex);
    }

    std::size_t PointParallelHashGridSearcher2::getHashKeyFromBucketIndex(const Point2I &bucketIndex) const
    {
        Point2I wrappedIndex = bucketIndex;
        // -1 % 2 = -1
        // -2 % 2 = 0
        // -3 % 2 = -1
        wrappedIndex.x = bucketIndex.x % _resolution.x;
        wrappedIndex.y = bucketIndex.y % _resolution.y;

        if (wrappedIndex.x < 0)
        {
            assert("there is a negative number!");
            wrappedIndex.x += _resolution.x;
        }
        if (wrappedIndex.y < 0)
        {
            assert("there is a negative number!");
            wrappedIndex.y += _resolution.y;
        }
        // And the hashKey ensure to be  positive,
        return static_cast<std::size_t>(wrappedIndex.x + wrappedIndex.y * _resolution.x);
    }

    Point2I PointParallelHashGridSearcher2::getBucketIndex(const Vector2D &position) const
    {
        Point2I bucketIndex;
        bucketIndex.x = static_cast<ssize_t>(std::floor(position.x / _gridSpacing));
        bucketIndex.y = static_cast<ssize_t>(std::floor(position.y / _gridSpacing));
        return bucketIndex;
    }

    void PointParallelHashGridSearcher2::forEachNearbyPoint(const Vector2D &origin, double radius, const ForEachNearbyPointFunc &callback) const
    {
    }

    bool PointParallelHashGridSearcher2::hasNearbyPoint(const Vector2D &origin, double radius) const
    {
    }

    std::shared_ptr<PointNeighborSearcher2> PointParallelHashGridSearcher2::clone() const
    {
    }

    void PointParallelHashGridSearcher2::serialize(std::vector<uint8_t> *buffer) const
    {
    }

    void PointParallelHashGridSearcher2::deserialize(const std::vector<uint8_t> &buffer)
    {
    }

}