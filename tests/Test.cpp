#include <iostream>
using namespace std;

#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"
using namespace pandemic;

Board board;

TEST_CASE("Initialize board")
{

    CHECK(board.is_clean());

    board[City::London] = 3;       // 3 blue diseases.
    board[City::Paris] = 2;        // 2 blue diseases.
    board[City::SanFrancisco] = 3; // 1 blue disease.

    board[City::Tehran] = 5; // 5 black diseases.
    board[City::Mumbai] = 1; // 1 black disease.
    board[City::Delhi] = 2;  // 2 black diseases.

    board[City::Tokyo] = 3;    // 3 red diseases.
    board[City::Seoul] = 4;    // 4 red diseases.
    board[City::HongKong] = 4; // 4 red diseases.

    board[City::Lima] = 4;       // 1 yellow disease.
    board[City::MexicoCity] = 3; // 3 yellow diseases.
    board[City::Bogota] = 4;     // 4 yellow diseases.

    CHECK_FALSE(board.is_clean());
}

TEST_CASE("OperationsExpert")
{
    board.remove_cures();

    OperationsExpert player{board, City::Paris};
    player.take_card(City::NewYork)    // blue
        .take_card(City::SanFrancisco) // blue
        .take_card(City::Washington)   // blue
        .take_card(City::Sydney)       // red
        .take_card(City::Chicago)      // blue
        .take_card(City::Tehran)       // black
        .take_card(City::Atlanta);     // blue

    //drive method and build Research station in London.
    CHECK_THROWS(player.drive(City::Beijing)); // This city isn't neighbor of Paris.
    CHECK_NOTHROW(player.drive(City::London)); //  This city is neighbor of Paris.
    CHECK_NOTHROW(player.build());             // Build Research station in London.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::Karachi));  // He doesn't have card of Karachi.
    CHECK_NOTHROW(player.fly_direct(City::Atlanta)); // He has card of Atlanta.

    //fly_charter method.
    CHECK_THROWS(player.fly_charter(City::Shanghai)); // He doesn't have card of Atlanta.
    player.take_card(City::Atlanta);
    CHECK_NOTHROW(player.fly_charter(City::Shanghai)); // He has card of Atlanta.

    //fly_shuttle method and build Research station in Shanghai.
    CHECK_THROWS(player.fly_shuttle(City::Karachi)); // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::London));  // City with Research station.
    CHECK_NOTHROW(player.build());                   // Build Research station in Shanghai.
    CHECK_NOTHROW(player.fly_shuttle(City::London)); // City with Research station.

    //discover_cure method.
    CHECK_THROWS(player.discover_cure(Color::Blue)); // He has 3 blue cards.
    player.take_card(City::Milan);
    CHECK_NOTHROW(player.discover_cure(Color::Blue)); // He heve 5 blue cards.

    //treat method
    CHECK(board[City::London] == 3);
    CHECK_NOTHROW(player.treat(City::London)); // There is blue medicine.
    CHECK(board[City::London] == 0);

    player.fly_direct(City::Tehran);
    CHECK(board[City::Tehran] == 5);           // There are 5 disease cubes in Teheran.
    CHECK_NOTHROW(player.treat(City::Tehran)); // Sick city.
    CHECK(board[City::Tehran] == 4);           // There are 4 disease cubes in Teheran now.

    CHECK_THROWS(player.treat(City::MexicoCity)); // Sick city but he dosen't thier.
    player.drive(City::Baghdad);
    CHECK_THROWS(player.treat(City::Baghdad)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "OperationsExpert");
}

