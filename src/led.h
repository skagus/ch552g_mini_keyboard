#pragma once
#include <stdint.h>
// Key colors (hue value: 0..191)
#define NEO_RED    0x00F   // red
#define NEO_YEL    0x0FF   // yellow
#define NEO_GREEN  0x0F0   // green
#define NEO_CYAN   0xFF0   // cyan
#define NEO_BLUE   0xF00   // blue
#define NEO_MAG    0xF0F   // magenta
#define NEO_WHITE  0xFFF   // white
#define NEO_OFF    0x000   // Off.
#define NEO_BRIGHT_KEYS 1

enum led_keyboard_mode_t
{
  LED_LOOP,
  LED_FIX,
  LED_BLINK
};

void led_boot_mode();

// change led mode
void led_set_mode(enum led_keyboard_mode_t mode);

// set led color in FIX mode
void led_set_color_hue(uint8_t led0, uint8_t led1, uint8_t led2);

// update led task
void led_update();

//if in loop mode, change color to pressed key
void led_presskey(int key);

