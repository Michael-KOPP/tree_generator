#include "tree_mesh.h"
#include <iostream>

tree_mesh::tree_mesh(class tree const& tree):
    m_tree(tree)
{

}

void tree_mesh::update()
{
    int i = 0;
    this->m_points.clear();
    this->m_indices.clear();

    this->m_tree.foreach_branch([&](branch const& b){
        this->m_points.push_back(b.get_position());
        this->m_points.push_back(b.get_position() + b.get_length() * b.get_orientation());

        this->m_indices.push_back(i);
        this->m_indices.push_back(i+1);
        i+=2;
    });

    // auto now = std::chrono::steady_clock::now();
    // std::chrono::duration elapsed_time = now - this->m_start;
    // if(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() > 100)
    // {
    //     this->m_start = now;
    //     this->m_tick++;
    // }

    // size_t const count = 10;
    // double const PI = 3.1415;
    // this->m_points.clear();

    // for(int i = 0; i < count; ++i)
    // {
    //     glm::vec3 circle_point = glm::vec3((float)cos((2.*PI*i + m_tick)/count), (float)sin((2.*PI*i+m_tick)/count), 0.0f);
    //     this->m_points.push_back(circle_point);
    //     this->m_points.push_back(0.5f*circle_point);
    // }

    // this->m_points.push_back(this->m_points[0]);
    // this->m_points.push_back(this->m_points[1]);
}

std::vector<glm::vec3> const& tree_mesh::points() const
{
    return this->m_points;
}


std::vector<unsigned int> const& tree_mesh::indices() const
{
    return this->m_indices;
}
