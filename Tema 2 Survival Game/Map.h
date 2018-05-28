#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Agent.h"
#include "German.h"
#include "Soviet.h"
#include "American.h"
#include "Item.h"
#include "SMG.h"
#include "Tank.h"
#include "Medpack.h"
#define MAX 100000

using namespace std;

class Map///Harta
{
    int rows, cols, ger_number, ger_nr, sov_number, sov_nr, usa_number, usa_nr;///Harta tine minte numarul de agenti din
    ///fiecare factiune
    vector <vector<char> > game_map;
    German *ger;
    Soviet *sov;
    American *usa;
    SMG *weapon;
    Tank *vehicle;
    Medpack *consumable;///Alocare dinamica a agentilor si itemurilor
public:
    Map();
    void afisare();///Functie ce afiseaza matricea
    int get_rows()///Functie ce returneaza numarul de randuri
    {
       return rows;
    }
    int get_cols()///Functie ce returneaza numarul de coloane
    {
        return cols;
    }
    int movement(int &row, int &col, vector <char> country, int &agent_id);///Functia de miscare
    void set_agent_location(int number, int agent_type);///Functia de plasare a unui agent
    void set_item_location();///Functia de plasare a unui item
    void battle(int agent_type[], int agent_number[]);///Functia de confruntare
    int simulator();///Simularea unei runde
    void menu();///Meniul
    ~Map()///Destructor
    {
        for(int i=0;i<rows;i++)
            game_map[i].clear();
        game_map.clear();
    }
};

#endif // MAP_H_INCLUDED
