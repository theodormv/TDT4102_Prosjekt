//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor


#include "AnimationWindow.h"
#include "./inc/simulation.h"





int main() {


    Simulation sim(50, 50, WIDTH, HEIGHT, "simulation");

    
    sim.loadFromFile("./input/stable_three_body_problem.txt");

    while(!sim.is_finished()){
        sim.update();
    }

    return 0;
}

