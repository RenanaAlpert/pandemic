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
    class GeneSplicer : public Player
    {
        public:
            GeneSplicer(pandemic::Board b, pandemic::City c): Player(b, c, "GeneSplicer") {};
            ~GeneSplicer() {};

            GeneSplicer& discover_cure(pandemic::Color color);
    };
};