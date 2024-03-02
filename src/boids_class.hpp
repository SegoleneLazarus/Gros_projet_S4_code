#pragma once
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/glm.hpp"

double fonction_rand();

int pile_ou_face(float p);

float random_float(float max);

float distanceVect(const glm::vec2& v1, const glm::vec2& v2);

glm::vec2 normalize_to_vit(glm::vec2 pos, glm::vec2 vit);

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
        glm::vec2 this_minus_other_pos(0.0f, 0.0f);

        // int       count = 0;
        float distance=0;
        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                distance = glm::distance(other.pos, pos);
                if (distance < distance_min)
                {
                    this_minus_other_pos = pos - other.pos;
                    // count++;
                }
            }
        }

        // if (count > 0)
        // separation /= static_cast<float>(count);
        // glm::normalize(separation);
        if (distance_min < separationRadius)
        {
            //std::cout << int(1 / distance_min) << std::endl;
            // vit = (vit + 1/separation_min * glm::vec2(separationForce + int(1 / distance_min), separationForce + (1 / distance_min))) / glm::vec2(separationForce + int(1 / distance_min) + 1, separationForce + 1 / distance_min + 1);
            // vit = (vit + glm::vec2(1 / separation_min.x, 1 / separation_min.y) * glm::vec2(separationForce, separationForce)) / glm::vec2(separationForce + 1, separationForce + 1);
            vit = normalize_to_vit(vit + normalize_to_vit(this_minus_other_pos, vit) * separationForce * (1 /(distance*distance)), vit);
        }
    }

    void cohesion(std::vector<Boids>& boids_tab, float cohesionForce)
    {
        float distance_min = 10;
        // glm::vec2 vit_boid_mini(0.0f, 0.0f);
        glm::vec2 this_minus_other_pos(0.0f, 0.0f);

        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                float distance = glm::distance(other.pos, pos);
                if (distance < distance_min)
                {
                    // vit_boid_mini = other.vit;
                    distance_min         = distance;
                    this_minus_other_pos = pos - other.pos;
                }
            }
        }
        if (distance_min > this->cohesionRadius)
        {
            // le boid se rapproche du boid le plus proche, ça veut dire qu'on fait la moyenne des deux boids
            // this->vit = (this->vit + vit_boid_mini * glm::vec2(cohesionForce, cohesionForce)) / glm::vec2(cohesionForce + 1, cohesionForce + 1);
            // j'additionne la différence de position(son opposé parce que sinon ça l'éloigne) et la vitesse du boid afin que le boid se rapproche et je normalize
            vit = normalize_to_vit(vit - normalize_to_vit(this_minus_other_pos, vit) * glm::vec2(cohesionForce, cohesionForce), vit);
        }
    }

    void cohesion2(std::vector<Boids>& boids_tab, float cohesionForce)
    {
        // version où tout les autres boids influencent la direction de notre boid de manière inversement proportionelle à la distance
        glm::vec2 this_minus_other_pos(0.0f, 0.0f);

        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                float distance       = glm::distance(other.pos, pos);
                this_minus_other_pos = pos - other.pos;
                // j'additionne la différence de position(son opposé parce que sinon ça l'éloigne) et la vitesse du boid afin que le boid se rapproche et je normalize
                // vit = normalize_to_vit(vit - normalize_to_vit(this_minus_other_pos, vit) * glm::vec2(cohesionForce * (1 / distance) * (1 / distance), cohesionForce * (1 / distance) * (1 / distance)), vit);
                vit = normalize_to_vit(vit - normalize_to_vit(this_minus_other_pos, vit) * cohesionForce * (1 / distance), vit);
            }
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
