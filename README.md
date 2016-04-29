# biskner_CSCI2270_FinalProject

Project Summary:
My final project is a text adventure game. In it, you are an apprecntice training in computer wizardry, and for your final examination you must defeat the evil troll COG. In order to do so you will need to explore the map to collect weapons, unlock areas, and find your missing spellbook. Specifically, you must traverse the world, solve puzzles, and fight enemies by selecting options from the on screen menu. The project itself functions by allowing objects of class/structure: hero, map, character,location, and item to interact in a main.cpp file by means of their respective public methods.

How to Run:
In order to run you will need a functioning VM and CodeBlocks program. Start by downloading the final project files as a zip from GitHub, subsequently open the .cbp and link all the header and source files together under the project->build options->add files dropdown (excluding hellowold.cpp and the readme as these are not for my project). Finally, make sure that under project->build options you have the project follow -std=c++11. The driver file is main.cpp.

Dependencies:
I use numerous c++ libraries in my program such as vector, cstdlib, and string; consequently, c++11 is necessary to run my project.

System Requirements:
Linux

Group Members:
Blake Biskner

Contributors:
None

Open Issues/ Bugs:
I believe most of the bugs have been fixed; however, if you get the item "Protein of Whey" you can receive unlimited health bonuses by equipping and reequipping it. This was intentional to make the final boss easier, though it may seem like a bug at first. Also the combat system is pretty simple so if you have any ideas let me know. Thank you for your help and enjoy the game.

Technical Requirements:

Class- Hero, Map, Character

Data Structure- Linked List (Used to Construct Map)

Public Methods- Character Contains 10 Public Methods. Further, Hero Inherits these 10 Functions and Adds 8 Other Hero Specific Methods


