#pragma once
#include <time.h>
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

    void separationBoid(const std::vector<Boids>& boids, float separationForce)
    {
        glm::vec2 separation(0.0f, 0.0f);
        int       count = 0;

        for (const auto& other : boids)
        {
            if (&other != this)
            {
                float distance = glm::distance(other.pos, pos);
                if (distance < separationRadius)
                {
                    separation += (pos - other.pos);
                    count++;
                }
            }
        }

        if (count > 0)
        {
            separation /= static_cast<float>(count);
            glm::normalize(separation);
            vit += separation * separationForce;
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
            this->vit = (this->vit + vit_boid_mini * glm::vec2(cohesionForce, cohesionForce)) / glm::vec2(2, 2);
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
            this->separationRadius = 0.002;
            this->cohesionRadius   = 0.005;
        }
    }
};

float distanceVect(const glm::vec2& v1, const glm::vec2& v2);