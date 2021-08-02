#include "Medic.hpp"
using namespace pandemic;

// When he do "treat", he removes all the disease cubes from the city he is in, and not just one.
Medic &Medic::treat(pandemic::City city)
{
    if (this->city != city)
    {
        string exp = "you are not in " + to_string(city);
        throw std::invalid_argument{exp};
    }

    if (this->board[city] == 0)
    {
        string exp = to_string(city) + " is not sick";
        throw std::invalid_argument{exp};
    }
    this->board[city] = 0;

    return *this;
}

// If a cure for the disease has already discovered, it automatically lowers all disease cubes from any city it enters, without do "treat".
Medic &Medic::drive(pandemic::City city)
{
    Player::drive(city);
    pandemic::Color c = this->board.board_map.at(city).color;
    if (this->board.cures[c])
    {
        this->board[city] = 0;
    }
    return *this;
}

// If a cure for the disease has already discovered, it automatically lowers all disease cubes from any city it enters, without do "treat".
Medic &Medic::fly_direct(pandemic::City city)
{
    Player::fly_direct(city);
    pandemic::Color c = this->board.board_map.at(city).color;
    if (this->board.cures[c])
    {
        this->board[city] = 0;
    }
    return *this;
}

// If a cure for the disease has already discovered, it automatically lowers all disease cubes from any city it enters, without do "treat".
Medic &Medic::fly_charter(pandemic::City city)
{
    Player::fly_charter(city);
    pandemic::Color c = this->board.board_map.at(city).color;
    if (this->board.cures[c])
    {
        this->board[city] = 0;
    }
    return *this;
}

// If a cure for the disease has already discovered, it automatically lowers all disease cubes from any city it enters, without do "treat".
Medic &Medic::fly_shuttle(pandemic::City city)
{
    Player::fly_shuttle(city);
    pandemic::Color c = this->board.board_map.at(city).color;
    if (this->board.cures[c])
    {
        this->board[city] = 0;
    }
    return *this;
}