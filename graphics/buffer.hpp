#pragma once
#include <glad/glad.h>

template<typename T>
class buffer
{
    public:
    buffer(size_t size)
    {
        if(glIsBuffer(this->m_vbo))
            throw std::runtime_error("vbo already existing");

        glGenBuffers(1, &this->m_vbo);

        if(this->m_vbo <= 0)
            throw std::runtime_error("vbo failed to create");

        glBufferData(GL_VERTEX_ARRAY, sizeof(T) * size, nullptr, GL_DYNAMIC_DRAW);
    }

    ~buffer()
    {
        glDeleteBuffers(1, &this->m_vbo);
    }
    private:
    GLuint m_vbo;
};