#include "../inc/pointmass.h"

void PointMass::draw(TDT4102::AnimationWindow* window){
    window->draw_circle(getPosition().toPoint2d(), 10, TDT4102::Color(255,0,0));
}

PointMass::PointMass(double m, Vector3d pos, Vector3d vel) : Mass(m, pos, vel){}
PointMass::PointMass() : Mass() {
    __debugbreak();
}