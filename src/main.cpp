#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <time.h>
#include <random>
#include "boids_class.hpp"
#include "boids_deplacement.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

void separation()
{
    // deux boids ne peuvent pas être trop proches, ils doivent donc s'éloigner l'un de l'autre à partir d'une certaine distance
}

void alignement()
{
}

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();
    std::vector<Boids> boids_tab;
    int                nombre_boids = 20;
    Boids              bdt{};
    for (int i = 0; i < nombre_boids; i++)
    {
        bdt.boid_initializer();
        boids_tab.push_back(bdt);
        bdt.separationRadius = -0.001;
    }
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Yellow);

        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
        for (int i = 0; i < nombre_boids; i++)
        {
            ctx.circle(
                p6::Center{boids_tab[i].pos},
                p6::Radius{0.02f}
            );
            boids_tab[i].cohesion(boids_tab, 1);
        }

        // float xvit = boids_tab[0].vit.x;
        // float yvit = boids_tab[0].vit.y;
        // glm::vec2 vecTemp(-yvit,-xvit);
        // ctx.triangle(
        //     vecTemp+boids_tab[0].pos,
        //     boids_tab[0].pos+boids_tab[0].vit,
        //     -vecTemp+boids_tab[0].pos
        // );

        boids_deplacement(boids_tab, nombre_boids);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}