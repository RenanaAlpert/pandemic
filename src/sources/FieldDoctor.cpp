#include "FieldDoctor.hpp"
using namespace pandemic;

// Can do "treat"not only in the city he is in but in any city near the city he is in, without throwing a card.
FieldDoctor &FieldDoctor::treat(pandemic::City city)
{
    if (this->city == city || this->board.board_map.at(this->city).neighbors.contains(city))
    {
        if (this->board[city] == 0)
        {
            string exp = Board::enum_to_string(city) + " is not sick";
            throw std::invalid_argument{exp};
        }

        pandemic::Color c = this->board.board_map.at(city).color;
        if (this->board.cures[c])
        {
            this->board[city] = 0;
        }
        else
        {
            this->board[city]--;
        }
    }
    else
    {
        string exp = "you can't treat " + Board::enum_to_string(city);
        throw std::invalid_argument{exp};
    }

    return *this;
}