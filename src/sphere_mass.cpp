#include "Sphere_mass.h"

SphereMass::SphereMass() : Mass(){
    radius = 1;
    elasisity = 1;
}

SphereMass::SphereMass(double m, double rad, double el, const Vector3d& pos, const Vector3d& vel) 
: Mass(m, pos, vel), radius(rad), elasisity(el) {}

void SphereMass::draw(TDT4102::AnimationWindow* win){
    win->draw_circle(getPosition().toPoint2d(), radius, TDT4102::Color(0x5555ff));
}

double SphereMass::getRadius() {return radius;}
double SphereMass::getElasticity() {return elasisity;}