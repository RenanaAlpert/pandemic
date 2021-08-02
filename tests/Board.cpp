#include "Board.hpp"
using namespace pandemic;

unsigned int &CityData::getDiseases()
{
    return this->diseases;
}

ostream &operator<<(ostream &os, const CityData &c)
{
    os << "city";
    return os;
}

void Board::loadCities()
{
    blackCities();
    yellowCities();
    redCities();
    blueCities();
}

void Board::blackCities()
{
    board_map[City::Algiers] = CityData(City::Algiers, Color::Black, 0, false, {City::Paris, City::Istanbul, City::Cairo, City::Madrid});
    board_map[City::Baghdad] = CityData(City::Baghdad, Color::Black, 0, false, {City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi});
    board_map[City::Cairo] = CityData(City::Cairo, Color::Black, 0, false, {City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh});
    board_map[City::Chennai] = CityData(City::Chennai, Color::Black, 0, false, {City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta});
    board_map[City::Delhi] = CityData(City::Delhi, Color::Black, 0, false, {City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata});
    board_map[City::Istanbul] = CityData(City::Istanbul, Color::Black, 0, false, {City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow});
    board_map[City::Karachi] = CityData(City::Karachi, Color::Black, 0, false, {City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi});
    board_map[City::Kolkata] = CityData(City::Kolkata, Color::Black, 0, false, {City::Delhi, City::Chennai, City::Bangkok, City::HongKong});
    board_map[City::Moscow] = CityData(City::Moscow, Color::Black, 0, false, {City::StPetersburg, City::Istanbul, City::Tehran});
    board_map[City::Mumbai] = CityData(City::Mumbai, Color::Black, 0, false, {City::Karachi, City::Delhi, City::Chennai});
    board_map[City::Riyadh] = CityData(City::Riyadh, Color::Black, 0, false, {City::Baghdad, City::Cairo, City::Karachi});
    board_map[City::Tehran] = CityData(City::Tehran, Color::Black, 0, false, {City::Baghdad, City::Moscow, City::Karachi, City::Delhi});
}

void Board::yellowCities()
{
    board_map[City::Bogota] = CityData(City::Bogota, Color::Yellow, 0, false, {City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires});
    board_map[City::BuenosAires] = CityData(City::BuenosAires, Color::Yellow, 0, false, {City::Bogota, City::SaoPaulo});
    board_map[City::Johannesburg] = CityData(City::Johannesburg, Color::Yellow, 0, false, {City::Kinshasa, City::Khartoum});
    board_map[City::Khartoum] = CityData(City::Khartoum, Color::Yellow, 0, false, {City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg});
    board_map[City::Kinshasa] = CityData(City::Kinshasa, Color::Yellow, 0, false, {City::Lagos, City::Khartoum, City::Johannesburg});
    board_map[City::Lagos] = CityData(City::Lagos, Color::Yellow, 0, false, {City::SaoPaulo, City::Khartoum, City::Kinshasa});
    board_map[City::Lima] = CityData(City::Lima, Color::Yellow, 0, false, {City::MexicoCity, City::Bogota, City::Santiago});
    board_map[City::LosAngeles] = CityData(City::LosAngeles, Color::Yellow, 0, false, {City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney});
    board_map[City::MexicoCity] = CityData(City::MexicoCity, Color::Yellow, 0, false, {City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota});
    board_map[City::Miami] = CityData(City::Miami, Color::Yellow, 0, false, {City::Atlanta, City::MexicoCity, City::Washington, City::Bogota});
    board_map[City::Santiago] = CityData(City::Santiago, Color::Yellow, 0, false, {City::Lima});
    board_map[City::SaoPaulo] = CityData(City::SaoPaulo, Color::Yellow, 0, false, {City::Bogota, City::BuenosAires, City::Lagos, City::Madrid});
}

void Board::redCities()
{
    board_map[City::Beijing] = CityData(City::Beijing, Color::Red, 0, false, {City::Shanghai, City::Seoul});
    board_map[City::HongKong] = CityData(City::HongKong, Color::Red, 0, false, {City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei});
    board_map[City::Tokyo] = CityData(City::Tokyo, Color::Red, 0, false, {City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco});
    board_map[City::Seoul] = CityData(City::Seoul, Color::Red, 0, false, {City::Beijing, City::Shanghai, City::Tokyo});
    board_map[City::Shanghai] = CityData(City::Shanghai, Color::Red, 0, false, {City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo});
    board_map[City::Taipei] = CityData(City::Taipei, Color::Red, 0, false, {City::Shanghai, City::HongKong, City::Osaka, City::Manila});
    board_map[City::Sydney] = CityData(City::Sydney, Color::Red, 0, false, {City::Jakarta, City::Manila, City::LosAngeles});
    board_map[City::Jakarta] = CityData(City::Jakarta, Color::Red, 0, false, {City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney});
    board_map[City::Manila] = CityData(City::Manila, Color::Red, 0, false, {City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney});
    board_map[City::Osaka] = CityData(City::Osaka, Color::Red, 0, false, {City::Taipei, City::Tokyo});
    board_map[City::HoChiMinhCity] = CityData(City::HoChiMinhCity, Color::Red, 0, false, {City::Jakarta, City::Bangkok, City::HongKong, City::Manila});
    board_map[City::Bangkok] = CityData(City::Bangkok, Color::Red, 0, false, {City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong});
}

void Board::blueCities()
{
    board_map[City::Atlanta] = CityData(City::Atlanta, Color::Blue, 0, false, {City::Chicago, City::Miami, City::Washington});
    board_map[City::Chicago] = CityData(City::Chicago, Color::Blue, 0, false, {City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal});
    board_map[City::Essen] = CityData(City::Essen, Color::Blue, 0, false, {City::London, City::Paris, City::Milan, City::StPetersburg});
    board_map[City::London] = CityData(City::London, Color::Blue, 0, false, {City::NewYork, City::Madrid, City::Essen, City::Paris});
    board_map[City::Madrid] = CityData(City::Madrid, Color::Blue, 0, false, {City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers});
    board_map[City::Milan] = CityData(City::Milan, Color::Blue, 0, false, {City::Essen, City::Paris, City::Istanbul});
    board_map[City::Montreal] = CityData(City::Montreal, Color::Blue, 0, false, {City::Chicago, City::Washington, City::NewYork});
    board_map[City::NewYork] = CityData(City::NewYork, Color::Blue, 0, false, {City::Montreal, City::Washington, City::London, City::Madrid});
    board_map[City::Paris] = CityData(City::Paris, Color::Blue, 0, false, {City::Algiers, City::Essen, City::Madrid, City::Milan, City::London});
    board_map[City::SanFrancisco] = CityData(City::SanFrancisco, Color::Blue, 0, false, {City::LosAngeles, City::Chicago, City::Tokyo, City::Manila});
    board_map[City::StPetersburg] = CityData(City::StPetersburg, Color::Blue, 0, false, {City::Essen, City::Istanbul, City::Moscow});
    board_map[City::Washington] = CityData(City::Washington, Color::Blue, 0, false, {City::Atlanta, City::NewYork, City::Montreal, City::Miami});
}

//get number of disease
unsigned int Board::operator[](pandemic::City city) const
{
    return 3;
}

//set number of disease
unsigned int &Board::operator[](pandemic::City city)
{
    return board_map.at(city).getDiseases();
}

bool Board::is_clean()
{
    return false;
}

void Board::remove_cures()
{
}

ostream &pandemic::operator<<(ostream &os, const Board &b)
{
    os << "board";
    return os;
}