#include "generated/partical_system_data2_generated.h"
#include "point_parallel_hash_grid_searcher2.h"
#include "parallel.h"
#include "particle_system_data2.h"
#include "timer.h"
#include "macros.h"

#include <algorithm>
#include <vector>

using namespace big;

static const std::size_t kDefaultHashGridResolution = 64;

ParticleSystemData2::ParticleSystemData2()
    : ParticleSystemData2(0)
{
}

ParticleSystemData2::ParticleSystemData2(std::size_t numberOfParticles)
{
    _positionIdx = addVectorData();
    _velocityIdx = addVectorData();
    _forceIdx = addVectorData();
}

std::size_t ParticleSystemData2::numberOfParticles() const
{
    return _numberOfParticles;
}

void ParticleSystemData2::resize(std::size_t newNumberOfParticles)
{
    for (auto &attr : _scalarDataList)
    {
        attr.resize(newNumberOfParticles, 0.0);
    }
    for (auto &attr : _vectorDataList)
    {
        attr.resize(newNumberOfParticles, Vector2D());
    }
}
std::size_t ParticleSystemData2::addScaleData(double initialVal)
{
    std::size_t attrIdx = _scalarDataList.size();
    _scalarDataList.emplace_back(numberOfParticles(), initialVal);
    return attrIdx;
}

std::size_t ParticleSystemData2::addVectorData(const Vector2D &initialVal)
{
    std::size_t attrIdx = _vectorDataList.size();
    _vectorDataList.emplace_back(numberOfParticles(), initialVal);
    return attrIdx;
}

double ParticleSystemData2::radius() const
{
    return _radius;
}

void ParticleSystemData2::setRadius(double newRadius)
{
    _radius = std::max(0.0, newRadius);
}

double ParticleSystemData2::mass() const
{
    return _mass;
}
void ParticleSystemData2::setMass(double newMass)
{
    _mass = std::max(0.0, newMass);
}
ConstArrayAccessor1<Vector2D> ParticleSystemData2::positions() const
{
    return vectorDataAt(_positionIdx);
}

ArrayAccessor1<Vector2D> ParticleSystemData2::positions()
{
    return vectorDataAt(_positionIdx);
}

ConstArrayAccessor1<Vector2D> ParticleSystemData2::velocities() const
{
    return vectorDataAt(_velocityIdx);
}

ArrayAccessor1<Vector2D> ParticleSystemData2::velocities()
{
    return vectorDataAt(_velocityIdx);
}

ConstArrayAccessor1<Vector2D> ParticleSystemData2::forces() const
{
    return vectorDataAt(_forceIdx);
}

ArrayAccessor1<Vector2D> ParticleSystemData2::forces()
{
    return vectorDataAt(_forceIdx);
}

ConstArrayAccessor1<double> ParticleSystemData2::scalarDataAt(std::size_t idx) const
{
    return _scalarDataList[idx].constAccessor();
}

ArrayAccessor1<double> ParticleSystemData2::scalarDataAt(std::size_t idx)
{
    return _scalarDataList[idx].accessor();
}

ConstArrayAccessor1<Vector2D> ParticleSystemData2::vectorDataAt(std::size_t idx) const
{
    return _vectorDataList[idx].constAccessor();
}

ArrayAccessor1<Vector2D> ParticleSystemData2::vectorDataAt(std::size_t idx)
{
    return _vectorDataList[idx].accessor();
}
void ParticleSystemData2::addParticle(const Vector2D &newPosition,
                                      const Vector2D &newVelocity,
                                      const Vector2D &newForce)
{
    Array1<Vector2D> newPositions = {newPosition};
    Array1<Vector2D> newVelocitys = {newVelocity};
    Array1<Vector2D> newForces = {newForce};
    addParticles(newPositions.constAccessor(), newVelocitys.constAccessor(), newForces.constAccessor());
}
void ParticleSystemData2::addParticles(const ConstArrayAccessor1<Vector2D> &newPositions,
                                       const ConstArrayAccessor1<Vector2D> &newVelocities,
                                       const ConstArrayAccessor1<Vector2D> &newForces)
{
    // the three of them must have the same size, alought each can be 0.
    BIG_THROW_INVALID_ARG_IF(newVelocities.size() > 0 && newVelocities.size() != newPositions.size());
    BIG_THROW_INVALID_ARG_IF(newForces.size() > 0 && newForces.size() != newPositions.size());

    std::size_t oldNumberOfParticles = numberOfParticles();
    std::size_t newNumberOfParticles = oldNumberOfParticles + newPositions.size();

    resize(newNumberOfParticles);

    // Return the corresponding array_accessor.
    auto pos_array_accessor = positions();
    auto vel_array_accessor = velocities();
    auto frc_array_accessor = forces();

    parallelFor(kZeroSize,
                newPositions.size(),
                [&](std::size_t i)
                {
                    pos_array_accessor[oldNumberOfParticles + i] = newPositions[i];
                });
    parallelFor(kZeroSize,
                newVelocities.size(),
                [&](std::size_t i)
                {
                    vel_array_accessor[oldNumberOfParticles + i] = newVelocities[i];
                });
    parallelFor(kZeroSize,
                newForces.size(),
                [&](std::size_t i)
                {
                    frc_array_accessor[oldNumberOfParticles + i] = newForces[i];
                });
}

const PointNeighborSearcher2Ptr &ParticleSystemData2::neighborSearcher() const
{
    return _neighborSearcher;
}
void ParticleSystemData2::setNeighborSearcher(const PointNeighborSearcher2Ptr &neighborSearcher)
{
    _neighborSearcher = neighborSearcher;
}

void ParticleSystemData2::buildNeighborSearcher(double gridSpacing)
{
    _neighborSearcher = std::make_shared<PointParallelHashGridSearcher2>(kDefaultHashGridResolution,
                                                                         kDefaultHashGridResolution,
                                                                         gridSpacing);
    _neighborSearcher->build(static_cast<ConstArrayAccessor1<Vector2D>>(positions()));
}

void ParticleSystemData2::buildNeighborLists(double maxSearchRadius)
{
    _neighborLists.resize(numberOfParticles());
    auto position = positions();
    for (std::size_t i = 0; i < numberOfParticles(); ++i)
    {
        Vector2D origin = position[i];
        _neighborLists[i].clear();

        _neighborSearcher->forEachNearbyPoint(
            origin,
            maxSearchRadius,
            [&](std::size_t j, const Vector2D &)
            {
                // Second parameter is not used.
                if (i != j)
                {
                    _neighborLists[i].push_back(j);
                }
            });
    }
}

void ParticleSystemData2::serialize(std::vector<uint8_t> *buffer) const
{
    flatbuffers::FlatBufferBuilder builder(1024);
    flatbuffers::Offset<fbs::ParticleSystemData2> fbsParticleSystemData;
    serializeParticleSystemData(&builder, &fbsParticleSystemData);
}
void ParticleSystemData2::deserialize(const std::vector<uint8_t> &buffer)
{
}

void ParticleSystemData2::serializeParticleSystemData(
    flatbuffers::FlatBufferBuilder *builder,
    flatbuffers::Offset<fbs::ParticleSystemData2> *fbsParticleSystemData) const
{
    std::vector<flatbuffers::Offset<fbs::ScalarParticleData2>> scalarDataList;
    for(const auto &scalarData : _scalarDataList)
    {
        auto fbsScalarData = fbs::CreateScalarParticleData2(
            *builder,
            builder->CreateVector(scalarData.data(), scalarData.size()));
        scalarDataList.push_back(fbsScalarData);
    }
    auto fbsScalarDataList = builder->CreateVector(scalarDataList);
}