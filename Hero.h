#ifndef HERO_H
#define HERO_H

#include <vector>
#include "Character.h"
#include "Map.h"
#include "Item.h"

class Hero:public Character
{
    public:
        Hero();
        virtual ~Hero();
        void displayHUB();
        //Precondition: Hero is created
        //Postcondition: HUB of hero is displayed
        int getLives();
        //Precondition: Hero variable is created
        //Postcondition: Number of Lives Hero has Remaining is Returned
        void loseLife();
        //Precondition: User has lost a life in the game
        //Postcondition: User's number of lives is decremented
        void pickUpItem(Item *roomItem);
        //Precondition: User has found Item in room
        //Postcondition: Item is added to player inventory
        void displayInventory();
        //Precondition: User is created
        //Postcondition: Items in inventory listed
        void equipItem(Item *inventoryItem);
        //Precondition: Item in Inventory
        //Postcondition: Item is Equipped to User
        string getEquippedItemName();
        //Precondition: User has Item Equipped
        //Postcondition: Name of Item is returned

        bool inInventory(string itemName);
        //Precondition: Items in inventory
        //Postcondition: Returned if item in inventory

    protected:
    private:
        int lives=3;
        int attackPoints=1;
        int defendPoints=1;
        Item *hands=new Item("Bare Fists",1,1,0);
        vector<Item*> inventory={hands};
        Item *equippedItem=NULL;
};

#endif // HERO_H
