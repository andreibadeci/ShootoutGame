#ifndef MAP_FUNCTII_H_INCLUDED
#define MAP_FUNCTII_H_INCLUDED

Map::Map()///Constructor
{
    int n,m;
    cout<<"Introduceti dimensiunea hartii\nHarta trebuie sa aiba dimensiunea minima 15x15\n";
    cout<<"Dimensiunea maxima este 30x30\n";
    int ok=1;
    while(ok)
    {
        cin>>n>>m;
        ok=0;
        if(n<15 or m<15)
        {
            ok=1;
            cout<<"Introduceti alte dimensiuni\n";
        }
        if(n>30 or m>30)
        {
            ok=1;
            cout<<"Introduceti alte dimensiuni\n";
        }
    }
    rows=n;
    cols=m;
    game_map.resize(rows);
    for(int i=0; i<rows; i++)
        game_map[i].assign(cols, '0');
    ger_number=0;
    sov_number=0;
    usa_number=0;///Initial, nu exista niciun agent
}

void Map:: afisare()///Afisarea matricei
{
    cout<<"    ";
    int i;
    for(i=0; i<rows; i++)
        cout<<i+1<<"    ";
    cout<<'\n';
    for(i=0; i<rows; i++)
    {
        for(int j=-1; j<cols; j++)
        {
            if(j==-1 and i<9)
                cout<<i+1<<"   ";
            else if(j==-1 and i>=9)
                cout<<i+1<<"  ";
            else if(j<9 and game_map[i][j]!='0')
                cout<<game_map[i][j]<<"    ";
            else if(j>=9 and game_map[i][j]!='0')
                cout<<game_map[i][j]<<"     ";
            else if(j<9)
                cout<<"     ";
            else
                cout<<"      ";
        }
        cout<<'\n';
    }
    cout<<'\n';
}

void Map:: set_agent_location(int number, int agent_type)
{
    ///Functia primeste ca parametrii numarul de agenti si tipul agentului pe care sa-l puna pe harta
    switch(agent_type)
    {
    case 1:
        ger= new German [number];
        ger_number=number;
        ger_nr=number;
        for(int i=0; i<number; i++)
        {
            int ok=1;
            while(ok)
            {
                int row=rand()%rows, col=rand()%cols;
                if(game_map[row][col]!='N' or game_map[row][col]!='S' or game_map[row][col]!='A')
                {
                    ///Daca casuta e libera
                    ger[i].set_row(row);
                    ger[i].set_col(col);
                    game_map[row][col]='N';
                    ok=0;///Daca nu e libera, atunci se incearca din nou
                }
            }
        }
        break ;
    case 2:///Analog urmatorii 2 agenti
        sov= new Soviet [number];
        sov_number=number;
        sov_nr=number;
        for(int i=0; i<number; i++)
        {
            int ok=1;
            while(ok)
            {
                int row=rand()%rows, col=rand()%cols;
                if(game_map[row][col]!='N' or game_map[row][col]!='S' or game_map[row][col]!='A')
                {
                    sov[i].set_row(row);
                    sov[i].set_col(col);
                    game_map[row][col]='S';
                    ok=0;
                }
            }
        }
        break ;
    case 3:
        usa= new American [number];
        usa_number=number;
        usa_nr=number;
        for(int i=0; i<number; i++)
        {
            int ok=1;
            while(ok)
            {
                int row=rand()%rows, col=rand()%cols;
                if(game_map[row][col]!='N' or game_map[row][col]!='S' or game_map[row][col]!='A')
                {
                    usa[i].set_row(row);
                    usa[i].set_col(col);
                    game_map[row][col]='A';
                    ok=0;
                }
            }
        }
        break ;
    default:
        break ;
    }
}

