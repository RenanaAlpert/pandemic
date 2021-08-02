#pragma once

#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
using namespace pandemic;

#include <iostream>
using namespace std;

namespace pandemic
{
    class Researcher : public Player
    {
        public:
            Researcher(pandemic::Board& b, const pandemic::City c): Player(b, c, "Researcher") {};
            ~Researcher() {};

            Researcher& discover_cure(pandemic::Color color);
    };
};