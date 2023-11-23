#ifndef INCLUDE_BIG_POINT_PARALLEL_HASH_GRID_SEARCHER_H_
#define INCLUDE_BIG_POINT_PARALLEL_HASH_GRID_SEARCHER_H_
#include "point_neighbor_searcher2.h"
#include "point2.h"
#include "size2.h"

#include <vector>

class PointParallelHashGridSearcher2Tests;

namespace big
{   
    /// @brief Parallel version for hash grid-based 2-D point searcher.
    ///
    /// This class implements parallel version of 2-D point searcher by using hash 
    /// grid for its internal acceleration data structure. Each point is recorded to
    /// its corresponding bucket where the hashing function is 2-D grid mapping.
    ///
    class PointParallelHashGridSearcher2 final : public PointNeighborSearcher2
    {
    public:
        BIG_NEIGHBOR_SEARCHER2_TYPE_NAME(PointParallelHashGridSearcher2)

        class Builder;

        /// @brief
        /// @param resolution
        /// @param gridSpacing
        PointParallelHashGridSearcher2(const Size2 &resolution, double gridSpacing);
        
        PointParallelHashGridSearcher2(std::size_t resolutionX, std::size_t resolutionY, double gridSpacing);

        PointParallelHashGridSearcher2(const PointParallelHashGridSearcher2& other);

        void set(const PointParallelHashGridSearcher2& other);

        /// @brief Build internal acceleration structure for given points list.
        /// @param points 
        void build(const ConstArrayAccessor1<Vector2D> &points) override;

        /// @brief Return the hash value for given 2-D bucket index.
        /// Scatter the mapping spatially sothat the number of points 
        /// inside the buckets is as similar as possible.
        /// @param bucketIndex 
        /// @return 
        std::size_t getHashKeyFromBucketIndex(const Point2I& bucketIndex) const;

        /// @brief Get the bucket index of a point, just by divide _gridSpacing and std::floor
        /// Converts the input position to integer coordinate
        /// @param position 
        /// @return 
        Point2I getBucketIndex(const Vector2D& position) const;

        void forEachNearbyPoint(const Vector2D& origin, double radius, const ForEachNearbyPointFunc& callback) const override;

        bool hasNearbyPoint(const Vector2D& origin, double radius) const override;

        std::shared_ptr<PointNeighborSearcher2> clone() const override;

        void serialize(std::vector<uint8_t> *buffer) const override;
        
        void deserialize(const std::vector<uint8_t> &buffer) override;         

    private:
        friend class PointParallelHashGridSearcher2Tests;

        double _gridSpacing = 1.0;
        Point2I _resolution = Point2I(1, 1);

        std::vector<Vector2D> _points; // 存储 points 容量取决于points
        std::vector<std::size_t> _keys;  // 存储 points的hashkey 容量取决于points
        std::vector<std::size_t> _sortedIndices; // 存储 从小到大 排序后 points的序号 容量取决于points

        std::vector<std::size_t> _startIndexTable; // 容量取决于_resolution
        std::vector<std::size_t> _endIndexTable;// 容量取决于_resolution
        

        /// @brief Return a hashkey for the given 2-D position.
        /// @param position 
        /// @return 
        std::size_t getHashKeyFromPosition(const Vector2D &position) const;

        void getNearbyKeys(const Vector2D &position, std::size_t *bucketIndices) const;
    };
    typedef std::shared_ptr<PointParallelHashGridSearcher2> PointParallelHashGridSearcher2Ptr;
}

#endif