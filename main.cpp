//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor


#include "AnimationWindow.h"
#include "./inc/simulation.h"

#define WIDTH 700
#define HEIGHT 700



int main() {

    Simulation sim(350, 50, WIDTH, HEIGHT, "simulation");
    
    PointMass& center = sim.addPointMass(1000, Vector3d(250, 250, 0));
    center.setName("center");
    PointMass& middle = sim.addPointMass(1, Vector3d(300, 250, 0), Vector3d(0, -5, 0));
    middle.setName("middle");   


    while(!sim.is_finished()){
        sim.update();
    }

    return 0;
}

