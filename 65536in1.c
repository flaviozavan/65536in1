#include <stdint.h>
#include <stdlib.h>
#include <uzebox.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "data/tileset.inc"

#define ARROW_TILE 10
#define PAINTED_TILE 11
#define PERIOD_TILE 14
#define SKY_TILE 0xbb
#define HIT_TILE 0xbd
#define FIRE_TILE 0xbf
#define CRACK_TILE 0xc0
#define WHITE_NUMBER 16
#define BLUE_NUMBER 64
#define GREEN_NUMBER 74
#define CPU_DELAY 30
#define STENCH_ROOM 1
#define BREEZE_ROOM 2
#define BOTH_ROOM 3
#define WUMPUS_ROOM 4
#define HOLE_ROOM 5
#define CORRIDOR 6
#define CAVE_WIDTH 12
#define CAVE_HEIGHT 10
#define MOVE_DELAY 20
#define SHOT_DELAY 60

const char strGreed[] PROGMEM = "GREED";
const char strPiles[] PROGMEM = "PILES";
const char strGrab[] PROGMEM = "GRAB";
const char str9[] PROGMEM = "9 SQUARES";
const char strGet[] PROGMEM = "GET 3";
const char strCircles[] PROGMEM = "OS AND XS";
const char strEscape[] PROGMEM = "ESCAPE";
const char strRun[] PROGMEM = "RUN";
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
const char strChampionship[] PROGMEM = "CHAMPIONSHIP";
const char strDuel[] PROGMEM = "DUEL";
const char strRacquet[] PROGMEM = "RACQUET";
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
  str9, strGet, strCircles,
  strEscape, strRun, strAdventure,
  strSlide, strPuzzle, strAncient,
  strOne, strRemove, strTake,
  strMonster, strDungeon, strHunt,
  strChampionship, strDuel, strRacquet,
  strRain, strFalling, strReflex,
  strArray, strSort, strFast,
  strRich, strChests, strDream
};

const char strVsCpu[] PROGMEM = "VS CPU";
const char strVsHuman[] PROGMEM = "VS HUMAN";
const char strExit[] PROGMEM = "EXIT";
const char strCFlavio[] PROGMEM = "\\ 2012 FL^VIO ZAVAN";
const char strLicense[] PROGMEM = "CODE LICENSED UNDER";
const char strMIT[] PROGMEM = "THE MIT LICENSE";
const char strTurn[] PROGMEM = "PLAYER  'S TURN";
const char strWins[] PROGMEM = "PLAYER   WINS";
const char strStart[] PROGMEM = "START";
const char strStarting[] PROGMEM = "PICK THE STARTING CHEST";
const char strSee[] PROGMEM = "LET'S SEE WHAT";
const char strInside[] PROGMEM = "WAS INSIDE THE CHEST";
const char strPhone[] PROGMEM = "THE PHONE IS RINGING";
const char strBanker[] PROGMEM = "IT'S THE BANKER";
const char strOffer[] PROGMEM = "HE'S OFFERING YOU";
const char strFor[] PROGMEM = "FOR YOUR CHEST";
const char strAccept[] PROGMEM = "ACCEPT";
const char strRefuse[] PROGMEM = "REFUSE";
const char strReceived[] PROGMEM = "YOU RECEIVED";
const char strCongratulations[] PROGMEM = "CONGRATULATIONS,";
const char strWantKeep[] PROGMEM = "DO YOU WANT TO KEEP";
const char strChestNo[] PROGMEM = "CHEST  OR DO YOU";
const char strTradeChest[] PROGMEM = "TRADE IT FOR CHEST   ?";
const char strKeep[] PROGMEM = "KEEP";
const char strTrade[] PROGMEM = "TRADE";
const char strInsideDef[] PROGMEM = "WAS INSIDE CHEST";
const char strCongrat[] PROGMEM = "CONGRATULATIONS";
const char strPlayer1[] PROGMEM = "PLAYER 1:";
const char strPlayer2[] PROGMEM = "PLAYER 2:";
const char strGenerating[] PROGMEM = "GENERATING A";
const char strGraph[] PROGMEM = "CONNECTED PLANAR GRAPH";
const char strWait[] PROGMEM = "PLEASE WAIT";
const char strAte[] PROGMEM = "THE WUMPUS ATE YOU";
const char strFell[] PROGMEM = "YOU FELL IN A HOLE";
const char strKill[] PROGMEM = "YOU KILLED THE WUMPUS";
const char strLives[] PROGMEM = "LIVES:";
const char strScore[] PROGMEM = "SCORE:";
const char strGameOver[] PROGMEM = "GAME OVER";
const char strDraw[] PROGMEM = "DRAW";

const char * const batteries[] PROGMEM = {
  battery0Map,
  battery1Map,
  battery2Map,
  battery3Map,
  battery4Map
};

const uint32_t prizes[] PROGMEM = {
  50, 100, 500, 1000, 2500, 5000, 7500, 10000, 20000, 30000, 40000, 50000,
  75000, 100000, 500000, 1000000, 2500000, 5000000, 7500000, 10000000,
  20000000, 30000000, 40000000, 50000000, 75000000, 100000000
};

