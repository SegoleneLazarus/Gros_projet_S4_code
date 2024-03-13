#pragma once
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/fwd.hpp"
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
    float     alignementRadius;

    Boids()
        : pos(0, 0), vit(0, 0), separationRadius(-0.001), cohesionRadius(0.1), alignementRadius(0.1){};
    // Boids() : pos(random_float(1), -1), vit(random_float(0.01),0.01), separationRadius(0.001){};

    void alignement(const std::vector<Boids>& boids_tab, float alignementForce)
    {
        glm::vec2 somme_vit(0.0f, 0.0f);
        float     nb_Bproches = 0;

        for (const auto& other : boids_tab)
        {
            if (distance(other.pos, pos) < alignementRadius)
            {
                somme_vit += normalize_to_vit(other.vit, vit);
                nb_Bproches++;
            }
        }
        vit = normalize_to_vit(vit + somme_vit * (1 / nb_Bproches), vit);
    }

    void separation(const std::vector<Boids>& boids_tab, float separationForce)
    {
        float     distance_mini = 10;
        glm::vec2 this_minus_other_pos(0.0f, 0.0f);

        // int       count = 0;
        float distance = 0;

        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                distance = glm::distance(other.pos, pos);

                if (distance < distance_mini)
                {
                    // std::cout << distance_min << std::endl;
                    this_minus_other_pos = pos - other.pos;
                    distance_mini        = distance;
                    // separation += (pos - other.pos);
                    // count++;
                }
            }
        }
        // separation = glm::normalize(separation);

        // vit += separation * separationForce;

        // if (count > 0)
        // separation /= static_cast<float>(count);
        // glm::normalize(separation);
        if (distance_mini < separationRadius) // separationRadius
        {
            // std::cout << int(1 / distance_min) << std::endl;
            //  vit = (vit + 1/separation_min * glm::vec2(separationForce + int(1 / distance_min), separationForce + (1 / distance_min))) / glm::vec2(separationForce + int(1 / distance_min) + 1, separationForce + 1 / distance_min + 1);
            //  vit = (vit + glm::vec2(1 / separation_min.x, 1 / separation_min.y) * glm::vec2(separationForce, separationForce)) / glm::vec2(separationForce + 1, separationForce + 1);
            glm::vec2 modifier = normalize_to_vit(this_minus_other_pos, vit) * separationForce * (1 / (distance_mini * distance_mini));
            std::cout << modifier.x << "/n" << modifier.y << std::endl;
            vit = normalize_to_vit(vit + modifier, vit);
        }
    }

    void cohesion2(std::vector<Boids>& boids_tab, float cohesionForce)
    {
        // version où tout les autres boids influencent la direction de notre boid de manière inversement proportionelle à la distance
        // glm::vec2 this_minus_other_pos(0.0f, 0.0f);
        glm::vec2 somme_other_dif_pos(0.0f, 0.0f);
        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                float distance = glm::distance(other.pos, pos);
                if (distance > this->cohesionRadius)
                {
                    somme_other_dif_pos += (pos - other.pos) * (1 / (distance * distance * distance));
                }
            }
        }
        vit = normalize_to_vit(vit - normalize_to_vit(somme_other_dif_pos, vit) * cohesionForce, vit);
    }

    void boid_initializer(float sepRad, float cohRad, float aliRad)
    {
        if (this->separationRadius < 0)
        {
            glm::vec2 pos(random_float(1), -1);
            glm::vec2 vit(random_float(0.01), 0.01);

            this->pos              = pos;
            this->vit              = vit;
            this->separationRadius = sepRad;
            this->cohesionRadius   = cohRad;
            this->cohesionRadius   = cohRad;
        }
    }
};
