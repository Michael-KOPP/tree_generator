#pragma once
#include <functional>
#include "core/camera.h"

class GLFWwindow;

class window
{
    public:
    window();
    ~window();

    void show(std::function<void(camera *)> const& render);

    void bind(camera& camera);

    real get_time() const;
    real get_dt() const;

    private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    void process_input();
    void process_mouse();

    private:
    static bool m_init;

    private:
    GLFWwindow * m_window = nullptr;
    camera * m_camera = nullptr;
    real m_dt = 0;
    real m_time = 0;
    real m_lastx = 0;
    real m_lasty = 0;
};
