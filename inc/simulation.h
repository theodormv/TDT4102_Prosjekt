#pragma once
#include "AnimationWindow.h"
#include "widgets/button.h"
#include "pointmass.h"
#include "math.h"
#include <fstream>


#define WIDTH 700
#define HEIGHT 700



class Simulation: public TDT4102::AnimationWindow{  
    std::vector<PointMass> pointMasses;

    double timestep = 5e-4;
    double time = 0; 
    double energySamplePeriod = 10;
    double lastSampleTime = -__DBL_MAX__;

    void update_physics();
    void update_window();

    unsigned long int iterations = 0;

    std::string energyOutputFilePath = "./output/default.txt";
    std::ofstream energyOutputFile = NULL;

    double totalKinetic = 0;
    double totalPotential = 0;


    double tol = 5e-4;
    void RungeKuttaGravityCalculation2Bodies();
    void RungeKutta4OrderStep2Bodies(PointMass * m1, PointMass * m2); // støtter bare interaksjoner mellom 2 masser
    void RungeKuttaGravityCalculation();
    void RungeKutta4OrderStep(PointMass * mass); //generell funkjon for større systemer
    bool timestepControlShouldContinue();


    double getTotalEnergy() const;
    double getTotalPotentialEnergy() const;
    double getTotalKineticEnergy() const;
    void writeEnergy();

    Vector3d getTotalMomentum() const;

    double getNextTotalKineticEnergy();
    double getNextTotalPotentialEnergy();
    double getNextTotalEnergy();


    static TDT4102::Button pauseButton;
    static void pauseFunction();
    static bool paused;

    public:

    Simulation();
    Simulation(size_t x, size_t y, size_t width, size_t height, std::string window_name);

    ~Simulation();



    //void loadInitialValues(std::string filepath);

    void initOutput();
    void initWindow();


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