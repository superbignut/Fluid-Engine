#ifndef INCLUDE_PARTICLE_NEIGHBOR_SEARCHER2_H_
#define INCLUDE_PARTICLE_NEIGHBOR_SEARCHER2_H_

#include "array_accessor1.h"
#include "serialization.h"
#include "vector2.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace big
{

    //! \brief Abstract base class for 2-D neighbor point searcher.

    //! This class provides interface for 2-D neighbor point searcher. For
    //! given list of points, the class builts internal cache to accelerate
    //! the search.Once build, the data structure is used to search nearby points
    //! for given origin point.
    class PointNeighborSearcher2 : public Serializable
    {
    public:
        /// @brief Callback function for nearby search query.first parameter is the index of the
        /// nearby point, and the second is the position of the point.
        typedef std::function<void(std::size_t, const Vector2D &)> ForEachNearbyPointFunc;

        /// @brief Return the name of derived class;
        /// @return 
        virtual std::string typeName() const = 0;

        /// @brief Build internal acceleration structure for given points list.
        /// @param points 
        virtual void build(const ConstArrayAccessor1<Vector2D> &points) = 0;

        /// @brief Invoke the callback function for each nearby point around the origin
        /// within given radius.
        /// @param origin The origin position
        /// @param radius The search radius
        /// @param callback The callback function
        virtual void forEachNearbyPoint(const Vector2D& origin, double radius, const ForEachNearbyPointFunc& callback) const = 0;

        /// @brief Return true if there are any nearby points for given origin within radius.
        /// @param origin 
        /// @param radius 
        /// @return 
        virtual bool hasNearbyPoint(const Vector2D& origin, double radius) const = 0;

        /// @brief Creates a new instance of the object with same properties than original.
        /// @return 
        virtual std::shared_ptr<PointNeighborSearcher2> clone() const = 0;
    };

    typedef std::shared_ptr<PointNeighborSearcher2> PointNeighborSearcher2Ptr;

    class PointNeighborSearcherBuilder2 {
        public:
            /// @brief Return shared_ptr of PointNeighborSearcher2 type.
            /// @return 
            virtual PointNeighborSearcher2Ptr buildPointNeighborSearcher() const = 0;
    };

    typedef std::shared_ptr<PointNeighborSearcher2> PointNeighborSearcherBuilder2Ptr;
    
    #define BIG_NEIGHBOR_SEARCHER2_TYPE_NAME(DerivedClassName) \
        std::string typeName() const override { \
            return #DerivedClassName; \
        }
}

#endif