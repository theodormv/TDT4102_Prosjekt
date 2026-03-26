#pragma once
#include "AnimationWindow.h"
#include "vector.h"
#include "physics.h"

class Mass{

    double mass;

    Vector3d position;
    Vector3d velocity;

    Vector3d nextPosition;
    Vector3d nextVelocity;
    std::string name; 
    
    //std::vector<std::shared_ptr<Physics::Force>> forces;

    public:
    Mass();
    Mass(double mass, const Vector3d& pos, const Vector3d& vel = {0,0,0});
    void setName(std::string n) { name = n;}
    void take_step();
    const Vector3d& getPosition() const;
    const Vector3d& getVelocity() const;

    const Vector3d& getNextVelocity() const {return nextVelocity;}
    const Vector3d& getNextPosition() const {return nextPosition;}

    //void addDeltaV(const Vector3d& dv) {delta_velocity += dv;}

    const Vector3d& setNextPosition(const Vector3d& next);
    const Vector3d& setNextVelocity(const Vector3d& next);

    double getMass() const {return mass;}

    virtual void draw(TDT4102::AnimationWindow*){}

    double getKineticEnergy() const;
    double getNextKineticEnergy() const;

    Vector3d getMomentum() const;
};