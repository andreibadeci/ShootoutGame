#ifndef MEDPACK_H_INCLUDED
#define MEDPACK_H_INCLUDED

void Medpack::set_row(int data)
{
    row=data;
}

void Medpack::set_col(int data)
{
    col=data;
}

int Medpack::get_item_id()
{
    return item_id;
}

int Medpack::get_buff()
{
    return buff;
}

int Medpack::get_row()
{
    return row;
}

int Medpack::get_col()
{
    return col;
}

vector <char> Medpack::get_buff_type()
{
    vector <char> temp;
    for(int i=0;i<buff_type.size();i++)
        temp.push_back(buff_type[i]);
    return temp;
}

#endif // MEDPACK_H_INCLUDED
