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
        const int cards_to_cure;

        public:
            Scientist(pandemic::Board& b, const pandemic::City c, const int cards): Player(b, c, "Scientist"), cards_to_cure(cards) {};
            ~Scientist() {};

            Scientist& discover_cure(pandemic::Color color);
    };
};