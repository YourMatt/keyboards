#pragma once

#define NUMBER_OF_RGB_LAYERS 8

const rgblight_segment_t PROGMEM layer_green[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_GREEN}
);
const rgblight_segment_t PROGMEM layer_red[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_RED}
);
const rgblight_segment_t PROGMEM layer_blue[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_BLUE}
);
const rgblight_segment_t PROGMEM layer_white[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_WHITE}
);
const rgblight_segment_t PROGMEM layer_yellow[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM layer_orange[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM layer_cyan[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_CYAN}
);
const rgblight_segment_t PROGMEM layer_purple[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_PURPLE}
);

// rgb colors, redefine RGBLIGHT_MAX_LAYERS if using >8
const rgblight_segment_t* const PROGMEM default_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_green,
    layer_red,
    layer_blue,
    layer_white,
    layer_yellow,
    layer_orange,
    layer_cyan,
    layer_purple
);