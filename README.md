                                Design  Document
===============================================================================
Authors:     Nick Carter (nac568), Alex Ip (ati84), Matt Schwartz (mas7279)
Project:     Final Assignment
Course:      CS 354R - Game Technology
Date:        04.08.2014
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
