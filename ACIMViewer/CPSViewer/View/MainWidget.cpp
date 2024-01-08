#include <string>

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

void CPSTabControl(float x, float y, float w, float h);

void MainWidget(const std::string &fileName) {
    // 初始化GLFW
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(540, 760, fileName.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // 初始化Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    // 初始化ImGui与OpenGL的集成
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // 设置ImGui样式
    ImGui::StyleColorsDark();

    io.Fonts->AddFontFromFileTTF("MiSans.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        CPSTabControl(0, 0, static_cast<float>(display_w), static_cast<float>(display_h));

        // 渲染ImGui
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 清理ImGui资源
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // 清理GLFW资源
    glfwDestroyWindow(window);
    glfwTerminate();
}