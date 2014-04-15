                                Design  Document
===============================================================================
Authors:     Nick Carter (nac568), Alex Ip (ati84), Matt Schwartz (mas7279)
Project:     Final Assignment
Course:      CS 354R - Game Technology
Date:        04.15.2014 (Updated)
===============================================================================

                            First Milestone Update
===============================================================================
Most of the work that we have completed so far has been dedicated to sketching
our a solid design in the code for us to follow for the rest of development. 
However, we do have a runnable application that displays two Room game objects
that were created within the rules of our design.

When our game is completed, we will have no keyboard movement - all the 
movement of the player's character will be via mouse clicks as is typical in 
modern dungeon crawlers. For now, we have enabled left (A) and right (D) 
panning of the camera so that you can see that two rooms are displayed.

I have included a couple of images that lay out some design features that we 
will be implementing in this game.

To summarize, this is what I have designed for our game:
    Firstly, I have segmented the code into two distinct categories: game 
    objects and game mechanics.

    Game Objects
    * An ObjectManager Singleton class manages all of our Game Objects (e.g., 
      Room and Monster objects) and allows for their addition into the game.
      Objects must be added this way so that they can be updated for rendering 
      and allow for input handling from the user's mouse and keyboard. 
    * Game Objects are created by their Game Mechanic counterparts. That is, a
      RoomObject is spawned by the Room class when appropriate.
    * To make this easier, all Game Objects are contained in the gameobjects/
      directory.

    Game Mechanics
    * As previously mentioned, classes that fall into this category have a 
      corresponding Game Object, which is their graphical realization within 
      the game world.
    * I am using a hierarchy of classes to closely mirror the abstract concept
      of the game. 
        - A World class is the entire game world, represented as Game Mechanics
          classes. It contains a Player and is responsible for loading new 
          Zones when the user starts the game and when the user takes a Nexus 
          to another Zone.
        - A Player is an Entity (as is a Monster) with an Inventory of Items 
          and gold.
        - A Zone is a collection of Rooms within the World with at least one
          Nexus.
        - A Room is a collection of Loot (the game world's representation of 
          Items), Entities and Doodads.
        - A Nexus is a stairway or some other means of travel from one Zone to
          the next.
        - A Doodad is an object with which the user can interact, like Chests
          and Doors.  
        - A Chest is a collection of Items.
        - A Door connects two Rooms together.
===============================================================================

                                 Overall Design
===============================================================================
We are planning on making a simple dungeon crawler as our final project. We
will be looking into other dungeon crawlers like Rogue (1980), Diablo and
the like for our inspiration when designing the gameplay. Unlike more 
modern dungeon crawlers (like Diablo 3), our game will not be as action-
oriented; instead, our players will be focused on trying to survive while
descending further and further into an infinite, randomly generated world,
collecting items and fighting monsters.

Like the original Rogue game, our scoring system will be based around the
amount of gold that the player has collected (dropped by monsters) as well
as the level he/she achieves before dying.
===============================================================================

                          Software Architecture & Plan
===============================================================================
Our first goal is to create a very basic engine as we will be starting this
game from scratch as opposed to using our previous game engines. The camera
will be locked from a top-down perspective (as in your typical action RPG)
but we may allow for a mousewheel zoom-in feature if required or desired.

Initially, we will just create one or two hard-coded levels instead of 
procedurally generating them for testing purposes. We may find at a later
date that procedurally generated levels are not going to be implemented
by the deadline and we will end up leaving these hard-coded levels in the 
game.

Our player object will be comprised of several attributes: strength, armor
and health. These can be boosted by items that are randomly generated when
dropped by a monster. 

We plan on using as many textures from the Ogre library as possible, but 
we may have to look other places for textures that we want but aren't in 
the library by default. 

The AI for our monsters will most likely be very rudimentary to begin with
and we may expand it later if we have time. Our goal for the AI is to make
sure that our monsters will eventually find and attack the player when the
player is near enough. As long as the monster doesn't get stuck somewhere 
or ignore the player right in front of it, we will be happy.

We want sound effects for when the player moves and when an attack is 
performed at the very least. We might also get some ambient sound effects
if we are able to find some.

We plan on using Bullet physics for detecting collisions between entity 
hits (e.g., whether the player has hit an enemy when he/she attacks).
===============================================================================

                               Division of Labor
===============================================================================
Nick
    Plans on working on monster and player models for the game. He will
    also be in charge of implementing the physics for collisions with the
    help of Matt. 
    Also will be responsible for creating the GUI for the game.

Alex
    Responsible for locating sound files that we can use in our game.
    Will be looking into AI for our monsters and gathering some textures
    for items and rooms. He will be helping Nick with the GUI stuff. 

Matt
    I will be responsible for implementing a procedurally generated level 
    and item system. I will also need to figure out how to dynamically load
    assets from disk for level generation. I will be figuring out how all
    the game aspects fit together in the code, coming up with the 
    representation/design of our game objects with the help of the other
    team members, when necessary. I plan on coming up with an interface 
    for us to use for communication between our objects.
===============================================================================
