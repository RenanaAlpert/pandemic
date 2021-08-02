#pragma once
#include <iostream>
using namespace std;

#include <list>
#include <map>
#include "City.hpp"
#include "Color.hpp"
using namespace pandemic;

namespace pandemic
{
    class CityData
    {

        pandemic::City city;
        pandemic::Color color;
        unsigned int diseases;
        bool is_reserches;
        list<pandemic::City> neighbors;

    public:
        CityData(){};
        CityData(const City c, const Color col, const unsigned int d, const bool r, const list<pandemic::City> l) : city(c), color(col), diseases(d), is_reserches(r)
        {
            neighbors = l;
        };
        ~CityData(){};
        unsigned int &getDiseases();
        friend ostream &operator<<(ostream &os, const CityData &c);
    };

    class Board
    {
        map<pandemic::City, CityData> board_map;
        map<pandemic::Color, bool> cures;
        void loadCities();
        void blackCities();
        void yellowCities();
        void redCities();
        void blueCities();

    public:
        Board() { loadCities(); };
        ~Board(){};
        unsigned int operator[](pandemic::City city) const; //get number of disease
        unsigned int &operator[](pandemic::City city);      //set number of disease
        bool is_clean();
        void remove_cures();
        friend ostream &operator<<(ostream &os, const Board &b);
    };
};