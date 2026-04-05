#include "../inc/mass.h"


Mass::Mass(){
    this->position = Vector3d(0,0,0);
    this->velocity = Vector3d(0,0,0);
    this->nextPosition = this->position;
    this->nextVelocity = this->velocity;
    this->mass = 0;
}

Mass::Mass(double m, const Vector3d& pos, const Vector3d& vel) :
 mass(m), position(pos), velocity(vel), nextPosition(pos), nextVelocity(vel){}

Mass::Mass(const std::string& descriptionString){
    position = {0,0,0};
    velocity = {0,0,0};

    std::stringstream descriptionStream;
    descriptionStream << descriptionString;
    
    if(descriptionString.empty()) throw BadMassDescription("empty line in mass description");

    descriptionStream >> name >> mass >> position[0] >> position[1] >> velocity[0] >> velocity[1];

    nextPosition = position;
    nextVelocity = velocity;
}



void Mass::take_step(){
    this->position = this->nextPosition;
    this->velocity = this->nextVelocity;
   // std::cout << this << " ";
}


double Mass::getKineticEnergy() const {
    return Physics::kineticEnergy(mass, velocity);
}

double Mass::getNextKineticEnergy() const {
    return Physics::kineticEnergy(mass, nextVelocity);
}

const Vector3d& Mass::setNextPosition(const Vector3d& next) {nextPosition = next; return nextPosition;}
const Vector3d& Mass::setNextVelocity(const Vector3d& next) {nextVelocity = next; return nextVelocity;}

Vector3d Mass::getMomentum() const {
    return velocity*mass;
}