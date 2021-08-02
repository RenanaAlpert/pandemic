#include "Researcher.hpp"
using namespace pandemic;

// Can do "discover_cure" in any city - doesn't have to be at a research station.
Researcher &Researcher::discover_cure(pandemic::Color color)
{
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