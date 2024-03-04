#include "tree_mesh.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

tree_mesh::tree_mesh(class tree const& tree):
    m_tree(tree)
{

}

void tree_mesh::update()
{
    int i = 0;
    this->m_points.clear();
    this->m_indices.clear();
    
    int index = 0;

    this->m_tree.foreach_branch([&](branch const& b){
        int N = 10;
        int M = 10;

        float h =  + 1.0f/(N+1);

        auto get_cicle_point = [&](int j){
            float theta = atan2(b.get_orientation().x, b.get_orientation().z);

            glm::vec3 horizontal_branch_axis = glm::vec3(-sin(theta), 0.0f, cos(theta));

            glm::vec3 vertical_branch_axis = glm::cross(b.get_orientation(), horizontal_branch_axis);

            horizontal_branch_axis = glm::normalize(horizontal_branch_axis);
            vertical_branch_axis = glm::normalize(vertical_branch_axis);

            glm::vec3 x = (float)cos(2 * j * M_PI / M) * horizontal_branch_axis + (float)sin(2 * j * M_PI / M) * vertical_branch_axis;  
            return 0.01f * b.get_length() * x;
        };

        for(int i = 0; i < N; ++i)
        {
            glm::vec3 y = b.get_position() + i * h * b.get_length() * b.get_orientation();
            glm::vec3 next_y = b.get_position() + (i+1) * h * b.get_length() * b.get_orientation();
            for(int j = 0; j < M; ++j)
            {
                auto x = get_cicle_point(j);
                auto next_x = get_cicle_point(j+1);

                this->m_points.push_back(y+x);
                this->m_points.push_back(y+next_x);
                
                this->m_points.push_back(next_y+x);
                this->m_points.push_back(next_y+next_x);

                this->m_indices.push_back(index);
                this->m_indices.push_back(index+1);
                this->m_indices.push_back(index+2);

                this->m_indices.push_back(index+1);
                this->m_indices.push_back(index+2);
                this->m_indices.push_back(index+3);

                index += 4;
            }            
        }
    });
}

std::vector<glm::vec3> const& tree_mesh::points() const
{
    return this->m_points;
}


std::vector<unsigned int> const& tree_mesh::indices() const
{
    return this->m_indices;
}
