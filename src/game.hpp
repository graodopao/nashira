#pragma once
#include "level.hpp"

class Game {
public:
    void run();
private:
    Level* m_level{nullptr};
    bool m_should_quit{false};

    void pool_events();
};