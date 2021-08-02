#include "Scientist.hpp"
using namespace pandemic;

// Can do "discover_cure" using only n cards, with the n parameter passed to the constructor.
Scientist &Scientist::discover_cure(pandemic::Color color)
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

    if (count_cards >= this->cards_to_cure)
    {
        if (!cure)
        {
            count_cards = this->cards_to_cure;
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
        throw exp;
    }

    return *this;
}