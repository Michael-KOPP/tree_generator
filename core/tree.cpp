#include "tree.h"
#include <ranges>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <iostream>

branch::branch(glm::vec3 position, glm::vec3 orientation, real length, branch * parent):
    m_parent(parent),
    m_position(position),
    m_orientation(orientation),
    m_length(length)
{

}

glm::vec3 branch::get_position() const
{
    return this->m_position;
}

glm::vec3 branch::get_orientation() const
{
    return this->m_orientation;
}

bool branch::has_parent() const
{
    return this->m_parent != nullptr;
}

real branch::get_length() const
{
    return this->m_length;
}

branch& branch::parent()
{
    return *this->m_parent;
}

branch const& branch::parent() const
{
    return *this->m_parent;
}

void branch::foreach_branch(std::function<void(branch const&)> const& func) const
{
    func(*this);
    for(auto const& b : this->m_branches)
    {
        branch const& current_branch = *b;
        current_branch.foreach_branch(func);
    }
}

void branch::create_branches(int branch_count)
{
    this->m_branches.clear();
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(0, 1.f);
    for(int i = 0; i < branch_count; ++i)
    {
        float p = dis(gen);
        glm::vec3 new_position = this->m_position + p*this->m_length * this->m_orientation;

        float theta = atan2(m_orientation.x, m_orientation.z);

        glm::vec3 horizontal_branch_axis = glm::vec3(-sin(theta), 0.0f, cos(theta));

        glm::vec3 vertical_branch_axis = glm::cross(m_orientation, horizontal_branch_axis);

        horizontal_branch_axis = glm::normalize(horizontal_branch_axis);
        vertical_branch_axis = glm::normalize(vertical_branch_axis);

        float R = 1.0;
        float alpha = sin(M_PI / branch_count);

        if(alpha >= 0.5)
            R = 0.5/sin(alpha);

        float h = R*cos(2.0 * i * alpha);
        float v = R*sin(2.0 * i * alpha);
        float b = sqrt(1.0-R*R);

        glm::vec3 new_orientation = h * horizontal_branch_axis +
                                    v * vertical_branch_axis * v +
                                    b * this->m_orientation;

        auto const& vec_display = m_orientation;

        this->m_branches.emplace_back(std::make_unique<branch>(new_position, new_orientation, this->m_length / 2.f, this));
    }
}

void branch::grow_branches(int branch_count)
{
    if(this->m_branches.empty())
    {
        this->create_branches(branch_count);
    }
    else
    {

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(0, branch_count);

        for(auto& branch : this->m_branches)
        {

            int random_number = dis(gen);

            branch->grow_branches(random_number);
        }
    }
}

tree::tree(glm::vec3 position):
    m_branch(position, glm::vec3(0.f,1.f,0.f), 0.5f)
{
}

void tree::foreach_branch(std::function<void(branch const&)> const& func) const
{
    this->m_branch.foreach_branch(func);
}

void tree::grow()
{
    this->m_branch.grow_branches(4);
}