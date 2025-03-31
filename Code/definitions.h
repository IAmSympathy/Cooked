// ce file se trouve tout nos DEFINE et nos ENUM, il facilite la modification, car nous avons juste a modifier les chiffres d'ici

#pragma once

//GFX
#define WINDOW_SCREEN_WIDTH 1920
#define WINDOW_SCREEN_HEIGHT 1080
#define SPRITE_SIZE_MULTIPLIER 3.4 //! MULTIPLY EVERY SPRITE WITH THIS MULTIPLIER

#define UNDEFINED_VALUE -1

//---------Recipes
enum recipes { PIZZA, HAMBURGER };

#define PIZZA_DRESSING_CHOICES 5 // **** a modifier uniquement si on modifie allPizzaDressing aussi
#define HAMBURGER_DRESSING_CHOICES 4 // **** a modifier uniquement si on modifie HAMBURGER_DRESSING_CHOICES
#define MAX_DRESSING_HAMBURGER 5 // permet de gerer le nombre max de dressing sur un hamburger qui géré aléatoirement dans les commandes
#define MAX_DRESSING_PIZZA	4 //le nombre maximum de dressing pour la pizza, peut pas vraiment changer
#define REWARD_MULTIPLIER 2 // chaque aliment ajoute au repas fait monter son prix de 2$
#define TOTAL_CONDIMENTS_AMOUNT 18 //*** a modifier seulement si on rajoute des aliments
//Draw
#define BREADBOTTOM_HEIGHT 4
#define BREADTOP_HEIGHT 5
#define LETTUCE_HEIGHT 3
#define TOMATO_HEIGHT 2
#define STEAK_HEIGHT 4
#define CHEESE_HEIGHT 2
#define INGREDIENT_MULTIPLIER 4

//---------Stations
enum directions { DOWN, UP, LEFT, RIGHT };
enum ingredients { STEAK, BREAD, TOMATO, LETTUCE, ONION, MUSHROOM, PEPPER, PEPPERONI, CHEESE, PIZZA_DOUGH, OLIVE, CHEESE_SLICE, BREADBOTTOM, TOMATO_SAUCE };
#define PLATE_POSITION_ONE 21
#define PLATE_POSITION_TWO 22
#define PLATE_POSITION_THREE 23
#define PLATE_POSITION_FOUR 24
#define PLATE_POSITION_FIVE 25
#define STATION_TRASH 12
#define STATION_PLATE 13
#define STATION_PLATE_SMALL 14

#define STATION_WIDTH 41
#define STATION_HEIGHT 32
#define STATION_PLATE_WIDTH 34
#define STATION_PLATE_SMALL_WIDTH 26
#define STATION_PLATE_SMALL_HEIGHT 22

//---------Positions
#define POSITION_CLIENT_Y 317
#define POSITION_CLIENT_X 546
#define ESPACE_ENTRE_STATION_CLIENT 207
#define DEFAULT_SPAWN_RATES_FOR_CLIENTS 25 //en secondes

#define ESPACE_ENTRE_PIZZA 206.55
#define ESPACE_ENTRE_BURGER 210.55
#define MEAL_XPOS 500
#define PIZZA_YPOS 75
#define BURGER_YPOS 135



//---------Location of ressources
#define FONT_LOCATION "Cooked!_Data/Font/nintendo-nes-font.ttf"

//Global
#define PATH_AUDIO_MUSIC "Cooked!_Data/Audio/Music/soundtrack"

//In-Game
#define RECIPES_SPRITESHEET_LOCATION "Cooked!_Data/Textures/Recettes.png"
#define STATION_SPRITESHEET_LOCATION "Cooked!_Data/Textures/Stations.png"
#define PLAYER_SPRITESHEET_LOCATION "Cooked!_Data/Textures/Player.png"
#define LEVEL_BACKGROUNDS_LOCATION "Cooked!_Data/Textures/Levels/Level"
#define CLIENT_SPRITESHEET_LOCATION "Cooked!_Data/Textures/Clients.png"

#define SFX_KONAMI_LOCATION "Cooked!_Data/Audio/EE_Konami.mp3"
#define SFX_ENDGAME_LOCATION "Cooked!_Data/Audio/Level_End.mp3"
#define SFX_ORDER_MISSED_LOCATION "Cooked!_Data/Audio/Order_TimeOver.ogg"
#define SFX_PLAYER_INTERACT_LOCATION "Cooked!_Data/Audio/Player_Interact.mp3"
#define SFX_PLAYER_TRASH_LOCATION "Cooked!_Data/Audio/Player_Trash.mp3"
#define SFX_ORDER_PLACE "Cooked!_Data/Audio/Order_Place.wav"
#define SFX_SEND_ORDER_LOCATION "Cooked!_Data/Audio/Order_Send.ogg"
#define SFX_NEW_ORDER_LOCATION "Cooked!_Data/Audio/Order_New.mp3"

//Menu
#define SFX_MENU_BUTTON_MOVE "Cooked!_Data/Audio/Menu_ButtonMove.ogg"
#define GFX_MENU_BACKGROUND "Cooked!_Data/Menu/COOKED.png"
#define GFX_MENU_BACKGROUND2 "Cooked!_Data/Menu/COOKED2.png"
#define GFX_MENU_END_BACKGROUND "Cooked!_Data/Menu/EndScreen.png"

//position, la ou on veut placer les ingredient par ex:
// define positionplayeringredient1width 545
// define positionplayeringredient1height 222
