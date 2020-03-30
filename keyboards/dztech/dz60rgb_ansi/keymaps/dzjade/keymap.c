#include QMK_KEYBOARD_H
#define _DEFAULT 0
#define _MEDIA 1

#define FORCE_NKRO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_60_ansi(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,    KC_5,      KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,        KC_EQL,     KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,    KC_T,      KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,        KC_BSLS,
        MO(1),      KC_A,       KC_S,       KC_D,       KC_F,    KC_G,      KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,                                 KC_ENT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,    KC_B,      KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                                              KC_UP,
        KC_LCTL,    KC_LGUI,    KC_LALT,            KC_SPC,             MO(1),   KC_LEFT,   KC_DOWN,    KC_RIGHT
        ),

    [_MEDIA] = LAYOUT_60_ansi(
        KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,   KC_F5,     KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,      KC_F11,     KC_F12,             KC_DEL,
        KC_NO,      KC_NO,    KC_NO,      KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_INS,     KC_NO,      KC_PSCREEN,  KC_NO,      KC_NO,                    KC_PGUP,
        _______,    KC_NO,    KC_NO,      KC_NO,      KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,       KC_NO,                                 KC_PGDN,
        _______,    KC_NO,      KC_NO,      KC_CAPS,    KC_NO,   KC_NO,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_MPLY,                                              KC_VOLU,
        _______,    _______,    _______,            RESET,             _______,   KC_MPRV,   KC_VOLD,    KC_MNXT
    )
};

// led_config_t g_led_config = { {
//     {  13,  12,  11,  10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0 },
//     {  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14 },
//     {  40,  39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29, NO_LED,  28 },
//     {  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41, NO_LED, NO_LED },
//     {  60,  59,  58, NO_LED, NO_LED,  57, NO_LED, NO_LED, NO_LED,  56,  55,  54, NO_LED,  53 }
// }, {


//arrays of keys to choose, defined above by the manufacturer
int DEFAULT_A[] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
               40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 44, 43, 42,
               51, 50, 49, 48, 47, 46, 45, 57, 15, 16, 29, 30};
int DEFAULT_B[] = {13, 27, 40, 52, 60, 59, 58, 56, 55, 54, 53, 41, 28, 14, 0};

//P, I, Left Arrow, Right Arrow, Right Shift, Down Arrow, backspace for delete, page up and down
int MEDIA_ALPHA[] = {17, 19, 53, 54, 55, 41, 0, 28, 14, 49};

//F row
int F_ROW[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


//Get sizes of the arrays, lazy shorthand
int DEFAULT_A_SIZE = *(&DEFAULT_A + 1) - DEFAULT_A;
int DEFAULT_B_SIZE = *(&DEFAULT_B + 1) - DEFAULT_B;

int MEDIA_ALPHA_SIZE = *(&MEDIA_ALPHA + 1) - MEDIA_ALPHA;
int F_ROW_SIZE = *(&F_ROW + 1) - F_ROW;

//define colors by RGB values. manually adjusted for dz60rgb-ansi v1's purple pcb
static int BRIGHT_GREEN[] = {0, 255, 0};
static int PASTEL_GREEN[] = {30, 255, 30};
static int BRIGHT_PURPLE[] = {255, 0, 255};
// static int WHITE[] = {76.5, 255, 76.5};
static int WHITE2[] = {255, 255, 255};
static int BRIGHT_TEAL[] = {10, 255, 255};
static int BLACK[] = {0, 0, 0};

bool disable_rgb = 0;

// These shorthands are used below to set led colors on each matrix cycle
void loop_colorset(int *indices, int array_size, int* rgb) {
  for (int i = 0; i < array_size; i++) {
  rgb_matrix_set_color(indices[i], rgb[0], rgb[1], rgb[2]);
  }
}

// Code to change some led colors on layer change, using the above function
void rgb_matrix_indicators_user(void) {
  if (disable_rgb){loop_colorset(DEFAULT_A, DEFAULT_A_SIZE, BLACK);loop_colorset(DEFAULT_B, DEFAULT_B_SIZE, BLACK);}
  else {
  switch (biton32(layer_state)) {
      case _DEFAULT:
        loop_colorset(DEFAULT_A, DEFAULT_A_SIZE, WHITE2);  // set alpha layer
        loop_colorset(DEFAULT_B, DEFAULT_B_SIZE, PASTEL_GREEN);  // Set modifiers
        break;
      case _MEDIA:
        rgb_matrix_set_color_all(WHITE2[0], WHITE2[1], WHITE2[2]);
        loop_colorset(MEDIA_ALPHA, MEDIA_ALPHA_SIZE, BRIGHT_GREEN);
        loop_colorset(F_ROW, F_ROW_SIZE, BRIGHT_TEAL);
        break;
      default:
        loop_colorset(DEFAULT_A, DEFAULT_A_SIZE, PASTEL_GREEN);
        loop_colorset(DEFAULT_B, DEFAULT_B_SIZE, BRIGHT_PURPLE);
      break;
    }
  }
}
