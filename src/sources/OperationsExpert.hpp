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
    class OperationsExpert : public Player
    {
        public:
            OperationsExpert(pandemic::Board& b, const pandemic::City c): Player(b, c, "OperationsExpert") {};
            ~OperationsExpert() {};

            OperationsExpert& build();
    };
};