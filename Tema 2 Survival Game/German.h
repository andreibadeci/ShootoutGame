#ifndef GERMAN_H_INCLUDED
#define GERMAN_H_INCLUDED

void German::set_row(int data)
{
    row=data;
}

void German::set_col(int data)
{
    col=data;
}

void German::set_health(int data)
{
    health=data;
}

void German::set_attack(int data)
{
    attack=data;
}

void German::set_defence(int data)
{
    defence=data;
}

void German::set_item_id(int data)
{
    item_id=data;
    item_usage=3;
}

void German::update_item_usage(int data)
{
    item_usage=data;
}

int German::get_row()
{
    return row;
}

int German::get_col()
{
    return col;
}

int German::get_health()
{
    return health;
}

int German::get_attack()
{
    return attack;
}

int German::get_defence()
{
    return defence;
}

int German::get_item_id()
{
    return item_id;
}

int German::get_item_usage()
{
    return item_usage;
}

vector <char> German::get_nation()
{
    vector <char> temp;
    for(int i=0;i<nation.size();i++)
        temp.push_back(nation[i]);
    return temp;
}

#endif // GERMAN_H_INCLUDED
