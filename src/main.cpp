#include <imgui.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <time.h>
#include <random>
#include "boid_class.hpp"
#include "doctest/doctest.h"

void pushb_boids(std::vector<Boid>& boids_tab, int nombre_boids)
{
    for (int i = 0; i < nombre_boids; i++)
    {
        Boid bdt{};
        boids_tab.push_back(bdt);
    }
}

void actualise_boids_tab(std::vector<Boid>& boids_tab, int nombre_boids)
{
    if (nombre_boids > boids_tab.size())
    {
        pushb_boids(boids_tab, nombre_boids - boids_tab.size());
    }
    else if (nombre_boids < boids_tab.size())
    {
        boids_tab.resize(nombre_boids);
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
    pushb_boids(boids_tab, 40);

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
            actualise_boids_tab(boids_tab, nombre_boids);
        }
        ImGui::SliderFloat("Alignement", &alignement_force, 0.f, 1.f); // modif de la force
        ImGui::SliderFloat("Séparation", &separation_force, 0.f, 1.f); // modif de la force
        ImGui::SliderFloat("Cohésion", &cohesion_force, 0.f, 1.f);     // modif de la force
        ImGui::End();

        for (auto& boidy : boids_tab)
        {
            boidy.draw_boid(ctx);
            boidy.deplacement_boids(boids_tab, cohesion_force, separation_force, alignement_force);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}