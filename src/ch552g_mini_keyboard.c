#ifndef USER_USB_RAM
#error "Require USB RAM. Go Tools > USB Setting and pick the 2nd option in the dropdown list"
#endif

//lib include
#include "neo.h"
#include "usb/USBHIDKeyboardMouse.h"
#include "config.h"
//app include
#include "auto_mode.h"
#include "buttons.h"
#include "encoder.h"
#include "keyboard.h"
#include "led.h"
#include "util.h"

void test_blink()
{
	static uint32_t cnt_run = 0;
	switch((cnt_run / 1000) % 3)
	{
		case 0:
		NEO_writeColor(0, 100, 0, 0);
		break;
		case 1:
		NEO_writeColor(0, 0, 100, 0);
		break;
		case 2:
		NEO_writeColor(0, 0, 0, 100);
		break;
		default:
		break;
	}
	cnt_run++;
}

/**
 * Timer 2.
*/
uint32_t gnTick;
uint16_t gnPeriod;

// Period 24K -> 
void timer_init(uint16_t nPeriod)
{
	gnPeriod = nPeriod;
#if 1
	TR0 = 0;
	TMOD = (TMOD & ~bT0_M1 & ~bT0_GATE & ~bT0_CT) | bT0_M0;
	T2MOD &= ~bT0_CLK;
	TL0 = (uint8_t)(nPeriod & 0xFF);
	TH0 = (uint8_t)((nPeriod >> 8) & 0xFF);
	TF0 = 0;
	ET0 = 1;

	TR0 = 1;	// start.
#else

	TH0 = 0xFF;		/* 50ms timer value */
	TL0 = 0x00;
	TMOD = 0x01;		/* Timer0 mode1 */
	
	EA  = 1;         	/* Enable global interrupt */
	ET0 = 1;         	/* Enable timer0 interrupt */
	TR0 = 1;  	      	/* Start timer0 */
#endif

}

uint32_t millis()
{
	return gnTick;
}

void TIMER_ISR(void) __interrupt(INT_NO_TMR0)
{
	gnTick++;
	TL0 = (uint8_t)(gnPeriod & 0xFF);
	TH0 = (uint8_t)((gnPeriod >> 8) & 0xFF);
	test_blink();
}

void USBInterrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB)
{
	USBInterrupt();
}



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
//	timer_init(63536);
	timer_init(65036);

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
//	led_update();

	NEO_update();
	DLY_ms(1); 
}


void main()
{
	setup();
	while (1)
	{
		loop();
	}
}