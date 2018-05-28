#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

void Tank::set_row(int data)
{
    row=data;
}

void Tank::set_col(int data)
{
    col=data;
}

int Tank::get_item_id()
{
    return item_id;
}

int Tank::get_buff()
{
    return buff;
}

int Tank::get_row()
{
    return row;
}

int Tank::get_col()
{
    return col;
}

vector <char> Tank::get_buff_type()
{
    vector <char> temp;
    for(int i=0;i<buff_type.size();i++)
        temp.push_back(buff_type[i]);
    return temp;
}

#endif // TANK_H_INCLUDED
