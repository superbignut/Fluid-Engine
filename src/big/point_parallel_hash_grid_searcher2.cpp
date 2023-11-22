#include "point_parallel_hash_grid_searcher2.h"
#include "constants.h"
#include "parallel.h"

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

        _startIndexTable.resize(_resolution.x * _resolution.y, kMaxSize);
        _endIndexTable.resize(_resolution.x * _resolution.y, kMaxSize);

        // parallelFill(_startIndexTable.begin(), _startIndexTable.end(), kMaxSize); // use parallel instead of resize.
        // parallelFill(_endIndexTable.begin(), _endIndexTable.end(), kMaxSize);

        _keys.resize(numberOfPoints);
        _sortedIndices.resize(numberOfPoints);
        _points.resize(numberOfPoints);

        if (numberOfPoints == 0)
        {
            return;
        }

        // Initialize indices array and generate hash key for each point.
        parallelFor(kZeroSize, numberOfPoints, [&](std::size_t i){
            _sortedIndices[i] = i;
            _points[i] = points[i];
            tempKeys[i] = this->getHashKeyFromPosition(points[i]); }); // get the hashKey of each point.



        
    }

    std::size_t PointParallelHashGridSearcher2::getHashKeyFromPosition(const Vector2D &position) const
    {
        Point2I bucketIndex = getBucketIndex(position);
        return getHashKeyFromBucketIndex(bucketIndex);
    }

    std::size_t PointParallelHashGridSearcher2::getHashKeyFromBucketIndex(const Point2I &bucketIndex) const
    {
        Point2I wrappedIndex = bucketIndex;
        wrappedIndex.x = bucketIndex.x % _resolution.x;
        wrappedIndex.y = bucketIndex.y % _resolution.y;
        // Therefore, it will get same return if they have the same wrappedIndex by mod.
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

}