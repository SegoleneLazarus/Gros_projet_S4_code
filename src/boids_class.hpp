#pragma once
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/glm.hpp"

double fonction_rand();

int pile_ou_face(float p);

float random_float(float max);

struct Boids {
    glm::vec2 pos;
    glm::vec2 vit;
    float     separationRadius;
    float     cohesionRadius;

    Boids()
        : pos(0, 0), vit(0, 0), separationRadius(-0.001), cohesionRadius(0.1){};
    // Boids() : pos(random_float(1), -1), vit(random_float(0.01),0.01), separationRadius(0.001){};

    void separation(const std::vector<Boids>& boids_tab, float separationForce)
    {
        float     distance_min = 10;
        glm::vec2 separation_min(0.0f, 0.0f);
        // int       count = 0;

        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                float distance = glm::distance(other.pos, pos);
                if (distance < distance_min)
                {
                    separation_min = (pos - other.pos);
                    // count++;
                }
            }
        }

        // if (count > 0)
        // separation /= static_cast<float>(count);
        // glm::normalize(separation);
        if (distance_min < separationRadius)
        {
            std::cout << int(1 / distance_min) << std::endl;
            // vit = (vit + 1/separation_min * glm::vec2(separationForce + int(1 / distance_min), separationForce + (1 / distance_min))) / glm::vec2(separationForce + int(1 / distance_min) + 1, separationForce + 1 / distance_min + 1);
            vit = (vit + glm::vec2(1 / separation_min.x, 1 / separation_min.y) * glm::vec2(separationForce, separationForce)) / glm::vec2(separationForce + 1, separationForce + 1);
        }
    }

    void cohesion(std::vector<Boids>& boids_tab, float cohesionForce)
    {
        float     distance_min = 10;
        glm::vec2 vit_boid_mini(0.0f, 0.0f);

        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                float distance = glm::distance(other.pos, pos);
                if (distance < distance_min)
                {
                    vit_boid_mini = other.vit;
                    distance_min  = distance;
                }
            }
        }
        if (distance_min > this->cohesionRadius)
        {
            // le boid se rapproche du boid le plus proche, ça veut dire qu'on fait la moyenne des deux boids
            this->vit = (this->vit + vit_boid_mini * glm::vec2(cohesionForce, cohesionForce)) / glm::vec2(cohesionForce + 1, cohesionForce + 1);
        }
    }

    void boid_initializer()
    {
        if (this->separationRadius < 0)
        {
            glm::vec2 pos(random_float(1), -1);
            glm::vec2 vit(random_float(0.01), 0.01);

            this->pos              = pos;
            this->vit              = vit;
            this->separationRadius = 0.1;
            this->cohesionRadius   = 0.001;
        }
    }
};

float distanceVect(const glm::vec2& v1, const glm::vec2& v2);