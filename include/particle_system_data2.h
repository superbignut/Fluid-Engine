#ifndef INCLUDE_PARTICLE_SYSTEM_DATA2_H_
#define INCLUDE_PARTICLE_SYSTEM_DATA2_H_
#include "array1.h"
#include "serialization.h"
#include "point_neighbor_searcher2.h"
#include <memory>
#include <vector>

namespace flatbuffers
{
    template <bool Is64Aware>
    class FlatBufferBuilderImpl;

    using FlatBufferBuilder = class flatbuffers::FlatBufferBuilderImpl<false>;

    template <typename T>
    struct Offset;
}
namespace big
{
    namespace fbs
    {
        struct ParticleSystemData2;
    }
}

namespace big
{
    /// @brief 2-D particle system data.
    class ParticleSystemData2 : public Serializable
    {
    public:
        typedef Array1<double> ScalarData;

        typedef Array1<Vector2D> VectorData;

        ParticleSystemData2();

        explicit ParticleSystemData2(std::size_t numberOfParticles);

        ParticleSystemData2(const ParticleSystemData2 &other);

        ~ParticleSystemData2() = default;

        /// @brief Resize the number of particles of the container.
        /// @param newNumberOfParticles
        void resize(std::size_t newNumberOfParticles);

        /// @brief Return the number of particles of the container.
        /// @return
        std::size_t numberOfParticles() const;

        /// @brief Add a scalar data layer and return its index.
        /// @param initialVal
        /// @return
        std::size_t addScaleData(double initialVal = 0.0);

        /// @brief Add a vector data layer and return its index
        /// @param initialVal
        /// @return
        std::size_t addVectorData(const Vector2D &initialVal = Vector2D());

        double radius() const;

        virtual void setRadius(double newRadius);

        double mass() const;

        virtual void setMass(double newMass);

        /// @brief Return the corresponding ArrayAccessor1/ConstArrayAccessor1
        /// @return
        ConstArrayAccessor1<Vector2D> positions() const;

        ArrayAccessor1<Vector2D> positions();

        ConstArrayAccessor1<Vector2D> velocities() const;

        ArrayAccessor1<Vector2D> velocities();

        ConstArrayAccessor1<Vector2D> forces() const;

        ArrayAccessor1<Vector2D> forces();

        ConstArrayAccessor1<double> scalarDataAt(std::size_t idx) const;

        ArrayAccessor1<double> scalarDataAt(std::size_t idx);

        ConstArrayAccessor1<Vector2D> vectorDataAt(std::size_t idx) const;

        ArrayAccessor1<Vector2D> vectorDataAt(std::size_t idx);

        /// @brief Add a particle to the data structure.
        /// However, this function will invalidate neighbor seacher and neighbor lists; It is
        /// user's responsibility to call buildNeighborSearcher and buildNeighborLists to refresh.
        void addParticle(const Vector2D &newPosition,
                         const Vector2D &newVelocity = Vector2D(),
                         const Vector2D &newForce = Vector2D());

        /// @brief Add particles to the data structure.
        /// However, this function will invalidate neighbor seacher and neighbor lists; It is
        /// user's responsibility to call buildNeighborSearcher and buildNeighborLists to refresh.
        void addParticles(const ConstArrayAccessor1<Vector2D> &newPositions,
                          const ConstArrayAccessor1<Vector2D> &newVelocities = ConstArrayAccessor1<Vector2D>(),
                          const ConstArrayAccessor1<Vector2D> &newForces = ConstArrayAccessor1<Vector2D>());

        /// @brief  Reaturns neighbor searcher.
        /// @return
        const PointNeighborSearcher2Ptr &neighborSearcher() const;

        /// @brief Set neighbor searcher.
        /// @param neighborSearcher
        void setNeighborSearcher(const PointNeighborSearcher2Ptr &neighborSearcher);

        /// @brief Return neighbor List.
        /// @return
        const std::vector<std::vector<std::size_t>> &neighborLists() const;

        /// @brief Build neighbor searcher with given search radius.
        /// @param maxSearchRadius 
        void buildNeighborSearcher(double gridSpacing);

        void buildNeighborLists(double maxSearchRadius);

        /// @brief
        /// @param buffer
        void serialize(std::vector<uint8_t> *buffer) const override;
        /// @brief
        /// @param buffer
        void deserialize(const std::vector<uint8_t> &buffer) override;

        void set(const ParticleSystemData2 &other);

        ParticleSystemData2 &operator=(const ParticleSystemData2 &other);

    protected:
        /// @brief
        /// @param builder
        /// @param fbsParticleSystemData
        void serializeParticleSystemData(
            flatbuffers::FlatBufferBuilder *builder,
            flatbuffers::Offset<fbs::ParticleSystemData2> *fbsParticleSystemData) const;

        /// @brief
        /// @param fbsParticleSystemData
        void deserializeParticleSystemData(
            const fbs::ParticleSystemData2 *fbsParticleSystemData);

    private:
        double _radius = 1e-3;
        double _mass = 1e-3;
        std::size_t _numberOfParticles = 0;
        std::size_t _positionIdx;
        std::size_t _velocityIdx;
        std::size_t _forceIdx;

        /// @brief Useful vector and scalar data list:
        /// _vectorDataList[_velocityIdx] is the velocity vector,
        /// _vectorDataList[_positionIdx] is the position vector,
        /// which can be expanded easily.
        std::vector<ScalarData> _scalarDataList;
        std::vector<VectorData> _vectorDataList;

        /// @brief Build an internal acceleration structure for given points list.
        PointNeighborSearcher2Ptr _neighborSearcher;
        /// @brief Use _neighborSearcher->fuction() to find out each NearbyPoints.
        std::vector<std::vector<std::size_t>> _neighborLists;
    };

    typedef std::shared_ptr<ParticleSystemData2> ParticleSystemData2Ptr;

} // namespace big

#endif