void Map:: set_item_location()///Functia ce seteaza itemurile
{
    weapon= new SMG [6];
    vehicle= new Tank [6];
    consumable= new Medpack [6];///Exista doar 6 itemuri din fiecare tip
    for(int i=0; i<6; i++)
    {
        int ok=1;
        while(ok)
        {
            int row=rand()%rows, col=rand()%cols;
            if(game_map[row][col]!='N' or game_map[row][col]!='S' or game_map[row][col]!='A'
                    or game_map[row][col]!='4' or game_map[row][col]!='5' or game_map[row][col]!='6')
            {
                ///Analog plasare agenti
                weapon[i].set_row(row);
                weapon[i].set_col(row);
                game_map[row][col]='4';
                ok=0;
            }

        }
    }
    for(int i=0; i<6; i++)
    {
        int ok=1;
        while(ok)
        {
            int row=rand()%rows, col=rand()%cols;
            if(game_map[row][col]!='N' or game_map[row][col]!='S' or game_map[row][col]!='A'
                    or game_map[row][col]!='4' or game_map[row][col]!='5' or game_map[row][col]!='6')
            {
                vehicle[i].set_row(row);
                vehicle[i].set_col(row);
                game_map[row][col]='5';
                ok=0;
            }

        }
    }
    for(int i=0; i<6; i++)
    {
        int ok=1;
        while(ok)
        {
            int row=rand()%rows, col=rand()%cols;
            if(game_map[row][col]!='N' or game_map[row][col]!='S' or game_map[row][col]!='A'
                    or game_map[row][col]!='4' or game_map[row][col]!='5' or game_map[row][col]!='6')
            {
                consumable[i].set_row(row);
                consumable[i].set_col(row);
                game_map[row][col]='6';
                ok=0;
            }
        }
    }
}

int Map:: movement(int &row, int &col, vector <char> country, int &agent_id)
{
    ///Functia de miscare
    int dif=MAX, enemy_row, enemy_col;///Gaseste inamicul cel mai apropiat
    if(country.size()==45)///Pentru germani
    {
        if(sov_nr>0)
            for(int i=0; i<sov_number; i++)
                if(abs(row-sov[i].get_row())+abs(col-sov[i].get_col())<dif and sov[i].get_health()>0)
                {
                    ///Verifica valoarea absoluta a diferentei dintre linile si coloanele a doi agenti diferiti
                    dif=abs(row-sov[i].get_row())+abs(col-sov[i].get_col());
                    enemy_row=sov[i].get_row();
                    enemy_col=sov[i].get_col();
                    agent_id=i;///memoram id-ul agentului ca sa fie mai usor cand cautam
                }
        if(usa_nr>0)
            for(int i=0; i<usa_number; i++)
                if(abs(row-usa[i].get_row())+abs(col-usa[i].get_col())<dif and usa[i].get_health()>0)
                {
                    dif=abs(row-usa[i].get_row())+abs(col-usa[i].get_col());
                    enemy_row=usa[i].get_row();
                    enemy_col=usa[i].get_col();
                    agent_id=i;
                }
    }
    if(country.size()==71)///Pentru sovietici
    {
        if(ger_nr>0)
            for(int i=0; i<ger_number; i++)
                if(abs(row-ger[i].get_row())+abs(col-ger[i].get_col())<dif and ger[i].get_health()>0)
                {
                    ///Analog pentru urmatorii 2 agenti
                    dif=abs(row-ger[i].get_row())+abs(col-ger[i].get_col());
                    enemy_row=ger[i].get_row();
                    enemy_col=ger[i].get_col();
                    agent_id=i;
                }
        if(usa_nr>0)
            for(int i=0; i<usa_number; i++)
                if(abs(row-usa[i].get_row())+abs(col-usa[i].get_col())<dif and usa[i].get_health()>0)
                {
                    dif=abs(row-usa[i].get_row())+abs(col-usa[i].get_col());
                    enemy_row=usa[i].get_row();
                    enemy_col=usa[i].get_col();
                    agent_id=i;
                }
    }
    if(country.size()==48)///Pentru americani
    {
        if(ger_nr>0)
            for(int i=0; i<ger_number; i++)
                if(abs(row-ger[i].get_row())+abs(col-ger[i].get_col())<dif and ger[i].get_health()>0)
                {
                    dif=abs(row-ger[i].get_row())+abs(col-ger[i].get_col());
                    enemy_row=ger[i].get_row();
                    enemy_col=ger[i].get_col();
                    agent_id=i;
                }
        if(sov_nr>0)
            for(int i=0; i<sov_number; i++)
                if(abs(row-sov[i].get_row())+abs(col-sov[i].get_col())<dif and sov[i].get_health()>0)
                {
                    dif=abs(row-sov[i].get_row())+abs(col-sov[i].get_col());
                    enemy_row=sov[i].get_row();
                    enemy_col=sov[i].get_col();
                    agent_id=i;
                }
    }
    if(agent_id!=-1)///Daca s-a gasit un inamic
    {
        if(enemy_row==row and enemy_col==col)
            return 1;///Daca exista inamic pe aceasta pozitie, va fi o confruntare
        else if(enemy_row<row)
            row--;///Daca inamicul e mai jos, agentul coboara
        else if(enemy_row>row)
            row++;///Agentul urca
        else if(enemy_col<col)
            col--;///Agentul merge la stanga
        else if(enemy_col>col)
            col++;///Agentul merge la dreapta
    }
    if(game_map[row][col]=='4' or game_map[row][col]=='5' or game_map[row][col]=='6')
        return 2;///Agentul a gasit un item
    return 0;///Agentul n-a gasit nimic
}

