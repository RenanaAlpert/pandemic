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
    class Scientist : public Player
    {
        public:
            Scientist(pandemic::Board b, pandemic::City c, int cards): Player(b, c, "Scientist") {};
            ~Scientist() {};

            Scientist& discover_cure(pandemic::Color color);
    };
};