#include <stdint.h>
#include <stdlib.h>
#include <uzebox.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "data/tileset.inc"
#include "data/rtmaps.inc"
#include "data/marumbi.inc"
#include "data/trollen.inc"
#include "data/theone.inc"
#include "data/patches.inc"
#include "data/zipzipzip.inc"

#define WHITE_NUMBER 16
#define BLUE_NUMBER (-RAM_TILES_COUNT)
#define GREEN_NUMBER (10-RAM_TILES_COUNT)
#define CROSSED_OUT_NUMBER (20-RAM_TILES_COUNT)
#define CPU_DELAY 30
#define STENCH_ROOM 1
#define BREEZE_ROOM 2
#define BOTH_ROOM 3
#define WUMPUS_ROOM 4
#define HOLE_ROOM 5
#define CORRIDOR 6
#define CAVE_WIDTH 12
#define CAVE_HEIGHT 10
#define CAVE_OFFSET_X (VRAM_TILES_H/2-CAVE_WIDTH)
#define CAVE_OFFSET_Y (VRAM_TILES_V/2-CAVE_HEIGHT)
#define MOVE_DELAY 20
#define SHOT_DELAY 6
#define FASTER_DELAY 6
#define NO_TROLL 0
#define V_TROLL 1
#define H_TROLL 2
#define S_TROLL 3
#define TOP_WALL 1
#define RIGHT_WALL 2
#define BOTTOM_WALL 4
#define LEFT_WALL 8
#define MAX_TRAPS 3
#define VICTORY 1
#define DEFEAT 2
#define OUTSIDE 1
#define PEG 2
#define HOLE 3
#define GOOD_CURSOR 0x80
#define BAD_CURSOR 0x40
#define BLINK_DELAY 4
#define MARUMBI_BLUE 235
#define DEFAULT_GRAY 82
#define RED_6 6
#define RED_7 7
#define BROWN 20
#define BLUE_3 (3 << 6)
#define GREEN_3 (3 << 3)
#define TOTAL_CHESTS 26
#define LIMIT_COLOR 126
#define RAM 0
#define FLASH 1
#define COLOR_CHANGE_DELAY 2
#define SKY_COLOR 226
#define TOTAL_CAT_TILES 8
#define CAT_ANIMATION_DELAY 20
#define CAT_MOVE_DELAY 4

const char strGreed[] PROGMEM = "GREED";
const char strPiles[] PROGMEM = "PILES";
const char strGrab[] PROGMEM = "GRAB";
const char str9[] PROGMEM = "9 SQUARES";
const char strGet[] PROGMEM = "GET 3";
const char strGrid[] PROGMEM = "THE GRID";
const char strTrollen [] PROGMEM = "TROLLEN";
const char strEscape[] PROGMEM = "ESCAPE";
const char strAdventure[] PROGMEM = "ADVENTURE";
const char strSlide[] PROGMEM = "SLIDE";
const char strPuzzle[] PROGMEM = "PUZZLE";
const char strAncient[] PROGMEM = "ANCIENT GAME";
const char strOne[] PROGMEM = "THE ONE";
const char strRemove[] PROGMEM = "REMOVE";
const char strTake[] PROGMEM = "TAKE";
const char strMonster[] PROGMEM = "MONSTER";
const char strDungeon[] PROGMEM = "DUNGEON";
const char strHunt[] PROGMEM = "HUNT";
const char strSurvival[] PROGMEM = "SURVIVAL";
const char strAvoider[] PROGMEM = "AVOIDER";
const char strInstinct[] PROGMEM = "INSTINCT";
const char strRain[] PROGMEM = "RAIN";
const char strFalling[] PROGMEM = "FALLING BUTTONS";
const char strReflex[] PROGMEM = "REFLEX";
const char strArray[] PROGMEM = "ARRAY";
const char strSort[] PROGMEM = "SORT";
const char strFast[] PROGMEM = "BE FAST";
const char strRich[] PROGMEM = "RICH";
const char strChests[] PROGMEM = "CHESTS";
const char strDream[] PROGMEM = "DREAM";
const char * const names[] PROGMEM = {
  strGreed, strPiles, strGrab,
  strGrid, strGet, str9,
  strTrollen, strEscape, strAdventure,
  strSlide, strPuzzle, strAncient,
  strOne, strRemove, strTake,
  strMonster, strDungeon, strHunt,
  strSurvival, strAvoider, strInstinct,
  strRain, strFalling, strReflex,
  strArray, strSort, strFast,
  strRich, strChests, strDream
};
const char strVsCpu[] PROGMEM = "VS CPU";
const char strVsHuman[] PROGMEM = "VS HUMAN";
const char strExit[] PROGMEM = "EXIT";
const char strCFlavio[] PROGMEM = "\\ 2016 FL^VIO ZAVAN";
const char strLicense[] PROGMEM = "CODE LICENSED UNDER";
const char strMIT[] PROGMEM = "THE MIT LICENSE";
const char strTurn[] PROGMEM = "PLAYER  'S TURN";
const char strWins[] PROGMEM = "PLAYER   WINS";
const char strStart[] PROGMEM = "START";
const char strStarting[] PROGMEM = "PICK YOUR CHEST";
const char strOpenChest[] PROGMEM = "OPEN A CHEST";
const char strSee[] PROGMEM = "LET'S SEE WHAT";
const char strInside[] PROGMEM = "WAS INSIDE THE CHEST";
const char strPhone[] PROGMEM = "THE PHONE IS RINGING";
const char strBanker[] PROGMEM = "IT'S THE BANKER";
const char strOffer[] PROGMEM = "HE'S OFFERING YOU";
const char strFor[] PROGMEM = "FOR YOUR CHEST";
const char strAccept[] PROGMEM = "ACCEPT";
const char strRefuse[] PROGMEM = "REFUSE";
const char strReceived[] PROGMEM = "YOU RECEIVED";
const char strWantKeep[] PROGMEM = "DO YOU WANT TO KEEP";
const char strChestNo[] PROGMEM = "CHEST    OR DO YOU";
const char strTradeChest[] PROGMEM = "TRADE IT FOR CHEST   ?";
const char strKeep[] PROGMEM = "KEEP";
const char strTrade[] PROGMEM = "TRADE";
const char strInsideDef[] PROGMEM = "WAS INSIDE CHEST";
const char strCongrat[] PROGMEM = "CONGRATULATIONS";
const char strPlayer1[] PROGMEM = "PLAYER 1";
const char strPlayer2[] PROGMEM = "PLAYER 2";
const char strGenerating[] PROGMEM = "GENERATING LEVEL";
const char strWait[] PROGMEM = "PLEASE WAIT";
const char strAte[] PROGMEM = "THE MONSTER ATE YOU";
const char strFell[] PROGMEM = "YOU FELL IN A HOLE";
const char strKill[] PROGMEM = "YOU KILLED THE MONSTER";
const char strLives[] PROGMEM = "LIVES:";
const char strScore[] PROGMEM = "SCORE:";
const char strGameOver[] PROGMEM = "GAME OVER";
const char strDraw[] PROGMEM = "DRAW";
const char strDied[] PROGMEM = "YOU DIED";
const char strRainButtons[] PROGMEM = "<()>ABXYLR";
const char strMonster0[] PROGMEM = "THE MONSTER";
const char strMonster1[] PROGMEM = "ITS STENCH CAN BE";
const char strMonster2[] PROGMEM = "SMELLED TWO ROOMS AWAY";
const char strMonster3[] PROGMEM = "A HOLE";
const char strMonster4[] PROGMEM = "ITS BREEZE CAN BE";
const char strMonster5[] PROGMEM = "FELT A ROOM AWAY";
const char strNoMoves[] PROGMEM = "NO MOVES LEFT";
const char strToggle[] PROGMEM = "PRESS L TO TOGGLE MUSIC";

const char * const batteries[] PROGMEM = {
  battery0Map,
  battery1Map,
  battery2Map,
  battery3Map,
  battery4Map
};
const char * const monsterRooms[] PROGMEM = {
  clearRoomMap,
  redRoomMap,
  greenRoomMap,
  bothRoomMap,
  wumpusMap,
  holeMap,
  corridor1Map,
  corridor2Map,
};

const char * const marumbiMaps[] PROGMEM = {
  NULL,
  marumbi01Map,
  marumbi02Map,
  marumbi03Map,
  marumbi04Map,
  marumbi05Map,
  marumbi06Map,
  marumbi07Map,
  marumbi08Map,
  marumbi09Map,
  marumbi10Map,
  marumbi11Map,
  marumbi12Map,
  marumbi13Map,
  marumbi14Map,
  marumbi15Map,
};

const uint32_t prizes[] PROGMEM = {
  50, 100, 500, 1000, 2500, 5000, 7500, 10000, 20000, 30000, 40000, 50000,
  75000, 100000, 500000, 1000000, 2500000, 5000000, 7500000, 10000000,
  20000000, 30000000, 40000000, 50000000, 75000000, 100000000
};

const uint8_t monsterDx[] PROGMEM = {0, 1, 0, 255};
const uint8_t monsterDy[] PROGMEM = {255, 0, 1, 0};
const uint8_t monsterCor[2][4] PROGMEM = {
  {1, 0, 3, 2},
  {3, 2, 1, 0}
};

const uint8_t catAnimationPixels[][2] PROGMEM = {
  {1, 9},
  {15, 14},
  {62, 54},
  {0, 0},
  {6, 14},
  {8, 9},
  {57, 49},
};

struct int8_t_pair {
  int8_t x, y;
};

struct troll {
  struct int8_t_pair pos;
  uint8_t stun;
  uint8_t type;
};

struct trollenLevel {
  struct int8_t_pair hero;
  struct troll troll[2];
  struct int8_t_pair trap[MAX_TRAPS];
  uint8_t map[6][6];
};

/* A simple sprite for blitting onto a ram tile */
struct simpleSprite {
  uint16_t p;
  uint8_t rt;
  uint8_t bgTile;
  const char *fgTile;
  uint8_t fgSource;
};

extern Track tracks[CHANNELS];
extern bool playSong;
extern uint8_t vram[];
extern char ram_tiles[];
/* Controller Handling */
uint16_t held[2] = {0, 0},
  pressed[2] = {0, 0},
  released[2] = {0, 0},
  prev[2] = {0, 0};

void controllerStart();
void controllerEnd();
void playSound(uint8_t i);
void cutSong();
void copyTileToRam(const char *tt, uint8_t src, uint8_t dst);
void rtMirror(char src, char dst);
void rtRotate90(char src, char dst);
void rtReplaceColor(uint8_t t, char src, char dst);
void rtDrawRectangle(uint8_t t, uint8_t x, uint8_t y, uint8_t w, uint8_t h,
    uint8_t color);
void printColoredByte(uint8_t x, uint8_t y, uint8_t byte, uint8_t base);
void printColoredByte2(uint8_t x, uint8_t y, uint8_t byte, uint8_t base);
void printColoredShort(uint8_t x, uint8_t y, uint16_t byte, uint8_t base);
void loadColoredNumbers();
void ssLoadFromMap(const char *map, struct simpleSprite *ss,
    uint8_t x, uint8_t y, uint8_t baseRt, const char *tt);
void ssSwitchMap(const char *map, struct simpleSprite *ss, const char *tt);
void ssUnblit(struct simpleSprite *ss, uint8_t len);
void ssBlit(struct simpleSprite *ss, uint8_t len);
void ssMove(struct simpleSprite *ss, uint8_t len, int8_t x, int8_t y);
void printMoney(uint8_t x, uint8_t y, uint32_t value, uint8_t base);
void greedLoadBatteryTiles();
void greed(uint8_t human);
uint8_t rainMoveDown(uint8_t player);
void rainShoot(uint8_t player, uint8_t key);
void richDrawStatus(bool *available, uint8_t *order, uint8_t startingChest);
void rich();
uint8_t testSlide(uint8_t *m);
void switchSlide(uint8_t p, uint8_t o, uint8_t *m);
void slide();
void theOneLoadTiles();
void theOneDrawMap(const uint8_t map[9][9]);
bool theOneIsHoleGood(struct int8_t_pair peg, struct int8_t_pair hole,
    const uint8_t map[9][9]);
uint8_t theOneLoadBoard(uint8_t id, uint8_t map[9][9]);
bool theOneGetPossibleMove(uint8_t map[9][9], struct int8_t_pair peg,
    struct int8_t_pair *move);
void theOne(uint8_t boardId);
bool checkConnectivity(uint8_t map[][(CAVE_WIDTH+1)/2]);
void flagAround(uint8_t y, uint8_t x, uint8_t f, uint8_t dist,
  uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2]);
void monsterDrawMap(const uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    bool whole);
void monsterFixSS(struct simpleSprite *ss, uint8_t len);
void loadFrame(uint8_t bgColor, uint8_t offset);
void drawFrame(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t o);
void monsterGenerateLevel(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t *px, uint8_t *py);
void monsterPlay(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y);
uint8_t mapGetVisible(const uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y);
void mapSetVisible(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y);
void mapSetInvisible(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y);
uint8_t mapGetType(const uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y);
void mapSetType(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y, uint8_t t);
void monster();
bool testArray(const int8_t *m);
void gridDrawCursor(int8_t x, int8_t y, uint8_t tile);
int8_t gridCheck(const int8_t l[3][3]);
struct int8_t_pair gridGetMove(int8_t p, int8_t l[3][3]);
void grid(uint8_t human);
void animateCat();
bool survivalMoveDown(uint8_t p, int8_t height[2][10]);
void survival(uint8_t players);
void rain(uint8_t human);
void array(uint8_t human);
void trollenLoadBaseTiles();
void trollenLoadLevel(uint8_t n, struct trollenLevel *level);
void trollenDrawLevel(const struct trollenLevel *level);
void trollenDrawTitle();
uint8_t trollen(uint8_t level);
uint16_t topmenu();
void drawBaseTitle(uint16_t game);
int8_t twoPlayersMenu();
int8_t onePlayerMenu(uint8_t level, uint8_t levels);
int main();

void controllerStart() {
  held[0] = ReadJoypad(0);
  pressed[0] = held[0] & (held[0] ^ prev[0]);
  released[0] = prev[0] & (held[0] ^ prev[0]);

  held[1] = ReadJoypad(1);
  pressed[1] = held[1] & (held[1] ^ prev[1]);
  released[1] = prev[1] & (held[1] ^ prev[1]);
}

