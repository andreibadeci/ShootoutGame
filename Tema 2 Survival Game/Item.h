#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

class Item
{
public:
    virtual void set_row(int data)=0;///Functie care seteaza randul
    virtual void set_col(int data)=0;///Functie care seteaza coloana
    virtual int get_item_id()=0;///Functie care returneaza id-ul itemului
    virtual int get_buff()=0;///Functie care returneaza buff-ul itemului
    virtual int get_row()=0;///Functie care returneaza randul
    virtual int get_col()=0;///Functie care returneaza coloana
    virtual vector <char> get_buff_type()=0;///Functie care returneaza statusurile ce vor fi modificate
                                            ///de item
    virtual ~Item()=0;///Destructor
};

Item::~Item(){}

class SMG : public Item
{
    int item_id, buff, row, col;///Fiecare item are un id, buff(modificarea adusa agentului)
    vector <char> buff_type;///si buff_type (ce anume modifica)
public:                     ///buff_type are 3 elemente, prima casuta pentru viata,
                            ///a doua pentru atac si a treia pentru armura
    SMG()
    {
        item_id=2;
        buff=10;
        buff_type.assign(3,'0');
        buff_type[1]='1';
    }
    void set_row(int data);
    void set_col(int data);
    int get_item_id();
    int get_buff();
    int get_row();
    int get_col();
    vector <char> get_buff_type();
    ~SMG()
    {
        buff_type.clear();
    }
};

class Tank : public Item
{
    int item_id, buff, row, col;;
    vector <char> buff_type;
public:
    Tank()
    {
        item_id=3;
        buff=20;
        buff_type.assign(3,'0');
        buff_type[1]='1';
        buff_type[2]='1';
    }
    void set_row(int data);
    void set_col(int data);
    int get_item_id();
    int get_buff();
    int get_row();
    int get_col();
    vector <char> get_buff_type();
    ~Tank()
    {
        buff_type.clear();
    }
};

class Medpack : public Item
{
    int item_id, buff, row, col;;
    vector <char> buff_type;
public:
    Medpack()
    {
        item_id=4;
        buff=50;
        buff_type.assign(3,'0');
        buff_type[0]='1';
    }
    void set_row(int data);
    void set_col(int data);
    int get_item_id();
    int get_buff();
    int get_row();
    int get_col();
    vector <char> get_buff_type();
    ~Medpack()
    {
        buff_type.clear();
    }
};

#endif // ITEM_H_INCLUDED
