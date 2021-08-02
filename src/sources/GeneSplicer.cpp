#include "GeneSplicer.hpp"
using namespace pandemic;

// Can do "discover_cure" with 5 cards - not necessarily from the color of the disease.
GeneSplicer &GeneSplicer::discover_cure(pandemic::Color color)
{
    bool researches = this->board.board_map.at(this->city).is_researches;
    if (!researches)
    {
        string exp = "you don't in research station";
        throw std::invalid_argument{exp};
    }

    bool cure = this->board.cures[color];

    int count_cards = this->cards.size();
    if (count_cards >= CARDS_TO_CURE)
    {
        if (!cure)
        {
            count_cards = CARDS_TO_CURE;
            set<pandemic::City>::iterator itr;
            for (itr = this->cards.begin(); count_cards > 0;)
            {
                itr = this->cards.erase(itr);
                count_cards--;
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