void Map::battle(int agent_type[], int agent_number[])
{
    if(agent_type[0]==1 and agent_type[1]==2)
    {
        ///Exista 3 tipuri de confruntari germani-sovietici, germani-americani si sovietici-americani
        int health1=ger[agent_number[0]].get_health();
        int attack1=ger[agent_number[0]].get_attack();
        int defence1=ger[agent_number[0]].get_defence();
        int  health2=sov[agent_number[1]].get_health();
        int attack2=sov[agent_number[1]].get_attack();
        int defence2=sov[agent_number[1]].get_defence();
        while(health1>0 and health2>0)
        {
            ///Mai intai scade armura fiecarui agent apoi viata
            if(defence2>0)
                defence2=defence2-attack1;
            if(defence1>0)
                defence1=defence1-attack2;
            if(defence2<=0)
                health2=health2-attack1;
            if(health2>0 and defence1<=0)
                health1=health1-attack2;
        }
        if(health1<=0)
        {
            ger[agent_number[0]].set_health(0);
            game_map[ger[agent_number[0]].get_row()][ger[agent_number[0]].get_col()]='S';
            ger_nr--;///Daca agentul a murit, atunci scade numarul de agenti ai tarii
            ///respective
        }
        if(health2<=0)
        {
            sov[agent_number[1]].set_health(0);
            game_map[sov[agent_number[1]].get_row()][sov[agent_number[1]].get_col()]='N';
            sov_nr--;
        }
        int usage=ger[agent_number[0]].get_item_usage();
        if(!usage)
            usage--;///Scade uzura itemului daca avea unul
        if(!usage and health1>0)
        {
            ger[agent_number[0]].set_attack(10);
            ger[agent_number[0]].set_defence(10);
            ger[agent_number[0]].set_health(100);
        }
        ger[agent_number[0]].update_item_usage(usage);
        usage=sov[agent_number[1]].get_item_usage();
        if(!usage)
            usage--;
        if(!usage and health2>0)
        {
            sov[agent_number[1]].set_attack(10);
            sov[agent_number[1]].set_defence(10);
            sov[agent_number[1]].set_health(100);
        }
        sov[agent_number[1]].update_item_usage(usage);
    }
    if(agent_type[0]==1 and agent_type[1]==3)
    {
        ///Analog urmatoarele 2 cazuri
        int health1=ger[agent_number[0]].get_health();
        int attack1=ger[agent_number[0]].get_attack();
        int defence1=ger[agent_number[0]].get_defence();
        int health2=usa[agent_number[1]].get_health();
        int attack2=usa[agent_number[1]].get_attack();
        int defence2=usa[agent_number[1]].get_defence();
        while(health1>0 and health2>0)
        {
            if(defence2>0)
                defence2=defence2-attack1;
            if(defence1>0)
                defence1=defence1-attack2;
            if(defence2<=0)
                health2=health2-attack1;
            if(health2>0 and defence1<=0)
                health1=health1-attack2;
        }
        if(health1<=0)
        {
            ger[agent_number[0]].set_health(0);
            game_map[ger[agent_number[0]].get_row()][ger[agent_number[0]].get_col()]='A';
            ger_nr--;
        }
        if(health2<=0)
        {
            usa[agent_number[1]].set_health(0);
            game_map[usa[agent_number[0]].get_row()][usa[agent_number[0]].get_col()]='N';
            usa_nr--;
        }
        int usage=ger[agent_number[0]].get_item_usage();
        if(!usage)
            usage--;
        if(!usage and health1>0)
        {
            ger[agent_number[0]].set_attack(10);
            ger[agent_number[0]].set_defence(10);
            ger[agent_number[0]].set_health(100);
        }
        ger[agent_number[0]].update_item_usage(usage);
        usage=usa[agent_number[1]].get_item_usage();
        if(!usage)
            usage--;
        if(!usage and health2>0)
        {
            usa[agent_number[1]].set_attack(10);
            usa[agent_number[1]].set_defence(10);
            usa[agent_number[1]].set_health(100);
        }
        usa[agent_number[1]].update_item_usage(usage);
    }
    if(agent_type[0]==3 and agent_type[1]==2)
    {
        int health1=usa[agent_number[0]].get_health();
        int attack1=usa[agent_number[0]].get_attack();
        int defence1=usa[agent_number[0]].get_defence();
        int health2=sov[agent_number[1]].get_health();
        int attack2=sov[agent_number[1]].get_attack();
        int defence2=sov[agent_number[1]].get_defence();
        while(health1>0 and health2>0)
        {
            if(defence2>0)
                defence2=defence2-attack1;
            if(defence1>0)
                defence1=defence1-attack2;
            if(defence2<=0)
                health2=health2-attack1;
            if(health2>0 and defence1<=0)
                health1=health1-attack2;
        }
        if(health1<=0)
        {
            usa[agent_number[0]].set_health(0);
            game_map[usa[agent_number[0]].get_row()][usa[agent_number[0]].get_col()]='S';
            usa_nr--;
        }
        if(health2<=0)
        {
            sov[agent_number[1]].set_health(0);
            game_map[sov[agent_number[1]].get_row()][sov[agent_number[1]].get_col()]='A';
            sov_nr--;
        }
        int usage=usa[agent_number[0]].get_item_usage();
        if(!usage)
            usage--;
        if(!usage and health1>0)
        {
            usa[agent_number[0]].set_attack(10);
            usa[agent_number[0]].set_defence(10);
            usa[agent_number[0]].set_health(100);
        }
        usa[agent_number[0]].update_item_usage(usage);
        usage=sov[agent_number[1]].get_item_usage();
        if(!usage)
            usage--;
        if(!usage and health2>0)
        {
            sov[agent_number[1]].set_attack(10);
            sov[agent_number[1]].set_defence(10);
            sov[agent_number[1]].set_health(100);
        }
        sov[agent_number[1]].update_item_usage(usage);
    }
}

