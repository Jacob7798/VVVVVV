#include "player.h"
#include "gamestate.h"

struct Player player;

void initPlayer(char x, char y, char faceUp) {
  player.x = x;
  player.y = y;
  player.isAirborne = 0;
  player.isFaceUp = faceUp;
}

void movePlayer() {
  signed char gravityDir = (player.isFaceUp == 1) ? -1 : 1;
  checkAirborne(gravityDir);

  // Airborne movement
  if(player.isAirborne) {
    player.y += gravityDir;
    clampPlayerPos();
    return;
  }

  // Ground movement
  if(leftBtn) {
    if(getTileId(player.x-1, player.y) == air) { player.x--; }
  }
  else if(rightBtn) {
    if(getTileId(player.x+1, player.y) == air) { player.x++; }
  }
  else if(gravityBtn) {
    player.isFaceUp = ~player.isFaceUp;
  }

  clampPlayerPos();
  updatePlayerSprite();
  checkCurTile();
}

// Clamp player position in bounds of the LCD screen
void clampPlayerPos() {
  if(player.y < 1) { player.y = 1; }
  else if(player.y > lcdHeight) { player.y = lcdHeight; }
  if(player.x < 1) { player.x = 1; }
  else if(player.x > lcdWidth) { player.x = lcdWidth; }
}

void updatePlayerSprite() {
  char i;

  signed char gravityDir = (player.isFaceUp == 1) ? -1 : 1;
  short tileId = getTileId(player.x, player.y - gravityDir);
  char playerSprite = player.y % 2 + 2*(1-player.isFaceUp);
  char combinedTile[lcdCharLength];

  // Combine player sprite with upper/lower tile sprite
  for(i = 0; i < lcdCharLength; i++) {
    combinedTile[i] = playerSprites[playerSprite][i] | tileSprites[tileId][i];
  }

  // Write combined tile to memory
  Lcd_Cmd(charEntryMemory);
  for(i = 0; i < lcdCharLength; i++) { Lcd_Chr_Cp(combinedTile[i]); }
  Lcd_Cmd(_LCD_RETURN_HOME);

  // Draw player sprite to LCD screen
  Lcd_Chr((player.y-1)/2 + 1, player.x, 0);
}

// Check if the player is falling or not
void checkAirborne(signed char gravityDir) {
  short below = getTileId(player.x, player.y + gravityDir);
  if(below == undefined) {
    changeGameState(ST_GAMEOVER);
    return;
  }

  player.isAirborne = (below == air) ? 1 : 0;
}

// Check current tile for objectives and dangers
void checkCurTile() {
  short tileId = getTileId(player.y, player.x);
  if(tileId == goal) { changeGameState(ST_GOAL); }
  else if(tileId == spikeU || tileId == spikeD) { changeGameState(ST_GAMEOVER); }
}
