#pragma once
#include "AnimationWindow.h"
#include "pointmass.h"
#include "math.h"
#include <fstream>



class Simulation: public TDT4102::AnimationWindow{  
    std::vector<PointMass> pointMasses;

    double timestep = 5e-4;
    double time = 0; 
    double energySamplePeriod = 100;
    double lastSampleTime = 0;

    void update_physics();
    void update_window();

    unsigned long int iterations = 0;

    std::string energyOutputFilePath = "./output/default.txt";
    std::ofstream energyOutputFile = NULL;

    double totalKinetic = 0;
    double totalPotential = 0;


    double tol = 1e-5;
    void RungeKuttaGravityCalculation();
    void RungeKutta4OrderStep(PointMass * m1, PointMass * m2);
    bool timestepControlShouldContinue();


    double getTotalEnergy();
    double getTotalPotentialEnergy();
    double getTotalKineticEnergy();
    void writeEnergy();

    double getNextTotalKineticEnergy();
    double getNextTotalPotentialEnergy();
    double getNextTotalEnergy();

    //void RungeKutta4OrderStep();
    public:

    Simulation();
    Simulation(size_t x, size_t y, size_t width, size_t height, std::string window_name);

    ~Simulation();

    //void loadInitialValues(std::string filepath);

    void initOutput();

    template<typename ... Margs> 
    //varadic template gjør at jeg kan legge til pointmasses med alle konstruktørene uten å måtte overloade
    PointMass& addPointMass(Margs&& ... args){
        pointMasses.emplace_back(args...);
        totalKinetic = getTotalKineticEnergy();
        totalPotential = getTotalPotentialEnergy();
        return pointMasses[pointMasses.size() - 1];
    }

    bool is_finished();
    void update();

    
};