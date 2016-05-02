#include <iostream>
#include <string>
#include <cstdlib> //Random number generator for combat (like dice rollS)

//User Defined Class Header Files
#include "Hero.h"
#include "Map.h"


using namespace std;

bool display_Welcome_Message ();
//Precondition: User has started program
//Postcondition: Welcome message is displayed, game begins or user exits

bool create_character (Hero *user);
//Precondition: User has chosen to play game
//Postcondition: Dynamic hero object created with personalized name

void play_game (Hero *user,Map *world);
//Precondition: User and map are created
//Postcondition: Game information is displayed

void game_combat (Hero *user, Character *enemy, Map *combatArea);
//Precondition: User has engaged in combat with enemy
//Postcondition: User Defeats enemy, quits, or loses a life

void boss_combat (Hero *user, Character *enemy);
//Precondition: User has made it to final boss battle
//Postcondition: Game is won or user dies

int main()
{
    bool playerOneReady=display_Welcome_Message();
    if(playerOneReady) //Continues into the game if the user selected 1 after the welcome message
    {
        playerOneReady==false; //Resets variable
        Hero *playerOne=new Hero; //Creates Hero for user in Heap
        playerOneReady=create_character(playerOne);
        if(playerOneReady) //If user has decided to continue after creating hero
        {
            char choice;
            Map *gameMap=new Map;
            play_game(playerOne,gameMap);
            delete gameMap; //Free dynamic memory
        }
        delete playerOne; //Frees dynamic memory
    }
    return 0;
}

bool display_Welcome_Message()
{
    string choice1;
    int choice;

    cout<<"========================== WELCOME SCREEN ============================"<<endl<<endl;
    cout<<"                       Welcome to CU BalderDash                       "<<endl;
    cout<<"         A Mystical Land with Danger Lurking Around Every Corner      "<<endl<<endl;
    cout<<" You Are a Lowly Apprentice Training in the Art of Computer Wizardry  "<<endl;
    cout<<"       After Years of Study it has come Time for Your Final Trial     "<<endl;
    cout<<"       You Must now Employ all you have Learned to Defeat \"COG\"     "<<endl;
    cout<<"         The Dreaded Mechanical Troll From the Land of MOO-DELL       "<<endl<<endl;
    cout<<"Equip Yourself with Items from Around the Map to Prepare for this Test"<<endl;
    cout<<"                             But be Warned                            "<<endl;
    cout<<"           This Quest is Only for Those \"Savage\" in Spirit          "<<endl<<endl;
    cout<<"                       Press \"1\" To Continue...                     "<<endl;
    cout<<"           OR Press \"2\" To Be a Quitter and Earn a Prize...         "<<endl<<endl;

    do
    {
        cout<<"Enter Choice: ";
        //cin.ignore();                                                         //Changes Start Here
        getline(cin,choice1);                                                   //
        if(choice1.size() != 1 ||(choice1[0] != '1' && choice1[0] != '2')){     //
            choice = 0;                                                         //
        }                                                                       //
        else{                                                                   //
            choice = stoi(choice1,nullptr,10);                                  //
        }                                                                       //
        //cin>>choice;                                                          // End Here
        switch(choice)
        {
        case 1:
            cout<<"You are Either Very Brave or Extremely Naive..."<<endl;
            cout<<"Either Way Best of Luck"<<endl<<endl;
            return true;
        case 2:
            cout<<"Your Prize is the Knowledge of Your Cowardice..."<<endl;
            cout<<"You Get to Keep it For the Rest of Your Life"<<endl;
            return false;
        default:
            cout<<"Please Make a Valid Choice..."<<endl<<endl;
        }
    }
    while((choice!=1)||(choice!=2));
}

