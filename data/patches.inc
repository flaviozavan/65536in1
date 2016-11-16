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
const struct PatchStruct patch_struct[] PROGMEM = {
  {0, NULL, move_selection_patch, 0, 0},
  {0, NULL, place_battery_patch, 0, 0},
  {0, NULL, take_battery_patch, 0, 0},
  {0, NULL, victory_patch, 0, 0},
  {0, NULL, loss_patch, 0, 0},
};
#define LOSS_PATCH 4
#define MOVE_SELECTION_PATCH 0
#define PLACE_BATTERY_PATCH 1
#define TAKE_BATTERY_PATCH 2
#define VICTORY_PATCH 3
