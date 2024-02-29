#pragma once
#include "defs.h"
#include <glm/glm.hpp>
#include <functional>
#include <vector>
#include <memory>
#include <optional>
#include <ostream>
#include <functional>

class branch
{
public:
    branch(glm::vec3 position, glm::vec3 orientation, real length, branch * parent = nullptr);

    glm::vec3 get_position() const;
    glm::vec3 get_orientation() const;
    real get_length() const;

    bool has_parent() const;
    branch& parent();
    branch const& parent() const;

    void foreach_branch(std::function<void(branch const&)> const& func) const;
    void create_branches(int branch_count);
    void grow_branches(int branch_count);
private:
    branch * m_parent;
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    real m_length;
    std::vector<std::unique_ptr<branch>> m_branches;
};

class tree
{
public:
    tree(glm::vec3 position);
    void foreach_branch(std::function<void(branch const&)> const& func) const;
    void grow();
private:
    branch m_branch;
};

// class tree
// {
//     friend std::ostream& operator<<(std::ostream& os, tree const& tree);
// public:
//     struct leaf
//     {

//     };

//     class node
//     {
//     public:
//         class branch
//         {
//             friend std::ostream& operator<<(std::ostream& os, branch const& tree);
//         public:
//             branch(node const& owning_node, real length, real section);
//             branch(node const& owning_node);
//             void grow();

//             void print(std::ostream& os, int level) const;

//             using iterator = std::vector<node>::iterator;
//             using const_iterator = std::vector<node>::const_iterator;

//             iterator begin();
//             iterator end();

//             const_iterator begin() const;
//             const_iterator end() const;

//             const_iterator cbegin() const;
//             const_iterator cend() const;
//         private:
//             real m_length;
//             real m_section;
//             std::vector<node> m_nodes;

//             node const& m_owning_node;
//         };
//     public:
//         node(glm::vec3 position, glm::vec3 orientation, real length, real section);
//         node(node::branch const * parent = nullptr);
//         void grow();
//         bool should_grow_branch() const;
//         bool is_on_a_branch() const;
//         branch const& owning_branch() const;

//         void print(std::ostream& os, int level) const;
//     private:
//         glm::vec3 m_position;
//         glm::vec3 m_orientation;
//         std::optional<leaf> m_leaf;
//         std::unique_ptr<branch> m_branch;

//         branch const * m_parent;

//     };
// public:
//     tree();

//     void grow();

//     node const& get_trunc_node() const;
//     node::branch const& get_trunc() const;

// private:
//     node m_trunc;
// };
