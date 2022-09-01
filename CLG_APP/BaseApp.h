#pragma once
#include "imgui.h"
static void glfw_error_callback(int error, const char* description);
struct GLFWwindow;
class base_app
{
public:
	static void start();
	static void end();
    void virtual update();
    void virtual init();
    void run();
    ImGuiIO io;
    base_app();
    virtual ~base_app();
private:
    GLFWwindow* window_{};
};
