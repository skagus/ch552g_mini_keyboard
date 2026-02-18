//#include <Arduino.h>
#include "usb/USBHIDKeyboardMouse.h"
#include "neo.h"
#include "util.h"
#include "led.h"
#include "keyboard.h"
#include "auto_mode.h"

static button_function_t button_auto_s = {BUTTON_NULL};
static uint8_t auto_counter_s = 0;
static uint32_t last_update = 0;

void auto_set_cycle(button_function_t* button_auto)
{
  auto_counter_s = 0;
  last_update = 0;
  button_auto_s = *button_auto;
  led_set_mode(LED_FIX);
  led_set_color_hue(NEO_RED, NEO_YEL, NEO_YEL);
}

void auto_update()
{
  if (button_auto_s.type == BUTTON_NULL)
  {
    return;
  }

  uint32_t current_time = millis();

  if (button_auto_s.type == BUTTON_AUTO_KEYBOARD)
  {
	  if(current_time - last_update < button_auto_s.function.sequence.delay)
	  {
		  return;
	  }
	  last_update = current_time;

    led_set_color_hue(NEO_GREEN, NEO_YEL, NEO_YEL);
    Keyboard_press(button_auto_s.function.sequence.sequence[auto_counter_s]);
    DLY_ms(10); // button_auto_s.function.sequence.delay);

    Keyboard_releaseAll();
    led_set_color_hue(NEO_GREEN, NEO_GREEN, NEO_YEL);

    auto_counter_s++;
    if (auto_counter_s >= button_auto_s.function.sequence.length)
    {
      led_set_color_hue(NEO_GREEN, NEO_GREEN, NEO_GREEN);
      auto_counter_s = 0;
    }
  }
  if (button_auto_s.type == BUTTON_AUTO_MOUSE)
  {
	  if(current_time - last_update < button_auto_s.function.mouse.delay)
	  {
		  return;
	  }
	  last_update = current_time;

    led_set_color_hue(NEO_GREEN, NEO_YEL, NEO_YEL);
    switch (button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].type)
    {
    case UP:
      Mouse_move(0, -button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    case DOWN:
      Mouse_move(0, button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    case LEFT:
      Mouse_move(-button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value, 0);
      break;
    case RIGH:
      Mouse_move(button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value, 0);
      break;
    case LEFT_CLICK:
      Mouse_click(MOUSE_LEFT);
      break;
    case RIGHT_CLICK:
      Mouse_click(MOUSE_RIGHT);
      break;
    case SCROLL_UP:
      Mouse_scroll(button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    case SCROLL_DOWN:
      Mouse_scroll(-button_auto_s.function.mouse.mouse_event_sequence[auto_counter_s].value);
      break;
    default:
      break;
    }
    // delay(button_auto_s.function.mouse.delay);
	DLY_ms(10);
    auto_counter_s++;
    if (auto_counter_s >= button_auto_s.function.mouse.length)
    {
      led_set_color_hue(NEO_GREEN, NEO_GREEN, NEO_GREEN);
      auto_counter_s = 0;
    }
  }
}