TEST_CASE("Dispatcher")
{
    board.remove_cures();

    Dispatcher player{board, City::Beijing};
    player.take_card(City::Miami)    // yellow
        .take_card(City::LosAngeles) // yellow
        .take_card(City::Lagos)      // yellow
        .take_card(City::Jakarta)    // red
        .take_card(City::Chicago)    // blue
        .take_card(City::Cairo)      // black
        .take_card(City::SaoPaulo);  // yellow

    //drive method.
    CHECK_THROWS(player.drive(City::Istanbul));  // This city isn't neighbor of Beijing.
    CHECK_NOTHROW(player.drive(City::Shanghai)); //  This city is neighbor of Beijing.

    //fly_ditect mathod.
    CHECK_NOTHROW(player.fly_direct(City::Paris));  // He in Research station so he doesn't need card.
    CHECK_THROWS(player.fly_direct(City::Karachi)); // He doesn't have card of Karachi.
    CHECK_NOTHROW(player.fly_direct(City::Cairo));  // He has card of Cairo.

    //fly_charter method.
    CHECK_THROWS(player.fly_charter(City::Lagos)); // He doesn't have card of Cairo.
    player.take_card(City::Cairo);
    CHECK_NOTHROW(player.fly_charter(City::Lagos)); // He has card of Cairo.

    //fly_shuttle method and build Research station in Lagos.
    CHECK_THROWS(player.fly_shuttle(City::Karachi));   // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::Shanghai));  // City with Research station.
    CHECK_NOTHROW(player.build());                     // Build Research station in Lagos.
    CHECK_NOTHROW(player.fly_shuttle(City::Shanghai)); // City with Research station.

    //discover_cure method.
    CHECK_THROWS(player.discover_cure(Color::Yellow)); // He has 3 yellow cards.
    player.take_card(City::MexicoCity)
        .take_card(City::Kinshasa);
    CHECK_NOTHROW(player.discover_cure(Color::Yellow)); // He hes 5 yellow cards.

    //treat method
    player.take_card(City::Bogota).fly_direct(City::Bogota);
    CHECK(board[City::Bogota] == 4);
    CHECK_NOTHROW(player.treat(City::Bogota)); // There is yellow medicine.
    CHECK(board[City::Bogota] == 0);

    player.drive(City::MexicoCity);
    CHECK(board[City::MexicoCity] == 3);           // There are 3 disease cubes in MexicoCity.
    CHECK_NOTHROW(player.treat(City::MexicoCity)); // Sick city.
    CHECK(board[City::MexicoCity] == 2);           // There are 2 disease cubes in MexicoCity now.

    CHECK_THROWS(player.treat(City::Tokyo)); // Sick city but he dosen't thier.
    player.drive(City::LosAngeles);
    CHECK_THROWS(player.treat(City::LosAngeles)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "Dispatcher");
}

TEST_CASE("Researcher")
{
    board.remove_cures();

    Researcher player{board, City::Chennai};
    player.take_card(City::Miami) // yellow
        .take_card(City::Beijing) // red
        .take_card(City::Osaka)   // red
        .take_card(City::Bangkok) // red
        .take_card(City::NewYork) // blue
        .take_card(City::Delhi)   // black
        .take_card(City::Essen);  // blue

    //drive method.
    CHECK_THROWS(player.drive(City::Istanbul)); // This city isn't neighbor of Chennai.
    CHECK_NOTHROW(player.drive(City::Mumbai));  //  This city is neighbor of Chennai.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::Paris));    // she doesn't have card of Paris.
    CHECK_NOTHROW(player.fly_direct(City::NewYork)); // she has card of NewYork.

    //fly_charter method.
    CHECK_THROWS(player.fly_charter(City::Essen)); // she doesn't have card of NewYork.
    player.take_card(City::NewYork);
    CHECK_NOTHROW(player.fly_charter(City::Essen)); // she has card of NewYork.

    //fly_shuttle method and build Research station in Essen.
    CHECK_THROWS(player.fly_shuttle(City::Paris));  // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::Lagos));  // City with Research station.
    CHECK_NOTHROW(player.build());                  // Build Research station in Essen.
    CHECK_NOTHROW(player.fly_shuttle(City::Lagos)); // City with Research station.

    //discover_cure method not in Research station.
    player.fly_direct(City::Miami);
    CHECK_THROWS(player.discover_cure(Color::Red)); // she has 3 red cards.
    player.take_card(City::Taipei)
        .take_card(City::Manila);
    CHECK_NOTHROW(player.discover_cure(Color::Red)); // she has 5 Red cards.

    //treat method
    player.take_card(City::Seoul).fly_direct(City::Seoul);
    CHECK(board[City::Seoul] == 4);
    CHECK_NOTHROW(player.treat(City::Seoul)); // There is Red medicine.
    CHECK(board[City::Seoul] == 0);

    player.fly_direct(City::Delhi);
    CHECK(board[City::Delhi] == 2);           // There are 2 disease cubes in Delhi.
    CHECK_NOTHROW(player.treat(City::Delhi)); // Sick city.
    CHECK(board[City::Delhi] == 1);           // There are 1 disease cubes in Delhi now.

    CHECK_THROWS(player.treat(City::HongKong)); // Sick city but she dosen't thier.
    player.drive(City::Kolkata);
    CHECK_THROWS(player.treat(City::Kolkata)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "Researcher");
}

