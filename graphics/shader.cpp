#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

shader::shader(const char* vertexPath, const char* fragmentPath)
{
    // Lecture des shaders depuis les fichiers
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // S'assurer que ifstream peut lancer des exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Ouvrir les fichiers
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Lire le contenu des fichiers
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // Fermer les fichiers
        vShaderFile.close();
        fShaderFile.close();
        // Convertir les stringstream en string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Erreur lors de la lecture des shaders" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compilation des shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Vérification des erreurs de compilation
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "Erreur lors de la compilation du vertex shader\n" << infoLog << std::endl;
    };

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Vérification des erreurs de compilation
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "Erreur lors de la compilation du fragment shader\n" << infoLog << std::endl;
    }

    // Création du programme shader
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    // Vérification des erreurs de liaison
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cerr << "Erreur lors de la liaison du shader program\n" << infoLog << std::endl;
    }

    // Suppression des shaders une fois le programme shader créé
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void shader::use() const
{
    glUseProgram(this->m_id);
}

void shader::set(std::string const& name, glm::mat4 const& mat) const
{
    GLuint varLoc = glGetUniformLocation(this->m_id, name.c_str());

    glUniformMatrix4fv(varLoc, 1, GL_FALSE, glm::value_ptr(mat));
}
