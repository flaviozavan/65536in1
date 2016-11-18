/* Created with Uzebox Patch Studio 0.0.2 */
const char cannon_patch[] PROGMEM = {
  0, PC_WAVE, 0,
  0, PC_ENV_SPEED, -80,
  0, PC_PITCH, 70,
  4, PATCH_END,
};
const char explosion_patch[] PROGMEM = {
  0, PC_WAVE, 0,
  0, PC_ENV_SPEED, -32,
  0, PC_LOOP_START, 2,
  0, PC_PITCH, 30,
  0, PC_ENV_VOL, 255,
  8, PC_LOOP_END, 2,
  0, PATCH_END,
};
const char gets_piece_patch[] PROGMEM = {
  0, PC_WAVE, 0,
  0, PC_PITCH, 56,
  0, PC_ENV_SPEED, -6,
  20, PC_NOTE_UP, 3,
  0, PC_ENV_VOL, 255,
  0, PC_SLIDE, 12,
  0, PC_SLIDE_SPEED, 8,
  40, PATCH_END,
};
const char hits_floor_patch[] PROGMEM = {
  0, PC_WAVE, 1,
  0, PC_PITCH, 45,
  0, PC_ENV_SPEED, -32,
  8, PATCH_END,
};
const char loss_patch[] PROGMEM = {
  0, PC_WAVE, 1,
  0, PC_ENV_SPEED, -8,
  0, PC_PITCH, 58,
  8, PC_NOTE_DOWN, 12,
  0, PC_ENV_VOL, 255,
  10, PC_NOTE_DOWN, 5,
  0, PC_ENV_VOL, 255,
  16, PATCH_END,
};
const char move_selection_patch[] PROGMEM = {
  0, PC_WAVE, 0,
  0, PC_PITCH, 90,
  0, PC_ENV_SPEED, -64,
  4, PATCH_END,
};
const char phone_patch[] PROGMEM = {
  0, PC_WAVE, 8,
  0, PC_ENV_SPEED, -8,
  0, PC_PITCH, 90,
  0, PC_LOOP_START, 16,
  0, PC_ENV_VOL, 0,
  1, PC_ENV_VOL, 255,
  4, PC_LOOP_END, 0,
  0, PATCH_END,
};
const char place_battery_patch[] PROGMEM = {
  0, PC_WAVE, 2,
  0, PC_ENV_SPEED, -32,
  0, PC_PITCH, 70,
  4, PC_NOTE_UP, 10,
  0, PC_ENV_VOL, 255,
  8, PATCH_END,
};
const char slide_horizontal_patch[] PROGMEM = {
  0, PC_WAVE, 0,
  0, PC_ENV_SPEED, 0,
  0, PC_PITCH, 50,
  24, PC_NOTE_DOWN, 10,
  0, PC_ENV_VOL, 255,
  0, PC_ENV_SPEED, -80,
  4, PATCH_END,
};
const char slide_vertical_patch[] PROGMEM = {
  0, PC_WAVE, 0,
  0, PC_ENV_SPEED, 0,
  0, PC_PITCH, 50,
  20, PC_NOTE_DOWN, 10,
  0, PC_ENV_VOL, 255,
  0, PC_ENV_SPEED, -80,
  4, PATCH_END,
};
const char square_piano[] PROGMEM = {
  0, PC_WAVE, 9,
  0, PC_ENV_SPEED, -15,
  4, PC_ENV_SPEED, -7,
  0, PATCH_END,
};
const char take_battery_patch[] PROGMEM = {
  0, PC_WAVE, 2,
  0, PC_ENV_SPEED, -32,
  0, PC_PITCH, 70,
  4, PC_NOTE_DOWN, 10,
  0, PC_ENV_VOL, 255,
  8, PATCH_END,
};
const char victory_patch[] PROGMEM = {
  0, PC_WAVE, 1,
  0, PC_ENV_SPEED, -16,
  0, PC_PITCH, 70,
  8, PC_NOTE_UP, 12,
  0, PC_ENV_VOL, 255,
  10, PC_NOTE_UP, 5,
  0, PC_ENV_VOL, 255,
  16, PATCH_END,
};
const char walking_patch[] PROGMEM = {
  0, PC_WAVE, 1,
  0, PC_ENV_SPEED, -32,
  0, PC_LOOP_START, 2,
  0, PC_PITCH, 32,
  0, PC_ENV_VOL, 255,
  10, PC_LOOP_END, 0,
  0, PATCH_END,
};
const char hero_walking_patch[] PROGMEM = {
  0, PC_WAVE, 1,
  0, PC_ENV_SPEED, -32,
  0, PC_LOOP_START, 2,
  0, PC_PITCH, 40,
  0, PC_ENV_VOL, 255,
  10, PC_LOOP_END, 0,
  0, PATCH_END,
};
const char merge_patch[] PROGMEM = {
  0, PC_WAVE, 2,
  0, PC_ENV_SPEED, -6,
  0, PC_PITCH, 56,
  10, PC_NOTE_UP, 12,
  0, PC_ENV_VOL, 255,
  10, PC_NOTE_UP, 6,
  0, PC_ENV_VOL, 255,
  0, PC_SLIDE, -24,
  0, PC_SLIDE_SPEED, 8,
  40, PATCH_END,
};
const char stunned_patch[] PROGMEM = {
  0, PC_WAVE, 1,
  0, PC_ENV_SPEED, -6,
  0, PC_PITCH, 48,
  16, PC_NOTE_DOWN, 12,
  0, PC_ENV_VOL, 255,
  0, PC_TREMOLO_LEVEL, 64,
  0, PC_TREMOLO_RATE, 16,
  48, PATCH_END,
};
const struct PatchStruct patch_struct[] PROGMEM = {
  {0, NULL, square_piano, 0, 0},
  {0, NULL, square_piano, 0, 0},
  {0, NULL, move_selection_patch, 0, 0},
  {0, NULL, place_battery_patch, 0, 0},
  {0, NULL, take_battery_patch, 0, 0},
  {0, NULL, victory_patch, 0, 0},
  {0, NULL, loss_patch, 0, 0},
  {0, NULL, slide_horizontal_patch, 0, 0},
  {0, NULL, slide_vertical_patch, 0, 0},
  {0, NULL, cannon_patch, 0, 0},
  {0, NULL, explosion_patch, 0, 0},
  {0, NULL, hits_floor_patch, 0, 0},
  {0, NULL, gets_piece_patch, 0, 0},
  {0, NULL, phone_patch, 0, 0},
  {0, NULL, walking_patch, 0, 0},
  {0, NULL, hero_walking_patch, 0, 0},
  {0, NULL, merge_patch, 0, 0},
  {0, NULL, stunned_patch, 0, 0},
};
#define CANNON_PATCH 9
#define EXPLOSION_PATCH 10
#define GETS_PIECE_PATCH 12
#define HERO_WALKING_PATCH 15
#define HITS_FLOOR_PATCH 11
#define LOSS_PATCH 6
#define MERGE_PATCH 16
#define MOVE_SELECTION_PATCH 2
#define PHONE_PATCH 13
#define PLACE_BATTERY_PATCH 3
#define SLIDE_HORIZONTAL_PATCH 7
#define SLIDE_VERTICAL_PATCH 8
#define SQUARE_PIANO 0
#define STUNNED_PATCH 17
#define TAKE_BATTERY_PATCH 4
#define VICTORY_PATCH 5
#define WALKING_PATCH 14