TEST_CASE("Scientist")
{
    board.remove_cures();

    Scientist player{board, City::Montreal, 4};
    player.take_card(City::Cairo)    // black
        .take_card(City::Algiers)    // black
        .take_card(City::Moscow)     // black
        .take_card(City::Tokyo)      // red
        .take_card(City::London)     // blue
        .take_card(City::Washington) // blue
        .take_card(City::Bogota);    // yellow

    //drive method.
    CHECK_THROWS(player.drive(City::StPetersburg)); // This city isn't neighbor of Montreal.
    CHECK_NOTHROW(player.drive(City::Washington));  //  This city is neighbor of Montreal.

    //fly_charter method.
    CHECK_NOTHROW(player.fly_charter(City::NewYork)); // she has card of Washington.
    CHECK_THROWS(player.fly_charter(City::Essen));    // she doesn't have card of NewYork.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::Paris));   // she doesn't have card of Paris.
    CHECK_NOTHROW(player.fly_direct(City::Bogota)); // she has card of Bogota.

    //fly_shuttle method and build Research station in Bogota.
    CHECK_THROWS(player.fly_shuttle(City::Manila)); // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::London)); // City with Research station.
    player.take_card(City::Bogota);
    CHECK_NOTHROW(player.build());                   // Build Research station in Bogota.
    CHECK_NOTHROW(player.fly_shuttle(City::London)); // City with Research station.

    //discover_cure method with 4 card.
    CHECK_THROWS(player.discover_cure(Color::Black)); // she has 3 blach cards.
    player.take_card(City::Baghdad);
    CHECK_NOTHROW(player.discover_cure(Color::Black)); // she has 4 black cards.

    //treat method
    player.fly_charter(City::Tehran);
    CHECK(board[City::Tehran] == 4);
    CHECK_NOTHROW(player.treat(City::Tehran)); // There is Black medicine.
    CHECK(board[City::Tehran] == 0);

    player.fly_direct(City::Tokyo);
    CHECK(board[City::Tokyo] == 3);           // There are 3 disease cubes in Tokyo.
    CHECK_NOTHROW(player.treat(City::Tokyo)); // Sick city.
    CHECK(board[City::Tokyo] == 2);           // There are 2 disease cubes in MexicoCity now.

    CHECK_THROWS(player.treat(City::HongKong)); // Sick city but she dosen't thier.
    player.drive(City::Seoul);
    CHECK_THROWS(player.treat(City::Seoul)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "Scientist");
}

TEST_CASE("Virologist")
{
    board.remove_cures();

    Virologist player{board, City::Chennai};
    player.take_card(City::HongKong) // red
        .take_card(City::Beijing)    // red
        .take_card(City::Osaka)      // red
        .take_card(City::Lima)       // yellow
        .take_card(City::SaoPaulo)   // yellow
        .take_card(City::Istanbul)   // black
        .take_card(City::Miami);     // yellow

    //drive method.
    CHECK_THROWS(player.drive(City::Istanbul)); // This city isn't neighbor of Chennai.
    CHECK_NOTHROW(player.drive(City::Kolkata)); //  This city is neighbor of Chennai.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::SanFrancisco)); // she doesn't have card of SanFrancisco.
    CHECK_NOTHROW(player.fly_direct(City::Miami));       // she has card of Miami.

    //fly_charter method.
    CHECK_THROWS(player.fly_charter(City::SaoPaulo)); // she doesn't have card of Miami.
    player.take_card(City::Miami);
    CHECK_NOTHROW(player.fly_charter(City::SaoPaulo)); // she has card of Miami.

    //fly_shuttle method and build Research station in SaoPaulo.
    CHECK_THROWS(player.fly_shuttle(City::Chicago));   // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::Shanghai));  // City with Research station.
    CHECK_NOTHROW(player.build());                     // Build Research station in SaoPaulo.
    CHECK_NOTHROW(player.fly_shuttle(City::Shanghai)); // City with Research station.

    //discover_cure method.
    CHECK_THROWS(player.discover_cure(Color::Red)); // she has 3 red cards.
    player.take_card(City::Taipei)
        .take_card(City::Jakarta);
    CHECK_NOTHROW(player.discover_cure(Color::Red)); // she has 5 Red cards.

    //treat method
    player.take_card(City::Tokyo);
    CHECK(board[City::Tokyo] == 2);
    CHECK_NOTHROW(player.treat(City::Tokyo)); // There is Red medicine.
    CHECK(board[City::Tokyo] == 0);

    CHECK(board[City::Lima] == 4);           // There are 4 disease cubes in Lima.
    CHECK_NOTHROW(player.treat(City::Lima)); // Sick city.
    CHECK(board[City::Lima] == 3);           // There are 3 disease cubes in Lima now.

    CHECK_THROWS(player.treat(City::Kolkata)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "Virologist");
}

