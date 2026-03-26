#include "simulation.h"

void Simulation::update_physics(){
    do
    {
        RungeKuttaGravityCalculation();
    }
    while(timestepControlShouldContinue());

    for(auto it = pointMasses.begin(); it < pointMasses.end(); it++){
        it->take_step();
    }

    time += timestep;

    totalKinetic = getTotalKineticEnergy();
    totalPotential = getTotalPotentialEnergy();
}

double Simulation::getTotalEnergy() const{
    return totalKinetic + totalPotential;
}

double Simulation::getTotalKineticEnergy() const{
    double calculationKineticTotal = 0;
    for(auto it = pointMasses.begin(); it < pointMasses.end(); it++){
        calculationKineticTotal += it->getKineticEnergy();
    }
    return calculationKineticTotal;
}

double Simulation::getTotalPotentialEnergy() const{
    double calculationPotentialTotal = 0;
    for(auto it_outer = pointMasses.begin(); it_outer < pointMasses.end(); it_outer++){
        for (auto it_inner = it_outer + 1; it_inner < pointMasses.end(); it_inner++){
            calculationPotentialTotal += Physics::potentialEnergy(it_outer->getMass(), it_inner->getMass()
            , it_outer->getPosition(), it_inner->getPosition());
        }
    }
    return calculationPotentialTotal;
}

double Simulation::getNextTotalEnergy(){
    return getNextTotalKineticEnergy() + getNextTotalPotentialEnergy();
}

double Simulation::getNextTotalKineticEnergy(){
    double calculationKineticTotal = 0;
    for(auto it = pointMasses.begin(); it < pointMasses.end(); it++){
        calculationKineticTotal += it->getNextKineticEnergy();
    }
    return calculationKineticTotal;
}

double Simulation::getNextTotalPotentialEnergy(){
    double calculationPotentialTotal = 0;
    for(auto it_outer = pointMasses.begin(); it_outer < pointMasses.end(); it_outer++){
        for (auto it_inner = it_outer + 1; it_inner < pointMasses.end(); it_inner++){
            calculationPotentialTotal += Physics::potentialEnergy(it_outer->getMass(), it_inner->getMass()
            , it_outer->getNextPosition(), it_inner->getNextPosition());
        }
    }
    return calculationPotentialTotal;
}

Vector3d Simulation::getTotalMomentum() const{
    Vector3d workingMomentum = {0,0,0};

    for(auto it = pointMasses.begin(); it < pointMasses.end(); it++){
        workingMomentum += it->getMomentum();
    }

    return workingMomentum;
}

