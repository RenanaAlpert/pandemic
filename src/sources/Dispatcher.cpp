#include "Dispatcher.hpp"
using namespace pandemic;

// When he is at a research station, he can do a "fly direct" to any city he wants, without throwing a card.
Dispatcher &Dispatcher::fly_direct(pandemic::City city)
{
    if (this->city == city)
    {
        string exp = "you can't fly from city to itself";
        throw std::invalid_argument{exp};
    }

    if (this->board.board_map.at(this->city).is_researches)
    {
        this->city = city;
    }
    else
    {
        Player::fly_direct(city);
    }
    return *this;
}