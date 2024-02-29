#include "window_factory.h"
#include <GLFW/glfw3.h>

window_factory::window_factory()
{
    glfwInit();
}

window_factory::~window_factory()
{
    glfwTerminate();
}

std::unique_ptr<window> window_factory::make() const
{
    return std::make_unique<window>();
}
