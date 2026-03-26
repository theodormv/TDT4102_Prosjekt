#pragma once
#include "mass.h"
#include <memory>


class PointMass : public Mass{


    public:
    PointMass();
    PointMass(double mass, Vector3d position, Vector3d velocity = {0,0,0});

    void draw(TDT4102::AnimationWindow*);





};