void controllerEnd() {
  prev[0] = held[0];
  prev[1] = held[1];
}

void playSound(uint8_t i) {
  TriggerFx(i, 0xff, true);
}

void cutSong() {
  for (uint8_t i = 0; i < CHANNELS; i++) {
    tracks[i].envelopeStep = -128;
  }
  playSong = false;
}

void copyTileToRam(const char *tt, uint8_t src, uint8_t dst) {
  const char *t = tt + 64*src;
  char *rt = ram_tiles + 64*dst;
  for (uint8_t i = 0; i < 64; i++)
    rt[i] = pgm_read_byte(t+i);
}

void rtMirror(char src, char dst) {
  const char *srt = ram_tiles + 64*src;
  char *drt = ram_tiles + 64*dst;
  uint8_t i, j;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      drt[i*8+j] = srt[i*8+(7-j)];
}

void rtRotate90(char src, char dst) {
  const char *srt = ram_tiles + 64*src;
  char *drt = ram_tiles + 64*dst;
  uint8_t i, j;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
      drt[i*8+j] = srt[(7-j)*8+i];
}

void rtReplaceColor(uint8_t t, char src, char dst) {
  char *rt = ram_tiles + 64*t;
  for (uint8_t i = 0; i < 64; i++)
    if (rt[i] == src)
      rt[i] = dst;
}

void rtDrawRectangle(uint8_t t, uint8_t x, uint8_t y, uint8_t w, uint8_t h,
    uint8_t color) {
  uint8_t i;
  uint8_t j;
  char *rt = ram_tiles+64*t+8*y;

  for (i = 0; i < h; i++, rt+=8)
    for (j = 0; j < w; j++)
      rt[x+j] = color;
}

void printColoredByte(uint8_t x, uint8_t y, uint8_t byte, uint8_t base) {
  SetTile(x--, y, base + (byte % 10));

  byte /= 10;
  SetTile(x--, y, (byte? base + (byte % 10) : 0));

  byte /= 10;
  SetTile(x--, y, (byte? base + (byte % 10) : 0));
}

void printColoredByte2(uint8_t x, uint8_t y, uint8_t byte, uint8_t base) {
  /* Print exactly two digits with zero padding */
  SetTile(x--, y, base + (byte % 10));

  byte /= 10;
  SetTile(x--, y, base + (byte % 10));
}

void printColoredShort(uint8_t x, uint8_t y, uint16_t s, uint8_t base) {
  do {
    SetTile(x--, y, base + (s % 10));
    s /= 10;
  } while (s);
}

void loadColoredNumbers() {
  uint8_t i = 0;

  for (i = 0; i < 10; i++) {
    copyTileToRam(tileset, WHITE_NUMBER+i, i);
    rtReplaceColor(i, 255, 168);
    copyTileToRam(tileset, WHITE_NUMBER+i, 10+i);
    rtReplaceColor(10+i, 255, 32);
  }
}

void ssLoadFromMap(const char *map, struct simpleSprite *ss,
    uint8_t x, uint8_t y, uint8_t baseRt, const char *tt) {
  uint8_t w = pgm_read_byte(map++);
  uint8_t h = pgm_read_byte(map++);
  uint8_t i, j, p;
  uint8_t *row = vram + y*VRAM_TILES_H;

  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      ss->p = (y+i)*VRAM_TILES_H + x+j;
      ss->rt = baseRt++;
      ss->bgTile = row[x+j];
      p = pgm_read_byte(map++);
      if (p > 256-RAM_TILES_COUNT) {
        ss->fgSource = RAM;
        p += RAM_TILES_COUNT;
      }
      else
        ss->fgSource = FLASH;
      ss->fgTile = (ss->fgSource == FLASH? tt : ram_tiles) + 64*p;
      ss++;
    }
    row += VRAM_TILES_H;
  }
}

void ssSwitchMap(const char *map, struct simpleSprite *ss, const char *tt) {
  uint8_t w = pgm_read_byte(map++);
  uint8_t h = pgm_read_byte(map++);
  uint8_t i, p;

  ssUnblit(ss, w*h);
  for (i = 0; i < w*h; i++) {
    p = pgm_read_byte(map++);
    if (p > 256-RAM_TILES_COUNT) {
      ss[i].fgSource = RAM;
      p += RAM_TILES_COUNT;
    }
    else
      ss[i].fgSource = FLASH;
    ss[i].fgTile = (ss[i].fgSource == FLASH? tt : ram_tiles) + 64*p;
  }
  ssBlit(ss, w*h);
}

void ssUnblit(struct simpleSprite *ss, uint8_t len) {
  while (len--) {
    vram[ss->p] = ss->bgTile;
    ss++;
  }
}

void ssBlit(struct simpleSprite *ss, uint8_t len) {
  uint8_t i, b;
  char *rt;
  const char *bg;
  bool ram;

  while (len--) {
    rt = ram_tiles + 64*ss->rt;
    ram = ss->bgTile < RAM_TILES_COUNT;
    /* Current tileset info is not available, assume it's tileset */
    bg = (ram? ram_tiles : tileset - 64*RAM_TILES_COUNT) + 64*ss->bgTile;
    for (i = 0; i < 64; i++) {
      b = ss->fgSource == FLASH? pgm_read_byte(ss->fgTile+i) : ss->fgTile[i];
      rt[i] = b == TRANSLUCENT_COLOR? (ram? bg[i] : pgm_read_byte(bg+i)) : b;
    }
    vram[ss->p] = ss->rt;
    ss++;
  }
}

void ssMove(struct simpleSprite *ss, uint8_t len, int8_t x, int8_t y) {
  while (len--) {
    ss->p += VRAM_TILES_H*y + x;
    ss->bgTile = vram[ss->p];
    ss++;
  }
}

void printMoney(uint8_t x, uint8_t y, uint32_t value, uint8_t base) {
  SetTile(x--, y, base + (value % 10));
  value /= 10;

  SetTile(x--, y, base + (value % 10));
  value /= 10;

  SetTile(x--, y, '.' - ' ');

  SetTile(x--, y, base + (value % 10));
  value /= 10;

  while (value) {
    SetTile(x--, y, base + (value % 10));
    value /= 10;
  }

  SetTile(x, y, '$' - ' ');
}

void greedLoadBatteryTiles() {
  uint8_t i, j;
  uint8_t newColors[] = {72, 67, 19, 236};
  uint8_t p = 20;

  for (i = 0; i < 4; i++)
    for (j = 1; j < 6; j++) {
      if (j == 3)
        continue;
      copyTileToRam(tileset, pgm_read_byte(battery0Map+2+j), p);
      rtReplaceColor(p++, 24, newColors[i]);
    }
}

void greed(uint8_t human) {
  uint8_t i, n, t, s, v, w, xor, h, nv, d;
  uint8_t array[5];

  ClearVram();

  /* Randomly generate a new game and draw on the screen */
  for (i = 0; i < 5; i++) {
    array[i] = (random() % 8) + 1;
    PrintByte(5 + 5 * i, 24, array[i], 0);
    for (n = 0; n < array[i]; n++) {
      DrawMap2(3 + 5 * i, 21 - (n << 1),
        (const char *) pgm_read_word(batteries + i));
    }
  }

  t = (human? random() % 2 : 0);
  s = 0;
  w = 0;
  v = 0;
  nv = 0;
  d = 0;
  Print(8, 4, strTurn);
  SetTile(15, 4, WHITE_NUMBER + 1 + t);
  printColoredByte(5, 24, array[0], BLUE_NUMBER);

  while (1) {
    controllerStart();

    /* Select returns to the menu */
    if (pressed[0] & BTN_SELECT) {
      return;
    }

    if (!t || human) {
      if (!s) {
        /* Choosing a pile */
        if (pressed[t] & BTN_RIGHT) {
          greed_move_right:
          playSound(MOVE_SELECTION_PATCH);
          printColoredByte(5 + 5 * w, 24, array[w], WHITE_NUMBER);
          w = (w + 1) % 5;
          printColoredByte(5 + 5 * w, 24, array[w], BLUE_NUMBER);
        }
        else if (pressed[t] & BTN_LEFT) {
          playSound(MOVE_SELECTION_PATCH);
          printColoredByte(5 + 5 * w, 24, array[w], WHITE_NUMBER);
          w = (10 + w - 1) % 5;
          printColoredByte(5 + 5 * w, 24, array[w], BLUE_NUMBER);
        }
        else if (pressed[t] & BTN_A && array[w]) {
          greed_select:
          playSound(MOVE_SELECTION_PATCH);
          s = (t && !human? 2 : 1);
          v = array[w];
          printColoredByte(5 + 5 * w, 24, array[w], GREEN_NUMBER);
        }
      }
      /* Reducing */
      else {
        if (pressed[t] & BTN_DOWN && v) {
          greed_reduce:
          playSound(TAKE_BATTERY_PATCH);
          Fill(3 + 5 * w, 21 - (--v << 1), 3, 2, 0);
          printColoredByte(5 + 5 * w, 24, v, GREEN_NUMBER);
        }
        else if (pressed[t] & BTN_UP && v < array[w]) {
          playSound(PLACE_BATTERY_PATCH);
          DrawMap2(3 + 5 * w, 21 - (v << 1),
            (const char *) pgm_read_word(batteries + w));
          printColoredByte(5 + 5 * w, 24, ++v, GREEN_NUMBER);
        }
        else if (pressed[t] & BTN_B) {
          playSound(PLACE_BATTERY_PATCH);
          for (i = 0; i < array[w]; i++) {
            DrawMap2(3 + 5 * w, 21 - (i << 1),
              (const char *) pgm_read_word(batteries + w));
          }
          s = 0;
          printColoredByte(5 + 5 * w, 24, array[w], BLUE_NUMBER);
        }
        else if (pressed[t] & BTN_A && v < array[w]) {
          greed_apply:
          playSound(TAKE_BATTERY_PATCH);
          array[w] = v;
          printColoredByte(5 + 5 * w, 24, array[w], WHITE_NUMBER);
          w = 0;
          printColoredByte(5, 24, array[0], BLUE_NUMBER);

          s = 0;
          t ^= 1;
          SetTile(15, 4, WHITE_NUMBER + 1 + t);

          /* Check for victory */
          for (i = 0; i < 5; i++) {
            if (array[i]) {
              break;
            }
          }
          if (i == 5) {
            break;
          }

        }
      }
    }
    else {
      /* AI */
      if (!s) {
        s = 1;
        d = CPU_DELAY;

        /* Calculate the play */
        xor = 0;
        for (i = 0; i < 5; i++) {
          xor ^= array[i];
        }

        /* No winning strategy */
        if (!xor) {
          for (i = 0; i < 5; i++) {
            if (array[i]) {
              n = i;
              break;
            }
          }

          nv = array[n] - 1;
          goto greed_finish;
        }

        /* The if is going to be met because xor != 0 */
        for (h = 3; ; h--) {
          if (xor & (1 << h)) {
            break;
          }
        }

        for (i = 0; i < 5; i++) {
          if (array[i] & (1 << h)) {
            n = i;
            break;
          }
        }

        nv = xor ^ array[n];
      }
      else if (s == 1) {
        /* Select the right pile */
        if (d) {
          d--;
          goto greed_finish;
        }

        d = CPU_DELAY;

        if (w != n) {
          goto greed_move_right;
        }
        else {
          goto greed_select;
        }
      }
      else {
        /* Reduce */
        if (d) {
          d--;
          goto greed_finish;
        }

        d = CPU_DELAY;

        if (v != nv) {
          goto greed_reduce;
        }
        else {
          goto greed_apply;
        }
      }
    }

    greed_finish:
    WaitVsync(1);
    controllerEnd();
  }

  /* Announce the winner */
  Fill(5, 4, 20, 1, 0);
  Print(8, 4, strWins);
  SetTile(15, 4, WHITE_NUMBER + 1 + !t);
  playSound(!t && !human? LOSS_PATCH : VICTORY_PATCH);

  /* Wait one of the players to press start */
  while (1) {
    controllerStart();

    if (pressed[0] & BTN_START)
      break;

    WaitVsync(1);
    controllerEnd();
  }
}

void printChests(bool *available) {
  uint8_t y, x, i;

  x = 3;
  y = 4;
  for (i = 0; i < TOTAL_CHESTS; i++) {
    if (!available[i])
      continue;

    DrawMap2(x, y, closedChestMap);
    printColoredByte2(x + 2, y + 1, i, WHITE_NUMBER);

    x += 5;
    if (x > 23) {
      x = 3;
      y += 4;
    }
  }
}

void richDrawStatus(bool *available, uint8_t *order, uint8_t startingChest) {
  uint8_t i;
  uint8_t revOrder[TOTAL_CHESTS];
  for (i = 0; i < TOTAL_CHESTS; i++) {
    revOrder[order[i]] = i;
  }

  for (i = 0; i < TOTAL_CHESTS; i++) {
    printMoney(i < TOTAL_CHESTS/2? 10 : 26, 1+2*(i%(TOTAL_CHESTS/2)),
        pgm_read_dword(prizes+i),
        revOrder[i] == startingChest || available[revOrder[i]]?
        WHITE_NUMBER : CROSSED_OUT_NUMBER);
  }
}

