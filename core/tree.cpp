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

        // Calculer l'angle theta selon laquelle m_orientation est incliné par rapport à l'axe y
        float theta = atan2(m_orientation.x, m_orientation.z);

        // Utiliser trigonométrie pour calculer horizontal_branch_axis
        glm::vec3 horizontal_branch_axis = glm::vec3(-sin(theta), 0.0f, cos(theta));

        // Calculer vertical_branch_axis normalement
        glm::vec3 vertical_branch_axis = glm::cross(m_orientation, horizontal_branch_axis);

        // Normaliser les vecteurs résultants
        horizontal_branch_axis = glm::normalize(horizontal_branch_axis);
        vertical_branch_axis = glm::normalize(vertical_branch_axis);

        float h = cos(2.0 * i * M_PI / branch_count);
        float v = sin(2.0 * i * M_PI / branch_count);
        float b = sqrt(4.0 * sin(M_PI / branch_count) * sin(M_PI / branch_count) - 1);

        glm::vec3 new_orientation = h * horizontal_branch_axis +
                                    v * vertical_branch_axis * v +
                                    b * this->m_orientation;

        new_orientation /= 2 * sin(M_PI / branch_count);

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
    this->m_branch.grow_branches(6);
}

// tree::tree(glm::vec3 position, glm::vec3 orientation, glm::vec3 stem_length, glm::vec3 stem_section):
//     m_trunc(position,
//              orientation,
//              stem_length, stem_section)
// {

// }

// void tree::grow()
// {
//     this->m_trunc.grow();
// }


// tree::node const& tree::get_trunc_node() const
// {
//     return this->m_trunc;
// }

// tree::node::branch const& tree::get_trunc() const
// {
//     return *this->m_trunc.m_branch;
// }

// tree::node::node(glm::vec3 position, glm::vec3 orientation, real length, real section):
//     m_position(position),
//     m_orientation(orientation),
//     m_branch(std::make_unique<tree::node::branch>(*this, length, section))
// {

// }

// tree::node::node(tree::node::branch const * parent):
//     m_parent(parent)
// {

// }

// void tree::node::grow()
// {
//     if(this->m_branch)
//     {
//         this->m_branch->grow();
//     }
//     else if(this->should_grow_branch())
//     {
//         this->m_branch = std::make_unique<tree::node::branch>(*this);
//     }
// }

// bool tree::node::should_grow_branch() const
// {
//     return true;
// }

// bool tree::node::is_on_a_branch() const
// {
//     return this->m_parent != nullptr;
// }

// tree::node::branch::branch(node const& owning_node, real length, real section):
//     m_owning_node(owning_node),
//     m_length(length),
//     m_section(section)
// {
//     for(int i = 0; i < 3; ++i)
//     {
//         this->m_nodes.push_back(node(this));
//     }
// }

// tree::node::branch::branch(node const& owning_node):
//     m_owning_node(owning_node)
// {
//     if(!m_owning_node.is_on_a_branch())
//         return;

//     branch const& parent_branch = m_owning_node.owning_branch();

//     this->m_length = 0.25 * parent_branch.m_length;
//     this->m_section = 0.25 * parent_branch.m_section;
//     for(int i = 0; i < 3; ++i)
//     {
//         this->m_nodes.push_back(node(this));
//     }
// }

// void tree::node::branch::grow()
// {
//     this->m_length *= 1.1;
//     this->m_section *= 1.1*1.1;

//     for(tree::node& node : this->m_nodes)
//     {
//         node.grow();
//     }
// }

// tree::iterator tree::node::branch::begin()
// {
//     return this->m_nodes.begin();
// }

// tree::iterator tree::node::branch::end()
// {
//     return this->m_nodes.end();
// }

// tree::const_iterator tree::node::branch::begin() const
// {
//     return this->m_nodes.begin();
// }

// tree::const_iterator tree::node::branch::end() const
// {
//     return this->m_nodes.end();
// }

// tree::const_iterator tree::node::branch::cbegin() const
// {
//     return this->m_nodes.cbegin();
// }

// tree::const_iterator tree::node::branch::cend() const
// {
//     return this->m_nodes.cend();
// }

// tree::node::branch const& tree::node::owning_branch() const
// {
//     return *this->m_parent;
// }

// std::ostream& operator<<(std::ostream& os, tree const& tree)
// {
//     tree.m_trunc.print(os, 0);
//     return os;
// }

// std::ostream& indent(std::ostream& os, int level)
// {
//     for(int i = 0; i < level; ++i)
//     {
//         os << "\t";
//     }
//     return os;
// }

// void tree::node::print(std::ostream& os, int level) const
// {

//     indent(os,level) << "has branch : " << (bool)this->m_branch << "\n";
//     indent(os,level) << "has leaf : " << (bool)this->m_leaf << "\n";
//     if(this->m_branch) {
//         indent(os,level) << "branch : " << "\n";
//         this->m_branch->print(os, level + 1);
//     }
// }

// void tree::node::branch::print(std::ostream& os, int level) const
// {
//     indent(os,level) << "length : " << this->m_length << "\n";
//     indent(os,level) << "section : " << this->m_section << "\n";
//     for(tree::node const& node : this->m_nodes)
//     {
//         indent(os,level) << "nodes :  " << "\n";
//         node.print(os, level + 1);
//     }
// }
