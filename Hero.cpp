#include "Hero.h"

Hero::Hero():Character() //Invokes Character default constructor
{

}

Hero::~Hero()//Invokes Character default destructor automatically
{
    //dtor
}

void Hero::displayHUB()
{
    int choice;
    do
    {
        cout<<"==== HUB ===="<<endl;
        cout<<"Name of Hero: "<<getName()<<endl;
        cout<<"Health: "<<getHealth()<<"0%"<<endl;
        cout<<"Lives Remaining: ";
        switch(lives) //Displays lives graphic based on player's current number of lives
        {
            case 3:
                cout<<"* * *"<<endl;
                break;
            case 2:
                cout<<"* *"<<endl;
                break;
            case 1:
                cout<<"*"<<endl;
                break;
        }
        cout<<endl;
        cout<<"Attack Power: "<<attackPoints<<"/3"<<endl;
        cout<<"Defense Power: "<<defendPoints<<"/3"<<endl;
        cout<<"Equipped Items: ";
        if(equippedItem==NULL)
        {
            cout<<"Bare Fists"<<endl;
        }
        else
        {
            cout<<equippedItem->name<<endl;
        }
        cout<<endl;
        cout<<"1. To Exit HUB"<<endl; //Exits HUB if 2 is selected

        cin>>choice;
        cout<<endl;
    }
    while(choice!=1);
}

int Hero::getLives()
{
    return lives;
}

void Hero::loseLife()
{
    lives--;
}

void Hero::pickUpItem(Item *roomItem)
{
    inventory.push_back(roomItem);
}

void Hero::equipItem(Item *inventoryItem)
{
    equippedItem=inventoryItem;
    attackPoints=inventoryItem->attackBonus; //Augments player stats based on item stats
    defendPoints=inventoryItem->defenseBonus;
    setHealth(getHealth()+inventoryItem->healthBonus);
    if(getHealth()<=0) //If Item Takes Away All User's Health
    {
        cout<<"You Have Lost A Life"<<endl;
        lives=lives-1;
        setHealth(10);
    }
}
void Hero::displayInventory()
{
    cout<<"===== INVENTORY ====="<<endl;
    for(int i=0;i<inventory.size();i++) //Displays names of all items in inventory
    {
        cout<<i<<". "<<inventory[i]->name<<endl;
    }
    int choice;
    do
    {
        cout<<"Please Choose Item to Equip or Exit By Entering \"-1\" "<<endl;
        cout<<"Choice: ";
        cin>>choice;
    }
    while((choice>inventory.size())&&(choice!=(-1))); //Continues to display message until valid choice is made

    if(choice!=-1) //If User Selected Item
    {
        equipItem(inventory[choice]);
    }
    if(inventory.empty())
    {
        cout<<"No Items in Inventory"<<endl;
    }
    cout<<endl;
}

string Hero::getEquippedItemName()
{
    if(equippedItem!=NULL)
    {
        return equippedItem->name;
    }
    else //Prevents seg fault if no item is equipped yet
    {
        return"Bare Fists";
    }
}

bool Hero::inInventory(string itemName)
{
    for(int i=0;i<inventory.size();i++)
    {
        if(inventory[i]->name==itemName)
        {
            return true;
        }
    }
    return false; //Returns false if item not found
}
