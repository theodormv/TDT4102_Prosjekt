#include "simulation.h"

void Simulation::RungeKuttaGravityCalculation2Bodies(){
    for(auto mass1 = pointMasses.begin(); mass1 < pointMasses.end(); mass1++){
        for(auto mass2 = pointMasses.begin(); mass2 < pointMasses.end(); mass2++){
            if(mass1 == mass2) continue;
            RungeKutta4OrderStep2Bodies(&*mass1, &*mass2);
        }
    }
}

void Simulation::RungeKutta4OrderStep2Bodies(PointMass* m1, PointMass* m2){

    m1->setNextPosition( m1->getPosition() + m1->getVelocity()*timestep );

    Vector3d k1 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition(), m2->getPosition());
    Vector3d k2 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition() + k1*0.5*timestep, m2->getPosition());
    Vector3d k3 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition() + k2*0.5*timestep, m2->getPosition());
    Vector3d k4 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition() + k3*timestep, m2->getPosition());

    m1->setNextVelocity(m1->getVelocity() + (k1 + k2*2 + k3*2 + k4)*timestep/(6 * m1->getMass()));
}

void Simulation::RungeKuttaGravityCalculation(){
    for(auto mass1 = pointMasses.begin(); mass1 < pointMasses.end(); mass1++){
        RungeKutta4OrderStep(&*mass1);
    }

}

void Simulation::RungeKutta4OrderStep(PointMass* mass){

    mass->setNextPosition( mass->getPosition() + mass->getVelocity()*timestep );

    Vector3d k1 = {0,0,0};
    Vector3d k2 = {0,0,0};
    Vector3d k3 = {0,0,0};
    Vector3d k4 = {0,0,0};

    Vector3d workingVelocity = mass->getVelocity();

    for(auto mass2 = pointMasses.begin(); mass2 < pointMasses.end(); mass2++){
        if(mass == &*mass2) continue;
        k1 = Physics::calcGravity(mass->getMass(), mass2->getMass(), mass->getPosition(), mass2->getPosition());
        k2 = Physics::calcGravity(mass->getMass(), mass2->getMass(), mass->getPosition() + k1*0.5*timestep, mass2->getPosition());
        k3 = Physics::calcGravity(mass->getMass(), mass2->getMass(), mass->getPosition() + k2*0.5*timestep, mass2->getPosition());
        k4 = Physics::calcGravity(mass->getMass(), mass2->getMass(), mass->getPosition() + k3*timestep, mass2->getPosition());
        workingVelocity += (k1 + k2*2 + k3*2 + k4)*timestep/(6 * mass->getMass());
    }

    mass->setNextVelocity(workingVelocity);
}



bool Simulation::timestepControlShouldContinue(){
    double localError = abs(getTotalEnergy() - getNextTotalEnergy());
    
    if (localError > tol){

        double multiplier =  std::pow(tol/localError, 0.2);
        //std::cout << multiplier << std::endl;
        timestep = multiplier * timestep;
        return true;
    }
    return false;
}  



