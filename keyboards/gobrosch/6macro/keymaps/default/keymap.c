/* Copyright 2019 joaofbmaia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  /* LAYER 0
  * ,-----------------------.
  * |  F13  |  F14  | F15/FN|  Hold for FN
  * |-------+-------+-------|
  * |  F16  |  F17  |  F18  |
  * `-------+-------+-------'
  */
  [0] = LAYOUT(
    LCA(KC_H), LCA(KC_J), LCA(KC_L),
    KC_VOLD, KC_VOLU, LT(1, KC_MUTE)
  ),

  /* LAYER 1
  * ,-----------------------.
  * |RGB_TOG|RGBMOD+|       |
  * |-------+-------+-------|
  * |RGBHUE+|RGBBRI+|Spec FN|   Hold along with previous to access special funtions (RESET)
  * `-------+-------+-------'
  */
  [1] = LAYOUT(
    RESET, KC_2, KC_3,
    LALT(KC_TAB), LSA(KC_TAB), _______
  ),

  /* LAYER 2
  * ,-----------------------.
  * | RESET |RGBMOD-|       |
  * |-------+-------+-------|
  * |RGBHUE-|RGBBRI-|       |
  * `-------+-------+-------'
  */
  [2] = LAYOUT(
    RESET, RGB_RMOD, KC_NO,
    RGB_HUD, RGB_VAD, KC_TRNS
  )
  
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } 
    return false;
}

// Light all 4 LEDs in red when keyboard layer 0 is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_RED}
);
// Light all 4 LEDs in cyam when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_CYAN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,    // initial layer
    my_layer1_layer     // Overrides layer 0
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    return state;
}