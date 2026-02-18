#ifndef USER_USB_RAM
#error "Require USB RAM. Go Tools > USB Setting and pick the 2nd option in the dropdown list"
#endif

//lib include
#include "src/neo/neo.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"
#include "src/config.h"
//app include
#include "src/auto_mode.h"
#include "src/buttons.h"
#include "src/encoder.h"
#include "src/keyboard.h"
#include "src/led.h"
#include "src/util.h"

// Button (Mechnical, left to right)



// ===================================================================================
// Main section
// ============================================================================
// Initialize pins
void setup()
{
	// Initialize neopixels
	NEO_init();
	DLY_ms(10);
	NEO_clearAll();

	// Go in bootloader more if connected with encoder button pressed
	if(0 == PIN_read(PIN_ENC_SW))
	{
		NEO_writeHue(0, NEO_CYAN, NEO_BRIGHT_KEYS); // set led1 to cyan
		NEO_writeHue(1, NEO_BLUE, NEO_BRIGHT_KEYS); // set led2 to blue
		NEO_writeHue(2, NEO_MAG, NEO_BRIGHT_KEYS); //  set led3 to magenta
		NEO_update();                              // update pixels
		BOOT_now();     // jump to bootloader
	}

	keyboard_setup();
	encoder_setup();
	led_set_mode(LED_LOOP);
	USBInit();
}


//Main loop, read buttons
void loop()
{
	//task update
	buttons_update();
	auto_update();
	encoder_update();
	led_update();

	//debouncing
	DLY_ms(5); 
}
