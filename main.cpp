//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor


#include "AnimationWindow.h"
#include "./inc/simulation.h"





int main() {

    Simulation sim(350, 50, WIDTH, HEIGHT, "simulation");

    
    
    
    PointMass& center = sim.addPointMass(12, Vector3d(250, 250, 0));
    center.setName("center");

    PointMass& middle = sim.addPointMass(8, Vector3d(300, 250, 0), Vector3d(0, 0.1, 0));
    middle.setName("middle");

    PointMass& outer = sim.addPointMass(100, Vector3d(270, 325, 0), Vector3d(0, -1, 0));
    outer.setName("outer");


    while(!sim.is_finished()){
        sim.update();
    }

    return 0;
}

