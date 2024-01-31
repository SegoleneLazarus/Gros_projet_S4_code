#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include "boids_class.hpp"
#include "boids_deplacement.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();
    std::vector<Boids> boids_tab;
    Boids              bdt;
    bdt.xpos     = 0;
    bdt.ypos     = 0;
    bdt.vitesse  = 0.01;
    bdt.angle    = 0;
    boids_tab[0].push_back(bdt);
    boids_deplacement(boids_tab, 1);
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Yellow);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
        ctx.circle(
            p6::Center{boids_tab[0].xpos, boids_tab[0].ypos},
            p6::Radius{0.05f}
        );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}