void rich() {
  uint8_t i, n, s, left;
  uint32_t r;
  bool available[TOTAL_CHESTS];
  uint8_t order[TOTAL_CHESTS];
  uint8_t screenChest[TOTAL_CHESTS];
  memset(available, 1, sizeof(available));
  for (i = 0; i < 26; i++)
    order[i] = i;

  /* Generate crossed-out numbers */
  for (i = 0; i < 10; i++) {
    copyTileToRam(tileset, WHITE_NUMBER+i, 20+i);
    rtDrawRectangle(20+i, 0, 3, 8, 2, RED_6);
  }

  /* Randomize */
  for (i = 0; i < 26; i++) {
    n = (random() % (26 - i)) + i;
    s = order[i];
    order[i] = order[n];
    order[n] = s;
  }

  /* Select the starting chest */
  s = 0;
  ClearVram();
  Print(7, 6, strStarting);
  DrawMap2(13, 12, closedChestMap);
  for (bool done = false; !done; ) {
    controllerStart();

    if (pressed[0] & BTN_LEFT) {
      s = (TOTAL_CHESTS - 1+ s) % TOTAL_CHESTS;
      playSound(MOVE_SELECTION_PATCH);
    }
    else if (pressed[0] & BTN_RIGHT) {
      s = (s + 1) % TOTAL_CHESTS;
      playSound(MOVE_SELECTION_PATCH);
    }
    else if (pressed[0] & BTN_SELECT)
      return;
    else if (pressed[0] & BTN_A)
      done = true;

    printColoredByte2(15, 13, s, GREEN_NUMBER);

    WaitVsync(1);
    controllerEnd();
  }
  available[s] = 0;
  playSound(PLACE_BATTERY_PATCH);

  left = 25;
  r = 0;

  /* Play */
  while (left) {
    /* Pick a chest */
    ClearVram();
    Print(9, 2, strOpenChest);
    printChests(available);

    n = 0;
    for (i = 0; i < TOTAL_CHESTS; i++) {
      if (!available[i])
        continue;
      screenChest[n++] = i;
    }

    i = 0;
    for (bool done = false; !done; ) {
      controllerStart();

      printColoredByte2(5+5*(i%5), 5+4*(i/5), screenChest[i], WHITE_NUMBER);

      if (pressed[0] & BTN_RIGHT && i < left-1) {
        i++;
        playSound(MOVE_SELECTION_PATCH);
      }
      else if (pressed[0] & BTN_LEFT && i > 0) {
        i--;
        playSound(MOVE_SELECTION_PATCH);
      }
      else if (pressed[0] & BTN_UP && i >= 5) {
        i -= 5;
        playSound(MOVE_SELECTION_PATCH);
      }
      else if (pressed[0] & BTN_DOWN && i < left-5) {
        i += 5;
        playSound(MOVE_SELECTION_PATCH);
      }
      else if (pressed[0] & BTN_A)
        done = true;
      else if (pressed[0] & BTN_SELECT)
        return;

      printColoredByte2(5+5*(i%5), 5+4*(i/5), screenChest[i], BLUE_NUMBER);

      WaitVsync(1);
      controllerEnd();
    }
    playSound(PLACE_BATTERY_PATCH);

    /* Open the chest */
    i = screenChest[i];
    left--;
    available[i] = 0;

    ClearVram();
    Print(8, 5, strSee);
    Print(5, 6, strInside);
    DrawMap2(13, 12, closedChestMap);
    WaitVsync(60);
    DrawMap2(13, 12, openChestMap);
    printMoney(19, 10, pgm_read_dword(prizes + order[i]), WHITE_NUMBER);
    playSound(order[i] > 13? LOSS_PATCH : VICTORY_PATCH);

    for (bool done = false; !done; ) {
      controllerStart();

      if (pressed[0] & BTN_A)
        done = true;
      else if (pressed[0] & BTN_SELECT)
        return;

      WaitVsync(1);
      controllerEnd();
    }

    /* Show status */
    ClearVram();
    richDrawStatus(available, order, s);
    WaitVsync(30);
    for (bool done = false; !done; ) {
      controllerStart();

      if (pressed[0] & BTN_A) {
        done = true;
      }
      else if (pressed[0] & BTN_SELECT) {
        controllerEnd();
        return;
      }

      WaitVsync(1);
      controllerEnd();
    }

    /* Offer */
    if (left != 20 && left != 15 && left != 10 && left != 6 && left != 4
      && left != 2 && left != 1) {

      continue;
    }

    /* Switch chests */
    if (left == 1) {
      ClearVram();

      for (i = 0; !available[i]; i++);

      Print(6, 6, strWantKeep);
      Print(6, 7, strChestNo);
      printColoredByte2(13, 7, s, WHITE_NUMBER);
      Print(4, 8, strTradeChest);
      printColoredByte2(24, 8, i, WHITE_NUMBER);
      Print(12, 15, strKeep);
      Print(12, 16, strTrade);
      SetTile(10, 15, ARROW_TILE);

      n = 0;
      for (bool done = false; !done; ) {
        controllerStart();

        if (pressed[0] & BTN_A)
          done = true;
        else if (pressed[0] & BTN_DOWN || pressed[0] & BTN_UP) {
          SetTile(10, 15 + n, 0);
          n ^= 1;
          SetTile(10, 15 + n, ARROW_TILE);
          playSound(MOVE_SELECTION_PATCH);
        }
        else if (pressed[0] & BTN_SELECT)
          return;

        WaitVsync(1);
        controllerEnd();
      }
      playSound(PLACE_BATTERY_PATCH);

      if (n) {
        s ^= i;
        i ^= s;
        s ^= i;
      }
      r = pgm_read_dword(prizes + order[s]);
      left--;

      /* Animate the opening */
      ClearVram();
      Print(8, 5, strSee);
      Print(5, 6, strInsideDef);
      printColoredByte2(23, 6, i, WHITE_NUMBER);
      DrawMap2(13, 12, closedChestMap);

      WaitVsync(60);

      DrawMap2(13, 12, openChestMap);
      printMoney(19, 10, pgm_read_dword(prizes + order[i]),
        WHITE_NUMBER);
      playSound(order[i] > 13? LOSS_PATCH : VICTORY_PATCH);

      /* Wait for the input */
      for (bool done = false; !done; ) {
        controllerStart();

        if (pressed[0] & BTN_A)
          done = true;
        else if (pressed[0] & BTN_SELECT)
          return;

        WaitVsync(1);
        controllerEnd();
      }
    }
    else {
      /* Calculate the average */
      r = 0;
      n = 0;
      for (i = 0; i < 26; i++) {
        if (available[i] || i == s) {
          r += pgm_read_dword(prizes + order[i]);
          n++;
        }
      }
      r /= (uint32_t) n;

      /* Banker animation */
      ClearVram();
      DrawMap2(13, 13, phoneMap);
      playSound(PHONE_PATCH);
      WaitVsync(120);
      playSound(PHONE_PATCH);
      Print(6, 4, strPhone);
      WaitVsync(60);
      Print(8, 5, strBanker);
      WaitVsync(60);
      Print(7, 7, strOffer);
      WaitVsync(60);
      printMoney(20, 8, r, WHITE_NUMBER);
      Print(8, 9, strFor);
      WaitVsync(60);
      Print(12, 18, strAccept);
      Print(12, 19, strRefuse);
      SetTile(10, 18, ARROW_TILE);

      /* Read the input */
      i = 0;
      for (bool done = false; !done; ) {
        controllerStart();

        if (pressed[0] & BTN_A) {
          done = true;
          if (!i)
            left = 0;
        }
        else if (pressed[0] & BTN_UP || pressed[0] & BTN_DOWN) {
          SetTile(10, 18 + i, 0);
          i ^= 1;
          SetTile(10, 18 + i, ARROW_TILE);
          playSound(MOVE_SELECTION_PATCH);
        }
        else if (pressed[0] & BTN_SELECT)
          return;

        WaitVsync(1);
        controllerEnd();
      }
    }
    playSound(PLACE_BATTERY_PATCH);
  }

  ClearVram();
  playSound(VICTORY_PATCH);
  Print(8, 6, strCongrat);
  Print(10, 7, strReceived);
  printMoney(20, 9, r, WHITE_NUMBER);
  DrawMap2(13, 11, openChestMap);

  while (1) {
    controllerStart();

    if (pressed[0] & BTN_START) {
      controllerEnd();
      break;
    }

    WaitVsync(1);
    controllerEnd();
  }
}

uint8_t testSlide(uint8_t *m) {
  int i;
  for (i = 0; i < 16; i++) if (m[i] != i) return 0;
  return 1;
}

void switchSlide(uint8_t p, uint8_t o, uint8_t *m) {
  m[p] = m[o];
  m[o] = 0;

  uint8_t xx = (p&3)*6+3;
  uint8_t yy = (p>>2)*5+4;
  uint8_t x = (o&3)*6+3;
  uint8_t y = (o>>2)*5+4;

  while (x != xx || y != yy) {
    Fill(x, y, 6, 5, -RAM_TILES_COUNT);

    if (x < xx)
      x++;
    else if (x > xx)
      x--;
    else if (y > yy)
      y--;
    else
      y++;

    DrawMap2(x, y, (const char *) pgm_read_word(marumbiMaps+m[p]));

    WaitVsync(4);
  }

}

void slide() {
  uint8_t m[16];
  uint8_t i, p;

  /* Randomize the board */
  for (i = 0; i < 16; i++)
    m[i] = i;
  for (i = 0; i < 15; i++) {
    p = (random() % (16 - i)) + i;
    if (p != i) {
      m[p] ^= m[i];
      m[i] ^= m[p];
      m[p] ^= m[i];
    }
  }
  if (testSlide(m)) {
    m[0] = 1;
    m[1] = 0;
  }
  for (p = 0; m[p]; p++);

  /* Draw the initial state */
  copyTileToRam(marumbi, 0, 0);
  rtReplaceColor(0, MARUMBI_BLUE, DEFAULT_GRAY);
  memset(vram, 0, VRAM_TILES_H*VRAM_TILES_V);
  drawFrame(3, 4, 6*4, 5*4, 30);
  for (i = 0; i < 16; i++) {
    if (m[i])
      DrawMap2((i & 3) * 6 + 3, (i >> 2) * 5 + 4,
        (const char *) pgm_read_word(marumbiMaps+m[i]));
  }

  /* Process the input */
  while (!testSlide(m)) {
    controllerStart();

    if (pressed[0] & BTN_UP && (p >> 2) < 3) {
      playSound(SLIDE_VERTICAL_PATCH);
      switchSlide(p, p + 4, m);
      p += 4;
    }
    else if (pressed[0] & BTN_DOWN && p >> 2) {
      playSound(SLIDE_VERTICAL_PATCH);
      switchSlide(p, p - 4, m);
      p -= 4;
    }
    else if (pressed[0] & BTN_LEFT && (p & 3) < 3) {
      playSound(SLIDE_HORIZONTAL_PATCH);
      switchSlide(p, p + 1, m);
      p += 1;
    }
    else if (pressed[0] & BTN_RIGHT && p & 3) {
      playSound(SLIDE_HORIZONTAL_PATCH);
      switchSlide(p, p - 1, m);
      p -= 1;
    }
    else if (pressed[0] & BTN_SELECT)
      return;

    WaitVsync(1);
    controllerEnd();
  }

  /* Winning screen */
  Fill(3, 4, 6, 5, 0);
  playSound(VICTORY_PATCH);
  for (bool done = false; !done; ) {
    controllerStart();

    if (pressed[0] & BTN_START)
      done = true;

    WaitVsync(1);
    controllerEnd();
  }
}

void theOneLoadTiles() {
  uint8_t i, j;
  uint8_t newColors[] = {DEFAULT_GRAY, BLUE_3};

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      copyTileToRam(tileset, pgm_read_byte(badPegMap+2+j), 2*i+j);
      rtReplaceColor(2*i+j, RED_7, newColors[i]);
    }
    for (j = 0; j < 2; j++) {
      copyTileToRam(tileset, pgm_read_byte(badPegHoleMap+2+j), 2*(i+2)+j);
      rtReplaceColor(2*(i+2)+j, RED_7, newColors[i]);
    }
  }
}

void theOneDrawMap(const uint8_t map[9][9]) {
  for (uint8_t i = 0; i < 9; i++)
    for (uint8_t j = 0; j < 9; j++) {
      if (map[i][j] == OUTSIDE)
        continue;
      DrawMap2(2+3*j, 5+i*2,
          (map[i][j] & 0xf) == HOLE?
          (map[i][j] & GOOD_CURSOR?
             goodPegHoleMap : (map[i][j] & BAD_CURSOR?
               badPegHoleMap : pegHoleMap))
          : (map[i][j] & GOOD_CURSOR?
             goodPegMap : (map[i][j] & BAD_CURSOR?
               badPegMap : pegMap)));
    }
}

bool theOneIsHoleGood(struct int8_t_pair peg, struct int8_t_pair hole,
    const uint8_t map[9][9]) {
  if ((peg.x != hole.x && peg.y != hole.y)
      || (abs(peg.x-hole.x) + abs(peg.y-hole.y) != 2))
    return false;

  if (peg.x > hole.x && (map[peg.y][peg.x-1] & 0xf) != PEG)
    return false;
  else if (peg.x < hole.x && (map[peg.y][peg.x+1] & 0xf) != PEG)
    return false;
  else if (peg.y > hole.y && (map[peg.y-1][peg.x] & 0xf) != PEG)
    return false;
  else if (peg.y < hole.y && (map[peg.y+1][peg.x] & 0xf) != PEG)
    return false;

  return true;
}

uint8_t theOneLoadBoard(uint8_t id, uint8_t map[9][9]) {
  uint8_t pegs = 0;
  const uint8_t *b = theOneBoards[id];

  /* The last element is not stored, it's always outside and would cost an
   * extra byte for each board */
  map[8][8] = OUTSIDE;
  for (uint8_t i = 0; i < (9*9)-1; i++) {
    if (i && !(i % 8))
      b++;
    map[i/9][i%9] = (pgm_read_byte(b) >> (7-(i%8))) & 1? PEG : OUTSIDE;
    if (map[i/9][i%9] != OUTSIDE)
      pegs++;
  }
  map[4][4] = HOLE;

  return pegs;
}

bool theOneGetPossibleMove(uint8_t map[9][9], struct int8_t_pair peg,
    struct int8_t_pair *move) {
  struct int8_t_pair hole;

  for (hole.y = 0; hole.y < 9; hole.y++)
    for (hole.x = 0; hole.x < 9; hole.x++)
      if ((map[hole.y][hole.x] & 0xf) == HOLE
          && theOneIsHoleGood(peg, hole, map)) {
        *move = hole;
        return true;
      }

  return false;
}

