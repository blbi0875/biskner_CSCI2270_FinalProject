#include "Character.h"

Character::Character()
{
    health=10;
    attackPoints=1;
    defendPoints=1;
    message1="";
    message2="";
}


Character::Character(string characterName,int characterHealth,int AP,int DP,string m1,string m2)
{
    name=characterName;
    health=characterHealth; //Character health is initialize to 100%
    attackPoints=AP;
    defendPoints=DP;
    message1=m1;
    message2=m2;
}

Character::~Character()
{

}

int Character::getHealth()
{
    return health;
}

void Character::setHealth(int characterHealth)
{
    health=characterHealth;
}

string Character::getName()
{
    return name;
}

void Character::setName(string characterName)
{
    name=characterName;
}

string Character::getMessage(int mNumber)
{
    if(mNumber==1)
    {
        return message1;
    }
    else if(mNumber==2)
    {
        return message2;
    }
}

int Character::getAttackPoints()
{
    return attackPoints;
}

int Character::getDefendPoints()
{
    return defendPoints;
}
