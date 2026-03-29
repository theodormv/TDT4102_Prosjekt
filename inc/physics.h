#pragma once
#include "vector.h"

namespace Physics{
    #define G 6.6743015e-11
    constexpr double GravitationalConstant = 1;

    Vector3d newtonsGravity(double m1, double m2, const Vector3d& r1, const Vector3d& r2);
    
    double potentialEnergy(double m1, double m2, const Vector3d& r1, const Vector3d& r2);

    inline double kineticEnergy(double mass, const Vector3d& velocity){
        return 0.5*mass*velocity.squareNorm();
    }
};