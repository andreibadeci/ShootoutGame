#include <iostream>
#include <ctime>
#include "Map.h"
#include "Map_functii.h"

using namespace std;

int main()
{
    Map battlefield;
    srand (time(NULL));
    battlefield.menu();
    return 0;
}
