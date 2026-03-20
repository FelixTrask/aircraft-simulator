#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include "Aircraft.h"
#include "Wing.h"
#include "Flight_Condition.h"
#include "PerformanceResult.h"
#include "Simulator.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {

    // GLFW / ImGUI stuff

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 800, "Aircraft Simulator", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    io.IniFilename = nullptr;

    // aircraft stuff

    float aircraft_mass = 0;
    float wingspan = 0;
    float wing_area = 0;
    float available_thrust = 0;
    float CD0 = 0;
    float oswald_efficiency = 0;
    float flight_velocity = 0;

    PerformanceResult results{};
    Simulator simulator;
    Environment environment = Environment();

    const int GRAPH_POINTS = 100;

    float velocity_data[GRAPH_POINTS];
    float lift_data[GRAPH_POINTS];
    float drag_data[GRAPH_POINTS];

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        {
            ImGui::Begin("Aircraft Simulator");

            ImGui::Text("Aircraft Parameters");
            ImGui::Separator();

            ImGui::InputFloat("Mass (kg)", &aircraft_mass, 1.0f, 10.0f);
            ImGui::InputFloat("Wingspan (m)", &wingspan, 0.1f, 1.0f);
            ImGui::InputFloat("Wing Area (m^2)", &wing_area, 0.1f, 1.0f);
            ImGui::InputFloat("Thrust (N)", &available_thrust, 10.0f, 100.0f);

            ImGui::Spacing();

            ImGui::Text("Aerodynamics");
            ImGui::Separator();

            ImGui::InputFloat("CD0", &CD0, 0.001f, 0.01f);
            ImGui::InputFloat("Oswald Efficiency", &oswald_efficiency, 0.01f, 0.1f);

            ImGui::Spacing();

            ImGui::Text("Flight Condition");
            ImGui::Separator();

            ImGui::InputFloat("Velocity (m/s)", &flight_velocity, 1.0f, 10.0f);

            if (ImGui::Button("Run Simulation", ImVec2(200,40)))
            {
                Wing wing = Wing(wingspan, wing_area);
                Aircraft aircraft = Aircraft(aircraft_mass, available_thrust, wing, CD0, oswald_efficiency);

                for (int i = 0; i < GRAPH_POINTS; i++) {
                    float v = 1.0f + i * 2.0f; // velocities from 1 to 200 m/s

                    Flight_Condition fc(v);

                    PerformanceResult r = simulator.run_simulation(aircraft, environment, fc);

                    velocity_data[i] = v;
                    lift_data[i] = r.lift;
                    drag_data[i] = r.drag;
                }

                Flight_Condition flight_condition = Flight_Condition(flight_velocity);

                results = simulator.run_simulation(aircraft, environment, flight_condition);
            }

            ImGui::Separator();
            ImGui::Text("Simulation Results");

            ImGui::TextColored(ImVec4(0,1,0,1), "Lift: %.2f N", results.lift);
            ImGui::TextColored(ImVec4(1,0,0,1), "Drag: %.2f N", results.drag);

            ImGui::Text("Required CL: %.2f", results.required_CL);
            ImGui::Text("Aspect Ratio: %.2f", results.aspect_ratio);
            ImGui::Text("L/D Ratio: %.2f", results.lift_to_drag_ratio);
            ImGui::Text("TWR: %.2f", results.TWR);

            ImGui::Text("Level flight possible: %d (1 yes, 0 no)", results.level_flight_possible);

            ImGui::End();

            ImGui::Begin("Graphs");

            ImGui::Text("Performance Graphs");
            ImGui::Separator();
            
            ImGui::PlotLines(
                "Lift vs Velocity",
                lift_data,
                GRAPH_POINTS,
                0,
                nullptr,
                FLT_MAX,
                FLT_MAX,
                ImVec2(0,150)
            );

            ImGui::PlotLines(
                "Drag vs Velocity",
                drag_data,
                GRAPH_POINTS,
                0,
                nullptr,
                FLT_MAX,
                FLT_MAX,
                ImVec2(0,150)
            );

            ImGui::End();
        }

        // render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}