bool create_character(Hero *user)
{
    string name;
    char choice;

    //prevents cin.ignore() from occurring on the first loop
    int flag = 0;

    cout<<"==== CHARACTER CREATION ===="<<endl;
    do
    {
        cout<<"Enter Name of Hero: ";
        if(flag != 0){                                                  //Changes start here
            cin.ignore(); //Needed to ensure getline works properly     //
        }                                                               //
        flag = 1;                                                       //End Here
        getline(cin,name); //Gets name of user
        cout<<"Are You Sure You Wish to be Called "<<name<<" for the WHOLE Game?"<<endl;
        cout<<"Enter Y or N: "; //Allows user opportunity to verify name
        cin>>choice;
        while((choice!='Y')&&(choice!='N')) //Ensures valid input
        {
            cout<<"Enter Y or N: ";
            cin>>choice;
        }
    }
    while(choice!='Y');
    cout<<"As You Wish...";
    user->setName(name); //Set the name of the player
    cout<<user->getName()<<" (*Chuckling Sound if You Put Dirty Word*)"<<endl<<endl; //Displays the name of the player

    cout<<"If You Are Ready to Begin Press Y if You Wish to Quit Now Press N"<<endl;
    cout<<"Enter Y or N: ";
    cin>>choice;
    while((choice!='Y')&&(choice!='N'))
    {
        cout<<"Enter Y or N: ";
        cin>>choice;
    }
    cout<<endl;
    if(choice=='N')
    {
        return false;
    }
    else if(choice=='Y')
    {
        return true;
    }
}

