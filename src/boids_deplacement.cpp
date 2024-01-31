#include "boids_deplacement.hpp"
#include <cmath>
#include <iostream>
#include <vector>


void boids_deplacement(std::vector<Boids> boids_tab, int nombre_boids)
{
    for (int i = 0; i < nombre_boids; i++)
    {
        Boids bdt = boids_tab[i];
        bdt.xpos += bdt.vitesse * cos(bdt.angle);
        bdt.ypos += bdt.vitesse * sin(bdt.angle);
        c
        }
}