/* Controller Handling */
uint16_t held[2] = {0, 0},
  pressed[2] = {0, 0},
  released[2] = {0, 0},
  prev[2] = {0, 0};
/* Monster's */
uint8_t parent[CAVE_HEIGHT * CAVE_WIDTH];
uint8_t map[CAVE_HEIGHT][CAVE_WIDTH];

inline void controllerStart();
inline void controllerEnd();
void printColoredByte(uint8_t x, uint8_t y, uint8_t byte, uint8_t base);
void printColoredByte2(uint8_t x, uint8_t y, uint8_t byte, uint8_t base);
void printMoney(uint8_t x, uint8_t y, uint32_t value, uint8_t base);
void greed(uint8_t human);
void rich();
uint8_t testSlide(uint8_t *m);
void switchSlide(uint8_t p, uint8_t o, uint8_t *m);
void slide();
uint8_t getParent(uint8_t v);
uint8_t checkConnectivity(uint8_t map[CAVE_HEIGHT][CAVE_WIDTH], uint8_t l);
void flagAround(uint8_t y, uint8_t x, uint8_t f, uint8_t dist,
  uint8_t map[CAVE_HEIGHT][CAVE_WIDTH]);
void monster();
uint8_t testArray(uint8_t *m);
void rain(uint8_t human);
void sort(uint8_t human);
uint16_t topmenu();
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

void printColoredByte(uint8_t x, uint8_t y, uint8_t byte, uint8_t base) {
  SetTile(x--, y, base + (byte % 10));

  byte /= 10;
  SetTile(x--, y, (byte? base + (byte % 12) : 0));

  byte /= 10;
  SetTile(x--, y, (byte? base + (byte % 10) : 0));
}

