#include <iostream>
#include <stdlib.h>
#include <string>
#include <Board.hpp>
#include <Player.hpp>
#include <Dispatcher.hpp>
#include <FieldDoctor.hpp>
#include <GeneSplicer.hpp>
#include <Medic.hpp>
#include <OperationsExpert.hpp>
#include <Researcher.hpp>
#include <Scientist.hpp>
#include <Virologist.hpp>

using namespace std;
using namespace pandemic;

Board board;

void print_cities()
{
    cout << "-------------------- cities --------------------" << endl;
    for (auto city : board.get_board())
    {
        //int num_city = atoi(to_string(city.first));
        if (city.first % 2 == 0)
        {
            cout << to_string(city.first) << " - " << Board::enum_to_string(city.first) << "\t\t|";
        }
        else
        {
            cout << "\t" << to_string(city.first) << " - " << Board::enum_to_string(city.first) << endl;
            ;
        }
    }
    cout << "------------------------------------------------" << endl;
}

void play(Player &player)
{
    cout << "\n" << player.role() << " Wellcom to Atlanta\n\n";
    while (true)
    {
        int c;
        int disease;
        cout << "Enter number of city and how many disease their. exemple: 5 3. Enter -1 to continue" << endl;
        cin >> c;
        if(c == -1){
            break;
        }
        cin >> disease;
        City city = (City)c;
        board[city] = disease;
    }
    bool flag = true;
    while (flag)
    {
        int c;
        City city;
        Color color;
        int num;
        cout << "What do you want to do? press the mach number" << endl;
        cout << "1 - drive\n2 - fly_direct\n3 - fly_charter\n4 - fly_shuttle\n5 - build\n";
        cout << "6 - discover_cure\n7 - treat\n8 - take_card\n9 - print board\n10 - exit" << endl;
        cin >> num;
        switch (num)
        {
        case 1: //drive
            cout << "\nWhere do you want to drive? enter the number of city:" << endl;
            cin >> c;
            city = (City)c;
            player.drive(city);
            break;
        case 2: //fly direct
            cout << "\nWhere do you want to fly? enter the number of city:" << endl;
            cin >> c;
            city = (City)c;
            player.fly_direct(city);
            break;
        case 3: //fly charter
            cout << "\nWhere do you want to fly? enter the number of city:" << endl;
            cin >> c;
            city = (City)c;
            player.fly_charter(city);
            break;
        case 4: //fly shuttle
            cout << "\nWhere do you want to fly? enter the number of city:" << endl;
            cin >> c;
            city = (City)c;
            player.fly_shuttle(city);
            break;
        case 5: //build
            player.build();
            cout << "success" << endl;
            break;
        case 6: //discover cure
            cout << "\nwhich cure you want to dscover? enter the number of color:" << endl;
            cout << "0 - yellow\t1 - black\n2 - blue\t3 - red" << endl;
            cin >> c;
            color = (Color)c;
            player.discover_cure(color);
            break;
        case 7: //treat
            cout << "\nwhich city do you want to treat? enter the number of city:" << endl;
            cin >> c;
            city = (City)c;
            player.treat(city);
            break;
        case 8: //take card
            cout << "\nwhich card do you want? enter the number of city:" << endl;
            cin >> c;
            city = (City)c;
            player.take_card(city);
            break;
        case 9: //print board
            cout << board;
            break;
        case 10: //exit
            flag = false;
            break;
        }
    }
}

int main()
{
    print_cities();
    cout << "Choose player:" << endl;
    cout << "D - Dispatcher\nF - FieldDoctor\nG - GeneSplicer\nM - Medic\nO - OperationsExpert\n";
    cout << "R - Researcher\nS - Scientist\nV - Virologist" << endl;
    char p;
    cin >> p;
    if (p == 'D')
    {
        Dispatcher playerD{board, City::Atlanta};
        play(playerD);
    }
    else if (p == 'F')
    {
        FieldDoctor playerF{board, City::Atlanta};
        play(playerF);
    }
    else if (p == 'G')
    {
        GeneSplicer playerG{board, City::Atlanta};
        play(playerG);
    }
    else if (p == 'M')
    {
        Medic playerM{board, City::Atlanta};
        play(playerM);
    }
    else if (p == 'O')
    {
        OperationsExpert playerO{board, City::Atlanta};
        play(playerO);
    }
    else if (p == 'R')
    {
        Researcher playerR{board, City::Atlanta};
        play(playerR);
    }
    else if (p == 'S')
    {
        cout << "How many cards to discover cure?" << endl;
        int cards;
        cin >> cards;
        Scientist playerS{board, City::Atlanta, cards};
        play(playerS);
    }
    else if (p == 'V')
    {
        Virologist playerV{board, City::Atlanta};
        play(playerV);
    }
    else
    {
        Player player{board, City::Atlanta, "Player"};
        play(player);
    }
    return 1;
}