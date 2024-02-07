#pragma once
#include "glm/glm.hpp"
#include <random>
#include <time.h>


double fonction_rand() {
        thread_local std::default_random_engine gen{std::random_device{}()};
        thread_local auto distrib =
            std::uniform_real_distribution<double>{0.0, 1.0};

        return distrib(gen);
};

int pile_ou_face(float p) {
        double random = fonction_rand();
        return random > p ? 0 : 1;
};

float random_float(float max) {
    float random_float_max1_minm1;
    
    random_float_max1_minm1= fonction_rand()*max;
    if (pile_ou_face(0.5) == 0)
        return -random_float_max1_minm1;
    return random_float_max1_minm1;
};

struct Boids 
{
    glm::vec2 pos;
    glm::vec2 vit;

    Boids() : pos(random_float(1), -1), vit(random_float(0.01),0.01){}
    
};