#include "Virologist.hpp"
using namespace pandemic;

// Can do "treat", not only in the city in which it is located, but in any city in the world - by throwing a card of that city.
Virologist &Virologist::treat(pandemic::City city)
{
    if (this->city != city && !this->cards.contains(city))
    {
        string exp = "you don't have card of " + Board::enum_to_string(city);
        throw std::invalid_argument{exp};
    }

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
    if (this->city != city)
    {
        this->cards.erase(city);
    }

    return *this;
}