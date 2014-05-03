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
../src/doodad/ChestDoodad.h \
../src/entities/Entity.h \
../src/entities/player/Inventory.h \
../src/entities/player/Player.h \
../src/entities/monsters/SkeletonEntity.h \
../src/entities/monsters/GoblinEntity.h \
../src/gameobjects/DoodadObject.h \
../src/gameobjects/EntityObject.h \
../src/gameobjects/GameObject.h \
../src/gameobjects/LootObject.h \
../src/gameobjects/ObjectManager.h \
../src/gameobjects/RoomObject.h \
../src/gameobjects/PlayerObject.h \
../src/gameobjects/ChestDoodadObject.h \
../src/gameobjects/DoorDoodadObject.h \
../src/gameobjects/GoblinEntityObject.h \
../src/items/Affix.h \
../src/items/Equippable.h \
../src/items/Item.h \
../src/main/BaseApplication.h \
../src/main/main.h \
../src/gui/GUIManager.h \
../src/gui/menu/MainMenu.h \
../src/gui/menu/Menu.h \
../src/gui/menu/NewPlayerMenu.h \
../src/gui/menu/OptionsMenu.h \
../src/gui/menu/DeathMenu.h \
../src/gui/menu/LoadingMenu.h \
../src/gui/menu/ingamemenu/AdvancedAttributesPanel.h \
../src/gui/menu/ingamemenu/BasicAttributesPanel.h \
../src/gui/menu/ingamemenu/InGameMenu.h \
../src/gui/menu/ingamemenu/InfoLogPanel.h \
../src/gui/menu/ingamemenu/PlayerAttributesPanel.h \
../src/gui/menu/ingamemenu/PlayerInventoryPanel.h \
../src/utility/Common.h \
../src/utility/ConsoleWriter.h \
../src/utility/MathHelper.h \
../src/utility/KeyMap.h \
../src/utility/StringHelper.h \
../src/utility/TipsUtility.h \
../src/world/Room.h \
../src/world/World.h \
../src/world/Zone.h \
../src/input/InputManager.h \
../src/input/KeyHandler.h \
../src/pcg/RoomGenerator.h \
../src/pcg/ZoneGenerator.h \
../src/sound/SoundEffect.h \
../src/sound/SoundManager.h \
../src/sound/GameSoundEffect.h \
../src/sound/MenuSoundEffect.h



bin_PROGRAMS = rogue
rogue_CPPFLAGS = -std=c++0x -I$(top_srcdir)/../
rogue_SOURCES = ../src/doodad/Doodad.cpp \
../src/entities/Entity.cpp \
../src/entities/player/Inventory.cpp \
../src/entities/player/Player.cpp \
../src/entities/monsters/SkeletonEntity.cpp \
../src/entities/monsters/GoblinEntity.cpp \
../src/gameobjects/ChestDoodadObject.cpp \
../src/gameobjects/EntityObject.cpp \
../src/gameobjects/LootObject.cpp \
../src/gameobjects/ObjectManager.cpp \
../src/gameobjects/RoomObject.cpp \
../src/gameobjects/PlayerObject.cpp \
../src/gameobjects/DoorDoodadObject.cpp \
../src/gameobjects/GoblinEntityObject.cpp \
../src/items/Equippable.cpp \
../src/items/Item.cpp \
../src/main/BaseApplication.cpp \
../src/main/main.cpp \
../src/gui/GUIManager.cpp \
../src/gui/menu/MainMenu.cpp \
../src/gui/menu/Menu.cpp \
../src/gui/menu/NewPlayerMenu.cpp \
../src/gui/menu/OptionsMenu.cpp \
../src/gui/menu/DeathMenu.cpp \
../src/gui/menu/LoadingMenu.cpp \
../src/gui/menu/ingamemenu/AdvancedAttributesPanel.cpp \
../src/gui/menu/ingamemenu/BasicAttributesPanel.cpp \
../src/gui/menu/ingamemenu/InGameMenu.cpp \
../src/gui/menu/ingamemenu/InfoLogPanel.cpp \
../src/gui/menu/ingamemenu/PlayerAttributesPanel.cpp \
../src/gui/menu/ingamemenu/PlayerInventoryPanel.cpp \
../src/world/Room.cpp \
../src/world/World.cpp \
../src/world/Zone.cpp \
../src/input/InputManager.cpp \
../src/input/KeyMap.cpp \
../src/pcg/RoomGenerator.cpp \
../src/pcg/ZoneGenerator.cpp \
../src/sound/SoundEffect.cpp \
../src/sound/SoundManager.cpp \
../src/sound/GameSoundEffect.cpp \
../src/sound/MenuSoundEffect.cpp



rogue_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(SDL_CFLAGS) $(bullet_CFLAGS) $(SDLMIXER_CFLAGS) $(SDLNET_CFLAGS) $(CEGUI_CFLAGS) $(CEGUI_OGRE_CFLAGS)
rogue_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(SDL_LIBS) $(bullet_LIBS) $(SDLMIXER_LIBS) $(SDLNET_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