void theOne(uint8_t boardId) {
  uint8_t map[9][9];
  uint8_t pegs = theOneLoadBoard(boardId, map);
  struct int8_t_pair nc, peg, hole, possibleMove;
  struct int8_t_pair c = (struct int8_t_pair) {4, 4};
  bool moves = true;

  ClearVram();
  Fill(2, 5, 3*9-2, 2*9, WOODEN_TILE);
  drawFrame(2, 5, 3*9-2, 2*9, 30);
  theOneDrawMap(map);

  while (pegs > 1 && moves) {
    /* Picking the peg */
    peg.x = -1;
    nc = c;
    map[c.y][c.x] |= ((map[c.y][c.x] & 0xf) != HOLE
        && theOneGetPossibleMove(map, c, &possibleMove)?
        GOOD_CURSOR : BAD_CURSOR);
    while (peg.x == -1) {
      controllerStart();

      theOneDrawMap(map);

      if (pressed[0] & BTN_SELECT)
        return;
      else if (pressed[0] & BTN_UP)
        nc.y--;
      else if (pressed[0] & BTN_RIGHT)
        nc.x++;
      else if (pressed[0] & BTN_DOWN)
        nc.y++;
      else if (pressed[0] & BTN_LEFT)
        nc.x--;

      if ((nc.x != c.x || nc.y != c.y)) {
        if (nc.x >= 0 && nc.x < 9 && nc.y >= 0 && nc.y < 9
            && map[nc.y][nc.x] != OUTSIDE) {
          playSound(MOVE_SELECTION_PATCH);
          map[c.y][c.x] &= 0xf;
          c = nc;
          map[c.y][c.x] |= (map[c.y][c.x] == HOLE
              || !theOneGetPossibleMove(map, c, &possibleMove)?
              BAD_CURSOR : GOOD_CURSOR);
        }
        else
          nc = c;
      }
      else if (pressed[0] & BTN_A) {
        if ((map[c.y][c.x] & GOOD_CURSOR)) {
          peg = c;
          playSound(PLACE_BATTERY_PATCH);
        }
        else {
          playSound(TAKE_BATTERY_PATCH);
        }
      }

      WaitVsync(1);
      controllerEnd();
    }

    /* Picking the hole */
    c = possibleMove;
    map[c.y][c.x] |= (map[c.y][c.x] == HOLE && theOneIsHoleGood(peg, c, map)?
        GOOD_CURSOR : BAD_CURSOR);
    hole.x = -1;
    nc = c;
    while (hole.x == -1) {
      controllerStart();

      theOneDrawMap(map);

      if (pressed[0] & BTN_SELECT)
        return;
      else if (pressed[0] & BTN_UP)
        nc.y--;
      else if (pressed[0] & BTN_RIGHT)
        nc.x++;
      else if (pressed[0] & BTN_DOWN)
        nc.y++;
      else if (pressed[0] & BTN_LEFT)
        nc.x--;
      else if (pressed[0] & BTN_B) {
        playSound(TAKE_BATTERY_PATCH);
        break;
      }

      if ((nc.x != c.x || nc.y != c.y)) {
        if (nc.x >= 0 && nc.x < 9 && nc.y >= 0 && nc.y < 9
            && (nc.x != peg.x || nc.y != peg.y)
            && map[nc.y][nc.x] != OUTSIDE) {
          playSound(MOVE_SELECTION_PATCH);
          map[c.y][c.x] &= 0xf;
          map[nc.y][nc.x] |= (map[nc.y][nc.x] == HOLE
              && theOneIsHoleGood(peg, nc, map)?
              GOOD_CURSOR : BAD_CURSOR);
          c = nc;
        }
        else {
          nc = c;
        }
      }
      else if (pressed[0] & BTN_A) {
        if ((map[c.y][c.x] & GOOD_CURSOR))
          hole = c;
        else
          playSound(TAKE_BATTERY_PATCH);
      }

      WaitVsync(1);
      controllerEnd();
    }

    if (hole.x != -1) {
      map[peg.y][peg.x] = HOLE;
      map[hole.y][hole.x] = PEG;
      c = hole;
      pegs--;
      playSound(GETS_PIECE_PATCH);

      if (peg.x > hole.x)
        map[peg.y][peg.x-1] = HOLE;
      else if (peg.x < hole.x)
        map[peg.y][peg.x+1] = HOLE;
      else if (peg.y < hole.y)
        map[peg.y+1][peg.x] = HOLE;
      else if (peg.y > hole.y)
        map[peg.y-1][peg.x] = HOLE;
    }
    else {
      map[c.y][c.x] &= 0xf;
      c = peg;
    }

    moves = false;
    for (nc.y = 0; nc.y < 9; nc.y++)
      for (nc.x = 0; nc.x < 9; nc.x++)
        if ((map[nc.y][nc.x] & 0xf) == PEG
            && theOneGetPossibleMove(map, nc, &possibleMove))
          moves = true;
  }

  theOneDrawMap(map);
  Print(8, 12, pegs == 1? strCongrat : strNoMoves);
  playSound(pegs == 1? VICTORY_PATCH : LOSS_PATCH);
  for (bool done = false; !done; ) {
    controllerStart();

    if (pressed[0] & BTN_START)
      done = true;

    WaitVsync(1);
    controllerEnd();
  }
}

bool checkConnectivity(uint8_t map[][(CAVE_WIDTH+1)/2]) {
  uint8_t y, x, i, xx, yy, d;
  uint8_t yxType, yyxxType;
  uint8_t added = true, good = true;

  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (mapGetType(map, x, y) == HOLE_ROOM
          || mapGetType(map, x, y) >= CORRIDOR)
        continue;
      mapSetVisible(map, x, y);
      goto first_room_found;
    }
  }

  first_room_found:
  while(added) {
    added = false;
    for (y = 0; y < CAVE_HEIGHT; y++) {
      for (x = 0; x < CAVE_WIDTH; x++) {
        /* Using visible to signal it being visited */
        yxType = mapGetType(map, x, y);
        if (!mapGetVisible(map, x, y)
            || yxType == HOLE_ROOM || yxType >= CORRIDOR)
          continue;

        for (i = 0; i < 4; i++) {
          d = i;
          xx = x;
          yy = y;
          do {
            yy = yy + CAVE_HEIGHT + pgm_read_byte(monsterDy+d);
            yy %= CAVE_HEIGHT;
            xx = xx + CAVE_WIDTH + pgm_read_byte(monsterDx+d);
            xx %= CAVE_WIDTH;
            yyxxType = mapGetType(map, xx, yy);
            if (!mapGetVisible(map, xx, yy)) {
              mapSetVisible(map, xx, yy);
              added = true;
            }
            if (yyxxType >= CORRIDOR)
              d = pgm_read_byte(monsterCor[yyxxType-CORRIDOR]+d);
          } while(yyxxType >= CORRIDOR);
        }
      }
    }
  }

  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (!mapGetVisible(map, x, y))
        good = false;
      mapSetInvisible(map, x, y);
    }
  }

  return good;
}

void flagAround(uint8_t y, uint8_t x, uint8_t f, uint8_t dist,
  uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2]) {
  uint8_t yy, xx, i, d, t;

  for (i = 0; i < 4; i++) {
    yy = y + CAVE_HEIGHT + pgm_read_byte(monsterDy+i);
    yy %= CAVE_HEIGHT;
    xx = x + CAVE_WIDTH + pgm_read_byte(monsterDx+i);
    xx %= CAVE_WIDTH;
    d = i;
    while (mapGetType(map, xx, yy) >= CORRIDOR) {
      d = pgm_read_byte(monsterCor[mapGetType(map, xx, yy) - CORRIDOR]+d);
      yy = yy + CAVE_HEIGHT + pgm_read_byte(monsterDy+d);
      yy %= CAVE_HEIGHT;
      xx = xx + CAVE_WIDTH + pgm_read_byte(monsterDx+d);
      xx %= CAVE_WIDTH;
    }

    t = mapGetType(map, xx, yy);
    if (t <= BOTH_ROOM) {
      mapSetType(map, xx, yy, t | f);
      if (dist > 1)
        flagAround(yy, xx, f, dist - 1, map);
    }
  }
}

void monsterDrawMap(const uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    bool whole) {
  uint8_t i, n;

  for (i = 0; i < CAVE_HEIGHT; i++) {
    for (n = 0; n < CAVE_WIDTH; n++) {
      if (whole || mapGetVisible(map, n, i)) {
        DrawMap2(CAVE_OFFSET_X + n*2,
          CAVE_OFFSET_Y + i*2,
          (const char *) pgm_read_word(monsterRooms + mapGetType(map, n, i)));
      }
      else
        Fill(CAVE_OFFSET_X + n*2, CAVE_OFFSET_Y + i*2, 2, 2, 0);
    }
  }
}

void monsterFixSS(struct simpleSprite *ss, uint8_t len) {
  uint8_t i, x, y;

  for (i = 0; i < len; i++, ss++) {
    x = ss->p % VRAM_TILES_H;
    y = ss->p / VRAM_TILES_H;

    if (x >= CAVE_OFFSET_X+2*CAVE_WIDTH)
      x -= 2*CAVE_WIDTH;
    else if (x < CAVE_OFFSET_X)
      x += 2*CAVE_WIDTH;

    if (y >= CAVE_OFFSET_Y+2*CAVE_HEIGHT)
      y -= 2*CAVE_HEIGHT;
    else if (y < CAVE_OFFSET_Y)
      y += 2*CAVE_HEIGHT;

    ss->p = y*VRAM_TILES_H + x;
    ss->bgTile = vram[ss->p];
  }
}

void loadFrame(uint8_t bgColor, uint8_t offset) {
  uint8_t i;

  copyTileToRam(tileset, BORDER_CORNER, offset);
  rtReplaceColor(offset, SKY_COLOR, bgColor);
  copyTileToRam(tileset, BORDER_STRAIGHT, offset+1);

  for (i = 0; i < 6; i++)
    rtRotate90(offset+i, offset+i+2);
}

void drawFrame(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t o) {
  SetTile(x-1, y-1, o-RAM_TILES_COUNT);
  Fill(x, y-1, w, 1, o+1-RAM_TILES_COUNT);
  SetTile(x+w, y-1, o+2-RAM_TILES_COUNT);
  Fill(x+w, y, 1, h, o+3-RAM_TILES_COUNT);
  SetTile(x+w, y+h, o+4-RAM_TILES_COUNT);
  Fill(x, y+h, w, 1, o+5-RAM_TILES_COUNT);
  SetTile(x-1, y+h, o+6-RAM_TILES_COUNT);
  Fill(x-1, y, 1, h, o+7-RAM_TILES_COUNT);
}

void monsterGenerateLevel(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t *px, uint8_t *py) {
  uint8_t n, l, i, t, y, x, tt;

  generate_cave:
  memset(map, 0, CAVE_HEIGHT*((CAVE_WIDTH+1)/2));
  /* Corridors */
  n = (random() % (CAVE_WIDTH*CAVE_HEIGHT)/4) + (CAVE_WIDTH*CAVE_HEIGHT)/2;
  l = CAVE_WIDTH * CAVE_HEIGHT;
  for (i = 0; i < n; i++) {
    /* Remove the t-th clean room */
    t = random() % l;
    for (y = 0; y < CAVE_HEIGHT; y++) {
      for (x = 0; x < CAVE_WIDTH; x++) {
        if (!mapGetType(map, x, y) && !(t--)) goto tth_found;
      }
    }
    tth_found:
    l--;
    tt = CORRIDOR + (random() & 1);
    mapSetType(map, x, y, tt);
  }

  /* Holes */
  n = (random() % 8) + 1;
  for (i = 0; i < n; i++) {
    /* Make the t-th clean room a hole */
    t = random() % l;
    for (y = 0; y < CAVE_HEIGHT; y++) {
      for (x = 0; x < CAVE_WIDTH; x++) {
        if (mapGetType(map, x, y) <= BOTH_ROOM && !(t--)) goto tth_found_hole;
      }
    }
    tth_found_hole:
    l--;
    mapSetType(map, x, y, HOLE_ROOM);
    /* Put the breeze on the adjacent rooms */
    flagAround(y, x, BREEZE_ROOM, 1, map);
  }

  /* Wumpus */
  t = random() % l;
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (mapGetType(map, x, y) <= BOTH_ROOM && !(t--)) goto tth_found_wumpus;
    }
  }
  tth_found_wumpus:
  mapSetType(map, x, y, WUMPUS_ROOM);
  /* Put the stench on the adjacent rooms */
  flagAround(y, x, STENCH_ROOM, 2, map);

  /* Guy */
  i = 0;
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (!mapGetType(map, x, y)) i++;
    }
  }
  t = random() % i;
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (!mapGetType(map, x, y) && !(t--)) goto tth_found_guy;
    }
  }
  /* This shouldn't happen, but just in case there are no clean rooms */
  goto generate_cave;
  tth_found_guy:
  *px = x;
  *py = y;

  /* Only accept connected graphs */
  if (!checkConnectivity(map)) goto generate_cave;
}

