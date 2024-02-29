#include <iostream>
#include "window/window_factory.h"
#include "core/tree.h"
#include "graphics/tree_renderer.h"
#include "graphics/shader.h"

int main()
{
    tree t(glm::vec3(0.f,0.f,0.f));
    window_factory factory;
    std::unique_ptr<window> window = factory.make();

    shader s("C:\\Users\\micha\\Documents\\Dev\\3d\\src\\shader.vertex", "C:\\Users\\micha\\Documents\\Dev\\3d\\src\\shader.frag");

    tree_mesh mesh(t);
    tree_renderer renderer(mesh);

    camera cam(glm::vec3(0.f,0.f,1.0f));

    window->bind(cam);

    glm::mat4 projection = glm::perspective(45.0f, 16/9.0f, 0.1f, 100.0f);

    real last_time = window->get_time();

    window->show([&](camera * cam){
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(real new_time = window->get_time(); new_time - last_time > 3)
        {
            last_time = new_time;
            t.grow();
        }

        mesh.update();
        renderer.update();
        glm::mat4 view(1.0);
        if(cam)
            view = cam->get_view_matrix();
        view = projection * view;
        renderer.draw(s, view);

    });

    return 0;
}
