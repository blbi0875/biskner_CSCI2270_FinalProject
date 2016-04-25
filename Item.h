//Declared separate header file for struct as it is used in multiple other header files
#ifndef ITEM_H
#define ITEM_H

#include<string>

using namespace std;

struct Item //Define structure for all items in Map
{
    string name;
    int attackBonus;
    int defenseBonus;
    int healthBonus;

    Item() {} //Default Constructor
    Item(string N,int AB,int DB,int HB) //Item constructor
    {
        name=N;
        attackBonus=AB;
        defenseBonus=DB;
        healthBonus=HB;
    }
};

#endif // ITEM_H
