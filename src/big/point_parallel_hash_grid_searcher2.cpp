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

        _startIndexTable.resize(_resolution.x * _resolution.y);
        _endIndexTable.resize(_resolution.x * _resolution.y);

        // parallelFill

    }

}