TEST_CASE("GeneSplicer")
{
    board.remove_cures();

    GeneSplicer player{board, City::StPetersburg};
    player.take_card(City::Lima)        // yellow
        .take_card(City::HoChiMinhCity) // red
        .take_card(City::Montreal)      // blue
        .take_card(City::Milan)         // blue
        .take_card(City::NewYork)       // blue
        .take_card(City::Algiers)       // black
        .take_card(City::Moscow);       // black

    //drive method.
    CHECK_THROWS(player.drive(City::LosAngeles)); // This city isn't neighbor of StPetersburg.
    CHECK_NOTHROW(player.drive(City::Moscow));    //  This city is neighbor of StPetersburg.

    //fly_charter method.
    CHECK_NOTHROW(player.fly_charter(City::Essen)); // she has card of Moscow.
    CHECK_THROWS(player.fly_charter(City::Delhi));  // she doesn't has card of Essen.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::Paris));    // she doesn't has card of Paris.
    CHECK_NOTHROW(player.fly_direct(City::NewYork)); // she has card of NewYork.

    //fly_shuttle method and build Research station in NewYork.
    CHECK_THROWS(player.fly_shuttle(City::Tehran));    // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::SaoPaulo));  // City with Research station.
    player.take_card(City::NewYork);
    CHECK_NOTHROW(player.build());                     // Build Research station in NewYork.
    CHECK_NOTHROW(player.fly_shuttle(City::SaoPaulo)); // City with Research station.

    //discover_cure method with veraity cards.
    player.take_card(City::Taipei);
    CHECK_NOTHROW(player.discover_cure(Color::Blue));  // with 2 blue cards, 1 black card, 2 red cards.
    CHECK_THROWS(player.discover_cure(Color::Yellow)); //with 1 card

    //treat method
    player.take_card(City::Paris).fly_direct(City::Paris);
    CHECK(board[City::Paris] == 2);
    CHECK_NOTHROW(player.treat(City::Paris)); // There is Blue medicine.
    CHECK(board[City::Paris] == 0);

    player.fly_direct(City::Lima);
    CHECK(board[City::Lima] == 3);           // There are 3 disease cubes in Lima.
    CHECK_NOTHROW(player.treat(City::Lima)); // Sick city.
    CHECK(board[City::Lima] == 2);           // There are 2 disease cubes in Lima now.

    CHECK_THROWS(player.treat(City::HongKong)); // Sick city but she dosen't thier.
    player.drive(City::Santiago);
    CHECK_THROWS(player.treat(City::Santiago)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "GeneSplicer");
}

