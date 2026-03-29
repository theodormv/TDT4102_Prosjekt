#include "../inc/physics.h"

Vector3d Physics::newtonsGravity(double m1, double m2, const Vector3d& r1, const Vector3d& r2){
    Vector3d distance = r2 - r1;
    return  distance.getNormalized() * (GravitationalConstant * m1 * m2 / (distance.squareNorm() + 1e-3));
}

double Physics::potentialEnergy(double m1, double m2, const Vector3d& r1, const Vector3d& r2){
    Vector3d distance = r2 - r1;
    return  - (GravitationalConstant * m1 * m2 / distance.norm());
}
