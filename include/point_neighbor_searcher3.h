#ifndef INCLUDE_PARTICLE_NEIGHBOR_SEARCHER3_H_
#define INCLUDE_PARTICLE_NEIGHBOR_SEARCHER3_H_

#include "array_accessor1.h"
#include "serialization.h"
#include "vector3.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace big
{

    //! \brief Abstract base class for 3-D neighbor point searcher.

    //! This class provides interface for 3-D neighbor point searcher. For
    //! given list of points, the class builts internal cache to accelerate
    //! the search.Once build, the data structure is used to search nearby points
    //! for given origin point.
    class PointNeighborSearcher3 : public Serializable
    {
    public:
        /// @brief Callback function for nearby search query.first parameter is the index of the
        /// nearby point, and the second is the position of the point.
        typedef std::function<void(std::size_t, const Vector3D &)> ForEachNearbyPointFunc;

        PointNeighborSearcher3() = default;

        virtual ~PointNeighborSearcher3() = default;

        /// @brief Return the name of derived class;
        /// @return 
        virtual std::string typeName() const = 0;

        /// @brief Build internal acceleration structure for given points list.
        /// @param points 
        virtual void build(const ConstArrayAccessor1<Vector3D> &points) = 0;

        /// @brief Invoke the callback function for each nearby point around the origin
        /// within given radius.
        /// @param origin The origin position
        /// @param radius The search radius
        /// @param callback The callback function
        virtual void forEachNearbyPoint(const Vector3D& origin, double radius, const ForEachNearbyPointFunc& callback) const = 0;

        /// @brief Return true if there are any nearby points for given origin within radius.
        /// @param origin 
        /// @param radius 
        /// @return 
        virtual bool hasNearbyPoint(const Vector3D& origin, double radius) const = 0;

        /// @brief Creates a new instance of the object with same properties than original.
        /// @return 
        virtual std::shared_ptr<PointNeighborSearcher3> clone() const = 0;
    };

    typedef std::shared_ptr<PointNeighborSearcher3> PointNeighborSearcher3Ptr;

    #define BIG_NEIGHBOR_SEARCHER3_TYPE_NAME(DerivedClassName) \
        std::string typename() const override { \
            return #DerivedClassName; \
        }
}

#endif