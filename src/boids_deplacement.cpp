#include "boids_deplacement.hpp"



void boids_deplacement(std::vector<Boids> &boids_tab, int nombre_boids)
{
    for (int i = 0; i < nombre_boids; i++)
    {
        boids_tab[i].pos += boids_tab[i].vit;
    }
}