void monsterPlay(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y) {
  uint8_t d, yy, xx;
  uint8_t shooting = 0;
  int8_t nx, ny, ox, oy;
  struct simpleSprite sSprites[8];
  bool needsRedraw = true;

  mapSetVisible(map, x, y);

  /* Process input */
  memset(vram, SKY_TILE+RAM_TILES_COUNT, VRAM_TILES_H*VRAM_TILES_V);
  drawFrame(CAVE_OFFSET_X, CAVE_OFFSET_Y, CAVE_WIDTH*2, CAVE_HEIGHT*2, 30);
  Fill(CAVE_OFFSET_X, CAVE_OFFSET_Y, CAVE_WIDTH*2, CAVE_HEIGHT*2, 0);
  FadeIn(3, true);

  while (1) {
    /* Redraw */
    if (!shooting && needsRedraw) {
      monsterDrawMap(map, false);
      ssLoadFromMap(guyMap, sSprites,
          CAVE_OFFSET_X+x*2, CAVE_OFFSET_Y+y*2, 0, tileset);
      ssBlit(sSprites, 4);
      needsRedraw = false;
    }

    /* Draw the targets if shooting */
    for (d = 0; shooting && d < 4; d++) {
      yy = y + CAVE_HEIGHT + pgm_read_byte(monsterDy+d);
      yy %= CAVE_HEIGHT;
      xx = x + CAVE_WIDTH + pgm_read_byte(monsterDx+d);
      xx %= CAVE_WIDTH;

      DrawMap2(CAVE_OFFSET_X + xx*2,
        CAVE_OFFSET_Y + yy*2,
        targetMap);
    }
    /* End game */
    if (mapGetType(map, x, y) >= WUMPUS_ROOM)
      break;

    controllerStart();
    d = 0xff;

    if (pressed[0] & BTN_UP) {
      d = 0;
    }
    else if (pressed[0] & BTN_RIGHT) {
      d = 1;
    }
    else if (pressed[0] & BTN_DOWN) {
      d = 2;
    }
    else if (pressed[0] & BTN_LEFT) {
      d = 3;
    }
    else if (pressed[0] & BTN_A) {
      needsRedraw = true;
      shooting ^= 1;
    }
    else if (pressed[0] & BTN_SELECT) {
      return;
    }

    /* Moving */
    if (d != 0xff) {
      needsRedraw = true;
      yy = y;
      xx = x;
      do {
        ox = CAVE_OFFSET_X+x*2;
        oy = CAVE_OFFSET_Y+y*2;
        y = y + CAVE_HEIGHT + pgm_read_byte(monsterDy+d);
        x = x + CAVE_WIDTH + pgm_read_byte(monsterDx+d);
        nx = CAVE_OFFSET_X+(x-CAVE_WIDTH)*2;
        ny = CAVE_OFFSET_Y+(y-CAVE_HEIGHT)*2;

        y %= CAVE_HEIGHT;
        x %= CAVE_WIDTH;
        mapSetVisible(map, x, y);

        if (mapGetType(map, x, y) >= CORRIDOR)
          d = pgm_read_byte(monsterCor[mapGetType(map, x, y) - CORRIDOR]+d);

        do {
          if (ox < nx)
            ox++;
          else if(ox > nx)
            ox--;
          else if(oy < ny)
            oy++;
          else if(oy > ny)
            oy--;
          monsterDrawMap(map, false);
          if (shooting)
            ssLoadFromMap(bombMap, sSprites+4, ox, oy, 4, tileset);
          else
            ssLoadFromMap(guyMap, sSprites, ox, oy, 0, tileset);
          monsterFixSS(sSprites + (shooting? 4 : 0), 4);
          ssBlit(sSprites, shooting? 8 : 4);
          playSound(SHORT_WALKING_PATCH);
          WaitVsync(4);
        } while (ox != nx || oy != ny);
      } while (mapGetType(map, x, y) >= CORRIDOR);

      if (shooting) {
        ssUnblit(sSprites+4, 4);
        ssSwitchMap(explosionMap, sSprites+4, tileset);
        playSound(EXPLOSION_PATCH);
        WaitVsync(30);
        if (mapGetType(map, x, y) == WUMPUS_ROOM)
          shooting = 2;
        x = xx;
        y = yy;
        break;
      }
    }

    controllerEnd();
    WaitVsync(1);
  }

  /* Print the result */
  if (shooting == 2) {
    Print(8, 6, strCongrat);
    Print(4, 14, strKill);
    playSound(VICTORY_PATCH);
  }
  else {
    Print(6, 14, mapGetType(map, x, y) == HOLE_ROOM? strFell : strAte);
    playSound(LOSS_PATCH);
  }

  for (bool done = false; !done;) {
    controllerStart();
    if (pressed[0] & BTN_START)
      done = true;
    WaitVsync(1);
    controllerEnd();
  }

  /* Draw the whole cave */
  monsterDrawMap(map, true);
  ssBlit(sSprites, (shooting? 8 : 4));

  for (bool done = false; !done;) {
    controllerStart();
    if (pressed[0] & BTN_START)
      done = true;
    WaitVsync(1);
    controllerEnd();
  }
}

uint8_t mapGetVisible(const uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y) {
  return (map[y][x/2] & (x & 1? 0x80 : 0x8));
}

void mapSetVisible(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y) {
  map[y][x/2] |= (x & 1? 0x80 : 0x8);
}

void mapSetInvisible(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y) {
  map[y][x/2] &= (x & 1? 0x7f : 0xf7);
}

uint8_t mapGetType(const uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y) {
  return x&1? (map[y][x/2] & 0x70) >> 4 : map[y][x/2] & 0x7;
}

void mapSetType(uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2],
    uint8_t x, uint8_t y, uint8_t t) {
  map[y][x/2] = x&1?(map[y][x/2] & 0xf) | (t << 4)
    : (map[y][x/2] & 0xf0) | (t & 0xf);
}


void monster() {
  uint8_t map[CAVE_HEIGHT][(CAVE_WIDTH+1)/2];
  uint8_t x, y;

  copyTileToRam(tileset, HIT_TILE, 20);
  rtReplaceColor(20, SKY_COLOR, TRANSLUCENT_COLOR);
  rtRotate90(20, 21);
  rtMirror(21, 20);

  /* Print loading screen */
  ClearVram();
  Print(7, 9, strGenerating);
  Print(9, 14, strWait);

  /* Generate a map */
  DisableSoundEngine();
  monsterGenerateLevel(map, &x, &y);
  EnableSoundEngine();
  FadeOut(3, true);

  monsterPlay(map, x, y);
}

bool testArray(const int8_t *m) {
  int8_t i;
  for (i = 1; i < 16; i++)
    if (m[i] < m[i - 1])
      return false;
  return true;
}

int8_t gridCheck(const int8_t l[3][3]) {
  for (uint8_t i = 0; i < 3; i++) {
    if (l[i][0] && l[i][0] == l[i][1] && l[i][0] == l[i][2])
      return l[i][0];
    if (l[0][i] && l[0][i] == l[1][i] && l[0][i] == l[2][i])
      return l[0][i];
  }

  if (l[0][0] && l[0][0] == l[1][1] && l[0][0] == l[2][2])
    return l[0][0];
  if (l[0][2] && l[0][2] == l[1][1] && l[0][2] == l[2][0])
    return l[0][2];

  for (uint8_t i = 0; i < 3; i++)
    for (uint8_t j = 0; j < 3; j++)
      if (!l[i][j])
        return 0x3f;

  return 0;
}

struct int8_t_pair gridGetMove(int8_t p, int8_t l[3][3]) {
  int8_t best = -p;
  int8_t move = -1;
  struct int8_t_pair a;
  int8_t c = gridCheck(l);

  if (c != 0x3f)
    return (struct int8_t_pair) {c, -1};

  for (uint8_t i = 0; i < 3; i++)
    for (uint8_t j = 0; j < 3; j++) {
      if (l[i][j]) continue;
      l[i][j] = p;
      a = gridGetMove(-p, l);
      l[i][j] = 0;
      if (move == -1 || (p > 0 && a.x > best) || (p < 0 && a.x < best)) {
        move = i*3+j;
        best = a.x;
      }
    }

  return (struct int8_t_pair) {best, move};
}

void gridDrawCursor(int8_t x, int8_t y, uint8_t tile) {
  Fill(5+7*x, 6+6*y, 6, 1, tile);
  Fill(5+7*x, 7+6*y, 1, 3, tile);
  Fill(10+7*x, 7+6*y, 1, 3, tile);
  Fill(5+7*x, 10+6*y, 6, 1, tile);
}

void grid(uint8_t players) {
  int8_t level[3][3];
  int8_t x, y, c, winner;
  int8_t turn = 0;

  memset(level, 0, sizeof(level));

  ClearVram();
  Fill(5, 11, 20, 1, PAINTED_TILE);
  Fill(5, 17, 20, 1, PAINTED_TILE);
  Fill(11, 6, 1, 17, PAINTED_TILE);
  Fill(18, 6, 1, 17, PAINTED_TILE);

  for (int8_t p = random()&1; (winner = gridCheck(level)) == 0x3f; p ^= 1) {
    DrawMap2(2, 2, p? openChestMap : phoneMap);
    Print(8, 3, strTurn);
    SetTile(15, 3, WHITE_NUMBER + p+1);

    if (p && players == 1) {
      bool songWasPlaying = IsSongPlaying();
      cutSong();
      WaitVsync(13);
      DisableSoundEngine();
      struct int8_t_pair m = !turn?
        (struct int8_t_pair) {0, random() % 9} :gridGetMove(!p? 1 : -1, level);
      x = m.y%3;
      y = m.y/3;
      EnableSoundEngine();
      if (songWasPlaying)
        ResumeSong();
      if (turn)
        WaitVsync(30);
    }
    else {
      x = y = 0;
      c = players == 1? 0 : p;
      gridDrawCursor(x, y, SKY_TILE);
      for (bool played = false; !played; ) {
        controllerStart();

        if (pressed[0] & BTN_SELECT)
          return;
        else if (pressed[c] & BTN_UP && y) {
          gridDrawCursor(x, y, 0);
          gridDrawCursor(x, --y, SKY_TILE);
          playSound(MOVE_SELECTION_PATCH);
        }
        else if (pressed[c] & BTN_RIGHT && x < 2) {
          gridDrawCursor(x, y, 0);
          gridDrawCursor(++x, y, SKY_TILE);
          playSound(MOVE_SELECTION_PATCH);
        }
        else if (pressed[c] & BTN_LEFT && x) {
          gridDrawCursor(x, y, 0);
          gridDrawCursor(--x, y, SKY_TILE);
          playSound(MOVE_SELECTION_PATCH);
        }
        else if (pressed[c] & BTN_DOWN && y < 2) {
          gridDrawCursor(x, y, 0);
          gridDrawCursor(x, ++y, SKY_TILE);
          playSound(MOVE_SELECTION_PATCH);
        }
        else if (pressed[c] & BTN_A && !level[y][x]) {
          gridDrawCursor(x, y, 0);
          played = true;
        }

        WaitVsync(1);
        controllerEnd();
      }
    }

    level[y][x] = !p? 1 : -1;
    playSound(PLACE_BATTERY_PATCH);
    DrawMap2(6+7*x, 7+6*y, p? openChestMap : phoneMap);
    turn++;
  }

  Fill(0, 0, 30, 5, 0);
  if (winner) {
    Print(7, 3, strWins);
    Fill(7, 3, 8, 1, 0);
    DrawMap2(10, 2, winner == -1? openChestMap : phoneMap);
    playSound(players == 1 && winner == -1? LOSS_PATCH : VICTORY_PATCH);
  }
  else {
    Print(13, 3, strDraw);
    playSound(LOSS_PATCH);
  }

  for (bool done = false; !done; ) {
    controllerStart();

    if (pressed[0] & BTN_START)
      done = true;

    WaitVsync(1);
    controllerEnd();
  }
}

void animateCat() {
  for (uint8_t i = 0; i < 7; i++) {
    uint8_t a = pgm_read_byte(catAnimationPixels[i]);
    uint8_t b = pgm_read_byte(catAnimationPixels[i]+1);
    char *rt = ram_tiles + 64*i;
    rt[a] ^= rt[b];
    rt[b] ^= rt[a];
    rt[a] ^= rt[b];
  }
}

bool survivalMoveDown(uint8_t p, int8_t height[2][10]) {
  const uint8_t yOffset = 8;
  const uint8_t xOffset = p? 17 : 3;
  uint8_t *vRow = vram + ((yOffset+16)*VRAM_TILES_H) + xOffset;
  uint8_t *vTopRow = vRow - VRAM_TILES_H;
  bool cleaning = true;

  for (uint8_t i = 0; i < 10; i++) {
    if (!height[p][i])
      cleaning = false;
  }

  for (uint8_t y = 0; y < 16; y++) {
    vRow = vTopRow;
    vTopRow -= VRAM_TILES_H;
    for (uint8_t x = 0; x < 10; x++)
      if (cleaning)
        vRow[x] = vTopRow[x];
      else if (y > height[p][x]) {
        vRow[x] = vTopRow[x] == RAM_TILES_COUNT+ABOUT_TILE
          || vTopRow[x] < TOTAL_CAT_TILES?
          RAM_TILES_COUNT+SKY_TILE : vTopRow[x];
      }
      else if (y == height[p][x] && vTopRow[x] != RAM_TILES_COUNT+SKY_TILE) {
        vRow[x] = vTopRow[x] < TOTAL_CAT_TILES?
          RAM_TILES_COUNT+SKY_TILE : vTopRow[x];
        if (vRow[x] == RAM_TILES_COUNT+BLOCK_TILE) {
          height[p][x]++;
          vTopRow[x] = RAM_TILES_COUNT+SKY_TILE;
        }
      }
  }

  if (cleaning)
    for (uint8_t i = 0; i < 10; i++) {
      height[p][i]--;
    }

  Fill(xOffset, yOffset, 10, 1, SKY_TILE);

  return cleaning;
}

