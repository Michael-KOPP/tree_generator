#pragma once
#include <chrono>
#include "graphics/mesh.h"
#include "core/tree.h"

class tree_mesh : public mesh
{
public:
    tree_mesh(tree const& tree);

    void update();

    std::vector<glm::vec3> const& points() const;
    std::vector<unsigned int> const& indices() const;
private:
    tree const& m_tree;
    std::vector<glm::vec3> m_points;
    std::vector<unsigned int> m_indices;
};
