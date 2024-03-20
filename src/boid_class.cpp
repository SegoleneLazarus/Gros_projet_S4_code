#include "boid_class.hpp"

struct Boid boids;

double fonction_rand()
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib =
        std::uniform_real_distribution<double>{0.0, 1.0};

    return distrib(gen);
};

int pile_ou_face(float p)
{
    double random = fonction_rand();
    return random > p ? 0 : 1;
};

float random_float(float max)
{
    float random_float_max1_minm1;

    random_float_max1_minm1 = fonction_rand() * max;
    if (pile_ou_face(0.5) == 0)
        return -random_float_max1_minm1;
    return random_float_max1_minm1;
};

glm::vec2 normalize_to_vit(glm::vec2 position, glm::vec2 vitesse)
{
    // this fonction allows to normalize a position to the length of a speed (vit as vitesse), it is usefull if I want to use a difference of position between 2 boids to change the speed of one of them (cohesion, separation)
    float length_vit = glm::length(vitesse);
    position         = normalize(position) * length_vit;
    return position;
}