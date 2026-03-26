#include "../inc/simulation.h"
Simulation::Simulation(){
    
    initOutput();
    totalKinetic = getTotalKineticEnergy();
    totalPotential = getTotalPotentialEnergy();
}

Simulation::Simulation(size_t x, size_t y, size_t width, size_t height, std::string window_name) : 
TDT4102::AnimationWindow(x,y,width, height, window_name){
    initOutput();
    totalKinetic = getTotalKineticEnergy();
    totalPotential = getTotalPotentialEnergy();
}


bool Simulation::is_finished(){
    return this->should_close();
}

void Simulation::initOutput(){
    energyOutputFile.open(energyOutputFilePath, std::ofstream::trunc);
    std::cout << "initialized output" << std::endl;
}

void Simulation::update(){
    
    update_physics();

    if(time > lastSampleTime + energySamplePeriod){
        lastSampleTime = time;
        writeEnergy();
    }

    if(iterations%10000 == 0)
        update_window();


    iterations++;
}


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

void Simulation::update_window(){
    this->setBackgroundColor(TDT4102::Color(0xffffff));
    for (auto it = pointMasses.begin(); it != pointMasses.end(); it++){
        it->draw(this);
    }
    this->next_frame();
}

/*
void Simulation::GravityBetween( PointMass* m1, PointMass* m2) const{
    Vector3d F = Physics::calcGravity(m1->getMass(),  m2->getMass(), m1->getPosition(), m2->getPosition());
    if (F.squareNorm() == 0) std::cout << m1 << ", " << m2 <<": NULL FORCE" <<std::endl;
    m1->addDeltaV(F/m1->getMass());
    m2->addDeltaV(-F/m2->getMass());
}
*/

void Simulation::RungeKuttaGravityCalculation(){
    for(auto mass1 = pointMasses.begin(); mass1 < pointMasses.end(); mass1++){
        for(auto mass2 = pointMasses.begin(); mass2 < pointMasses.end(); mass2++){
            if(mass1 == mass2) continue;
            RungeKutta4OrderStep(&*mass1, &*mass2);
        }
    }
}

void Simulation::RungeKutta4OrderStep(PointMass* m1, PointMass* m2){

    m1->setNextPosition( m1->getPosition() + m1->getVelocity()*timestep );

    Vector3d k1 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition(), m2->getPosition());
    Vector3d k2 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition() + k1*0.5*timestep, m2->getPosition());
    Vector3d k3 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition() + k2*0.5*timestep, m2->getPosition());
    Vector3d k4 = Physics::calcGravity(m1->getMass(), m2->getMass(), m1->getPosition() + k3*timestep, m2->getPosition());

    m1->setNextVelocity(m1->getVelocity() + (k1 + k2*2 + k3*2 + k4)*timestep/(6 * m1->getMass()));
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



double Simulation::getTotalEnergy(){
    return totalKinetic + totalPotential;
}

double Simulation::getTotalKineticEnergy(){
    double calculationKineticTotal = 0;
    for(auto it = pointMasses.begin(); it < pointMasses.end(); it++){
        calculationKineticTotal += it->getKineticEnergy();
    }
    return calculationKineticTotal;
}

double Simulation::getTotalPotentialEnergy(){
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



void Simulation::writeEnergy(){
    energyOutputFile << std::setw(8) << time << ";" << std::setw(15) << totalPotential << ";" << std::setw(15) << totalKinetic <<";" << std::setw(15) << getTotalEnergy() <<";\n";
}

Simulation::~Simulation(){
    energyOutputFile.close();
}