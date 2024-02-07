#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include "boids_class.hpp"
#include "boids_deplacement.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"
#include <random>
#include <time.h>

void separation(){
    // deux boids ne peuvent pas être trop proches, ils doivent donc s'éloigner l'un de l'autre à partir d'une certaine distance

}

void cohesion(){
    
}

void alignement(){
    
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
    Boids              bdt();
    boids_tab.push_back(bdt);
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Yellow);

        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
        ctx.circle(
            p6::Center{boids_tab[0].pos},
            p6::Radius{0.02f}
        );

        // float xvit = boids_tab[0].vit.x;
        // float yvit = boids_tab[0].vit.y;
        // glm::vec2 vecTemp(-yvit,-xvit);
        // ctx.triangle(
        //     vecTemp+boids_tab[0].pos,
        //     boids_tab[0].pos+boids_tab[0].vit,
        //     -vecTemp+boids_tab[0].pos
        // );

        boids_deplacement(boids_tab, 1);

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}