void survival(uint8_t players) {
  uint16_t score[2] = {0, 0};
  bool alive[2] = {true, players > 1};
  uint8_t cat[2][2] = {{4, 23}, {4, 23}};
  int8_t height[2][10];
  int8_t about = -1;
  uint8_t movementDelay = MOVE_DELAY;
  uint8_t shotDelay = SHOT_DELAY;
  uint8_t nextMovement = movementDelay;
  uint8_t nextShot = 2*shotDelay;
  uint8_t fasterDelay = FASTER_DELAY;
  uint8_t nextFaster = fasterDelay;
  uint8_t nextBlink = BLINK_DELAY;
  uint8_t blinkState = 0;
  uint8_t catAnimation = CAT_ANIMATION_DELAY;
  uint8_t nextMove[2] = {0, 0};
  uint8_t catDir[2] = {1, 1};
  int8_t moving[2] = {0, 0};

  memset(height, 0, sizeof(height));

  ClearVram();
  for (uint8_t i = 0; i < 2; i++) {
    Fill(3+14*i, 8, 10, 16, SKY_TILE);
    drawFrame(3+14*i, 8, 10, 17, 20);
    Fill(3+14*i, 24, 10, 1, BLOCK_TILE);
    Print(2+14*i, 6, strScore);
  }

  /* Build the cat */
  copyTileToRam(tileset, CAT_TILE, 1);
  rtRotate90(1, 0);
  rtRotate90(0, 2);
  rtRotate90(2, 0);
  rtRotate90(1, 2);
  rtMirror(0, 4);
  rtMirror(1, 5);
  rtMirror(2, 6);

  while (alive[0] || alive[1]) {
    controllerStart();

    if (pressed[0] & BTN_SELECT)
      return;

    if (about != -1 && !(--nextBlink)) {
      nextBlink = BLINK_DELAY;
      blinkState ^= 1;
      if (alive[0])
        SetTile(3+about, 8, blinkState? ABOUT_TILE : SKY_TILE);
      if (alive[1])
        SetTile(3+14+about, 8, blinkState? ABOUT_TILE : SKY_TILE);
    }

    if (!(--nextMovement)) {
      if (!(--nextShot) && about != -1) {
        uint8_t type = random() & 0x7;
        if (type < 4)
          type = BLOCK_TILE;
        else if (type == 7)
          type = GREEN_BALL_TILE;
        else
          type = RED_BALL_TILE;
        if (alive[0])
          SetTile(3+about, 8, type);
        if (alive[1])
          SetTile(3+14+about, 8, type);
        playSound(CANNON_PATCH);
      }

      for (uint8_t i = 0; i < 2; i++) {
        if (!alive[i])
          continue;

        if (survivalMoveDown(i, height))
          cat[i][1]--;
      }

      if (!nextShot) {
        about = random() % 10;
        blinkState = 1;
        for (uint8_t i = 0; i < 2; i++)
          if (alive[i] && height[i][about] <= 10)
              SetTile(3+14*i+about, 8, ABOUT_TILE);

        if (!(--nextFaster)) {
          nextFaster = fasterDelay;
          if (movementDelay > 4)
            movementDelay--;
          else if (shotDelay > 2)
            shotDelay--;
        }

        nextShot = shotDelay;
      }

      nextMovement = movementDelay;
    }

    for (uint8_t p = 0; p < 2; p++) {
      if (!alive[p])
        continue;

      uint8_t x = 3+14*p+cat[p][0];
      uint8_t y = cat[p][1];
      uint8_t *tile = vram + (y*VRAM_TILES_H+x);

      if (*tile < TOTAL_CAT_TILES)
        SetTile(x, y, SKY_TILE);
      else if (*tile == RAM_TILES_COUNT+BLOCK_TILE) {
        if (*(tile+VRAM_TILES_H) == RAM_TILES_COUNT+BLOCK_TILE) {
          alive[p] = false;
          SetTile(x, y+1, BLOODY_BLOCK_TILE);
          playSound(HITS_FLOOR_PATCH);
          continue;
        }
        else {
          moving[p] = 0;
          catDir[p] = (catDir[p] & 0x4) | 0x1;
          cat[p][1]++;
          tile = vram + (y*VRAM_TILES_H+x);
        }
      }

      bool falling = !moving[p]
        && (*(tile+VRAM_TILES_H) != RAM_TILES_COUNT+BLOCK_TILE);
      if (falling || (moving[p] && !(--nextMove[p]))) {
        if (falling || !(catDir[p] & 0x3)) {
          if (*(tile+VRAM_TILES_H) == RAM_TILES_COUNT+BLOCK_TILE) {
            moving[p] = 0;
            catDir[p] = (catDir[p] & 0x4) | 0x1;
            falling = false;
          }
          else
            cat[p][1]++;
        }
        else if (*(tile+moving[p]) != RAM_TILES_COUNT+BLOCK_TILE) {
          cat[p][0] += moving[p];
          if (*(tile+VRAM_TILES_H+moving[p]) == RAM_TILES_COUNT+BLOCK_TILE) {
            catDir[p] = (catDir[p] & 0x4) | 0x1;
            moving[p] = 0;
          }
          else
            catDir[p] &= 0x4;
        }
        else if ((catDir[p] & 0x3) == 1)
          catDir[p] = (catDir[p] & 0x4) | 0x2;
        else if (*(tile-VRAM_TILES_H) != RAM_TILES_COUNT+BLOCK_TILE)
          cat[p][1]--;
        else {
          catDir[p] = (catDir[p] & 0x4) | 0x1;
          moving[p] = 0;
          falling = *(tile+VRAM_TILES_H) != RAM_TILES_COUNT+BLOCK_TILE;
        }
        nextMove[p] = CAT_MOVE_DELAY;
      }

      if (!falling && !moving[p]) {
        if (pressed[p] & BTN_LEFT && cat[p][0]) {
          catDir[p] &= 3;
          moving[p] = -1;
          nextMove[p] = CAT_MOVE_DELAY;
        }
        else if (pressed[p] & BTN_RIGHT && cat[p][0] < 9) {
          catDir[p] |= 4;
          moving[p] = 1;
          nextMove[p] = CAT_MOVE_DELAY;
        }
      }

      x = 3+14*p+cat[p][0];
      y = cat[p][1];
      tile = vram + (y*VRAM_TILES_H+x);
      if (*tile == RAM_TILES_COUNT+RED_BALL_TILE) {
        score[p]++;
        playSound(TAKE_BATTERY_PATCH);
      }
      else if (*tile == RAM_TILES_COUNT+GREEN_BALL_TILE) {
        score[p] += 3;
        playSound(TAKE_BATTERY_PATCH);
      }
      SetTile(x, y, catDir[p]-RAM_TILES_COUNT);

      printColoredShort(13+14*p, 6, score[p], GREEN_NUMBER);
    }

    if (!(--catAnimation)) {
      animateCat();
      catAnimation = CAT_ANIMATION_DELAY;
    }

    WaitVsync(1);
    controllerEnd();
  }

  WaitVsync(60);
  Print(11, 12, strGameOver);
  playSound(VICTORY_PATCH);
  if (players > 1) {
    if (score[0] == score[1])
      Print(13, 14, strDraw);
    else {
      Print(8, 14, strWins);
      SetTile(15, 14, WHITE_NUMBER + (score[0] > score[1]? 1 : 2));
    }
  }
  for (bool done = false; !done; ) {
    controllerStart();

    if (pressed[0] & BTN_START)
      done = true;

    WaitVsync(1);
    controllerEnd();
  }
}

uint8_t rainMoveDown(uint8_t player) {
  const uint8_t yOffset = 8;
  const uint8_t xOffset = player? 18 : 3;
  uint8_t *vRow = vram + ((yOffset+15)*VRAM_TILES_H) + xOffset;
  uint8_t *vTopRow = vRow - VRAM_TILES_H;
  uint8_t hits = 0;

  for (uint8_t x = 0; x < 10; x++) {
    if (vTopRow[x] == RAM_TILES_COUNT+SKY_TILE
        || vTopRow[x] == RAM_TILES_COUNT+HIT_TILE) {
      vRow[x] = RAM_TILES_COUNT + SKY_TILE;
      vRow[x+VRAM_TILES_H] = RAM_TILES_COUNT;
    }
    else {
      hits++;
      playSound(HITS_FLOOR_PATCH);
      vRow[x] = RAM_TILES_COUNT + HIT_TILE;
      vRow[x+VRAM_TILES_H] = RAM_TILES_COUNT + CRACK_TILE;
    }
  }

  Fill(xOffset, yOffset-1, 10, 1, NON_FIRE_TILE);

  for (uint8_t y = yOffset+14; y > yOffset; y--) {
    vRow = vTopRow;
    vTopRow -= VRAM_TILES_H;
    for (uint8_t x = 0; x < 10; x++)
      vRow[x] = vTopRow[x] == RAM_TILES_COUNT + HIT_TILE?
        RAM_TILES_COUNT + SKY_TILE : vTopRow[x];
  }
  Fill(xOffset, yOffset, 10, 1, SKY_TILE);

  return hits;
}

void rainShoot(uint8_t player, uint8_t key) {
  const uint8_t yOffset = 8;
  const uint8_t xOffset = player? 18 : 3;

  SetTile(xOffset+key, yOffset-1, FIRE_TILE);
  SetTile(xOffset+key, yOffset, 30-RAM_TILES_COUNT+key);
}

bool rainRemove(uint8_t player, uint8_t key) {
  const uint8_t yOffset = 8;
  const uint8_t xOffset = player? 18 : 3;
  uint8_t *vCell = vram + ((yOffset+14)*VRAM_TILES_H) + xOffset + key;

  for (uint8_t y = yOffset+14; y >= yOffset; y--, vCell -= VRAM_TILES_H) {
    if (*vCell != RAM_TILES_COUNT + SKY_TILE) {
      *vCell = RAM_TILES_COUNT + HIT_TILE;
      return true;
    }
  }

  return false;
}

void rain(uint8_t players) {
  int8_t l[2] = {8, 8};
  uint8_t i, j;
  uint16_t score = 0;
  uint8_t movementDelay = MOVE_DELAY;
  uint8_t shotDelay = SHOT_DELAY;
  uint8_t nextMovement = movementDelay;
  uint8_t nextShot = 2*shotDelay;
  uint8_t fasterDelay = FASTER_DELAY;
  uint8_t nextFaster = fasterDelay;
  uint8_t falling[2][10];
  uint16_t buttonMap[10] = {BTN_LEFT, BTN_UP, BTN_DOWN, BTN_RIGHT, BTN_A,
    BTN_B, BTN_X, BTN_Y, BTN_SL, BTN_SR};

  memset(falling, 0, sizeof(falling));

  /* Load the characters with the right BG */
  for (i = 0; i < 10; i++) {
    copyTileToRam(tileset, pgm_read_byte(strRainButtons+i)-' ', 30+i);
    rtReplaceColor(30+i, DEFAULT_GRAY, SKY_COLOR);
  }

  /* Draw the basic screen */
  ClearVram();
  for (i = 0; i < players; i++) {
    for (j = 0; j < 10; j++) {
      DrawMap2(3 + j + (15 * i), 6, canonMap);
    }
    drawFrame(3+(15*i), 6, 10, 19, 20);
    Fill(3+(15*i), 8, 10, 17, SKY_TILE);
    Print(3 + 15 * i, 4, strLives);
  }
  if (players == 1) {
    Print(18, 4, strScore);
  }

  while (l[0] && l[1]) {
    controllerStart();

    if (!(--nextMovement)) {
      for (i = 0; i < players; i++)
        l[i] -= rainMoveDown(i);

      if (!(--nextShot)) {
        uint8_t nextKey = random() % 10;
        for (i = 0; i < players; i++) {
          rainShoot(i, nextKey);
          falling[i][nextKey]++;
          playSound(CANNON_PATCH);
        }

        if (!(--nextFaster)) {
          nextFaster = fasterDelay;
          if (movementDelay > 4)
            movementDelay--;
          else if (shotDelay > 2)
            shotDelay--;
        }

        nextShot = shotDelay;
      }

      nextMovement = movementDelay;
    }

    for (i = 0; i < players; i++)
      printColoredByte2(11 + (15 * i) , 4, l[i], GREEN_NUMBER);

    /* Destroy falling buttons */
    for (i = 0; i < players; i++) {
      for (j = 0; j < 10; j++) {
        if (pressed[i] & buttonMap[j]) {
          if (falling[i][j]) {
            if (rainRemove(i, j)) {
              playSound(EXPLOSION_PATCH);
              if (players == 1)
                score++;
            }
          }
        }
      }
    }

    if (players == 1) {
      printColoredShort(27 , 4, score, GREEN_NUMBER);
    }

    if (pressed[0] & BTN_SELECT) {
      controllerEnd();
      return;
    }

    WaitVsync(1);
    controllerEnd();
  }

  ClearVram();
  /* One player, game over */
  if (players == 1) {
    Print(10, 10, strGameOver);
    Print(10, 12, strScore);
    printColoredByte2(18, 12, score, GREEN_NUMBER);
    playSound(LOSS_PATCH);
  }
  /* Announce the winner. */
  else {
    if (l[0] == l[1]) {
      Print(12, 12, strDraw);
      playSound(LOSS_PATCH);
    }
    else {
      Print(8, 14, strWins);
      SetTile(15, 14, WHITE_NUMBER + 1 + (l[1] > l[0]));
      playSound(VICTORY_PATCH);
    }
  }

  while (1) {
    controllerStart();
    if (pressed[0] & BTN_START) break;
    WaitVsync(1);
    controllerEnd();
  }
  controllerEnd();
}

void array(uint8_t human) {
  int8_t m[2][16], i, n, p[2], s[2], d;

  /* Generate a random order */
  for (i = 0; i < 16; i++) m[0][i] = i;
  while (testArray(m[0])) {
    for (i = 0; i < 16; i++) {
      n = (random() % (16 - i)) + i;
      if (n != i) {
        m[0][n] ^= m[0][i];
        m[0][i] ^= m[0][n];
        m[0][n] ^= m[0][i];
      }
    }
  }
  for (i = 0; i < 16; i++) m[1][i] = m[0][i];
  p[0] = p[1] = 0;
  s[0] = s[1] = 0x7f;

  ClearVram();
  Print(10, 6, strPlayer1);
  Print(10, 14, strPlayer2);

  d = CPU_DELAY;

  drawFrame(3, 8, 23, 4, 30);
  drawFrame(3, 16, 23, 4, 30);

  while (!testArray(m[0]) && !testArray(m[1])) {
    controllerStart();

    /* AI */
    if (!human && !(--d)) {
      d = CPU_DELAY;

      if (s[1] == 0x7f) {
        if (m[1][p[1]] == p[1])
          pressed[1] = m[1][p[1]^8] != (p[1]^8)? BTN_UP : BTN_RIGHT;
        else
          pressed[1] = BTN_A;
      }
      else {
        if (m[1][s[1]] == p[1])
          pressed[1] = BTN_A;
        else {
          if ((m[1][s[1]] & 8) != (p[1] & 8))
            pressed[1] = BTN_UP;
          else if (p[1] > m[1][s[1]])
            pressed[1] = BTN_LEFT;
          else
            pressed[1] = BTN_RIGHT;
        }
      }
    }

    if ((pressed[0] | pressed[1]) & (BTN_RIGHT | BTN_LEFT | BTN_UP | BTN_DOWN))
      playSound(MOVE_SELECTION_PATCH);
    else if ((pressed[0] | pressed[1]) & BTN_A)
      playSound(PLACE_BATTERY_PATCH);
    else if ((pressed[0] | pressed[1]) & BTN_B)
      playSound(TAKE_BATTERY_PATCH);

    for (i = 0; i < 2; i++) {
      Fill(3*(p[i]&7)+3, (i? 16 : 8) + (p[i] < 8? 1 : 3), 2, 1, 0);
      if (pressed[i] & BTN_RIGHT)
        p[i] = (p[i]&8) + ((p[i]+1)&7);
      else if (pressed[i] & BTN_LEFT)
        p[i] = (p[i]&8) + ((p[i]+7)&7);
      else if (pressed[i] & BTN_UP || pressed[i] & BTN_DOWN)
        p[i] ^= 8;
      else if (pressed[i] & BTN_A) {
        if (s[i] == 0x7f)
          s[i] = p[i];
        else {
          if (s[i] != p[i]) {
            m[i][s[i]] ^= m[i][p[i]];
            m[i][p[i]] ^= m[i][s[i]];
            m[i][s[i]] ^= m[i][p[i]];
          }
          s[i] = 0x7f;
        }
      }
      else if (pressed[i] & BTN_B)
        s[i] = 0x7f;
      else if (pressed[i] & BTN_SELECT)
        return;

      for (n = 0; n < 16; n++) {
        printColoredByte2(3 * (n&7) + 4,
          (i? 16 : 8) + (n < 8? 0 : 2), m[i][n],
          n == s[i]? BLUE_NUMBER
          : (n == m[i][n]? GREEN_NUMBER : WHITE_NUMBER));
      }
      Fill(3*(p[i]&7)+3, (i? 16 : 8) + (p[i] < 8? 1 : 3), 2, 1, '('-' ');
    }

    WaitVsync(1);
    controllerEnd();
  }
  ClearVram();

  Print(8, 14, strWins);
  SetTile(15, 14, WHITE_NUMBER + 1 + testArray(m[1]));
  playSound(human || testArray(m[0])? VICTORY_PATCH : LOSS_PATCH);
  while (1) {
    controllerStart();
    if (pressed[0] & BTN_START)
      break;
    WaitVsync(1);
    controllerEnd();
  }
}

