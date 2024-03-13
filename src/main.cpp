#include <imgui.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <time.h>
#include <random>
#include "boid_class.hpp"
#include "boids_deplacement.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

void push_back_boids(std::vector<Boid>& boids_tab, int nombre_boids)
{
    Boid bdt{};
    for (int i = 0; i < nombre_boids; i++)
    {
        bdt.boid_initializer(0.1, 0.1, 0.3);
        boids_tab.push_back(bdt);
        bdt.separationRadius = -0.001;
    }
}

void actualise_boids_tab(std::vector<Boid>& boids_tab, int nombre_boids)
{
    if (nombre_boids > boids_tab.size())
    {
        push_back_boids(boids_tab, nombre_boids - boids_tab.size());
    }
    if (nombre_boids < flag_nb_boids)
    {
        // TODO
    }
}

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code

    // Show a simple window

    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    // initialize boids_tab
    std::vector<Boid> boids_tab;
    push_back_boids(boids_tab, 40);

    // Declare your infinite update loop.

    float alignement_force = 0.5;
    float separation_force = 0.5;
    float cohesion_force   = 0.5;

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Yellow);

        ImGui::Begin("Test");
        {
            int nombre_boids = boids_tab.size();
            ImGui::SliderInt("Nb de boids", &nombre_boids, 0, 100);
            actualise_boids_tab(nombre_boids);
        }
        ImGui::SliderFloat("Alignement", &alignement_force, 0.f, 1.f); // modif de la force
        ImGui::SliderFloat("Séparation", &separation_force, 0.f, 1.f); // modif de la force
        ImGui::SliderFloat("Cohésion", &cohesion_force, 0.f, 1.f);     // modif de la force
        ImGui::End();
        // Show the official ImGui demo window
        // It is very useful to discover all the widgets available in ImGui
        ImGui::ShowDemoWindow();

        // ctx.circle(
        //     p6::Center{ctx.mouse()},
        //     p6::Radius{0.1f}
        // );

        for (const auto& boidy : boids_tab)
        {
            ctx.circle(
                p6::Center{boidy.pos},
                p6::Radius{0.02f}
            );
            boidy.cohesion2(boids_tab, cohesion_force);
            boidy.separation(boids_tab, separation_force);
            boidy.alignement(boids_tab, alignement_force);
            boidy.pos += boidy.vit;
            boidy.limites();
        }

        // float xvit = boids_tab[0].vit.x;
        // float yvit = boids_tab[0].vit.y;
        // glm::vec2 vecTemp(-yvit,-xvit);
        // ctx.triangle(
        //     vecTemp+boids_tab[0].pos,
        //     boids_tab[0].pos+boids_tab[0].vit,
        //     -vecTemp+boids_tab[0].pos
        // );
    }

                 // Should be done last. It starts the infinite loop.
                 ctx.start();
}