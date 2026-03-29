#include "AnimationWindow.h"
#include "./inc/simulation.h"

int main() {


    Simulation sim(50, 50, WIDTH, HEIGHT, "simulation");
    sim.loadFromFile("./input/three_body_problem.txt");


    while(!sim.is_finished()){
        sim.update();
    }

    return 0;
}

