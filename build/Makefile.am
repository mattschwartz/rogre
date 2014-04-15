MAIN = ../src/main
DOODADS = ../src/doodad
ENTITIES = ../src/entities
PLAYER = $(ENTITIES)/player
GAME_OBJECTS = ../src/gameobjects
ITEMS = ../src/items
PCG = ../src/pcg
UTILITY = ../src/utility
WORLD = ../src/world

noinst_HEADERS = ../src/doodad/Doodad.h \
				../src/entities/Entity.h \
				../src/entities/player/Inventory.h \
				../src/entities/player/Player.h \
				../src/gameobjects/DoodadObject.h \
				../src/gameobjects/EntityObject.h \
				../src/gameobjects/GameObject.h \
				../src/gameobjects/LootObject.h \
				../src/gameobjects/ObjectManager.h \
				../src/gameobjects/RoomObject.h \
				../src/items/Affix.h \
				../src/items/Equippable.h \
				../src/items/Item.h \
				../src/main/BaseApplication.h \
				../src/main/main.h \
				../src/utility/Common.h \
				../src/utility/ConsoleWriter.h \
				../src/utility/MathHelper.h \
				../src/world/Room.h \
				../src/world/World.h \
				../src/world/Zone.h

bin_PROGRAMS = rogue
rogue_CPPFLAGS = -std=c++0x -I$(top_srcdir)/../
rogue_SOURCES = ../src/doodad/Doodad.cpp \
				../src/entities/Entity.cpp \
				../src/entities/player/Inventory.cpp \
				../src/entities/player/Player.cpp \
				../src/gameobjects/DoodadObject.cpp \
				../src/gameobjects/EntityObject.cpp \
				../src/gameobjects/LootObject.cpp \
				../src/gameobjects/ObjectManager.cpp \
				../src/gameobjects/RoomObject.cpp \
				../src/items/Equippable.cpp \
				../src/items/Item.cpp \
				../src/main/BaseApplication.cpp \
				../src/main/main.cpp \
				../src/pcg/RoomGenerator.cpp \
				../src/world/Room.cpp \
				../src/world/World.cpp \
				../src/world/Zone.cpp

rogue_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(sdl_CFLAGS) $(bullet_CFLAGS)
rogue_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(sdl_LIBS) $(bullet_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign