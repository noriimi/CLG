#pragma once
#include "imgui.h"
static void glfw_error_callback(int error, const char* description);
struct GLFWwindow;
class BaseApp
{
public:
    void Start();
    void End();
    void virtual Update();
    void virtual Init();
    void Run();
    ImGuiIO io;
    BaseApp();
    virtual ~BaseApp();
private:
    GLFWwindow* window;
};
