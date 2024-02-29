#include "window/window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

bool window::m_init = false;

window::window():
    m_camera(nullptr)
{
    if(!window::m_init)
    {
        if(!glfwInit())
            throw;
        window::m_init = true;
    }
    
    this->m_window = glfwCreateWindow(1920, 1080, "My Title", NULL, NULL);

    if(!this->m_window)
        throw;

    glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(this->m_window, &window::framebuffer_size_callback);


    double xpos, ypos;
    glfwGetCursorPos(this->m_window, &xpos, &ypos);
    this->m_lastx = xpos;
    this->m_lasty = ypos;

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw;
    }
}

window::~window()
{
    glfwDestroyWindow(this->m_window);
}

void window::show(std::function<void(camera *)> const& render)
{
    float lastFrame = glfwGetTime();
    while (!glfwWindowShouldClose(this->m_window))
    {
        this->process_mouse();
        this->process_input();

        // Calcul du temps écoulé
        float current_frame = glfwGetTime();
        this->m_time = current_frame;
        this->m_dt = current_frame - lastFrame;
        lastFrame = current_frame;

        render(this->m_camera);
    
        glfwSwapBuffers(this->m_window);
        glfwPollEvents();
    }
}

void window::bind(camera& camera)
{
    this->m_camera = &camera;
}

real window::get_time() const
{
    return this->m_time;
}

real window::get_dt() const
{
    return this->m_dt;
}

void window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void window::process_input()
{
    if(!this->m_camera)
        return;
    if (glfwGetKey(this->m_window, GLFW_KEY_W) == GLFW_PRESS)
        this->m_camera->process_keyboard(camera_movement::FORWARD, this->m_dt);
    if (glfwGetKey(this->m_window, GLFW_KEY_A) == GLFW_PRESS)
        this->m_camera->process_keyboard(camera_movement::LEFT, this->m_dt);
    if (glfwGetKey(this->m_window, GLFW_KEY_S) == GLFW_PRESS)
        this->m_camera->process_keyboard(camera_movement::BACKWARD, this->m_dt);
    if (glfwGetKey(this->m_window, GLFW_KEY_D) == GLFW_PRESS)
        this->m_camera->process_keyboard(camera_movement::RIGHT, this->m_dt);
}

void window::process_mouse()
{
    if(!this->m_camera)
        return;
    double xpos, ypos;
    glfwGetCursorPos(this->m_window, &xpos, &ypos);

    real xoffset = xpos - this->m_lastx;
    real yoffset = this->m_lasty - ypos;

    if(xoffset == 0 && yoffset == 0)
        return;

    this->m_lastx = xpos;
    this->m_lasty = ypos;

    this->m_camera->process_mouse_movement(xoffset, yoffset);
}