void play_game(Hero *user,Map *world)
{
    bool gameWon=false;
    char choice;
    cout<<endl;
    do //Allow User To Chose Action Until He Quits or Dies
    {
        cout<<"You are currently at the "<<world->getCurrentLocation()->name<<endl; //Display Current location
        cout<<"It Is "<<world->getCurrentLocation()->description<<endl;
        cout<<"What do You Want to Do?"<<endl<<endl;
        cout<<"==== CHOICES ===="<<endl;
        cout<<"L. Go Left to the ";
        if(world->getCurrentLocation()->previous==NULL)
        {
            cout<<"Carriage Path"<<endl; //If You are at Head of List Display This Option
        }
        else
        {
            cout<<world->getCurrentLocation()->previous->name<<endl;;
        }
        cout<<"R. Go Right to the ";
        if(world->getCurrentLocation()->next==NULL)
        {
            cout<<"Carriage Path"<<endl; //If You are at Tail of List Display this Option
        }
        else
        {
            cout<<world->getCurrentLocation()->next->name<<endl;
        }
        cout<<"E. Explore "<<world->getCurrentLocation()->name<<endl;
        cout<<"H. Display HUB"<<endl;
        cout<<"I. Search Inventory"<<endl;
        cout<<"C. Quit Game"<<endl;
        cout<<"Enter Choice: ";

        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case 'R':
            if(world->getCurrentLocation()->next==NULL) //You are at the tail of the list
            {
                cout<<"Don't J-Walk Across this Path..."<<endl;
            }
            else
            {
                cout<<world->getCurrentLocation()->next->warning<<endl;
            }
            cout<<"Are You Sure You Wish to Proceed"<<endl;
            cout<<"Enter Y or N: ";
            cin>>choice;
            while((choice!='Y')&&(choice!='N'))
            {
                cout<<"Enter Y or N: ";
                cin>>choice;
            }
            if(choice=='Y')
            {
                if(world->getCurrentLocation()->next==NULL)
                {
                    user->loseLife(); //Decrements user lives by One
                    user->setHealth(10); //Replenishes User Health
                    cout<<endl;
                    cout<<"You Got Hit By A Carriage And Lost A Life #ToldYaSo"<<endl;
                }
                else
                {
                    world->setCurrentLocation(world->getCurrentLocation()->next); //Moves User to the Next Node in the Linked List
                }
            }
            cout<<endl;
            break;

        case 'L':
            if(world->getCurrentLocation()->previous==NULL) //You are at the tail of the list
            {
                cout<<"Don't J-Walk Across this Path..."<<endl;
            }
            else
            {
                cout<<world->getCurrentLocation()->previous->warning<<endl;
            }
            cout<<"Are You Sure You Wish to Proceed"<<endl;
            cout<<"Enter Y or N: ";
            cin>>choice;
            while((choice!='Y')&&(choice!='N'))
            {
                cout<<"Enter Y or N: ";
                cin>>choice;
            }
            if(choice=='Y')
            {
                if(world->getCurrentLocation()->previous==NULL)
                {
                    user->loseLife(); //Decrements user lives by One
                    user->setHealth(10);
                    cout<<endl;
                    cout<<"You Got Hit By A Carriage And Lost A Life #ToldYaSo"<<endl;
                }
                else
                {
                    world->setCurrentLocation(world->getCurrentLocation()->previous); //Moves User to the Previous Node in the Linked List
                }
            }
            cout<<endl;
            break;

        case 'E':
            if(world->getCurrentLocation()->accessible) //If room is open
            {
                if((world->getCurrentLocation()->locationCharacter==NULL)&&(!world->getCurrentLocation()->itemFound)) //Allows user to collect item when character cleared and item not found
                {
                    if(world->getCurrentLocation()->name=="Training Arena") //Special case for area with no characters or items
                    {
                        cout<<"You Enter the Arena, And After Many Moons of Lifting You Become Ripped... However You Chose to Skip Leg Day Several Times. Your \"Appearance in Shorts\" Stat Decreases by 10%" <<endl<<endl;
                        world->traverseMap("House of Pi")->accessible=true; //House of Pi Now Open
                        world->getCurrentLocation()->itemFound=true;
                    }
                    else
                    {
                        char choice;
                        cout<<"Open Obligatory Hidden Loot Chest?"<<endl;
                        cout<<"Enter Y or N: ";
                        cin>>choice;
                        while((choice!='Y')&&(choice!='N'))
                        {
                            cout<<"Enter Y or N: ";
                            cin>>choice;
                        }
                        if(choice=='Y')
                        {
                            cout<<"You Found: "<<world->getCurrentLocation()->roomItem->name<<endl;
                            cout<<"==== Stats ===="<<endl;
                            cout<<"Attack Points: "<<world->getCurrentLocation()->roomItem->attackBonus<<endl;
                            cout<<"Defense Points: "<<world->getCurrentLocation()->roomItem->defenseBonus<<endl;
                            cout<<"Health Bonus: "<<world->getCurrentLocation()->roomItem->healthBonus<<"0%"<<endl<<endl;
                            cout<<"Would You Like to Put This Item in Your Inventory?"<<endl;
                            cout<<"Enter Y or N: ";
                            cin>>choice;
                            while((choice!='Y')&&(choice!='N'))
                            {
                                cout<<"Enter Y or N: ";
                                cin>>choice;
                            }
                            if(choice=='Y')
                            {
                                cout<<endl;
                                user->pickUpItem(world->getCurrentLocation()->roomItem); //Adds item to inventory
                                world->getCurrentLocation()->itemFound=true;
                            }
                        }
                    }
                }
                else if((world->getCurrentLocation()->locationCharacter!=NULL)&&(!world->getCurrentLocation()->itemFound)) //Case when character has not been defeated
                {
                    if(world->getCurrentLocation()->name=="House of Pi") //Scenario for house of Pi
                    {
                        cout<<"You Are Let In By the GateKeepers. \"Welcome "<<user->getName()<<"\" They Shout.";
                        cout<<" Inside you see the Shop Keeper Thadius Pounding Back Some Meed. You Approach"<<endl;

                        cout<<"\""<<world->getCurrentLocation()->locationCharacter->getMessage(1)<<user->getName()<<" \""<<endl<<endl;
                        int choice;
                        do
                        {
                            cout<<"==== DIALOGUE TREE ===="<<endl;
                            cout<<"1. Explain Dangers of Excessive Libations"<<endl;
                            cout<<"2. Plead for Him to Leave"<<endl;
                            cout<<"3. Tell Him You Want Him to Stay (* Reverse Psychology *)"<<endl;

                            cout<<"Enter Dialogue Choice: ";
                            cin>>choice;
                            cout<<endl;

                            switch(choice)
                            {
                            case 1:
                                cout<<world->getCurrentLocation()->locationCharacter->getMessage(2)<<endl<<endl;
                                world->getCurrentLocation()->locationCharacter=NULL; //Erases shopkeeper from area
                                world->traverseMap("Market")->accessible=true; //Opens Market
                                break;
                            case 3:
                                cout<<"He Stays"<<endl<<endl;
                                break;
                            default:
                                cout<<"Wrong Choice (*Hint: It's 1*)"<<endl<<endl;
                            }
                        }
                        while(choice!=1);
                    }
                    else if(world->getCurrentLocation()->name=="Market") //Scenario for Market
                    {
                        cout<<"You Are Greeted at the Door by Thadius"<<endl;
                        cout<<world->getCurrentLocation()->locationCharacter->getMessage(1)<<endl<<endl; //Displays Thadius Message
                        world->getCurrentLocation()->locationCharacter=NULL; //Erases Thadius from Area so You Can get Food
                        world->traverseMap("Castle of Knowledge")->accessible=true;
                    }
                    else if((world->getCurrentLocation()->name=="Ye Olde Hill")||(world->getCurrentLocation()->name=="Horse Path")) //Scenario for Combat Areas
                    {
                        cout<<"You Encounter "<<world->getCurrentLocation()->locationCharacter->getName()<<"."<<endl;
                        cout<<"\""<<world->getCurrentLocation()->locationCharacter->getMessage(1)<<"\""<<endl<<endl;
                        game_combat(user,world->getCurrentLocation()->locationCharacter,world); //engage in combat
                    }
                    else if(world->getCurrentLocation()->name=="Castle of Knowledge")
                    {
                        char choice;
                        if(user->inInventory("Nourishment Wrap of Chee-Bah"))
                        {
                            cout<<"\"I Already Told You No One is Getting In\" Says the Book Keeper his Stomach Rumbling"<<endl;
                            cout<<"W. Give Him Your Wrap."<<endl<<endl;
                            cout<<"Enter Choice: ";
                            cin>>choice;
                            cout<<endl;
                            if(choice!='W') //If wrong input selected
                            {
                                cout<<"(* Sigh *). You Know I Have been Programming for Too Long. I'm Just Gonna Say You Hit W"<<endl;
                            }
                            cout<<"\"Oh Thank You "<<user->getName()<<" That Looks Delicious and I am Starving (*Eats Part of Wrap*). But Still No One Is Getting In Here On My Watch... Jeez That Really Dries Out Your Mouth\""<<endl<<endl;
                            if(user->inInventory("Spoiled Burnetts Bottle")) //If user has collected Burnetts bottle
                            {
                                char choice;
                                do
                                {
                                    cout<<"B. Offer Burnetts to BookKeeper"<<endl<<endl;
                                    cout<<"Enter Choice: ";
                                    cin>>choice;
                                    cout<<endl;
                                }
                                while(choice!='B');
                                cout<<"\"Thank You Again "<<user->getName()<<" !\" (*Glug Glug*)"<<endl<<endl;
                                cout<<"... Moments Pass ..."<<endl<<endl;
                                cout<<"\"I Don't Feel So Good I'm Gonna Get Out of Here. Don't Touch Anything!\""<<endl<<endl;
                                world->getCurrentLocation()->locationCharacter=NULL; //Librarian is banished from area
                                world->traverseMap("House of Doom")->accessible=true;
                            }
                        }
                        else //In case they Have access to Cheebah roll but did not equip it
                        {
                            cout<<"\"I Already Told You No One is Getting In\" Says the Book Keeper his Stomach Rumbling"<<endl<<endl;
                        }
                    }
                    else if(world->getCurrentLocation()->name=="House of Doom")
                    {
                        if(!user->inInventory("TextBook of the House of C")) //If user has not picked up textbook
                        {
                            cout<<"I would not Recommend Going in Without Your Textbook"<<endl;
                        }
                        else
                        {
                            cout<<"You Approach COG..."<<endl<<endl;
                            cout<<"\"PUNY APPRENTICE. YOU THINK YOU CAN DEFEAT ME! IT IS TIME YOU LEARNED HUMILITY...\""<<endl;
                            cout<<"COG Rumbles Towards You, The Ground Shaking Under His Mighty Weight..."<<endl;
                            cout<<"\"IF YOU EVEN WISH TO FACE ME YOU MUST FIRST DEFEAT MY ARMY OF PROGRAMMING BUGS!\""<<endl;
                            Character *Bugs=new Character("Computer Bugs",10,1,1,"GOOD LUCK BEATING US WE'RE IMPOSSIBLE TO FIND","NICE WORK BUT WE'LL BE BACK NEXT WEEK");
                            while(Bugs->getHealth()>0)
                            {
                                boss_combat(user,Bugs);  //Must face bugs until they are defeated
                            }
                            delete Bugs; //Deletes bugs once they are defeated
                            cout<<endl;
                            cout<<"COG Lets Out a Mighty Roar"<<endl;
                            cout<<"\"NO MATTER I SHALL SQUASH YOU MYSELF!\""<<endl;
                            boss_combat(user,world->getCurrentLocation()->locationCharacter);
                            cout<<endl;
                            if(world->getCurrentLocation()->locationCharacter->getHealth()==0)//Defeated COG
                            {
                                cout<<"======= CONGRATULATIONS! ========"<<endl;
                                cout<<"YOU HAVE BEAT THE GAME!"<<endl;
                                cout<<"If It Means Anything Just Know I am Proud of You"<<endl;
                                gameWon=true; //Ends game
                            }
                        }
                    }
                }
            }
            else
            {
                cout<<world->getCurrentLocation()->closedMessage<<endl<<endl; //Display Message for When Area is Closed
            }
            break;

        case 'H':
            user->displayHUB();
            break;
        case 'I':
            user->displayInventory();
            break;
        case 'B':
            cout<<"Easter Egg"<<endl<<endl;
        }
    }
    while((choice!='C')&&(!gameWon)&&(user->getLives()!=0)); //Can potentially win game by pressing w
    if(choice=='C')
    {
        cout<<"C stands for chicken... Just Thought You Should Know"<<endl;
    }
    else if(user->getLives()==0)
    {
        cout<<"You Lost a Video Game Designed by Someone in a Freshman Programming Class..."<<endl;
        cout<<"No Words, No Words... They Should Have Brought a Poet"<<endl;
    }
}

