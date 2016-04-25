#ifndef MAP_H
#define MAP_H

#include<string>
#include<vector>

#include"Character.h"
#include"Hero.h"
#include"Item.h"

using namespace std;

struct Location
{
    string name;
    string description;
    string warning; //Brief description to warn user before moving
    string closedMessage; //Message displayed if room is not accessible hinting at how to get in
    bool accessible;
    bool itemFound; //Member variable used to denote if items have been collected
    Item *roomItem;//Item Chest Located at Each Location
    Character *locationCharacter;
    Location *next;
    Location *previous;

    Location() {}; //Default Constructor
};

class Map
{
    public:
        Map();
        virtual ~Map();
        void displayMap();
        //Precondition: User has started game
        //Postcondition: All locations and paths built
        Location *traverseMap(string localName);
        //Precondition: Map is built and name of desired location is entered
        //Postcondition: Pointer to desired location is returned
        void setCurrentLocation(Location *area);
        //Precondition: Map is built
        //Postcondition: Currentposition is changed to new location
        Location *getCurrentLocation();
        //Precondition: Current location is established
        //Postcondition: Current location is returned
    protected:
    private:
        Location *head;
        Location *tail;
        Location *currentLocation;
};

#endif // MAP_H
