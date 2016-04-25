#include "Map.h"

Map::Map()
{
    head=new Location;
    head->name="Scholar House";//Initialize Home

    head->description="A Quaint Barn Where You Can Relax in Peace";
    head->warning="No Danger There Proceed without Caution";
    head->closedMessage=""; //Room is always open
    head->accessible=true;

    head->itemFound=false;
    head->roomItem= new Item("Basic Sword",2,1,0); //Initializes sword item in room

    head->next=NULL;
    head->previous=NULL;
    head->locationCharacter=NULL;

    Location *current=head;

    for(int i=1;i<8;i++) //Build remainder of Map
    {
        Location *tmp=new Location;
        if(i==1)
        {
            tmp->name="House of Pi";
            tmp->description=
            "Known for its Outrageous Cotillions and Excess of Meed. Inhabited by a Lively Bunch it is a Fun Destination... Provided You Can Get In";
            tmp->warning="Be Warned this is a Place of Both Rad Festivities and Utter Peril";
            tmp->accessible=false;
            tmp->closedMessage=
            "You Are Questioned By the GateKeepers \"Who Doth You Knoweth Here\". With No Good Answer You Are Sent Away. \"Maybe We'd Let You In If You Weren't Such a Weakling\" They Taunt.";

            tmp->itemFound=false;
            tmp->roomItem=new Item("Basic Shield",1,2,0);
            string m1="I will not go back to that store. I am having too much fun "; //Character messages
            string m2="Oh thanks for the tip, I'm going back to the store to reevaluate my life choices.";
            tmp->locationCharacter=new Character("Thadius",10,1,1,m1,m2);
        }
        else if(i==2)
        {
            tmp->name="Ye Olde Hill";
            tmp->description=
            "The Destination for Many Balderdash Residents, and is Home both to a Bustling MarketPlace... and Some Unfriendly Characters";
            tmp->warning="If I May Offer A Word of Caution... Be Careful There";
            tmp->accessible=true;
            tmp->closedMessage="";

            tmp->itemFound=false;
            tmp->roomItem=new Item("Spoiled Burnetts Bottle",0,0,-5);


            string m1="What Are You Doing Herree...(*Slurred Words*)... I'm Going... You Gotta...I....(*Uhm*)...Let's Fight About It";
            string m2="You Won... You Deserve A Prize Take My Magic and Wondrous Elixir";
            tmp->locationCharacter=new Character("Drunken Fool",7,1,1,m1,m2);
        }
        else if(i==3)
        {
            tmp->name="Market";
            tmp->description=
            "A Place to Buy Whatever Trinket Your Heart Desires. It is a Fine Establishment... if the Shopkeeper is Home";
            tmp->warning="No Danger There... Except for Being Swindled Out of Your Doubloons or Tokens or Whatever Other Fantasy Currency You Prefer";
            tmp->accessible=false;
            tmp->closedMessage=
            "There is A Sign on The Door. \"Went to the House of Pi be Back at \'?\'.\" Not Knowing When \"?\" Is You May Need to Take Matters into Your Own Hands.";

            tmp->itemFound=false;
            tmp->roomItem=new Item("Nourishment Wrap of Chee-Bah",0,0,0);
            string m1="Thanks for Getting me Back to Work. As A Reward Have Whatever is Left in the Store.";
            tmp->locationCharacter=new Character("Shopkeeper",10,1,1,m1,"");
        }
        else if(i==4)
        {
            tmp->name="Castle of Knowledge";
            tmp->description=
            "The Go to Study Castle for Many CU Apprentices. From SwordPlay 101 to Upper-Division Witchcraft Much can Be Learned Here... if the Book Guardian Lets You In";
            tmp->accessible=false;
            tmp->closedMessage=
            "You Try To Get In But Are Stopped by The Book Keeper. \"Sorry Castle is Closed No One is Getting In On My Watch\". As You Walk Away You Hear His Stomach Rumbling.";
            tmp->warning="There is No Danger There... Though You May be Bored to Death";

            tmp->itemFound=false;
            tmp->roomItem=new Item("TextBook of the House of C",3,3,0);
            string m1="Thanks I am Starving But I am Still Not Letting You In... Can Make the Game Too Easy";
            string m2="I am Not Feeling too Good... I'll Be Back Don't Move";
            tmp->locationCharacter=new Character("Book Guardian",10,1,1,m1,m2);
        }
        else if(i==5)
        {
            tmp->name="Training Arena";
            tmp->description=
            "The Perfect Place to Boost Your Strength and Change Your Appearance";
            tmp->accessible=true;
            tmp->itemFound=false;
            tmp->warning="The Only Danger Therein Is How Dangerously Good-Looking You'll Be After a Few Good Reps";
            tmp->locationCharacter=NULL;
        }
        else if(i==6)
        {
            tmp->name="Horse Path";
            tmp->description=
            "The Path Which Leads Straight to Your Test, but It Can Be Treacherous";
            tmp->accessible=true;
            tmp->warning="I'm Not Going to Lie... There Might Be Something Bad Ogre There";

            tmp->itemFound=false;
            tmp->roomItem=new Item("Protein of WHEY",0,0,1);
            string m1="Puny Fresh Meat No One Shall Pass Me... Just WEIGHT Til I Defeat You!";
            string m2="You Have Defeated Me. Take This Magical Strengthing Dust";
            tmp->locationCharacter=new Character("Swoll\'gre",15,1,0,m1,m2);
        }
        else if(i==7)
        {
            tmp->name="House of Doom";
            tmp->description=
            "The Location of your Studies and Test. It Often Crushes Your Spirit. Enter if You Dare";
            tmp->accessible=false;
            tmp->closedMessage=
            "You Approach the Door Only to Find You Don't Have Your Spellbook. There is No Way to Defeat COG Without It. It Must Be Somewhere in BalderDash.";
            tmp->warning="There is Absolutely No Danger at The House of Doom (*Said the Programmer in a Sarcastic Voice*)";

            string m1="PREPARE TO PERISH!";
            string m2="THIS IS IMPOSSIBLE! HOW COULD YOU POSSIBLY DEFEAT ME! WELL I'LL BE BACK... IN UPPER DIVISION COURSES!\" (*DIES*)";
            tmp->locationCharacter=new Character("COG",20,1,1,m1,m2);
        }
        tmp->next=NULL;
        tmp->previous=current;
        current->next=tmp;
        current=tmp;
    }
    tail=current; //Sets the final location as the tail
    currentLocation=head;
}

Map::~Map()
{
    if(head!=NULL)
    {
        Location *tmp=head->next;
        while(tmp->next!=NULL)
        {
            delete tmp->previous->locationCharacter; //Deletes character at location
            delete tmp->previous->roomItem; //Deletes item at location
            delete tmp->previous;
            tmp=tmp->next;
        }
        delete tmp->previous->locationCharacter;
        delete tmp->previous;
        delete tmp->locationCharacter;
        delete tmp;
        head=NULL;
    }
}

void Map::displayMap()
{
    Location *tmp=head;
    while(tmp->next!=NULL)
    {
        cout<<tmp->name<<"<->";
        tmp=tmp->next;
    }
    cout<<tmp->name;
}

void Map::setCurrentLocation(Location *area)
{
    currentLocation=area;
}

Location *Map::getCurrentLocation()
{
    return currentLocation;
}

Location *Map::traverseMap(string localName) //Basic linked list search algorithm
{
    Location *tmp=head;
    bool found=false;
    while((!found)&&(tmp!=NULL))
    {
        if(tmp->name==localName)
        {
            found=true;
            return tmp;
        }
        else
        {
            tmp=tmp->next;
        }
    }
    return NULL;
}

