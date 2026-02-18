
#include "config.h"
#include "neo.h"
#include "keyboard.h"
#include "util.h"
#include "buttons.h"

// Previous button states
static uint8_t bt1ActiveState_s = 0;
static uint8_t bt2ActiveState_s = 0;
static uint8_t bt3ActiveState_s = 0;
static uint8_t btEncActiveState_s = 0;

// Current button states
static uint8_t bt1Active_s  = 0;
static uint8_t bt2Active_s  = 0;
static uint8_t bt3Active_s  = 0;
static uint8_t btEncActive_s  = 0;

#if 0
// Button setup
void buttons_setup()
{
	PIN_input_PU(PIN_KEY1);
	PIN_input_PU(PIN_KEY2);
	PIN_input_PU(PIN_KEY3);
	PIN_input_PU(PIN_ENC_SW);
}
#endif

void buttons_update(void)
{
    // Read the button states, default PULL HIGH (aka LOW Activate)
    bt1Active_s  = !PIN_read(PIN_KEY1);
    bt2Active_s  = !PIN_read(PIN_KEY2);
    bt3Active_s  = !PIN_read(PIN_KEY3);
    btEncActive_s  = !PIN_read(PIN_ENC_SW);

    if (bt1ActiveState_s != bt1Active_s)
    {
        bt1ActiveState_s = bt1Active_s;
        if (bt1Active_s)  
        {
            keyboard_press_button(BTN_1, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_1, BTM_RELEASE);
        }
    }

    // Button 2
    if (bt2ActiveState_s != bt2Active_s)
    {
        bt2ActiveState_s = bt2Active_s;
        if (bt2Active_s)  
        {
            keyboard_press_button(BTN_2, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_2, BTM_RELEASE);
        }
    }

    // Button 3
    if (bt3ActiveState_s != bt3Active_s)
    {
        bt3ActiveState_s = bt3Active_s;
        if (bt3Active_s)  
        {
            keyboard_press_button(BTN_3, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_3, BTM_RELEASE);
        }
    }

    // Button Encoder
    if (btEncActiveState_s != btEncActive_s)
    {
        btEncActiveState_s = btEncActive_s;
        if (btEncActive_s)  
        {
            keyboard_press_button(BTN_ENC, BTM_PRESS);
        }
        else
        {
            keyboard_press_button(BTN_ENC, BTM_RELEASE);
        }
    }
    if (btEncActive_s  && bt1Active_s  && bt2Active_s  && bt3Active_s)
    {
        // go in bootloader mode if press all buttons
        BOOT_now();
    }
}