void printColoredByte2(uint8_t x, uint8_t y, uint8_t byte, uint8_t base) {
  /* Print exactly two digits with zero padding */
  SetTile(x--, y, base + (byte % 10));

  byte /= 10;
  SetTile(x--, y, base + (byte % 10));
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
          printColoredByte(5 + 5 * w, 24, array[w], WHITE_NUMBER);
          w = (w + 1) % 5;
          printColoredByte(5 + 5 * w, 24, array[w], BLUE_NUMBER);
        }
        else if (pressed[t] & BTN_LEFT) {
          printColoredByte(5 + 5 * w, 24, array[w], WHITE_NUMBER);
          w = (10 + w - 1) % 5;
          printColoredByte(5 + 5 * w, 24, array[w], BLUE_NUMBER);
        }
        else if (pressed[t] & BTN_A && array[w]) {
          greed_select:
          s = (t && !human? 2 : 1);
          v = array[w];
          printColoredByte(5 + 5 * w, 24, array[w], GREEN_NUMBER);
        }
      }
      /* Reducing */
      else {
        if (pressed[t] & BTN_DOWN && v) {
          greed_reduce:
          Fill(3 + 5 * w, 21 - (--v << 1), 3, 2, 0);
          printColoredByte(5 + 5 * w, 24, v, GREEN_NUMBER);
        }
        else if (pressed[t] & BTN_UP && v < array[w]) {
          DrawMap2(3 + 5 * w, 21 - (v << 1),
            (const char *) pgm_read_word(batteries + w));
          printColoredByte(5 + 5 * w, 24, ++v, GREEN_NUMBER);
        }
        else if (pressed[t] & BTN_B) {
          for (i = 0; i < array[w]; i++) {
            DrawMap2(3 + 5 * w, 21 - (i << 1),
              (const char *) pgm_read_word(batteries + w));
          }
          s = 0;
          printColoredByte(5 + 5 * w, 24, array[w], BLUE_NUMBER);
        }
        else if (pressed[t] & BTN_A && v < array[w]) {
          greed_apply:
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

  /* Wait one of the players to press start */
  while (1) {
    controllerStart();

    if (pressed[0] & BTN_START || (human && pressed[1] & BTN_START)) {
      controllerEnd();
      break;
    }

    WaitVsync(1);
    controllerEnd();
  }
}

void printChests(uint8_t *available) {
  uint8_t y, x, i;

  x = 3;
  y = 4;
  for (i = 0; i < 26; i++) {
    if (!available[i]) {
      continue;
    }

    DrawMap2(x, y, closedChestMap);
    printColoredByte2(x + 2, y + 1, i, WHITE_NUMBER);

    x += 5;
    if (x > 23) {
      x = 3;
      y += 4;
    }
  }
}

void rich() {
  uint8_t i, n, s, left;
  uint8_t y, x;
  uint32_t r;
  uint8_t available[27];
  uint8_t order[26];
  memset(available, 1, sizeof(available));
  for (i = 0; i < 26; i++) {
    order[i] = i;
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
  Print(4, 6, strStarting);
  DrawMap2(13, 12, closedChestMap);
  printColoredByte2(15, 13, 0, GREEN_NUMBER);
  while (1) {
    controllerStart();

    if (pressed[0] & BTN_DOWN || pressed[0] & BTN_LEFT) {
      s = (25 + s) % 26;
      printColoredByte2(15, 13, s, GREEN_NUMBER);
    }
    else if (pressed[0] & BTN_UP || pressed[0] & BTN_RIGHT) {
      s = (s + 1) % 26;
      printColoredByte2(15, 13, s, GREEN_NUMBER);
    }
    else if (pressed[0] & BTN_A) {
      available[s] = 0;
      controllerEnd();
      break;
    }

    WaitVsync(1);
    controllerEnd();
  }

  left = 25;
  r = 0;

  /* Play */
  while (1) {
    /* Pick a chest */
    ClearVram();
    printChests(available);

    for (i = 0; !available[i]; i++);
    printColoredByte2(5, 5, i, BLUE_NUMBER);
    x = 3;
    y = 4;
    while (1) {
      controllerStart();

      if (pressed[0] & BTN_RIGHT) {
        printColoredByte2(x + 2, y + 1, i, WHITE_NUMBER);

        /* The array is 27 elements long, and 26 is always one */
        for (i = i + 1; !available[i]; i++);
        if (i == 26) {
          for (i = 0; !available[i]; i++);
          x = 3;
          y = 4;
        }
        else {
          x += 5;
          if (x > 23) {
            x = 3;
            y += 4;
          }
        }

        printColoredByte2(x + 2, y + 1, i, BLUE_NUMBER);
      }
      else if (pressed[0] & BTN_LEFT) {
        printColoredByte2(x + 2, y + 1, i, WHITE_NUMBER);

        for (i = i - 1; !available[i] && i < 255; i--);
        if (i == 255) {
          for (i = 25; !available[i]; i--);
          x = 3 + ((left - 1) % 5) * 5;
          y = 4 + ((left - 1) / 5) * 4;
        }
        else {
          x -= 5;
          if (x > 23) {
            x = 23;
            y -= 4;
          }
        }

        printColoredByte2(x + 2, y + 1, i, BLUE_NUMBER);
      }
      else if (pressed[0] & BTN_A) {
        controllerEnd();
        break;
      }
      else if (pressed[0] & BTN_SELECT) {
        controllerEnd();
        return;
      }

      WaitVsync(1);
      controllerEnd();
    }

    /* Open the chest */
    left--;
    available[i] = 0;

    ClearVram();
    Print(8, 5, strSee);
    Print(5, 6, strInside);
    DrawMap2(13, 12, closedChestMap);

    WaitVsync(60);

    DrawMap2(13, 12, openChestMap);
    printMoney(19, 10, pgm_read_dword(prizes + order[i]), WHITE_NUMBER);

    /* Wait for the input */
    while (1) {
      controllerStart();

      if (pressed[0] & BTN_A) {
        controllerEnd();
        break;
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
      while (1) {
        controllerStart();

        if (pressed[0] & BTN_A) {
          if (n) {
            s ^= i;
            i ^= s;
            s ^= i;
          }

          r = pgm_read_dword(prizes + order[s]);

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

          /* Wait for the input */
          while (1) {
            controllerStart();

            if (pressed[0] & BTN_A) {
              controllerEnd();
              break;
            }

            WaitVsync(1);
            controllerEnd();
          }
          break;
        }
        else if (pressed[0] & BTN_DOWN || pressed[0] & BTN_UP) {
          SetTile(10, 15 + n, 0);
          n ^= 1;
          SetTile(10, 15 + n, ARROW_TILE);
        }
        else if (pressed[0] & BTN_SELECT) {
          controllerEnd();
          return;
        }

        WaitVsync(1);
        controllerEnd();
      }

      goto rich_ending;
    }

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
    WaitVsync(60);
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
    while (1) {
      controllerStart();

      if (pressed[0] & BTN_A) {
        controllerEnd();

        if (!i) {
          goto rich_ending;
        }
        break;
      }
      else if (pressed[0] & BTN_UP || pressed[0] & BTN_DOWN) {
        SetTile(10, 18 + i, 0);
        i ^= 1;
        SetTile(10, 18 + i, ARROW_TILE);
      }
      else if (pressed[0] & BTN_SELECT) {
        controllerEnd();
        return;
      }

      WaitVsync(1);
      controllerEnd();
    }
  }

  rich_ending:
  ClearVram();
  Print(8, 6, strCongratulations);
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
  DrawMap2((p & 3) * 6 + 3, (p >> 2) * 5 + 4, boxMap);
  printColoredByte2((p & 3) * 6 + 6,
    (p >> 2) * 5 + 6, m[p],
    WHITE_NUMBER);

  Fill((o & 3) * 6 + 3, (o >> 2) * 5 + 4, 6, 5, 0);
}

void slide() {
  uint8_t m[16];
  uint8_t i, p;

  for (i = 0; i < 16; i++) {
    m[i] = i;
  }

  /* Randomize the board */
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
  ClearVram();
  for (i = 0; i < 16; i++) {
    if (!m[i]) continue;
    DrawMap2((i & 3) * 6 + 3, (i >> 2) * 5 + 4, boxMap);
    printColoredByte2((i & 3) * 6 + 6,
      (i >> 2) * 5 + 6, m[i],
      WHITE_NUMBER);
  }

  /* Process the input */
  while (1) {
    controllerStart();

    if (pressed[0] & BTN_UP && (p >> 2) < 3) {
      switchSlide(p, p + 4, m);
      p += 4;

      if (testSlide(m)) {
        controllerEnd();
        break;
      }
    }
    else if (pressed[0] & BTN_DOWN && p >> 2) {
      switchSlide(p, p - 4, m);
      p -= 4;

      if (testSlide(m)) {
        controllerEnd();
        break;
      }
    }
    else if (pressed[0] & BTN_LEFT && (p & 3) < 3) {
      switchSlide(p, p + 1, m);
      p += 1;

      if (testSlide(m)) {
        controllerEnd();
        break;
      }
    }
    else if (pressed[0] & BTN_RIGHT && p & 3) {
      switchSlide(p, p - 1, m);
      p -= 1;

      if (testSlide(m)) {
        controllerEnd();
        break;
      }
    }
    else if (pressed[0] & BTN_SELECT) {
      controllerEnd();
      return;
    }

    WaitVsync(1);
    controllerEnd();
  }

  /* Winning screen */
  ClearVram();
  Print(8, 12, strCongrat);
  while (1) {
    controllerStart();
    if (pressed[0] & BTN_START) break;
    WaitVsync(1);
    controllerEnd();
  }
  controllerEnd();
}

/* No memory for recursion */
uint8_t getParent(uint8_t v) {
  uint8_t i, o;

  for (i = v; parent[i] != i; i = parent[i]);
  o = parent[v];
  parent[v] = i;
  for (; parent[v] != v; v = o) {
    o = parent[v];
    parent[v] = i;
  }

  return i;
}

uint8_t checkConnectivity(uint8_t map[CAVE_HEIGHT][CAVE_WIDTH], uint8_t l) {
  uint8_t i, y, x, yy, xx, d;
  /* 255 == -1 because of the overflow */
  const uint8_t dx[] = {0, 1, 0, 255};
  const uint8_t dy[] = {255, 0, 1, 0};
  const uint8_t cor[2][4] =
    {
      {1, 0, 3, 2},
      {3, 2, 1, 0}
    };

  /* Parent array for the union find structure */
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      parent[(y << 4) | x] = (y << 4) | x;
    }
  }

  /* Union all the edges */
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (map[y][x] == HOLE_ROOM) continue;
      for (i = 0; i < 4; i++) {
        yy = y + CAVE_HEIGHT + dy[i];
        yy %= CAVE_HEIGHT;
        xx = x + CAVE_WIDTH + dx[i];
        xx %= CAVE_WIDTH;
        d = i;
        while (map[yy][xx] >= CORRIDOR) {
          /* No += and no % on the same line,
           * weirdest casting related bugs. */
          d = cor[map[yy][xx] - CORRIDOR][d];
          yy = yy + CAVE_HEIGHT + dy[d];
          yy %= CAVE_HEIGHT;
          xx = xx + CAVE_WIDTH + dx[d];
          xx %= CAVE_WIDTH;

          /* Detect and reject corridor loops */
          if (yy == y && xx == x && map[y][x] >= CORRIDOR)
            return 0;
        }

        /* Don't union holes or corridors */
        if (map[y][x] < CORRIDOR &&
          map[yy][xx] != HOLE_ROOM &&
          getParent((y << 4) | x) != getParent((yy << 4) | xx)) {

          l--;
          parent[parent[(y << 4) | x]] = parent[(yy << 4) | xx];
        }
      }
    }
  }

  return (l == 1);
}

