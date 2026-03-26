#include "../inc/simulation.h"

// STATIC MEMBERS
TDT4102::Button Simulation::pauseButton{{0, HEIGHT - 50}, 200, 50, "START"};
bool Simulation::paused = true;


Simulation::Simulation(){
    
    initOutput();
    initWindow();
    totalKinetic = getTotalKineticEnergy();
    totalPotential = getTotalPotentialEnergy();
}

Simulation::Simulation(size_t x, size_t y, size_t width, size_t height, std::string window_name) : 
TDT4102::AnimationWindow(x,y,width, height, window_name){
    initOutput();
    initWindow();
    totalKinetic = getTotalKineticEnergy();
    totalPotential = getTotalPotentialEnergy();
}


bool Simulation::is_finished(){
    return this->should_close();
}

void Simulation::initOutput(){
    energyOutputFile.open(energyOutputFilePath, std::ofstream::trunc);
    std::cout << "initialized output" << std::endl;
    energyOutputFile << std::setw(8) << "Time" << ";" << std::setw(15) << "Total Potential" << ";" << std::setw(15) 
    << "Total Kinetic" <<";" << std::setw(15) << "Total Energy" <<";" <<std::setw(20) << "Total Momentum" <<";\n";
}

void Simulation::initWindow(){
    pauseButton.setCallback(pauseFunction);
    this->add(pauseButton);
}

void Simulation::pauseFunction(){
    if(paused) pauseButton.setLabel("PAUSE");
    else pauseButton.setLabel("UNPAUSE");

    paused = !paused;

}

void Simulation::update(){
    if(!paused){
        update_physics();

        if(time > lastSampleTime + energySamplePeriod){
            lastSampleTime = time;
            writeEnergy();
        }
    }
    

    if(iterations%5000 == 0)
        update_window();


    iterations++;
}



void Simulation::update_window(){
    this->setBackgroundColor(TDT4102::Color(0x000000));
    for (auto it = pointMasses.begin(); it != pointMasses.end(); it++){
        it->draw(this);
    }

    
    std::string timeString = std::format("t = {}", std::round(time*100)/100.f);
    this->draw_text({0,0}, timeString, TDT4102::Color(0xffffff));

    this->next_frame();
}

void Simulation::writeEnergy() {
    std::stringstream momentumVector;
    momentumVector << getTotalMomentum();

    energyOutputFile << std::setw(8) << time << ";" << std::setw(15) << totalPotential << ";" << std::setw(15) << totalKinetic <<";" 
    << std::setw(15) << getTotalEnergy() <<";" <<std::setw(30) << momentumVector.str() <<";\n";
}

Simulation::~Simulation(){
    energyOutputFile.close();
}