void trollenLoadBaseTiles() {
  uint8_t i;
  uint8_t sides[] = {1, 4, 8, 2, 1|8, 4|8, 4|2, 1|2};

  for (i = 0; i < 8; i++) {
    copyTileToRam(tileset, FLASH_NO_TILE, i);
    copyTileToRam(tileset, FLASH_NO_TILE, 8+i);

    if (sides[i] & 1) {
      rtDrawRectangle(i, 0, 0, 8, 4, BROWN);
      if (i < 4)
        rtDrawRectangle(8+i, 0, 0, 8, 1, LIMIT_COLOR);
    }
    if (sides[i] & 2) {
      rtDrawRectangle(i, 4, 0, 4, 8, BROWN);
      if (i < 4)
        rtDrawRectangle(8+i, 7, 0, 1, 8, LIMIT_COLOR);
    }
    if (sides[i] & 4) {
      rtDrawRectangle(i, 0, 4, 8, 4, BROWN);
      if (i < 4)
        rtDrawRectangle(8+i, 0, 7, 8, 1, LIMIT_COLOR);
    }
    if (sides[i] & 8) {
      rtDrawRectangle(i, 0, 0, 4, 8, BROWN);
      if (i < 4)
        rtDrawRectangle(8+i, 0, 0, 1, 8, LIMIT_COLOR);
    }
  }

  copyTileToRam(tileset, FLASH_NO_TILE, NO_TILE+RAM_TILES_COUNT);
  rtDrawRectangle(GRASS_TILE+RAM_TILES_COUNT, 0, 0, 8, 8, GREEN_3);

  copyTileToRam(tileset, FLASH_SYMBOL_0, SYMBOL_0+RAM_TILES_COUNT);
  copyTileToRam(tileset, FLASH_SYMBOL_1, SYMBOL_1+RAM_TILES_COUNT);
  copyTileToRam(tileset, FLASH_SYMBOL_2, SYMBOL_2+RAM_TILES_COUNT);
  copyTileToRam(tileset, FLASH_SYMBOL_3, SYMBOL_3+RAM_TILES_COUNT);

  for (i = 0; i < 4; i++) {
    copyTileToRam(tileset, pgm_read_byte(hTrollMap+2+i), 18+i);
    if (i < 2)
      copyTileToRam(tileset, pgm_read_byte(stunnedHTrollMap+2+i), 18+4+i);
    copyTileToRam(tileset, pgm_read_byte(hTrollMap+2+i), 18+6+i);
  }

  for (i = 0; i < 6; i++) {
    rtReplaceColor(18+i, 31, 43);
    rtReplaceColor(18+i, 23, 32);
    rtReplaceColor(18+i, 168, 214);
  }
  for (i = 0; i < 4; i++) {
    rtReplaceColor(18+6+i, 31, 152);
    rtReplaceColor(18+6+i, 23, 128);
    rtReplaceColor(18+6+i, 168, 184);
  }
}

void trollenLoadLevel(uint8_t n, struct trollenLevel *level) {
  uint8_t i, t, b, o, x, y;
  uint8_t l[13];
  for (i = 0; i < 13; i++)
    l[i] = pgm_read_byte(trollenLevels[n] + i);

  memset(level->map, 0, 6*6*sizeof(uint8_t));

  for (i = 0; i < 6; i++) {
    level->map[0][i] |= TOP_WALL;
    level->map[i][5] |= RIGHT_WALL;
    level->map[5][i] |= BOTTOM_WALL;
    level->map[i][0] |= LEFT_WALL;
  }

  for (i = 0; i < 30; i++) {
    b = i / 8;
    o = i % 8;
    x = i % 5;
    y = i / 5;
    if ((l[b] >> o) & 1) {
      level->map[y][x] |= RIGHT_WALL;
      level->map[y][x+1] |= LEFT_WALL;
    }
  }
  for (i = 0; i < 30; i++) {
    b = (i+30) / 8;
    o = (i+30) % 8;
    x = i % 6;
    y = i / 6;
    if ((l[b] >> o) & 1) {
      level->map[y][x] |= BOTTOM_WALL;
      level->map[y+1][x] |= TOP_WALL;
    }
  }

  t = ((l[8] & 0x3) << 4) | ((l[7] >> 4) & 0xf);
  level->trap[0].x = (t%6)*4;
  level->trap[0].y = (t/6)*4;

  t = (l[8] >> 2) & 0x3f;
  level->trap[1].x = (t%6)*4;
  level->trap[1].y = (t/6)*4;

  t = l[9] & 0x3f;
  level->trap[2].x = (t%6)*4;
  level->trap[2].y = (t/6)*4;

  t = ((l[10] & 0xf) << 2) | ((l[9] >> 6) &  0x3f);
  level->hero.x = (t%6)*4;
  level->hero.y = (t/6)*4;

  t = ((l[11] & 0x3) << 4) | ((l[10] >> 4) & 0xf);
  level->troll[0].pos.x = (t%6)*4;
  level->troll[0].pos.y = (t/6)*4;;

  t = (l[11] >> 2) & 0x3f;
  level->troll[1].pos.x = (t%6)*4;
  level->troll[1].pos.y = (t/6)*4;;

  t = l[12] & 0x1f;
  if (t < 6)
    level->map[0][t] &= ~TOP_WALL;
  else if (t < 12)
    level->map[5][t%6] &= ~BOTTOM_WALL;
  else if (t < 18)
    level->map[t%6][0] &= ~LEFT_WALL;
  else if (t < 24)
    level->map[t%6][5] &= ~RIGHT_WALL;

  if (level->troll[0].pos.x >= 6*4 || level->troll[0].pos.y >= 6*4)
    level->troll[0].type = NO_TROLL;
  else if ((l[12] >> 5) & 1)
    level->troll[0].type = V_TROLL;
  else
    level->troll[0].type = H_TROLL;

  if (level->troll[1].pos.x >= 6*4 || level->troll[1].pos.y >= 6*4)
    level->troll[1].type = NO_TROLL;
  else if ((l[12] >> 6) & 1)
    level->troll[1].type = V_TROLL;
  else
    level->troll[1].type = H_TROLL;

  level->troll[0].stun = 0;
  level->troll[1].stun = 0;
}

void trollenDrawLevel(const struct trollenLevel *level) {
  uint8_t i, j, x, y;

  memset(vram, GRASS_TILE+RAM_TILES_COUNT, VRAM_TILES_H*VRAM_TILES_V);
  for (y = 2, i = 0; i < 6; i++, y += 4) {
    for (x = 3, j = 0; j < 6; j++, x += 4) {
      SetTile(x, y,
          level->map[i][j] & TOP_WALL?
            (level->map[i][j] & LEFT_WALL? TL_TILE : T_TILE)
            : (level->map[i][j] & LEFT_WALL? L_TILE : NO_TILE));

      SetTile(x+1, y, level->map[i][j] & TOP_WALL? T_TILE : NO_T_TILE);
      SetTile(x+2, y, level->map[i][j] & TOP_WALL? T_TILE : NO_T_TILE);

      SetTile(x+3, y,
          level->map[i][j] & TOP_WALL?
            (level->map[i][j] & RIGHT_WALL? TR_TILE : T_TILE)
            : (level->map[i][j] & RIGHT_WALL? R_TILE : NO_TILE));

      SetTile(x, y+1, level->map[i][j] & LEFT_WALL? L_TILE : NO_L_TILE);
      SetTile(x+1, y+1, NO_TILE);
      SetTile(x+2, y+1, NO_TILE);
      SetTile(x+3, y+1, level->map[i][j] & RIGHT_WALL? R_TILE : NO_R_TILE);

      SetTile(x, y+2, level->map[i][j] & LEFT_WALL? L_TILE : NO_L_TILE);
      SetTile(x+1, y+2, NO_TILE);
      SetTile(x+2, y+2, NO_TILE);
      SetTile(x+3, y+2, level->map[i][j] & RIGHT_WALL? R_TILE : NO_R_TILE);

      SetTile(x, y+3,
          level->map[i][j] & BOTTOM_WALL?
            (level->map[i][j] & LEFT_WALL? BL_TILE : B_TILE)
            : (level->map[i][j] & LEFT_WALL? L_TILE : NO_TILE));

      SetTile(x+1, y+3, level->map[i][j] & BOTTOM_WALL? B_TILE : NO_B_TILE);
      SetTile(x+2, y+3, level->map[i][j] & BOTTOM_WALL? B_TILE : NO_B_TILE);

      SetTile(x+3, y+3,
          level->map[i][j] & BOTTOM_WALL?
            (level->map[i][j] & RIGHT_WALL? BR_TILE : B_TILE)
            : (level->map[i][j] & RIGHT_WALL? R_TILE : NO_TILE));
    }
  }

  for (i = 0; i < MAX_TRAPS; i++)
    if (level->trap[i].x < 6*4 && level->trap[i].y < 6*4)
      DrawMap2(level->trap[i].x+4, level->trap[i].y+3, symbolMap);
}

void trollenDrawTitle() {
  struct simpleSprite sSprites[8];

  DrawMap2(11, 8, trollBoxMap);
  DrawMap2(15, 8, trollBoxMap);

  ssLoadFromMap(hTrollMap, sSprites, 12, 9, RAM_TILES_COUNT-8, tileset);
  ssLoadFromMap(vTrollMap, sSprites+4, 16, 9, RAM_TILES_COUNT-4, tileset);
  ssBlit(sSprites, 8);
}