void game_combat(Hero *user, Character *enemy, Map *combatArea)
{
    char choice;
    int heroAttack,enemyAttack,heroDefend,enemyDefend; //Initializes combat variables
    do
    {
        cout<<user->getName()<<" Health: "<<user->getHealth()<<"0%"<<endl;
        cout<<enemy->getName()<<" Health: "<<enemy->getHealth()<<"0%"<<endl<<endl;
        cout<<"Weapon: "<<user->getEquippedItemName()<<endl<<endl;
        cout<<"====COMBAT MENU===="<<endl;
        cout<<"A. Attack"<<endl;
        cout<<"D. Defend"<<endl;
        cout<<"E. Equip New Item"<<endl;
        cout<<"R. Run Away"<<endl;

        cout<<"Enter Choice: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case 'A':
            heroAttack=(rand()%2)+user->getAttackPoints(); //Simple Algorithm which Either Increases User Attack By 1 or 0
            enemyDefend=((rand()%2)+enemy->getDefendPoints());
            if(enemyDefend>heroAttack)
            {
                cout<<enemy->getName()<<" Blocked Your Attack and Parried"<<endl<<endl;
                user->setHealth(user->getHealth()-enemy->getDefendPoints()); //Decrement health based on defense of enemy
            }
            else if (enemyDefend==heroAttack)
            {
                cout<<enemy->getName()<<" Blocked Your Attack"<<endl<<endl;
            }
            else if (enemyDefend<heroAttack)
            {
                cout<<"Your Hit Lands..."<<enemy->getName()<<" Has Taken Damage"<<endl<<endl;
                enemy->setHealth(enemy->getHealth()-user->getAttackPoints());
            }
            break;
        case 'D': //Defensive Play
            heroDefend=(rand()%2)+user->getDefendPoints(); //Simple Algorithm which Either Increases User Defend By 1 or 0
            enemyAttack=((rand()%2)+enemy->getAttackPoints());
            if(heroDefend>enemyAttack)
            {
                cout<<"You Blocked "<<enemy->getName()<<"\'s Attack and Parried"<<endl<<endl;
                enemy->setHealth(enemy->getHealth()-user->getDefendPoints());
            }
            else if (heroDefend==enemyAttack)
            {
                cout<<"You Blocked "<<enemy->getName()<<"\'s Attack"<<endl<<endl;
            }
            else if (heroDefend<enemyAttack)
            {
                cout<<enemy->getName()<<"\'s Hit Lands..."<<"You Have Taken Heavy Damage"<<endl<<endl;
                user->setHealth(user->getHealth()-enemy->getAttackPoints());
            }
            break;
        case 'E':
            user->displayInventory();
            break;
        case 'R':
            cout<<"..."<<endl;
            cout<<"I Don't Know What You Expect Me To Say."<<endl<<endl;
            break;
        default:
            cout<<"Please make a valid selection."<<endl;
        }
    }
    while((choice!='R')&&(enemy->getHealth()>0)&&(user->getHealth()>0));
    if(enemy->getHealth()==0)
    {
        cout<<enemy->getMessage(2)<<endl;
        cout<<combatArea->getCurrentLocation()->roomItem->name<<" Added to Inventory"<<endl;
        cout<<"==== Stats ===="<<endl;
        cout<<"Attack Points: "<<combatArea->getCurrentLocation()->roomItem->attackBonus<<endl;
        cout<<"Defense Points: "<<combatArea->getCurrentLocation()->roomItem->defenseBonus<<endl;
        cout<<"Health Bonus: "<<combatArea->getCurrentLocation()->roomItem->healthBonus<<"0%"<<endl<<endl;

        user->pickUpItem(combatArea->getCurrentLocation()->roomItem);
        combatArea->getCurrentLocation()->itemFound=true;
        combatArea->getCurrentLocation()->locationCharacter=NULL;
    }
    else if(user->getHealth()==0)
    {
        cout<<"You Have Lost One Life"<<endl;
        user->loseLife();
        user->setHealth(10); //Replenish Health
    }
}

