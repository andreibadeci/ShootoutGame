#ifndef AMERICAN_H_INCLUDED
#define AMERICAN_H_INCLUDED

void American::set_row(int data)
{
    row=data;
}

void American::set_col(int data)
{
    col=data;
}

void American::set_health(int data)
{
    health=data;
}

void American::set_attack(int data)
{
    attack=data;
}

void American::set_defence(int data)
{
    defence=data;
}

void American::set_item_id(int data)
{
    item_id=data;
    item_usage=3;
}

void American::update_item_usage(int data)
{
    item_usage=data;
}

int American::get_row()
{
    return row;
}

int American::get_col()
{
    return col;
}

int American::get_health()
{
    return health;
}

int American::get_attack()
{
    return attack;
}

int American::get_defence()
{
    return defence;
}

int American::get_item_id()
{
    return item_id;
}

int American::get_item_usage()
{
    return item_usage;
}

vector <char> American::get_nation()
{
    vector <char> temp;
    for(int i=0;i<nation.size();i++)
        temp.push_back(nation[i]);
    return temp;
}

#endif // AMERICAN_H_INCLUDED
