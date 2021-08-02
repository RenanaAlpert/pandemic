#include "OperationsExpert.hpp"
using namespace pandemic;

// Can do "build" in any city he is in, without throwing a card.
OperationsExpert &OperationsExpert::build()
{
    this->board.board_map.at(this->city).is_researches = true;
    return *this;
}