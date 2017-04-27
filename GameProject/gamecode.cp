#line 1 "Z:/home/batman/git/VVVVVV/GameProject/gamecode.c"
#line 1 "z:/home/batman/git/vvvvvv/gameproject/gamestate.h"



typedef enum GameState {
 ST_MENU,
 ST_PAUSE,
 ST_INGAME,
 ST_GOAL,
 ST_GAMEOVER
} GameState;
extern GameState gameState;

void changeGameState(GameState newState);
#line 1 "z:/home/batman/git/vvvvvv/gameproject/lcd.h"
#line 9 "z:/home/batman/git/vvvvvv/gameproject/lcd.h"
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
#line 26 "z:/home/batman/git/vvvvvv/gameproject/lcd.h"
void initLCD();
#line 32 "z:/home/batman/git/vvvvvv/gameproject/lcd.h"
static const char lcdWidth = 20;
static const char lcdHeight = 4;
static const char lcdCharLength = 8;
static const char charEntryMemory = 64;
#line 1 "z:/home/batman/git/vvvvvv/gameproject/menu.h"
#line 9 "z:/home/batman/git/vvvvvv/gameproject/menu.h"
sbit selectBtn at PORTC.B5;
sbit upBtn at PORTC.B6;
sbit downBtn at PORTC.B7;

extern char menuSelection;
extern char prevMenuSelection;
#line 19 "z:/home/batman/git/vvvvvv/gameproject/menu.h"
void loadMenu();
void updateMenu();
void printSelectableLevels(char start);
#line 1 "z:/home/batman/git/vvvvvv/gameproject/levels.h"
#line 1 "z:/home/batman/git/vvvvvv/gameproject/lcd.h"
#line 10 "z:/home/batman/git/vvvvvv/gameproject/levels.h"
void loadLevel(char levelIndex);
short getTileId(char x, char y);
#line 18 "z:/home/batman/git/vvvvvv/gameproject/levels.h"
static char curLevel = 0;
static const char levels[][lcdHeight*2][lcdWidth] = {

 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

 {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

 {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,1,1},
 {0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},

 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1},
 {2,2,0,0,0,0,2,2,2,2,2,2,4,4,4,2,2,2,2,2}},


 {{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
 {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

 {3,3,3,3,3,3,3,3,5,5,5,5,3,3,3,3,3,3,3,3},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

 {0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,4,4,3,3},
 {0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},

 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {3,3,0,0,0,0,3,3,3,3,3,3,4,4,4,3,3,3,3,3}}
};
static const char levelCount = sizeof(levels) / sizeof(levels[0]);


enum Tile {
 undefined = -1,
 air = 0,
 halfBlockU = 1,
 halfBlockL = 2,
 spikeU = 3,
 spikeD = 4,
 start = 5,
 goal = 6
};


static const char tileSprites[][lcdCharLength] = {

 {0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000},


 {0b00011111,
 0b00011111,
 0b00011111,
 0b00011111,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000},


 {0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00011111,
 0b00011111,
 0b00011111,
 0b00011111},


 {0b00011111,
 0b00001110,
 0b00000100,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000},


 {0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000100,
 0b00001110,
 0b00011111},


 {0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000},


 {0b00000000,
 0b00000000,
 0b00000100,
 0b00001110,
 0b00001110,
 0b00000100,
 0b00000000,
 0b00000000},
};
static const char tileCount = sizeof(tileSprites) / sizeof(tileSprites[0]);
#line 1 "z:/home/batman/git/vvvvvv/gameproject/player.h"
#line 1 "z:/home/batman/git/vvvvvv/gameproject/lcd.h"
#line 1 "z:/home/batman/git/vvvvvv/gameproject/levels.h"
#line 11 "z:/home/batman/git/vvvvvv/gameproject/player.h"
sbit gravityBtn at PORTC.B5;
sbit leftBtn at PORTC.B6;
sbit rightBtn at PORTC.B7;

struct Player {
 char x, y;
 char isAirborne, isFaceUp;
};
extern struct Player player;
#line 25 "z:/home/batman/git/vvvvvv/gameproject/player.h"
void initPlayer(char x, char y, char faceUp);
void movePlayer();
void updatePlayerSprite();
void checkAirborne(signed char gravityDir);
void clampPlayerPos();
void playerDied();
void checkCurTile();
#line 38 "z:/home/batman/git/vvvvvv/gameproject/player.h"
static const char playerSprites[][lcdCharLength] = {

 {0b00001010,
 0b00000000,
 0b00010001,
 0b00001110,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000},


 {0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00001010,
 0b00000000,
 0b00010001,
 0b00001110},


 {0b00001110,
 0b00010001,
 0b00000000,
 0b00001010,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000},


 {0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00001110,
 0b00010001,
 0b00000000,
 0b00001010}
};
#line 7 "Z:/home/batman/git/VVVVVV/GameProject/gamecode.c"
GameState gameState = ST_MENU;


void initialize();
void initPIC();
void changeGameState(GameState newState);
void update();


static const char updateInterval = 50;



void main() {
 initialize();
 changeGameState(ST_MENU);
 while(1) { update(); }
}

void initialize() {
 initPIC();
 initLCD();
}

void initPIC() {
 OSCCON = 0b01110111;
 ANSEL = 0b00000000;
 ANSELH = 0b00000000;

 TRISA = 0b00000000;
 TRISB = 0b00000000;
 TRISC = 0b00000000;
 PORTA = 0b00000000;
 PORTB = 0b00000000;
 PORTC = 0b00000000;
}

void changeGameState(GameState newState) {

 if (newState == ST_MENU) {
 loadMenu();

 printSelectableLevels (0);
 }

 gameState = newState;
}


void update() {
 switch(gameState) {
 case ST_MENU:
 updateMenu();
 break;
 case ST_INGAME:
 movePlayer();
 break;
 case ST_PAUSE:
 break;
 case ST_GOAL:
 if(curLevel+1 < levelCount) { loadLevel(curLevel+1); }
 else { changeGameState(ST_MENU); }
 break;
 case ST_GAMEOVER:

 changeGameState(ST_MENU);
 break;
 }
 delay_ms(updateInterval);
}
