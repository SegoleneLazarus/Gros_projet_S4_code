#include "boids_deplacement.hpp"


Boids limites(Boids boidy);

void boids_deplacement(std::vector<Boids> &boids_tab, int nombre_boids)
{
    for (int i = 0; i < nombre_boids; i++)
    {
        boids_tab[i].pos += boids_tab[i].vit;
        boids_tab[i] = limites(boids_tab[i]);
    }
}

Boids limites(Boids boidy){
    if(abs(boidy.pos.x)>=1)
        boidy.pos.x = -boidy.pos.x/abs(boidy.pos.x);
    if(abs(boidy.pos.y)>=1)
        boidy.pos.y = -boidy.pos.y/abs(boidy.pos.y);
    return boidy;
}