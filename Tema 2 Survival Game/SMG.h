#ifndef SMG_H_INCLUDED
#define SMG_H_INCLUDED

void SMG::set_row(int data)
{
    row=data;
}

void SMG::set_col(int data)
{
    col=data;
}

int SMG::get_item_id()
{
    return item_id;
}

int SMG::get_buff()
{
    return buff;
}

int SMG::get_row()
{
    return row;
}

int SMG::get_col()
{
    return col;
}

vector <char> SMG::get_buff_type()
{
    vector <char> temp;
    for(int i=0;i<buff_type.size();i++)
        temp.push_back(buff_type[i]);
    return temp;
}

#endif // SMG_H_INCLUDED
