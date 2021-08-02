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
    class Dispatcher : public Player
    {
        public:
            Dispatcher(pandemic::Board& b, const pandemic::City c): Player(b, c, "Dispatcher") {};
            ~Dispatcher() {};

            Dispatcher& fly_direct(pandemic::City city);
    };
};