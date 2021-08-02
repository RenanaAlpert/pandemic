#pragma once
#include <iostream>
using namespace std;

#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
using namespace pandemic;

#include <set>

namespace pandemic
{

    class Player
    {
    protected:
        Board &board;
        City city;
        string role_name;
        set<pandemic::City> cards;

        const int CARDS_TO_CURE = 5;

    public:
        Player(pandemic::Board &b, const pandemic::City c, const string &r) : board(b), city(c), role_name(r){};
        ~Player(){};
        virtual Player &drive(pandemic::City city);
        virtual Player &fly_direct(pandemic::City city);
        virtual Player &fly_charter(pandemic::City city);
        virtual Player &fly_shuttle(pandemic::City city);
        virtual Player &build();
        virtual Player &discover_cure(pandemic::Color color);
        virtual Player &treat(pandemic::City city);
        virtual Player &take_card(pandemic::City city);
        string role() const;
        Player &remove_cards();
    };
};