#include "Player.hpp"
using namespace pandemic;

// Moving from the current city to a nearby city.
Player &Player::drive(pandemic::City city)
{
    if (this->city == city)
    {
        string exp = "you can't fly from city to itself";
        throw std::invalid_argument{exp};
    }

    if (this->board.board_map.at(this->city).neighbors.contains(city))
    {
        this->city = city;
    }
    else
    {
        string exp = Board::enum_to_string(city) + " is not neighbor of " + Board::enum_to_string(this->city);
        throw std::invalid_argument{exp};
    }
    return *this;
}

// Moving from the current city to the city of some card in his hand. To do this, _inv__throw_invalid_argument(exp) the appropriate card to the city you are flying to.
Player &Player::fly_direct(pandemic::City city)
{
    if (this->city == city)
    {
        string exp = "you can't fly from city to itself";
        throw std::invalid_argument{exp};
    }

    if (this->cards.contains(city))
    {
        this->city = city;
        this->cards.erase(city);
    }
    else
    {
        string exp = "you don't have card of " + Board::enum_to_string(city);
        throw std::invalid_argument{exp};
    }
    return *this;
}

// Moving from the current city to any city. To do this, _inv__throw_invalid_argument(exp) the appropriate card to the city you are in.
Player &Player::fly_charter(pandemic::City city)
{
    if (this->city == city)
    {
        string exp = "you can't fly from city to itself";
        throw std::invalid_argument{exp};
    }

    if (this->cards.contains(this->city))
    {
        this->cards.erase(this->city);
        this->city = city;
    }
    else
    {
        string exp = "you don't have card of " + Board::enum_to_string(this->city);
        throw std::invalid_argument{exp};
    }
    return *this;
}

// If there is a research station in the current city, you can fly to any other city that has a research station.
Player &Player::fly_shuttle(pandemic::City city)
{
    if (this->city == city)
    {
        string exp = "you can't fly from city to itself";
        throw std::invalid_argument{exp};
    }

    if (this->board.board_map.at(this->city).is_researches)
    {
        if (this->board.board_map.at(city).is_researches)
        {
            this->city = city;
        }
        else
        {
            string exp = Board::enum_to_string(city) + " is not research station";
            throw std::invalid_argument{exp};
        }
    }
    else
    {
        string exp = Board::enum_to_string(this->city) + " is not research station";
        throw std::invalid_argument{exp};
    }

    return *this;
}

// Construction of a research station in the city in which they are located. To do this, _inv__throw_invalid_argument(exp) the appropriate card to the city you are in.
Player &Player::build()
{
    if (!this->board.board_map.at(this->city).is_researches)
    {
        if (this->cards.contains(this->city))
        {
            this->board.board_map.at(this->city).is_researches = true;
            this->cards.erase(this->city);
        }
        else
        {
            string exp = "you don't have card of " + Board::enum_to_string(this->city);
            throw std::invalid_argument{exp};
        }
    }
    return *this;
}

// Discovery of a cure for a disease of a certain color. To do this, you must be in a city that has a research station, and _inv__throw_invalid_argument(exp) 5 colored cards of the disease. The color of the city they are in does not matter.
Player &Player::discover_cure(pandemic::Color color)
{
    bool researches = this->board.board_map.at(this->city).is_researches;
    if (!researches)
    {
        string exp = "you don't in research station";
        throw std::invalid_argument{exp};
    }

    bool cure = this->board.cures[color];

    int count_cards = 0;
    set<pandemic::City>::iterator itr;
    for (itr = this->cards.begin(); itr != this->cards.end(); itr++)
    {
        if (this->board.board_map.at(*itr).color == color)
        {
            count_cards++;
        }
    }

    if (count_cards >= CARDS_TO_CURE)
    {
        if (!cure)
        {
            count_cards = CARDS_TO_CURE;
            for (itr = this->cards.begin(); itr != this->cards.end() && count_cards > 0;)
            {
                if (this->board.board_map.at(*itr).color == color)
                {
                    itr = this->cards.erase(itr);
                    count_cards--;
                }
                else
                {
                    ++itr;
                }
            }
            this->board.cures[color] = true;
        }
    }
    else
    {
        string exp = "you don't have enough cards";
        throw std::invalid_argument{exp};
    }

    return *this;
}

// Downloading one disease cube from the city you are in.
Player &Player::treat(pandemic::City city)
{
    if (this->city != city)
    {
        string exp = "you are not in " + Board::enum_to_string(city);
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

    return *this;
}

// Taking some city card.
Player &Player::take_card(pandemic::City city)
{
    this->cards.insert(city);
    return *this;
}

// Returns the role of the player.
string Player::role() const
{
    return this->role_name;
}

// Remove all the cards from the player. To tests.
Player &Player::remove_cards()
{
    this->cards.clear();
    return *this;
}