TEST_CASE("FieldDoctor")
{
    FieldDoctor player{board, City::Atlanta};
    player.take_card(City::Mumbai)     // black
        .take_card(City::Kinshasa)     // yellow
        .take_card(City::Washington)   // blue
        .take_card(City::Bangkok)      // red
        .take_card(City::Johannesburg) // yellow
        .take_card(City::Karachi)      // black
        .take_card(City::Miami);       // blue

    //drive method.
    CHECK_THROWS(player.drive(City::Madrid));      // This city isn't neighbor of Atlanta.
    CHECK_NOTHROW(player.drive(City::Washington)); //  This city is neighbor of Atlanta.

    //fly_charter method.
    CHECK_NOTHROW(player.fly_charter(City::Madrid)); // He has card of Washington.
    CHECK_THROWS(player.fly_charter(City::Jakarta)); // He doesn't have card of Madrid.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::HoChiMinhCity)); // He doesn't has card of HoChiMinhCity.
    CHECK_NOTHROW(player.fly_direct(City::Mumbai));       // He has card of Mumbai.

    //fly_shuttle method and build Research station in Mumbai.
    CHECK_THROWS(player.fly_shuttle(City::Paris));  // City without Research station.
    CHECK_THROWS(player.fly_shuttle(City::Essen));  // City with Research station.
    player.take_card(City::Mumbai);
    CHECK_NOTHROW(player.build());                  // Build Research station in Mumbai.
    CHECK_NOTHROW(player.fly_shuttle(City::Essen)); // City with Research station.

    //discover_cure method.
    CHECK_THROWS(player.discover_cure(Color::Yellow)); // He has 3 Yellow cards.
    player.take_card(City::Lagos)
        .take_card(City::Bogota);
    CHECK_NOTHROW(player.discover_cure(Color::Yellow)); // He heve 5 Yellow cards.

    //treat method
    player.take_card(City::LosAngeles).fly_direct(City::LosAngeles);
    CHECK(board[City::MexicoCity] == 2);
    CHECK_NOTHROW(player.treat(City::MexicoCity)); // There is Yellow medicine.
    CHECK(board[City::MexicoCity] == 0);

    player.fly_direct(City::Bangkok);
    CHECK(board[City::HongKong] == 4);           // There are 4 disease cubes in Bangkok.
    CHECK_NOTHROW(player.treat(City::HongKong)); // Sick city.
    CHECK(board[City::HongKong] == 3);           // There are 3 disease cubes in Bangkok now.

    CHECK_THROWS(player.treat(City::Mumbai)); // Sick city but he dosen't thier or next to.
    player.drive(City::Jakarta);
    CHECK_THROWS(player.treat(City::Jakarta)); // The city isn't sick.

    //role method
    CHECK_EQ(player.role(), "FieldDoctor");
}

TEST_CASE("Medic")
{
    Medic player{board, City::SaoPaulo};
    player.take_card(City::Tehran)    // black
        .take_card(City::Algiers)     // black
        .take_card(City::NewYork)     // blue
        .take_card(City::HongKong)    // red
        .take_card(City::Lima)        // yellow
        .take_card(City::BuenosAires) // yellow
        .take_card(City::Cairo);      // black

    //drive method.
    CHECK_THROWS(player.drive(City::Seoul));        // This city isn't neighbor of SaoPaulo.
    CHECK_NOTHROW(player.drive(City::BuenosAires)); //  This city is neighbor of SaoPaulo.

    //fly_charter method.
    CHECK_NOTHROW(player.fly_charter(City::Madrid)); // He has card of BuenosAires.
    CHECK_THROWS(player.fly_charter(City::Jakarta)); // He doesn't have card of BuenosAires.

    //fly_ditect mathod.
    CHECK_THROWS(player.fly_direct(City::Baghdad));  // He doesn't have card of Baghdad.
    CHECK_NOTHROW(player.fly_direct(City::NewYork)); // He has card of NewYork.

    //fly_shuttle method.
    CHECK_NOTHROW(player.fly_shuttle(City::SaoPaulo)); // City with Research station.

    //discover_cure method.
    CHECK_THROWS(player.discover_cure(Color::Black)); // He has 3 black cards.
    player.take_card(City::Delhi)
        .take_card(City::Riyadh);
    CHECK_NOTHROW(player.discover_cure(Color::Black)); // He heve 5 black cards.

    //treat method
    CHECK_THROWS(player.treat(City::Mumbai)); // Sick city but he dosen't thier or next to.
    player.drive(City::Jakarta);
    CHECK_THROWS(player.treat(City::Jakarta)); // The city isn't sick.

    player.fly_direct(City::HongKong);
    CHECK(board[City::HongKong] == 3);
    CHECK_NOTHROW(player.treat(City::HongKong)); // there isn't red medicine.
    CHECK(board[City::HongKong] == 0);

    CHECK(board[City::SanFrancisco] == 3);
    player.take_card(City::HongKong).fly_charter(City::SanFrancisco); // There is blue madicine.
    CHECK(board[City::SanFrancisco] == 0);

    CHECK(board[City::Lima] == 3);
    player.fly_direct(City::Lima); // There is yellow madicine.
    CHECK(board[City::Lima] == 0);

    CHECK(board[City::Mumbai] == 1);
    player.drive(City::Bogota).fly_shuttle(City::Mumbai); // There is black madicine.
    CHECK(board[City::Mumbai] == 0);

    CHECK(board[City::Delhi] == 1);
    player.drive(City::Delhi); // There is black madicine.
    CHECK(board[City::Delhi] == 0);

    //role method
    CHECK_EQ(player.role(), "Medic");
}