void boss_combat(Hero *user, Character *enemy)
{
    char choice;
    int heroAttack,enemyAttack,heroDefend,enemyDefend; //Initializes combat variables
    do
    {
        cout<<user->getName()<<" Health: "<<user->getHealth()<<"0%"<<endl;
        cout<<enemy->getName()<<" Health: "<<enemy->getHealth()<<"0%"<<endl<<endl;
        cout<<"Weapon: "<<user->getEquippedItemName()<<endl<<endl;
        cout<<"====COMBAT MENU===="<<endl;
        cout<<"A. Attack"<<endl;
        cout<<"D. Defend"<<endl;
        cout<<"E. Equip New Item"<<endl;

        cout<<"Enter Choice: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case 'A':
            heroAttack=(rand()%2)+user->getAttackPoints(); //Simple Algorithm which Either Increases User Attack By 1 or 0
            enemyDefend=((rand()%2)+enemy->getDefendPoints());
            if(enemyDefend>heroAttack)
            {
                cout<<enemy->getName()<<" Blocked Your Attack and Parried"<<endl<<endl;
                user->setHealth(user->getHealth()-enemy->getDefendPoints()); //Decrement health based on defense of enemy
            }
            else if (enemyDefend==heroAttack)
            {
                cout<<enemy->getName()<<" Blocked Your Attack"<<endl<<endl;
            }
            else if (enemyDefend<heroAttack)
            {
                cout<<"Your Hit Lands..."<<enemy->getName()<<" Has Taken Damage"<<endl<<endl;
                enemy->setHealth(enemy->getHealth()-user->getAttackPoints());
            }
            break;
        case 'D': //Defensive Play
            heroDefend=(rand()%2)+user->getDefendPoints(); //Simple Algorithm which Either Increases User Defend By 1 or 0
            enemyAttack=((rand()%2)+enemy->getAttackPoints());
            if(heroDefend>enemyAttack)
            {
                cout<<"You Blocked "<<enemy->getName()<<"\'s Attack and Parried"<<endl<<endl;
                enemy->setHealth(enemy->getHealth()-user->getDefendPoints());
            }
            else if (heroDefend==enemyAttack)
            {
                cout<<"You Blocked "<<enemy->getName()<<"\'s Attack"<<endl<<endl;
            }
            else if (heroDefend<enemyAttack)
            {
                cout<<enemy->getName()<<"\'s Hit Lands..."<<"You Have Taken Heavy Damage"<<endl<<endl;
                user->setHealth(user->getHealth()-enemy->getAttackPoints());
            }
            break;
        case 'E':
            user->displayInventory();
            break;
        default:
            cout<<"Please make a valid selection."<<endl;
        }
    }
    while((enemy->getHealth()>0)&&(user->getHealth()>0));
    if(enemy->getHealth()==0)
    {
        cout<<enemy->getMessage(2)<<endl;
    }
    else if(user->getHealth()==0)
    {
        cout<<"You Have Lost One Life"<<endl;
        user->loseLife();
        user->setHealth(10); //Replenish Health
    }
}