uint8_t trollen(uint8_t levelNum) {
  struct trollenLevel level;
  struct int8_t_pair heroNext;
  struct int8_t_pair trollNext[2];
  uint8_t heroTile, tTile;
  uint8_t outcome = 0;
  struct simpleSprite sSprites[4*3];
  uint8_t usedSSprites = 0;
  struct int8_t_pair lastPos;

  trollenLoadLevel(levelNum, &level);
  trollenDrawLevel(&level);

  ssLoadFromMap(trollGuyMap, sSprites, level.hero.x+4, level.hero.y+3,
      RAM_TILES_COUNT-12, tileset);
  usedSSprites += 4;
  for (uint8_t i = 0; i < 2; i++) {
    if (level.troll[i].type == NO_TROLL)
      break;
    ssLoadFromMap(level.troll[i].type == V_TROLL? vTrollMap
        : (level.troll[i].type == H_TROLL? hTrollMap : sTrollMap),
        sSprites + 4*(i+1),
        level.troll[i].pos.x+4, level.troll[i].pos.y+3,
        RAM_TILES_COUNT-8+4*i, tileset);
    usedSSprites += 4;
  }
  ssBlit(sSprites, usedSSprites);

  while (!outcome) {
    /* Waiting for input */
    heroTile = level.map[level.hero.y/4][level.hero.x/4];
    heroNext = (struct int8_t_pair) {0x3f, 0x3f};
    while (heroNext.x == 0x3f) {
      controllerStart();

      if (pressed[0] & BTN_SELECT)
        return levelNum;
      else if (pressed[0] & BTN_UP && !(heroTile & TOP_WALL))
        heroNext = (struct int8_t_pair) {level.hero.x, level.hero.y-4};
      else if (pressed[0] & BTN_RIGHT && !(heroTile & RIGHT_WALL))
        heroNext = (struct int8_t_pair) {level.hero.x+4, level.hero.y};
      else if (pressed[0] & BTN_DOWN && !(heroTile & BOTTOM_WALL))
        heroNext = (struct int8_t_pair) {level.hero.x, level.hero.y+4};
      else if (pressed[0] & BTN_LEFT && !(heroTile & LEFT_WALL))
        heroNext = (struct int8_t_pair) {level.hero.x-4, level.hero.y};

      WaitVsync(1);
      controllerEnd();
    }

    if (heroNext.x >= 6*4 || heroNext.x < 0
        || heroNext.y >= 6*4 || heroNext.y < 0)
      outcome = VICTORY;
    else
      for (uint8_t i = 0; i < MAX_TRAPS; i++)
        if (level.trap[i].x == heroNext.x && level.trap[i].y == heroNext.y)
          outcome = DEFEAT;

    /* Hero moving */
    playSound(HERO_WALKING_PATCH);
    for (uint8_t i = outcome? 2 : 4; i > 0; i--) {
      ssUnblit(sSprites, 4);
      lastPos = level.hero;

      if (level.hero.x < heroNext.x)
        level.hero.x++;
      else if (level.hero.x > heroNext.x)
        level.hero.x--;
      else if (level.hero.y < heroNext.y)
        level.hero.y++;
      else if (level.hero.y > heroNext.y)
        level.hero.y--;

      ssMove(sSprites, 4, level.hero.x-lastPos.x, level.hero.y-lastPos.y);
      ssBlit(sSprites, 4);

      WaitVsync(5);
    }

    if (outcome)
      continue;

    for (uint8_t s = (level.troll[0].type == S_TROLL? 3 : 2); s > 0; s--) {
      for (uint8_t i = 0; i < 2; i++) {
        if (level.troll[i].type == NO_TROLL || level.troll[i].stun)
         continue;

        trollNext[i] = level.troll[i].pos;

        tTile = level.map[level.troll[i].pos.y/4][level.troll[i].pos.x/4];
        if (level.troll[i].type == V_TROLL) {
          if (level.hero.y < level.troll[i].pos.y && !(tTile & TOP_WALL))
            trollNext[i].y -= 4;
          else if (level.hero.y > level.troll[i].pos.y
              && !(tTile & BOTTOM_WALL))
            trollNext[i].y += 4;
          else if (level.hero.x < level.troll[i].pos.x && !(tTile & LEFT_WALL))
            trollNext[i].x -= 4;
          else if (level.hero.x > level.troll[i].pos.x
              && !(tTile & RIGHT_WALL))
            trollNext[i].x += 4;
        }
        else {
          if (level.hero.x < level.troll[i].pos.x && !(tTile & LEFT_WALL))
            trollNext[i].x -= 4;
          else if (level.hero.x > level.troll[i].pos.x
              && !(tTile & RIGHT_WALL))
            trollNext[i].x += 4;
          else if (level.hero.y < level.troll[i].pos.y && !(tTile & TOP_WALL))
            trollNext[i].y -= 4;
          else if (level.hero.y > level.troll[i].pos.y
              && !(tTile & BOTTOM_WALL))
            trollNext[i].y += 4;
        }
      }

      for (uint8_t i = 0; i < 2; i++) {
        if (level.troll[i].type != NO_TROLL && !level.troll[i].stun
            && (level.troll[i].pos.x != trollNext[i].x
              || level.troll[i].pos.y != trollNext[i].y)) {
          playSound(WALKING_PATCH);
        }
      }

      bool moved[2] = {false, false};
      for (uint8_t i = 4; i > 0; i--) {
        uint8_t still = 0;
        for (uint8_t j = 0; j < 2; j++) {
          if (level.troll[j].type == NO_TROLL || level.troll[j].stun) {
            still++;
            continue;
          }
          ssUnblit(sSprites+4*(j+1), 4);
          lastPos = level.troll[j].pos;

          if (level.troll[j].pos.x < trollNext[j].x) {
            level.troll[j].pos.x++;
            moved[j] = true;
          }
          else if (level.troll[j].pos.x > trollNext[j].x) {
            level.troll[j].pos.x--;
            moved[j] = true;
          }
          else if (level.troll[j].pos.y < trollNext[j].y) {
            level.troll[j].pos.y++;
            moved[j] = true;
          }
          else if (level.troll[j].pos.y > trollNext[j].y) {
            level.troll[j].pos.y--;
            moved[j] = true;
          }
          else
            still++;

          ssMove(sSprites+4*(j+1), 4,
              level.troll[j].pos.x-lastPos.x, level.troll[j].pos.y-lastPos.y);
          ssBlit(sSprites+4*(j+1), 4);
        }

        if (still == 2)
          break;

        WaitVsync(5);
      }

      for (uint8_t i = 0; i < 2; i++) {
        if (level.troll[i].type == NO_TROLL)
          continue;

        if (level.hero.x == level.troll[i].pos.x
            && level.hero.y == level.troll[i].pos.y)
          outcome = DEFEAT;

        for (uint8_t j = 0; j < MAX_TRAPS; j++) {
          if (moved[i] && level.troll[i].type != S_TROLL
              && !level.troll[i].stun
              && level.troll[i].pos.x == level.trap[j].x
              && level.troll[i].pos.y == level.trap[j].y) {
            playSound(STUNNED_PATCH);
            level.troll[i].stun = 4;
            ssSwitchMap(level.troll[i].type == H_TROLL?
                stunnedHTrollMap : stunnedVTrollMap,
                sSprites+4*(i+1), tileset);
            WaitVsync(1);
          }
        }
      }

      if (level.troll[0].pos.x == level.troll[1].pos.x
          && level.troll[0].pos.y == level.troll[1].pos.y
          && level.troll[0].type && level.troll[1].type) {
        playSound(MERGE_PATCH);
        level.troll[0].type = S_TROLL;
        level.troll[0].stun = 0;
        level.troll[1].type = NO_TROLL;

        ssUnblit(sSprites+8, 4);
        ssSwitchMap(sTrollMap, sSprites+4, tileset);
        usedSSprites -= 4;

        WaitVsync(1);

        break;
      }
    }

    for (uint8_t i = 0; i < 2; i++) {
      if (!level.troll[i].stun || --level.troll[i].stun)
        continue;
      ssSwitchMap(level.troll[i].type == H_TROLL? hTrollMap : vTrollMap,
          sSprites+4*(i+1), tileset);
    }
  }

  if (outcome == VICTORY) {
    playSound(VICTORY_PATCH);
    Print(8, 12, strCongrat);
  }
  else {
    playSound(LOSS_PATCH);
    Print(11, 12, strDied);
  }

  while (1) {
      controllerStart();

      if (pressed[0] & BTN_START)
        break;

      WaitVsync(1);
      controllerEnd();
  }

  return levelNum + (outcome == VICTORY? 1 : 0);
}

uint16_t topmenu() {
  uint16_t base = 0;
  uint16_t t;
  uint8_t i;
  char goingUp = 0;
  uint8_t nextColorChange = COLOR_CHANGE_DELAY;
  uint8_t nextLetter = 0;

  for (i = 0; i < 8; i++)
    rtDrawRectangle(i, 0, 0, 8, 8, random());

  draw_page:
  /* Build the basic interface */
  ClearVram();
  DrawMap2(1, 2, titleMap);
  FadeIn(3, true);
  Print(3, 24, strToggle);

  /* Print the list */
  for (i = 0; i < 16; i++) {
    t = base + (uint16_t) i;

    /* To always generate the same names */
    srandom(t);

    PrintInt(8, 8 + i, t, 0);
    SetTile(9, 8 + i, PERIOD_TILE);
    Print(11, 8 + i,
      (const char *) pgm_read_word(names +
      ((t % 10) * 3) +
      ((t < 30? t / 10: random() % 3))));
  }

  i = (goingUp? 15 : 0);
  SetTile(3, 8 + i, ARROW_TILE);

  while (1) {
    controllerStart();
    if (!(--nextColorChange)) {
      rtDrawRectangle(nextLetter++, 0, 0, 8, 8, random());
      nextLetter %= 8;
      nextColorChange = COLOR_CHANGE_DELAY;
    }

    if (pressed[0] & (BTN_DOWN | BTN_UP | BTN_RIGHT | BTN_LEFT | BTN_START))
      playSound(MOVE_SELECTION_PATCH);

    if (pressed[0] & BTN_DOWN) {
      if (i < 15) {
        SetTile(3, 8 + i++, 0);
        SetTile(3, 8 + i, ARROW_TILE);
      }
      else {
        base += 16;
        goingUp = 0;
        controllerEnd();
        goto draw_page;
      }
    }
    else if (pressed[0] & BTN_UP) {
      if (i) {
        SetTile(3, 8 + i--, 0);
        SetTile(3, 8 + i, ARROW_TILE);
      }
      else {
        base -= 16;
        goingUp = 1;
        controllerEnd();
        goto draw_page;
      }
    }
    else if (pressed[0] & BTN_RIGHT) {
        base += 16;
        goingUp = 0;
        controllerEnd();
        goto draw_page;
    }
    else if (pressed[0] & BTN_LEFT) {
        base -= 16;
        goingUp = 0;
        controllerEnd();
        goto draw_page;
    }
    else if (pressed[0] & BTN_SL) {
      if (IsSongPlaying())
        cutSong();
      else
        ResumeSong();
    }
    /* To properly read the controller */
    else if (pressed[0] & BTN_START) {
      controllerEnd();
      break;
    }

    WaitVsync(1);
    controllerEnd();
  }

  FadeOut(3, true);

  return (base + (uint16_t) i);
}

void drawBaseTitle(uint16_t game) {
  ClearVram();
  Print(5, 21, strCFlavio);
  Print(5, 23, strLicense);
  Print(7, 24, strMIT);

  srandom(game);
  const char *name = (const char *) pgm_read_word(names + (game%10)*3
      + ((game<30? game / 10: random() %3)));
  uint8_t len;
  for (len = 0; pgm_read_byte(name+len); len++);
  Print(15-len/2, 5, name);
}

int8_t twoPlayersMenu() {
  uint8_t i;
  uint32_t r;

  Print(12, 15, strVsCpu);
  Print(12, 16, strVsHuman);
  Print(12, 17, strExit);
  SetTile(10, 15, ARROW_TILE);
  FadeIn(3, true);

  i = 0;
  r = 0;
  while (1) {
    controllerStart();

    if (pressed[0] & (BTN_DOWN | BTN_UP | BTN_START))
      playSound(MOVE_SELECTION_PATCH);

    if (pressed[0] & BTN_DOWN) {
      SetTile(10, 15 + i, 0);
      i = (i + 1) % 3;
      SetTile(10, 15 + i, ARROW_TILE);
    }
    else if (pressed[0] & BTN_UP) {
      SetTile(10, 15 + i, 0);
      i = (6 + i - 1) % 3;
      SetTile(10, 15 + i, ARROW_TILE);
    }
    else if (pressed[0] & BTN_START) {
      controllerEnd();
      srandom(r);

      FadeOut(3, true);
      FadeIn(3, false);
      return i;
    }

    r++;
    WaitVsync(1);
    controllerEnd();
  }
}

int8_t onePlayerMenu(uint8_t level, uint8_t levels) {
  int8_t i = 0;
  uint32_t r = 0;

  Print(12, 16, strStart);
  Print(12, 17, strExit);
  SetTile(10, 16, ARROW_TILE);
  FadeIn(3, true);

  while (1) {
    controllerStart();

    if (pressed[0] & (BTN_DOWN | BTN_UP | BTN_RIGHT | BTN_LEFT | BTN_START))
      playSound(MOVE_SELECTION_PATCH);

    SetTile(10, 16 + i, 0);
    if (pressed[0] & BTN_DOWN)
      i = (i + 1) & 1;
    else if (pressed[0] & BTN_UP)
      i = (i - 1) & 1;
    else if (pressed[0] & BTN_LEFT && !i) {
      /* Level is unsigned */
      if (--level >= levels)
        level = levels-1;
    }
    else if (pressed[0] & BTN_RIGHT && !i) {
      if (++level >= levels)
        level = 0;
    }
    else if (pressed[0] & BTN_START) {
      controllerEnd();
      srandom(r);
      FadeOut(3, true);
      FadeIn(3, false);
      return (i? -1 : level);
    }

    SetTile(10, 16 + i, ARROW_TILE);
    if (levels)
      PrintByte(20, 16, level, 0);

    r++;
    WaitVsync(1);
    controllerEnd();
  }
}

int main() {
  uint16_t game;
  int8_t r;
  uint8_t trollenLevel = 0;
  InitMusicPlayer(patch_struct);
  SetMasterVolume(0x7f);
  SetTileTable(tileset);
  SetFontTilesIndex(0);
  StartSong(zipzipzip);

  while (1) {
    beginning:
    game = topmenu();

    while (1) {
      drawBaseTitle(game);

      switch(game % 10) {
        case 0:
          /* Greed */
          loadColoredNumbers();
          greedLoadBatteryTiles();
          DrawMap2(9, 7, (const char *) pgm_read_word(batteries + random()%5));
          DrawMap2(13, 7,
              (const char *) pgm_read_word(batteries + random()%5));
          DrawMap2(17, 7,
              (const char *) pgm_read_word(batteries + random()%5));

          r = twoPlayersMenu();
          if (r == 2)
            goto beginning;
          greed(r);
          break;

        case 1:
          /* The Grid */
          r = twoPlayersMenu();
          if (r == 2)
            goto beginning;
          grid(r+1);
          break;

        case 2:
          /* Trollen */
          trollenLoadBaseTiles();
          trollenDrawTitle();

          r = onePlayerMenu(trollenLevel, NUM_TROLLEN_LEVELS);
          if (r == -1)
            goto beginning;
          trollenLevel = trollen(r);
          break;

        case 3:
          /* Slide */
          r = onePlayerMenu(0, 0);
          if (r == -1)
            goto beginning;
          SetTileTable(marumbi);
          loadFrame(DEFAULT_GRAY, 30);
          slide();
          break;

        case 4:
          /* The One */
          theOneLoadTiles();
          loadFrame(DEFAULT_GRAY, 30);
          r = onePlayerMenu(0, NUM_THE_ONE_BOARDS);
          if (r == -1)
            goto beginning;
          theOne(r);
          break;

        case 5:
          /* Monster */
          DrawMap2(4, 7, wumpusMap);
          Print(7, 7, strMonster0);
          DrawMap2(4, 9, redRoomMap);
          Print(7, 9, strMonster1);
          Print(6, 10, strMonster2);
          DrawMap2(4, 11, holeMap);
          Print(7, 11, strMonster3);
          DrawMap2(4, 13, greenRoomMap);
          Print(7, 13, strMonster4);
          Print(6, 14, strMonster5);

          r = onePlayerMenu(0, 0);
          if (r == -1)
            goto beginning;
          loadFrame(SKY_COLOR, 30);
          monster();
          break;

        case 6:
          /* Survival */
          loadColoredNumbers();
          /* Overwrite the crossed-out numbers */
          loadFrame(DEFAULT_GRAY, 20);
          r = twoPlayersMenu();
          if (r == 2)
            goto beginning;
          survival(r+1);
          break;

        case 7:
          /* Rain */
          loadColoredNumbers();
          /* Overwrite the crossed-out numbers */
          loadFrame(DEFAULT_GRAY, 20);
          r = twoPlayersMenu();
          if (r == 2)
            goto beginning;
          rain(r+1);
          break;

        case 8:
          /* Array */
          loadColoredNumbers();
          loadFrame(DEFAULT_GRAY, 30);
          r = twoPlayersMenu();
          if (r == 2)
            goto beginning;
          array(r);
          break;

        case 9:
          /* Rich */
          loadColoredNumbers();
          r = onePlayerMenu(0, 0);
          if (r == -1)
            goto beginning;
          rich();
          break;

        default:
          goto beginning;
      }
      controllerEnd();

      FadeOut(3, true);
      SetTileTable(tileset);
    }
  }

  return 0;
}
