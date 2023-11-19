#include "generated/partical_system_data2_generated.h"
#include "parallel.h"
#include "particle_system_data2.h"
#include "timer.h"

#include <algorithm>
#include <vector>

using namespace big;

static const std::size_t kDefaultHashGridResolution = 64;

ParticleSystemData2::ParticleSystemData2()
    : ParticleSystemData2(0)
{
}
ParticleSystemData2

ParticleSystemData2::ParticleSystemData2(std::size_t numberOfParticles)
{
    _positionIdx = addVectorData();
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
    return _scalarDataList(idx).constAccessor();
}

ArrayAccessor1<double> ParticleSystemData2::scalarDataAt(std::size_t idx)
{
    return _scalarDataList(idx).accessor();
}

ConstArrayAccessor1<double> ParticleSystemData2::vectorDataAt(std::size_t idx) const
{
    return _vectorDataList(idx).constAccessor();
}

ArrayAccessor1<double> ParticleSystemData2::vectorDataAt(std::size_t idx)
{
    return _vectorDataList(idx).accessor();
}
void ParticleSystemData2::addParticle(const Vector2D &newPosition,
                                      const Vector2D &newVelocity = Vector2D(),
                                      const Vector2D &newForce = Vector2D())
{
    Array1<Vector2D> newPositions = {newPosition};
    Array1<Vector2D> newVelocitys = {newVelocity};
    Array1<Vector2D> newForces = {newForce};
    addParticles(newPositions.constAccessor(), newVelocitys.constAccessor(), newForces.constAccessor());
}
void ParticleSystemData2::addParticles(const ConstArrayAccessor1<Vector2D> &newPositions,
                  const ConstArrayAccessor1<Vector2D> &newVelocities = ConstArrayAccessor1<Vector2D>(),
                  const ConstArrayAccessor1<Vector2D> &newForces = ConstArrayAccessor1<Vector2D>())
{
}