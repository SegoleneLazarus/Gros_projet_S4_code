#pragma once
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"

double fonction_rand();

int pile_ou_face(float p);

float random_float(float max);

glm::vec2 normalize_to_vit(glm::vec2 position, glm::vec2 vitesse);

struct Boid {
private:
    float separationRadius;
    float cohesionRadius;
    float alignementRadius;

public:
    glm::vec2 pos;
    glm::vec2 vit;
    Boid(float sepRad = 0.1, float cohRad = 0.1, float aliRad = 0.3)
        : pos(random_float(1), -1), vit(random_float(0.01), 0.01), separationRadius(sepRad), cohesionRadius(cohRad), alignementRadius(aliRad){};

    void limites()
    {
        if (abs(pos.x) >= 1)
            pos.x = -pos.x / abs(pos.x);
        if (abs(pos.y) >= 1)
            pos.y = -pos.y / abs(pos.y);
    }

    void alignement(const std::vector<Boid>& boids_tab, float alignementForce)
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
        vit = normalize_to_vit(vit + somme_vit * (1.f / nb_Bproches) * alignementForce * 10.f, vit);
    }

    void separation(const std::vector<Boid>& boids_tab, float separationForce)
    {
        float     distance_mini = 10;
        glm::vec2 this_minus_other_pos(0.0f, 0.0f);

        float distance = 0;

        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                distance = glm::distance(other.pos, pos);

                if (distance < distance_mini)
                {
                    this_minus_other_pos = pos - other.pos;
                    distance_mini        = distance;
                }
            }
        }
        if (distance_mini < separationRadius)
        {
            glm::vec2 modifier = normalize_to_vit(this_minus_other_pos, vit) * separationForce * (1.f / (distance_mini * 20));

            vit = normalize_to_vit(vit + modifier, vit);
        }
    }

    void cohesion(const std::vector<Boid>& boids_tab, float cohesionForce)
    {
        // version où tout les autres boids influencent la direction de notre boid de manière inversement proportionelle à la distance
        glm::vec2 somme_other_dif_pos(0.0f, 0.0f);
        for (const auto& other : boids_tab)
        {
            if (&other != this)
            {
                float distance = glm::distance(other.pos, pos);
                if (distance > this->cohesionRadius)
                {
                    somme_other_dif_pos += (pos - other.pos) * (1.f / (distance));
                }
            }
        }
        vit = normalize_to_vit(vit - normalize_to_vit(somme_other_dif_pos, vit) * cohesionForce * (1.f / 10), vit);
    }

    void deplacement_boids(const std::vector<Boid>& boids_tab,const float cohesion_force, const float separation_force,const float alignement_force)
    {
        this->cohesion(boids_tab, cohesion_force);
        this->separation(boids_tab, separation_force);
        this->alignement(boids_tab, alignement_force);
        pos = pos + vit;
        this->limites();
    }

    void draw_boid(p6::Context& ctx)
    {
        ctx.circle(
            p6::Center{pos},
            p6::Radius{0.02f}
        );
    }
};
