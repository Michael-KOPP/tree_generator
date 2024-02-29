#pragma once
#include <glad/glad.h>
#include "graphics/renderer.h"
#include "tree_mesh.h"
#include "graphics/shader.h"

class tree_renderer : public renderer
{
public:
    tree_renderer(tree_mesh const& mesh);
    ~tree_renderer();

    void update();
    void draw(shader const& shader, glm::mat4 const& view);
private:
    tree_mesh const& m_mesh;

    GLuint m_ebo;
    GLuint m_vbo;
    GLuint m_vao;
};
