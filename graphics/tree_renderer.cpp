#include "tree_renderer.h"
#include "glad/glad.h"
#include <iostream>

tree_renderer::tree_renderer(tree_mesh const& mesh):
    m_mesh(mesh)
{
    glGenBuffers(1, &this->m_vbo);

    if(this->m_vbo <= 0)
        throw std::runtime_error("failed to create OpenGL vertex buffer");

    glGenBuffers(1, &this->m_ebo);

    if(this->m_ebo <= 0)
        throw std::runtime_error("failed to create OpenGL index buffer");

    glGenVertexArrays(1, &this->m_vao);

    if(this->m_vao <= 0)
        throw std::runtime_error("failed to create OpenGL VAO");

    glBindVertexArray(this->m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

tree_renderer::~tree_renderer()
{
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteBuffers(1, &this->m_ebo);
    glDeleteVertexArrays(1, &this->m_vao);
}

void tree_renderer::update()
{
    size_t points_size = this->m_mesh.points().size() * sizeof(glm::vec3);

    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, points_size, (void*)0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, points_size, this->m_mesh.points().data());

    size_t indices_size = this->m_mesh.indices().size() * sizeof(unsigned int);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, (void*)0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices_size, this->m_mesh.indices().data());
}

void tree_renderer::draw(shader const& shader, glm::mat4 const& view)
{
    shader.use();

    shader.set("transform", view);

    glBindVertexArray(this->m_vao);
    glLineWidth(2.0f);
    glDrawElements(GL_LINES, this->m_mesh.points().size(), GL_UNSIGNED_INT, nullptr);

}
