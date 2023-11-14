#include <iostream>
#include "physics_animation.h"
#include "array1.h"
#include "constant_vector_field3.h"
#include "vector3.h"
#include "manual_tests_include.h"

using namespace big;

class SimpleMassSpringAnimation : public PhysicsAnimation
{
public:
    struct Edge
    {
        std::size_t first;
        std::size_t second;
    };

    struct Constraint
    {
        std::size_t pointIndex;
        Vector3D fixedPosition;
        Vector3D fixedVelocity;
    };

    std::vector<Vector3D> positions;
    std::vector<Vector3D> velocities;
    std::vector<Vector3D> forces;
    std::vector<Edge> edges;

    double mass = 1.0;

    Vector3D gravity = Vector3D(0.0, -9.8, 0.0);

    double stiffness = 500.0; // 距离k

    double dragCoefficient = 0.1; // 速度阻尼

    double dampingCoefficient = 1.0; // 弹簧速度k

    double restLength = 1.0;

    double floorPositionY = -7.0;

    double restitutionCoefficient = 0.3; // 反弹系数

    VectorField3Ptr wind;

    std::vector<Constraint> constrains;

    SimpleMassSpringAnimation() = default;

    void makeChain(std::size_t numberOfPoints)
    {
        if (numberOfPoints == 0)
        {
            return;
        }
        std::size_t numberOfEdges = numberOfPoints - 1;

        positions.resize(numberOfPoints);
        velocities.resize(numberOfPoints);
        forces.resize(numberOfPoints);
        edges.resize(numberOfEdges);

        for (std::size_t i = 0; i < numberOfPoints; ++i)
        {
            positions[i].x = -static_cast<double>(i); // 初始位置
        }

        for (std::size_t i = 0; i < numberOfEdges; ++i)
        {
            edges[i] = Edge{i, i + 1};
        }
    }

    void exportStates(Array1<double> &x, Array1<double> &y) const
    {
        x.resize(positions.size());
        y.resize(positions.size());

        for (std::size_t i = 0; i < positions.size(); ++i)
        {
            x[i] = positions[i].x;
            y[i] = positions[i].y;
        }
    }

protected:
    void onAdvanceTimeStep(double actualTimeIntervalInSeconds) override
    {
        std::size_t numberOfPoints = positions.size();
        std::size_t numberOfEdges = edges.size();

        // compute force
        for (std::size_t i = 0; i < numberOfPoints; ++i)
        {
            forces[i] = mass * gravity;

            Vector3D relativeVel = velocities[i];
            if (wind != nullptr)
            {
                relativeVel -= wind->sample(positions[i]);
            }
            forces[i] += -dragCoefficient * relativeVel;
        }

        for (std::size_t i = 0; i < numberOfEdges; ++i)
        {
            std::size_t pointIndex0 = edges[i].first;
            std::size_t pointIndex1 = edges[i].second;

            Vector3D pos0 = positions[pointIndex0];
            Vector3D pos1 = positions[pointIndex1];
            Vector3D n = pos1 - pos0; // 正方向
            double distance = n.length();
            if (distance > 0.0)
            {
                Vector3D force = stiffness * (distance - restLength) * n.normalized();
                forces[pointIndex0] += force;
                forces[pointIndex1] -= force;
            }

            Vector3D vel0 = velocities[pointIndex0];
            Vector3D vel1 = velocities[pointIndex1];
            Vector3D relativeVel0 = vel1 - vel0;
            Vector3D damping = dampingCoefficient * relativeVel0;
            forces[pointIndex0] += damping;
            forces[pointIndex1] -= damping;
        }

        for (std::size_t i = 0; i < numberOfPoints; ++i)
        {
            Vector3D newAcceleration = forces[i] / mass;
            Vector3D newVelocity = velocities[i] + newAcceleration * actualTimeIntervalInSeconds;
            Vector3D newPosition = positions[i] + newVelocity * actualTimeIntervalInSeconds;

            if (newPosition.y < floorPositionY)
            {
                newPosition.y = floorPositionY;
                if (newVelocity.y < 0.0) // 还是向下的速度
                {
                    newVelocity.y *= -restitutionCoefficient;
                    newVelocity.y += actualTimeIntervalInSeconds * newVelocity.y;
                }
            }

            velocities[i] = newVelocity;
            positions[i] = newPosition;
        }
        for (std::size_t i = 0; i < constrains.size(); ++i)
        {
            std::size_t pointIndex = constrains[i].pointIndex;
            positions[pointIndex] = constrains[i].fixedPosition;
            velocities[pointIndex] = constrains[i].fixedVelocity;
        }
    }
};

int main()
{
    std::string outDirname = "manual_tests_output/PhysicsAnimation/SimpleMassSpringAnimation";
    sdata::creatDirectory(outDirname); // 在build目录下创建一个存放数据的目录

    Array1<double> x;
    Array1<double> y;
    SimpleMassSpringAnimation anim;

    anim.makeChain(10);
    anim.wind = std::make_shared<ConstantVectorField3>(Vector3D{30, 0, 0});

    anim.constrains.push_back({0, Vector3D(), Vector3D()});

    anim.exportStates(x, y);
    char filename[256];
    snprintf(filename, sizeof(filename), "data.#line2,0000,x.npy");
    sdata::saveData(x.constAccessor(), outDirname, filename);
    snprintf(filename, sizeof(filename), "data.#line2,0000,y.npy");
    sdata::saveData(y.constAccessor(), outDirname, filename);

    for (Frame frame(0, 1.0 / 60.0); frame._index < 360; frame.advance())
    {
        anim.update(frame);
        anim.exportStates(x, y);
        snprintf(filename, sizeof(filename), "data.#line2,%04d,x.npy", frame._index);
        sdata::saveData(x.constAccessor(), outDirname, filename);
        snprintf(filename, sizeof(filename), "data.#line2,%04d,y.npy", frame._index);
        sdata::saveData(y.constAccessor(), outDirname, filename);
    }
    return 0;
}