int Map:: simulator()
{
    for(int i=0; i<ger_number; i++)
    {
        if(ger[i].get_health()>0)
        {
            int player_row=ger[i].get_row(), player_col=ger[i].get_col(), agent_id=-1, ok;
            vector <char> country=ger[i].get_nation();
            int size=country.size();
            game_map[player_row][player_col]='0';
            ok=movement(player_row, player_col, country, agent_id);
            ger[i].set_row(player_row);
            ger[i].set_col(player_col);
            game_map[player_row][player_col]='N';
            if(ok==2 and !ger[i].get_item_usage())
            {
                for(int j=0; j<6; j++)
                    if(weapon[j].get_row()==player_row and weapon[j].get_col()==player_col)
                    {
                        ger[i].set_item_id(2);
                        weapon[j].set_row(-1);
                        weapon[j].set_col(-1);
                        int buff=weapon[j].get_buff();
                        vector <char> buff_type=weapon[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=ger[i].get_health();
                            health+=buff;
                            ger[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=ger[i].get_attack();
                            attack+=buff;
                            ger[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=ger[i].get_defence();
                            defence+=buff;
                            ger[i].set_defence(defence);
                        }
                    }
                for(int j=0; j<6; j++)
                    if(vehicle[j].get_row()==player_row and vehicle[j].get_col()==player_col)
                    {
                        ger[i].set_item_id(3);
                        vehicle[j].set_row(-1);
                        vehicle[j].set_col(-1);
                        int buff=vehicle[j].get_buff();
                        vector <char> buff_type=vehicle[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=ger[i].get_health();
                            health+=buff;
                            ger[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=ger[i].get_attack();
                            attack+=buff;
                            ger[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=ger[i].get_defence();
                            defence+=buff;
                            ger[i].set_defence(defence);
                        }
                    }
                for(int j=0; j<6; j++)
                    if(consumable[j].get_row()==player_row and consumable[j].get_col()==player_col)
                    {
                        ger[i].set_item_id(4);
                        consumable[j].set_row(-1);
                        consumable[j].set_col(-1);
                        int buff=consumable[j].get_buff();
                        vector <char> buff_type=consumable[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=ger[i].get_health();
                            health+=buff;
                            ger[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=ger[i].get_attack();
                            attack+=buff;
                            ger[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=ger[i].get_defence();
                            defence+=buff;
                            ger[i].set_defence(defence);
                        }
                    }
            }
            if(ok==1)
            {
                int agent_type[2], agent_number[2];
                if(agent_id<sov_number)
                    if(sov[agent_id].get_row()==player_row and sov[agent_id].get_col()==player_col and sov[agent_id].get_health()>0)
                    {
                        agent_type[0]=1;
                        agent_type[1]=2;
                        agent_number[0]=i;
                        agent_number[1]=agent_id;
                        battle(agent_type, agent_number);
                    }
                if(agent_id<usa_number)
                    if(usa[agent_id].get_row()==player_row and usa[agent_id].get_col()==player_col and usa[agent_id].get_health()>0)
                    {
                        agent_type[0]=1;
                        agent_type[1]=3;
                        agent_number[0]=i;
                        agent_number[1]=agent_id;
                        battle(agent_type, agent_number);
                    }
            }
        }
    }
    for(int i=0; i<sov_number; i++)
    {
        if(sov[i].get_health()>0)
        {
            int player_row=sov[i].get_row(), player_col=sov[i].get_col(), agent_id=-1, ok;
            vector <char> country=sov[i].get_nation();
            int size=country.size();
            game_map[player_row][player_col]='0';
            ok=movement(player_row, player_col, country, agent_id);
            sov[i].set_row(player_row);
            sov[i].set_col(player_col);
            game_map[player_row][player_col]='S';
            if(ok==2 and !sov[i].get_item_usage())
            {
                for(int j=0; j<6; j++)
                    if(weapon[j].get_row()==player_row and weapon[j].get_col()==player_col)
                    {
                        sov[i].set_item_id(2);
                        weapon[j].set_row(-1);
                        weapon[j].set_col(-1);
                        int buff=weapon[j].get_buff();
                        vector <char> buff_type=weapon[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=sov[i].get_health();
                            health+=buff;
                            sov[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=sov[i].get_attack();
                            attack+=buff;
                            sov[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=sov[i].get_defence();
                            defence+=buff;
                            sov[i].set_defence(defence);
                        }
                    }
                for(int j=0; j<6; j++)
                    if(vehicle[j].get_row()==player_row and vehicle[j].get_col()==player_col)
                    {
                        sov[i].set_item_id(3);
                        vehicle[j].set_row(-1);
                        vehicle[j].set_col(-1);
                        int buff=vehicle[i].get_buff();
                        vector <char> buff_type=vehicle[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=sov[i].get_health();
                            health+=buff;
                            sov[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=sov[i].get_attack();
                            attack+=buff;
                            sov[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=sov[i].get_defence();
                            defence+=buff;
                            sov[i].set_defence(defence);
                        }
                    }
                for(int j=0; j<6; j++)
                    if(consumable[j].get_row()==player_row and consumable[j].get_col()==player_col)
                    {
                        sov[i].set_item_id(4);
                        consumable[j].set_row(-1);
                        consumable[j].set_col(-1);
                        int buff=consumable[i].get_buff();
                        vector <char> buff_type=consumable[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=sov[i].get_health();
                            health+=buff;
                            sov[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=sov[i].get_attack();
                            attack+=buff;
                            sov[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=sov[i].get_defence();
                            defence+=buff;
                            sov[i].set_defence(defence);
                        }
                    }
            }
            if(ok==1)
            {
                int agent_type[2], agent_number[2];
                if(agent_id<ger_number)
                    if(ger[agent_id].get_row()==player_row and ger[agent_id].get_col()==player_col and ger[agent_id].get_health()>0)
                    {
                        agent_type[0]=1;
                        agent_type[1]=2;
                        agent_number[1]=i;
                        agent_number[0]=agent_id;
                        battle(agent_type, agent_number);
                    }
                if(agent_id<usa_number)
                    if(usa[agent_id].get_row()==player_row and usa[agent_id].get_col()==player_col and usa[agent_id].get_health()>0)
                    {
                        agent_type[0]=3;
                        agent_type[1]=2;
                        agent_number[1]=i;
                        agent_number[0]=agent_id;
                        battle(agent_type, agent_number);
                    }
            }
        }
    }
    for(int i=0; i<usa_number; i++)
    {
        if(usa[i].get_health()>0)
        {
            int player_row=usa[i].get_row(), player_col=usa[i].get_col(), agent_id=-1, ok;
            vector <char> country=usa[i].get_nation();
            int size=country.size();
            game_map[player_row][player_col]='0';
            ok=movement(player_row, player_col, country, agent_id);
            usa[i].set_row(player_row);
            usa[i].set_col(player_col);
            game_map[player_row][player_col]='A';
            if(ok==2 and !usa[i].get_item_usage())
            {
                for(int j=0; j<6; j++)
                    if(weapon[j].get_row()==player_row and weapon[j].get_col()==player_col)
                    {
                        usa[i].set_item_id(2);
                        weapon[j].set_row(-1);
                        weapon[j].set_col(-1);
                        int buff=weapon[j].get_buff();
                        vector <char> buff_type=weapon[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=usa[i].get_health();
                            health+=buff;
                            usa[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=usa[i].get_attack();
                            attack+=buff;
                            usa[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=usa[i].get_defence();
                            defence+=buff;
                            usa[i].set_defence(defence);
                        }
                    }
                for(int j=0; j<6; j++)
                    if(vehicle[j].get_row()==player_row and vehicle[j].get_col()==player_col)
                    {
                        usa[i].set_item_id(3);
                        vehicle[j].set_row(-1);
                        vehicle[j].set_col(-1);
                        int buff=vehicle[j].get_buff();
                        vector <char> buff_type=vehicle[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=usa[i].get_health();
                            health+=buff;
                            usa[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=usa[i].get_attack();
                            attack+=buff;
                            usa[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=usa[i].get_defence();
                            defence+=buff;
                            usa[i].set_defence(defence);
                        }
                    }
                for(int j=0; j<6; j++)
                    if(consumable[j].get_row()==player_row and consumable[j].get_col()==player_col)
                    {
                        usa[i].set_item_id(4);
                        consumable[j].set_row(-1);
                        consumable[j].set_col(-1);
                        int buff=consumable[j].get_buff();
                        vector <char> buff_type=consumable[j].get_buff_type();
                        if(buff_type[0]=='1')
                        {
                            int health=usa[i].get_health();
                            health+=buff;
                            usa[i].set_health(health);
                        }
                        if(buff_type[1]=='1')
                        {
                            int attack=usa[i].get_attack();
                            attack+=buff;
                            usa[i].set_attack(attack);
                        }
                        if(buff_type[2]=='1')
                        {
                            int defence=usa[i].get_defence();
                            defence+=buff;
                            usa[i].set_defence(defence);
                        }
                    }
            }
            if(ok==1)
            {
                int agent_type[2], agent_number[2];
                if(agent_id<ger_number)
                    if(ger[agent_id].get_row()==player_row and ger[agent_id].get_col()==player_col and ger[agent_id].get_health()>0)
                    {
                        agent_type[0]=1;
                        agent_type[1]=3;
                        agent_number[1]=i;
                        agent_number[0]=agent_id;
                        battle(agent_type, agent_number);
                    }
                if(agent_id<sov_number)
                    if(sov[agent_id].get_row()==player_row and sov[agent_id].get_col()==player_col and sov[agent_id].get_health()>0)
                    {
                        agent_type[0]=3;
                        agent_type[1]=2;
                        agent_number[1]=i;
                        agent_number[0]=agent_id;
                        battle(agent_type, agent_number);
                    }
            }
        }
    }
}

void Map::menu()///Meniul
{
    cout<<"Introduceti numarul de soldati nazisiti care participa la lupta pentru suprematie\n";
    int ok=1, n, map_size=get_rows()*get_cols();
    cin>>n;
    while(ok)
    {
        if(n>map_size)
        {
            cout<<"E prea mare, nu incape\n";
            cin>>n;
        }
        else
            ok=0;
    }
    map_size-=n;
    ok=1;
    set_agent_location(n, 1);
    cout<<"Introduceti numarul de soldati sovietici care lupta pentru tara mama\n";
    cin>>n;
    while(ok)
    {
        if(n>map_size)
        {
            cout<<"E prea mare, nu incape\n";
            cin>>n;
        }
        else
            ok=0;
    }
    map_size-=n;
    ok=1;
    set_agent_location(n, 2);
    cout<<"Introduceti numarul de soldati americani care lupta pentru 'Murica\n";
    cin>>n;
    while(ok)
    {
        if(n>map_size)
        {
            cout<<"E prea mare, nu incape\n";
            cin>>n;
        }
        else
            ok=0;
    }
    map_size-=n;
    set_agent_location(n,3);
    set_item_location();
    afisare();
    cout<<"Introduceti numarul de runde care se vor simula\n0 pentru oprire\n";
    cout<<"-1 pentru a simula pana la final\nOrice alt numar pentru a vedea situatia peste n runde\n";
    int rounds;
    cin>>rounds;
    while(rounds and rounds!=-1)
    {
        simulator();
        rounds--;
        afisare();
        if(sov_nr<=0 and usa_nr<=0)
        {
            cout<<"Victorie!\n";
            vector <char> winner=ger[0].get_nation();
            for(int i=0; i<winner.size(); i++)
                cout<<winner[i];
            return ;
        }
        if(ger_nr<=0 and usa_nr<=0)
        {
            cout<<"Victorie!\n";
            vector <char> winner=sov[0].get_nation();
            for(int i=0; i<winner.size(); i++)
                cout<<winner[i];
            return ;
        }
        if(ger_nr<=0 and sov_nr<=0)
        {
            cout<<"Victorie!\n";
            vector <char> winner=usa[0].get_nation();
            for(int i=0; i<winner.size(); i++)
                cout<<winner[i];
            return ;
        }
        if(rounds==0)
        {
            cout<<"Introduceti numarul de runde care se vor simula\n0 pentru oprire\n";
            cout<<"-1 pentru a simula pana la final\n";
            cout<<"Orice alt numar pentru a vedea situatia peste n runde\n";
            cin>>rounds;
        }
    }
    if(rounds==-1)
        while(ger_nr>0 or sov_nr>0 or usa_nr>0)
        {
            simulator();
            afisare();
            if(sov_nr<=0 and usa_nr<=0)
            {
                cout<<"Victorie!\n";
                vector <char> winner=ger[0].get_nation();
                for(int i=0; i<winner.size(); i++)
                    cout<<winner[i];
                return ;
            }
            if(ger_nr<=0 and usa_nr<=0)
            {
                cout<<"Victorie!\n";
                vector <char> winner=sov[0].get_nation();
                for(int i=0; i<winner.size(); i++)
                    cout<<winner[i];
                return ;
            }
            if(ger_nr<=0 and sov_nr<=0)
            {
                cout<<"Victorie!\n";
                vector <char> winner=usa[0].get_nation();
                for(int i=0; i<winner.size(); i++)
                    cout<<winner[i];
                return ;
            }
        }
}

#endif // MAP_FUNCTII_H_INCLUDED
