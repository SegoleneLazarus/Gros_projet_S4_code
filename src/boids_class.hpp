#pragma once
#include "glm/glm.hpp"
#include <random>
#include <time.h>


double fonction_rand();

int pile_ou_face(float p);

float random_float(float max);

struct Boids 
{
    glm::vec2 pos;
    glm::vec2 vit;
    float separationRadius;

    Boids() : pos(0,0), vit(0,0), separationRadius(-0.001){};
    //Boids() : pos(random_float(1), -1), vit(random_float(0.01),0.01), separationRadius(0.001){};
    
    void separationBoid(const std::vector<Boids>& boids, float separationForce) {
        glm::vec2 separation(0.0f, 0.0f);
        int count = 0;

        for (const auto& other : boids) {
            if (&other != this) {
                float distance = glm::distance(other.pos, pos);
                if (distance < separationRadius) {
                    separation += (pos - other.pos);
                    count++;
                }
            }
        }

        if (count > 0) {
            separation /= static_cast<float>(count);
            glm::normalize(separation);
            vit += separation * separationForce;
        }
    }

    void initializer(Boids& boidy)
    {
        if(boidy.separationRadius<0)
        {
            glm::vec2 pos(random_float(1), -1);
            glm::vec2 vit(random_float(0.01),0.01);

            boidy.pos = pos;
            boidy.vit = vit;
            boidy.separationRadius = 0.001;
        }        
            
    }
};

float distanceVect(const glm::vec2& v1, const glm::vec2& v2);