void flagAround(uint8_t y, uint8_t x, uint8_t f, uint8_t dist,
  uint8_t map[CAVE_HEIGHT][CAVE_WIDTH]) {
  /* 255 == -1 because of the overflow */
  const uint8_t dx[] = {0, 1, 0, 255};
  const uint8_t dy[] = {255, 0, 1, 0};
  const uint8_t cor[2][4] =
    {
      {1, 0, 3, 2},
      {3, 2, 1, 0}
    };
  uint8_t yy, xx, i, d;

  for (i = 0; i < 4; i++) {
    yy = y + CAVE_HEIGHT + dy[i];
    yy %= CAVE_HEIGHT;
    xx = x + CAVE_WIDTH + dx[i];
    xx %= CAVE_WIDTH;
    d = i;
    while (map[yy][xx] >= CORRIDOR) {
      /* No += and no % on the same line,
       * weirdest casting related bugs. */
      d = cor[map[yy][xx] - CORRIDOR][d];
      yy = yy + CAVE_HEIGHT + dy[d];
      yy %= CAVE_HEIGHT;
      xx = xx + CAVE_WIDTH + dx[d];
      xx %= CAVE_WIDTH;
    }

    if (map[yy][xx] < BOTH_ROOM) {
      map[yy][xx] |= f;
      if (dist > 1)
        flagAround(yy, xx, f, dist - 1, map);
    }
  }
}

