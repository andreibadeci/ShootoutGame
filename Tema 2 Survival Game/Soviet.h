#ifndef SOVIET_H_INCLUDED
#define SOVIET_H_INCLUDED

void Soviet::set_row(int data)
{
    row=data;
}

void Soviet::set_col(int data)
{
    col=data;
}

void Soviet::set_health(int data)
{
    health=data;
}

void Soviet::set_attack(int data)
{
    attack=data;
}

void Soviet::set_defence(int data)
{
    defence=data;
}

void Soviet::set_item_id(int data)
{
    item_id=data;
    item_usage=3;
}

void Soviet::update_item_usage(int data)
{
    item_usage=data;
}

int Soviet::get_row()
{
    return row;
}

int Soviet::get_col()
{
    return col;
}

int Soviet::get_health()
{
    return health;
}

int Soviet::get_attack()
{
    return attack;
}

int Soviet::get_defence()
{
    return defence;
}

int Soviet::get_item_id()
{
    return item_id;
}

int Soviet::get_item_usage()
{
    return item_usage;
}

vector <char> Soviet::get_nation()
{
    vector <char> temp;
    for(int i=0;i<nation.size();i++)
        temp.push_back(nation[i]);
    return temp;
}

#endif // SOVIET_H_INCLUDED
