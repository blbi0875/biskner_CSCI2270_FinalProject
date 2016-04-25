#ifndef CHARACTER_H
#define CHARACTER_H

// Parent Class for all Characters in Game World

#include <string>
#include <iostream>

using namespace std;

class Character
{
    public:
        Character();
        Character(string characterName);
        //Precondition: Program is running
        //Postcondition: Character name initialized to specific value and health initialized to default
        Character(string characterName, int characterHealth,int AP,int DP,string m1, string m2);
        //Precondition: Program is running
        //Postcondition: Character name and health initialized to specific values
        virtual ~Character();
        //Precondition: Character is created
        //Postcondition: Character deleted from heap

// Accessor and Mutator Functions
        int getHealth();
        //Precondition: Character is created
        //Postcondition: Health value of character is returned
        void setHealth(int characterHealth);
        //Precondition: Character is created
        //Postcondition: Character health is set to input value

        string getName();
        //Precondition: Character name is set
        //Postcondition: Name of character is returned

        void setName(string characterName);
        //Precondition: Character is created
        //Postcondition: Health of character is returned

        string getMessage(int mNumber);
        //Precondition: Character has messages initialized
        //Postcondition: Corresponding message displayed based on input

        int getAttackPoints();
        //Precondition: Character initialized
        //Postcondition: Attack points returned

        int getDefendPoints();
        //Precondition: Character initialized
        //Postcondition: Defense points returned

    protected:
    private:
        string name;
        string message1;
        string message2;

        int health;
        int attackPoints; //Attacking Power with no Weapons
        int defendPoints; //Defending Power with no Shield
};

#endif // CHARACTER_H
