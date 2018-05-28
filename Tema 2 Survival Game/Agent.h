#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Agent///Interfata pentru agenti
{
 public:
     virtual void set_row(int data)=0;///Functie care seteaza linia
     virtual void set_col(int data)=0;///Functie care seteaza coloana
     virtual void set_health(int data)=0;///Functie care seteaza viata
     virtual void set_attack(int data)=0;///Functie care seteaza atacul
     virtual void set_defence(int data)=0;///Functie care seteaza apararea
     virtual void set_item_id(int data)=0;///Functie care seteaza statusurile dupa un item luat
     virtual void update_item_usage(int data)=0;///Functie care modifica uzura itemului luat
     virtual int get_row()=0;///Functie care returneaza randul
     virtual int get_col()=0;///Functie care returneaza coloana
     virtual int get_health()=0;///Functie care returneaza viata
     virtual int get_attack()=0;///Functie care returneaza atacul
     virtual int get_defence()=0;///Functie care returneaza apararea
     virtual int get_item_id()=0;///Functie care returneaza id-ul itemului
     virtual int get_item_usage()=0;///Functie care returneaza uzura itemului
     virtual vector <char> get_nation()=0;///Functie care returneaza tara castigatoare
     virtual ~Agent()=0;///Destructor
};

Agent::~Agent(){}

class German: public Agent///Clasa German
{
    int health, attack, defence, item_id, item_usage, row, col;///Statusutile
    ///Fiecare item poate fi folosit de 3 ori, de aceea am item_usage
    vector <char> nation;///Tara agentului
public:
    German()///Constructor
    {
        nation.resize(23);
        char temp[]="G e r m a n  R e i c h";
        nation.insert(nation.begin(), temp, temp+strlen(temp));
        health=100;
        attack=10;
        defence=10;

    }
    void set_row(int data);
    void set_col(int data);
    void set_health(int data);
    void set_attack(int data);
    void set_defence(int data);
    void set_item_id(int data);
    void update_item_usage(int data);
    int get_row();
    int get_col();
    int get_health();
    int get_attack();
    int get_defence();
    int get_item_id();
    int get_item_usage();
    vector <char> get_nation();
    ~German()
    {
        nation.clear();
    }
};

class Soviet: public Agent///Clasa Soviet
{
    int health, attack, defence, item_id, item_usage, row, col;
    vector <char> nation;
public:
    Soviet()
    {
        nation.resize(36);
        char temp[]="Union of Soviet Socialist Republics";
        nation.insert(nation.begin(), temp, temp+strlen(temp));
        health=100;
        attack=10;
        defence=10;
    }
    void set_row(int data);
    void set_col(int data);
    void set_health(int data);
    void set_attack(int data);
    void set_defence(int data);
    void set_item_id(int data);
    void update_item_usage(int data);
    int get_row();
    int get_col();
    int get_health();
    int get_attack();
    int get_defence();
    int get_item_id();
    int get_item_usage();
    vector <char> get_nation();
    ~Soviet()
    {
        nation.clear();
    }
};

class American: public Agent///Clasa American
{
    int health, attack, defence, item_id, item_usage, row, col;
    vector <char> nation;
public:
    American()
    {
        nation.resize(24);
        char temp[]="United States of America";
        nation.insert(nation.begin(), temp, temp+strlen(temp));
        health=100;
        attack=10;
        defence=10;
    }
    void set_row(int data);
    void set_col(int data);
    void set_health(int data);
    void set_attack(int data);
    void set_defence(int data);
    void set_item_id(int data);
    void update_item_usage(int data);
    int get_row();
    int get_col();
    int get_health();
    int get_attack();
    int get_defence();
    int get_item_id();
    int get_item_usage();
    vector <char> get_nation();
    ~American()
    {
        nation.clear();
    }
};

#endif // AGENT_H_INCLUDED