void monster() {
  uint8_t i, n, t, l, x, y, d, wx, wy, yy, xx;
  const char *rooms[] = {clearRoomMap,
    redRoomMap,
    greenRoomMap,
    bothRoomMap,
    wumpusMap,
    holeMap,
    corridor1Map,
    corridor2Map,
    guyMap,
    redGuyMap,
    greenGuyMap,
    bothGuyMap,
    wumpusMap,
    holeMap,
    corridor1Map,
    corridor2Map};
  const uint8_t dx[] = {0, 1, 0, 255};
  const uint8_t dy[] = {255, 0, 1, 0};
  const uint8_t cor[2][4] =
    {
      {1, 0, 3, 2},
      {3, 2, 1, 0}
    };

  /* Print loading screen */
  ClearVram();
  Print(9, 9, strGenerating);
  Print(4, 10, strGraph);
  Print(9, 14, strWait);

  /* Generate a map */
  generate_cave:
  memset(map, 0, sizeof(map));
  /* Corridors */
  n = (random() % 31) + 60;
  l = CAVE_WIDTH * CAVE_HEIGHT;
  for (i = 0; i < n; i++) {
    /* Remove the t-th clean room */
    t = random() % l;
    for (y = 0; y < CAVE_HEIGHT; y++) {
      for (x = 0; x < CAVE_WIDTH; x++) {
        if (!map[y][x] && !(t--)) goto tth_found;
      }
    }
    tth_found:
    l--;
    map[y][x] = CORRIDOR + (random() & 1);
  }

  /* Holes */
  n = (random() % 8) + 1;
  for (i = 0; i < n; i++) {
    /* Make the t-th clean room a hole */
    t = random() % l;
    for (y = 0; y < CAVE_HEIGHT; y++) {
      for (x = 0; x < CAVE_WIDTH; x++) {
        if (map[y][x] <= BOTH_ROOM && !(t--)) goto tth_found_hole;
      }
    }
    tth_found_hole:
    l--;
    map[y][x] = HOLE_ROOM;
    /* Put the breeze on the adjacent rooms */
    flagAround(y, x, BREEZE_ROOM, 1, map);
  }

  /* Wumpus */
  t = random() % l;
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (map[y][x] <= BOTH_ROOM && !(t--)) goto tth_found_wumpus;
    }
  }
  tth_found_wumpus:
  map[y][x] = WUMPUS_ROOM;
  wy = y;
  wx = x;
  /* Put the stench on the adjacent rooms */
  flagAround(y, x, STENCH_ROOM, 2, map);

  /* Guy */
  i = 0;
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (!map[y][x]) i++;
    }
  }
  t = random() % i;
  for (y = 0; y < CAVE_HEIGHT; y++) {
    for (x = 0; x < CAVE_WIDTH; x++) {
      if (!map[y][x] && !(t--)) goto tth_found_guy;
    }
  }
  /* This shouldn't happen, but just in case there are no clean rooms */
  goto generate_cave;
  tth_found_guy:

  /* Only accept connected graphs */
  if (!checkConnectivity(map, l)) goto generate_cave;

  /* If the highest bit is set, the room is visible */
  map[y][x] |= 0x80;

  /* Process input */
  l = 0;
  ClearVram();
  while (1) {
    /* Redraw */
    for (i = 0; i < CAVE_HEIGHT; i++) {
      for (n = 0; n < CAVE_WIDTH; n++) {
        if (map[i][n] & 0x80) {
          DrawMap2(3 + (n << 1),
            4 + (i << 1),
            rooms[(i == y && x == n? 8 : 0) +
            (map[i][n] & 0x7f)]);
        }
      }
    }

    /* Draw the targets if shooting */
    for (i = 0; l && i < 4; i++) {
      yy = y + CAVE_HEIGHT + dy[i];
      yy %= CAVE_HEIGHT;
      xx = x + CAVE_WIDTH + dx[i];
      xx %= CAVE_WIDTH;

      DrawMap2(3 + (xx << 1),
        4 + (yy << 1),
        targetMap);
    }
    /* End game */
    if ((map[y][x] & 0x7f) >= WUMPUS_ROOM) break;

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
      l ^= 1;
      ClearVram();
    }
    else if (pressed[0] & BTN_SELECT) {
      controllerEnd();
      return;
    }

    /* Moving */
    if (d != 0xff) {
      yy = y;
      xx = x;

      y = y + CAVE_HEIGHT + dy[d];
      y %= CAVE_HEIGHT;
      x = x + CAVE_WIDTH + dx[d];
      x %= CAVE_WIDTH;
      while ((map[y][x] & 0x7f) >= CORRIDOR) {
        map[y][x] |= 0x80;
        d = cor[(map[y][x] & 0x7f) - CORRIDOR][d];
        y = y + CAVE_HEIGHT + dy[d];
        y %= CAVE_HEIGHT;
        x = x + CAVE_WIDTH + dx[d];
        x %= CAVE_WIDTH;
      }
      map[y][x] |= 0x80;
      /* Shooting */
      if (l) {
        if ((map[y][x] & 0x7f) != WUMPUS_ROOM) {
          y = wy;
          x = wx;
        }
        else {
          x = xx;
          y = yy;
        }
        controllerEnd();
        break;
      }
    }

    controllerEnd();
    WaitVsync(1);
  }

  /* Print the result */
  switch(map[y][x] & 0x7f) {
    case WUMPUS_ROOM:
      Print(6, 14, strAte);
      break;

    case HOLE_ROOM:
      Print(6, 14, strFell);
      break;

    default:
      Print(8, 6, strCongratulations);
      Print(4, 14, strKill);
  }
  while (1) {
    controllerStart();
    if (pressed[0] & BTN_START) break;
    WaitVsync(1);
    controllerEnd();
  }
  controllerEnd();

  /* Draw the hole cave */
  for (i = 0; i < CAVE_HEIGHT; i++) {
    for (n = 0; n < CAVE_WIDTH; n++) {
      DrawMap2(3 + (n << 1),
        4 + (i << 1),
        rooms[(i == y && x == n? 8 : 0) +
        (map[i][n] & 0x7f)]);
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

uint8_t testArray(uint8_t *m) {
  int i;
  for (i = 1; i < 16; i++) {
    if (m[i] < m[i - 1]) return 0;
  }
  return 1;
}

void rain(uint8_t human) {
  int8_t l[2] = {16, 16};
  uint8_t i, n, s = 0;
  /* Movement delay, shot delay, next movement, next shot */
  uint8_t md = MOVE_DELAY, sd = SHOT_DELAY, nm = md, ns = 120;
  uint8_t canons[20], ground[20];
  const uint8_t bitt[12] = {0, 1, 0, 0, 2, 3, 4, 5, 6, 7, 8, 9};

  memset(canons, 0, sizeof(canons));
  memset(ground, 0, sizeof(ground));

  /* Draw the basic screen */
  ClearVram();
  Fill(0, 5, 30, 19, SKY_TILE);
  Fill(14, 0, 2, 28, PAINTED_TILE);
  for (i = 0; i <= human; i++) {
    for (n = 0; n < 10; n++) {
      DrawMap2(3 + n + (15 * i), 6, canonMap);
      SetTile(3 + n + (15 * i), 24, CRACK_TILE);
    }
    Print(3 + 15 * i, 4, strLives);
    printColoredByte2(11 + (15 * i) , 4, l[i], GREEN_NUMBER);
  }
  if (!human) {
    Print(18, 4, strScore);
    printColoredByte2(26 , 4, s, GREEN_NUMBER);
  }

  /* Process the input */
  while (l[0] || l[2]) {
    controllerStart();

    /* Destroy falling numbers */
    for (i = 0; i <= human; i++) {
      for (n = 0; n < 12; n++) {
        if (n == 2 || n == 3) continue;
        if (pressed[i] & (1 << n)) {
        }
      }
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
  if (!human) {
    Print(10, 10, strGameOver);
    Print(10, 12, strScore);
    printColoredByte2(18, 12, s, GREEN_NUMBER);
  }
  /* Announce the winner. */
  else {
    if (l[0] == l[1]) {
      Print(12, 12, strDraw);
    }
    else {
      Print(8, 14, strWins);
      SetTile(15, 14, WHITE_NUMBER + 1 + (l[1] > l[0]));
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

void sort(uint8_t human) {
  uint8_t m[2][16], i, n, p[2], s[2], d;

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
  s[0] = s[1] = 0xff;

  /* Print the initial arrays */
  ClearVram();
  Print(10, 6, strPlayer1);
  Print(10, 14, strPlayer2);
  for (i = 0; i < 8; i++) {
    printColoredByte2(3 * i + 4,
      8, m[0][i],
      (i? WHITE_NUMBER : BLUE_NUMBER));
    printColoredByte2(3 * i + 4,
      10, m[0][i + 8],
      WHITE_NUMBER);

    printColoredByte2(3 * i + 4,
      16, m[1][i],
      (i? WHITE_NUMBER : BLUE_NUMBER));
    printColoredByte2(3 * i + 4,
      18, m[1][i + 8],
      WHITE_NUMBER);
  }

  /* Initialize the AI delay */
  d = CPU_DELAY;

  /* Process input */
  while (1) {
    controllerStart();

    for (i = 0; i < 2; i++) {
      n = p[i];
      if (!i || human) {
        if (pressed[i] & BTN_RIGHT) {
          sort_press_right:
          n = (p[i] + 1) & 0xf;
          if (n == s[i]) n = (n + 1) & 0xf;
        }
        else if (pressed[i] & BTN_LEFT) {
          sort_press_left:
          n = (p[i] + 15) & 0xf;
          if (n == s[i]) n = (n + 15) & 0xf;
        }
        else if (pressed[i] & BTN_A) {
          sort_select:
          if (s[i] == 0xff) {
            printColoredByte2(3 * (p[i] & 7) + 4,
              (p[i] < 8? 8 : 10) + (i? 8 : 0),
              m[i][p[i]], GREEN_NUMBER);
            s[i] = p[i];
            p[i] = n = (p[i] + 15) & 0xf;
          }
          else {
            m[i][s[i]] ^= m[i][p[i]];
            m[i][p[i]] ^= m[i][s[i]];
            m[i][s[i]] ^= m[i][p[i]];

            printColoredByte2(3 * (p[i] & 7) + 4,
              (p[i] < 8? 8 : 10) + (i? 8 : 0),
              m[i][p[i]], WHITE_NUMBER);
            printColoredByte2(3 * (s[i] & 7) + 4,
              (s[i] < 8? 8 : 10) + (i? 8 : 0),
              m[i][s[i]], WHITE_NUMBER);

            s[i] = 0xff;

            if (testArray(m[i])) {
              controllerEnd();
              goto endSort;
            }
          }
        }
        else if (pressed[i] & BTN_B && s[i] != 0xff) {
          printColoredByte2(3 * (s[i] & 7) + 4,
            (s[i] < 8? 8 : 10) + (i? 8 : 0),
            m[i][s[i]], WHITE_NUMBER);

          s[i] = 0xff;
        }
        else if (!i && pressed[i] & BTN_SELECT) {
          controllerEnd();
          return;
        }
      }
      /* AI */
      else if (d) {
        /* Delay the movements */
        d--;
      }
      else {
        d = CPU_DELAY;

        /* Select a number in the wrong position */
        if (s[i] == 0xff) {
          if (m[i][p[i]] == p[i])
            goto sort_press_right;
          else
            goto sort_select;
        }
        /* Put it in the right place */
        else {
          if (m[i][s[i]] != p[i])
            if ((p[i] > m[i][s[i]] && p[i] - m[i][s[i]] < 8) ||
              (p[i] < m[i][s[i]] && m[i][s[i]] - p[i] > 8)) {

              goto sort_press_left;
            }
            else {
              goto sort_press_right;
            }
          else
            goto sort_select;
        }
      }

      printColoredByte2(3 * (p[i] & 7) + 4,
        (p[i] < 8? 8 : 10) + (i? 8 : 0),
        m[i][p[i]], WHITE_NUMBER);
      printColoredByte2(3 * (n & 7) + 4,
        (n < 8? 8 : 10) + (i? 8 : 0),
        m[i][n], BLUE_NUMBER);
      p[i] = n;
    }

    WaitVsync(1);
    controllerEnd();
  }
  endSort:
  ClearVram();

  Print(8, 14, strWins);
  SetTile(15, 14, WHITE_NUMBER + 1 + testArray(m[1]));
  while (1) {
    controllerStart();
    if (pressed[0] & BTN_START) break;
    WaitVsync(1);
    controllerEnd();
  }
  controllerEnd();
}

uint16_t topmenu() {
  uint16_t base = 0;
  uint16_t t;
  uint8_t i;
  char goingUp = 0;

  draw_page:
  /* Build the basic interface */
  ClearVram();
  DrawMap2(1, 2, titleMap);

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
    /* To properly read the controller */
    else if (pressed[0] & BTN_START) {
      controllerEnd();
      break;
    }

    WaitVsync(1);
    controllerEnd();
  }

  return (base + (uint16_t) i);
}

int main() {
  uint16_t ret;
  uint32_t r;
  uint8_t i;
  /* InitMusicPlayer(patches); */
  SetMasterVolume(0xff);
  SetTileTable(tileset);
  SetFontTilesIndex(0);
  /* SetSpritesTileTable(sprite); */

  while (1) {
    beginning:
    ret = topmenu();

    switch(ret % 10) {
      case 0:
        /* Greed */
        while (1) {
          /* Draw the menu */
          ClearVram();
          DrawMap2(9, 7, (const char *) pgm_read_word(batteries +
            (ret % 30) / 10));
          DrawMap2(13, 7, (const char *) pgm_read_word(batteries +
            (ret % 30) / 10));
          DrawMap2(17, 7, (const char *) pgm_read_word(batteries +
            (ret % 30) / 10));
          Print(((ret % 30) / 10 == 2? 13 : 12), 5,
            (const char *) pgm_read_word(names +
              ((ret % 30) / 10)));
          Print(12, 15, strVsCpu);
          Print(12, 16, strVsHuman);
          Print(12, 17, strExit);
          SetTile(10, 15, ARROW_TILE);
          Print(5, 21, strCFlavio);
          Print(5, 23, strLicense);
          Print(7, 24, strMIT);

          i = 0;
          r = 0;
          while (1) {
            controllerStart();

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
              if (i == 2) {
                goto beginning;
              }
              srandom(r);
              greed(i);
              break;
            }

            r++;
            WaitVsync(1);
            controllerEnd();
          }
        }
        break;

      case 3:
        /* Slide */
        while (1) {
          /* Draw the menu */
          ClearVram();
          Print((((ret % 30) / 10) == 2? 10 : 13), 5,
            (const char *) pgm_read_word(names + 9 +
              ((ret % 30) / 10)));
          Print(12, 15, strStart);
          Print(12, 16, strExit);
          SetTile(10, 15, ARROW_TILE);
          Print(5, 21, strCFlavio);
          Print(5, 23, strLicense);
          Print(7, 24, strMIT);

          i = 0;
          r = 0;
          while (1) {
            controllerStart();

            if (pressed[0] & BTN_DOWN) {
              SetTile(10, 15 + i, 0);
              i = (i + 1) & 1;
              SetTile(10, 15 + i, ARROW_TILE);
            }
            else if (pressed[0] & BTN_UP) {
              SetTile(10, 15 + i, 0);
              i = (6 + i - 1) & 1;
              SetTile(10, 15 + i, ARROW_TILE);
            }
            else if (pressed[0] & BTN_START) {
              controllerEnd();
              if (i) {
                goto beginning;
              }
              srandom(r);
              slide(i);
              break;
            }

            r++;
            WaitVsync(1);
            controllerEnd();
          }
        }
        break;

      case 5:
        /* Monster */
        while (1) {
          /* Draw the menu */
          ClearVram();
          Print((((ret % 30) / 10) == 2? 13 : 12), 5,
            (const char *) pgm_read_word(names + 15 +
              ((ret % 30) / 10)));
          DrawMap2(12, 7, redRoomMap);
          DrawMap2(14, 7, redRoomMap);
          DrawMap2(16, 7, redRoomMap);
          DrawMap2(12, 9, redRoomMap);
          DrawMap2(14, 9, wumpusMap);
          DrawMap2(16, 9, redRoomMap);
          DrawMap2(12, 11, redRoomMap);
          DrawMap2(14, 11, redRoomMap);
          DrawMap2(16, 11, redRoomMap);
          Print(12, 15, strStart);
          Print(12, 16, strExit);
          SetTile(10, 15, ARROW_TILE);
          Print(5, 21, strCFlavio);
          Print(5, 23, strLicense);
          Print(7, 24, strMIT);

          i = 0;
          r = 0;
          while (1) {
            controllerStart();

            if (pressed[0] & BTN_DOWN) {
              SetTile(10, 15 + i, 0);
              i = (i + 1) & 1;
              SetTile(10, 15 + i, ARROW_TILE);
            }
            else if (pressed[0] & BTN_UP) {
              SetTile(10, 15 + i, 0);
              i = (6 + i - 1) & 1;
              SetTile(10, 15 + i, ARROW_TILE);
            }
            else if (pressed[0] & BTN_START) {
              controllerEnd();
              if (i) {
                goto beginning;
              }
              srandom(r);
              monster(i);
              break;
            }

            r++;
            WaitVsync(1);
            controllerEnd();
          }
        }
        break;

      case 7:
        /* Rain */
        while (1) {
          /* Draw the menu */
          ClearVram();
          Print((((ret % 30) / 10) == 2? 10 : 13), 5,
            (const char *) pgm_read_word(names + 21 +
              ((ret % 30) / 10)));
          Print(12, 15, strVsCpu);
          Print(12, 16, strVsHuman);
          Print(12, 17, strExit);
          SetTile(10, 15, ARROW_TILE);
          Print(5, 21, strCFlavio);
          Print(5, 23, strLicense);
          Print(7, 24, strMIT);

          i = 0;
          r = 0;
          while (1) {
            controllerStart();

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
              if (i == 2) {
                goto beginning;
              }
              srandom(r);
              rain(i);
              break;
            }


            r++;
            WaitVsync(1);
            controllerEnd();
          }
        }
        break;

      case 8:
        /* Array */
        while (1) {
          /* Draw the menu */
          ClearVram();
          Print((((ret % 30) / 10) == 2? 10 : 13), 5,
            (const char *) pgm_read_word(names + 24 +
              ((ret % 30) / 10)));
          Print(12, 15, strVsCpu);
          Print(12, 16, strVsHuman);
          Print(12, 17, strExit);
          SetTile(10, 15, ARROW_TILE);
          Print(5, 21, strCFlavio);
          Print(5, 23, strLicense);
          Print(7, 24, strMIT);

          i = 0;
          r = 0;
          while (1) {
            controllerStart();

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
              if (i == 2) {
                goto beginning;
              }
              srandom(r);
              sort(i);
              break;
            }


            r++;
            WaitVsync(1);
            controllerEnd();
          }
        }
        break;

      case 9:
        /* Rich */
        while (1) {
          /* Draw the menu */
          ClearVram();
          DrawMap2(14, 7, openChestMap);
          Print(((ret % 30) / 10? 13 : 14), 5,
            (const char *) pgm_read_word(names + 27 +
              ((ret % 30) / 10)));
          Print(12, 15, strStart);
          Print(12, 16, strExit);
          SetTile(10, 15, ARROW_TILE);
          Print(5, 21, strCFlavio);
          Print(5, 23, strLicense);
          Print(7, 24, strMIT);

          i = 0;
          r = 0;
          while (1) {
            controllerStart();

            if (pressed[0] & BTN_DOWN) {
              SetTile(10, 15 + i, 0);
              i = (i + 1) % 2;
              SetTile(10, 15 + i, ARROW_TILE);
            }
            else if (pressed[0] & BTN_UP) {
              SetTile(10, 15 + i, 0);
              i = (6 + i - 1) % 2;
              SetTile(10, 15 + i, ARROW_TILE);
            }
            else if (pressed[0] & BTN_START) {
              controllerEnd();
              if (i) {
                goto beginning;
              }
              srandom(r);
              rich(i);
              break;
            }

            r++;
            WaitVsync(1);
            controllerEnd();
          }
        }
        break;

      default:
        goto beginning;
    }
  }

  return 0;
}
