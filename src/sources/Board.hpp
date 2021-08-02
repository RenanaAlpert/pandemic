#pragma once
#include <iostream>
using namespace std;

#include <set>
#include <map>
#include "City.hpp"
#include "Color.hpp"
using namespace pandemic;

namespace pandemic
{
    // The data of a city.
    class CityData
    {

        pandemic::City city;
        pandemic::Color color;
        int diseases;
        bool is_researches;
        set<pandemic::City> neighbors;

        friend class Player;
        friend class Dispatcher;
        friend class FieldDoctor;
        friend class GeneSplicer;
        friend class OperationsExpert;
        friend class Researcher;
        friend class Scientist;
        friend class Virologist;
        friend class Medic;

    public:
        CityData(){};
        CityData(const City c, const Color col, const int d, const bool r, const set<pandemic::City> &l) : city(c), color(col), diseases(d), is_researches(r)
        {
            neighbors = l;
        };
        ~CityData(){};
        int &getDiseases();
        void setResearches(bool b);
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

        friend class Player;
        friend class Dispatcher;
        friend class FieldDoctor;
        friend class GeneSplicer;
        friend class OperationsExpert;
        friend class Researcher;
        friend class Scientist;
        friend class Virologist;
        friend class Medic;

    public:
        Board()
        {
            loadCities();
            cures[Color::Black] = false;
            cures[Color::Blue] = false;
            cures[Color::Red] = false;
            cures[Color::Yellow] = false;
        };
        ~Board(){};

        int &operator[](pandemic::City city);
        bool is_clean();
        void remove_cures();
        void remove_stations();
        friend ostream &operator<<(ostream &os, const Board &b);
        map<pandemic::City, CityData> &get_board();

        static string enum_to_string(City c)
        {
            switch (c)
            {
                //Blue cities
            case Atlanta:
                return "Atlanta";
                break;
            case Chicago:
                return "Chicago";
                break;
            case Essen:
                return "Essen";
                break;
            case London:
                return "London";
                break;
            case Madrid:
                return "Madrid";
                break;
            case Milan:
                return "Milan";
                break;
            case Montreal:
                return "Montreal";
                break;
            case NewYork:
                return "NewYork";
                break;
            case Paris:
                return "Paris";
                break;
            case SanFrancisco:
                return "SanFrancisco";
                break;
            case StPetersburg:
                return "StPetersburg";
                break;
            case Washington:
                return "Washington";
                break;

            //Black cities
            case Algiers:
                return "Algiers";
                break;
            case Baghdad:
                return "Baghdad";
                break;
            case Cairo:
                return "Cairo";
                break;
            case Chennai:
                return "Chennai";
                break;
            case Delhi:
                return "Delhi";
                break;
            case Istanbul:
                return "Istanbul";
                break;
            case Karachi:
                return "Karachi";
                break;
            case Kolkata:
                return "Kolkata";
                break;
            case Moscow:
                return "Moscow";
                break;
            case Mumbai:
                return "Mumbai";
                break;
            case Riyadh:
                return "Riyadh";
                break;
            case Tehran:
                return "Tehran";
                break;

            //Yellow cities
            case Bogota:
                return "Bogota";
                break;
            case BuenosAires:
                return "BuenosAires";
                break;
            case Johannesburg:
                return "Johannesburg";
                break;
            case Khartoum:
                return "Khartoum";
                break;
            case Kinshasa:
                return "Kinshasa";
                break;
            case Lagos:
                return "Lagos";
                break;
            case Lima:
                return "Lima";
                break;
            case LosAngeles:
                return "LosAngeles";
                break;
            case MexicoCity:
                return "MexicoCity";
                break;
            case Miami:
                return "Miami";
                break;
            case Santiago:
                return "Santiago";
                break;
            case SaoPaulo:
                return "SaoPaulo";
                break;

            //Red cities
            case Beijing:
                return "Beijing";
                break;
            case HongKong:
                return "HongKong";
                break;
            case Tokyo:
                return "Tokyo";
                break;
            case Seoul:
                return "Seoul";
                break;
            case Shanghai:
                return "Shanghai";
                break;
            case Taipei:
                return "Taipei";
                break;
            case Sydney:
                return "Sydney";
                break;
            case Jakarta:
                return "Jakarta";
                break;
            case Manila:
                return "Manila";
                break;
            case Osaka:
                return "Osaka";
                break;
            case HoChiMinhCity:
                return "HoChiMinhCity";
                break;
            case Bangkok:
                return "Bangkok";
                break;

            default:
                return "it's not city";
                break;
            }
        };

        static string enum_to_string(Color c)
        {
            switch (c)
            {
            case Yellow:
                return "yellow";
                break;
            case Black:
                return "black";
                break;
            case Blue:
                return "blue";
                break;
            case Red:
                return "red";
                break;
            default:
                return "it's not color";
                break;
            }
        };
    };
};