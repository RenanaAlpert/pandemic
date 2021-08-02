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
    class Virologist : public Player
    {
        public:
            Virologist(pandemic::Board& b, const pandemic::City c): Player(b, c, "Virologist") {};
            ~Virologist() {};

            Virologist& treat(pandemic::City city);
    };
};