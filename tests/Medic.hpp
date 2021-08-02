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
    class Medic : public Player
    {
        public:
            Medic(pandemic::Board b, pandemic::City c): Player(b, c, "Medic") {};
            ~Medic() {};

            Medic& treat(pandemic::City city);
            Medic& drive(pandemic::City city);
            Medic& fly_direct(pandemic::City city);
            Medic& fly_charter(pandemic::City city);
            Medic& fly_shuttle(pandemic::City city);
    };
};