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
    class FieldDoctor : public Player
    {
        public:
            FieldDoctor(pandemic::Board& b, const pandemic::City c): Player(b, c, "FieldDoctor") {};
            ~FieldDoctor() {};

            FieldDoctor& treat(pandemic::City city);
    };
};