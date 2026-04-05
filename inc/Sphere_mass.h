#pragma once
#include "mass.h"

class SphereMass : public Mass{
    double radius;
    double elasisity;


    public:
    SphereMass();
    SphereMass(double m, double rad, double el, const Vector3d& pos, const Vector3d& vel = {0,0,0});

    void draw(TDT4102::AnimationWindow* win);

    double getRadius();
    double getElasticity();

};