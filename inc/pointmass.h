#pragma once
#include "mass.h"
#include <memory>


class PointMass : public Mass{


    public:
    PointMass();
    PointMass(double mass, Vector3d position, Vector3d velocity = {0,0,0});
    PointMass(const std::string& description);

    void draw(TDT4102::AnimationWindow*);





};