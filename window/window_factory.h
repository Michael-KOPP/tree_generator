#pragma once
#include <memory>
#include "window/window.hpp"

class window_factory
{
public:
    window_factory();
    ~window_factory();

    std::unique_ptr<window> make() const;
};
