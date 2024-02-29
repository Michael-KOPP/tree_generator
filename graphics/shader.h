#pragma once
#include <string>
#include <glm/glm.hpp>

class shader {
public:
    shader(const char* vertexPath, const char* fragmentPath);

    void use() const;

    void set(std::string const& name, glm::mat4 const& mat) const;

private:
    unsigned int m_id;
};
