#include "configuration.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

const keyboard_configuration_t configurations[NUM_CONFIGURATION] = 
{
	{
		.button = { // 복사/붙여넣기 키보드 구성
			[BTN_1] = {
				.type = BUTTON_SEQUENCE,
				.function.sequence = {
					.sequence = {KEY_LEFT_CTRL, 'c'}, // Ctrl+C (복사)
					.length = 2,            // 시퀀스 길이
					.delay = 0             // 지연 없음
				}
			},
			[BTN_2] = {
				.type = BUTTON_SEQUENCE,
				.function.sequence = {
					.sequence = {KEY_LEFT_CTRL, 'v'}, // Ctrl+V (붙여넣기)
					.length = 2,            // 시퀀스 길이
					.delay = 0             // 지연 없음
				}
			},
			[BTN_3] = {
				.type = BUTTON_SEQUENCE,
				.function.sequence = {
					.sequence = {KEY_LEFT_CTRL, 'z'}, // Ctrl+Z (실행 취소)
					.length = 2,            // 시퀀스 길이
					.delay = 0             // 지연 없음
				}
			},
			[ENC_CW] = { // scroll up
				.type = BUTTON_MOUSE,
				.function.mouse = {
					.mouse_event_sequence = {
						{
							.type = SCROLL_DOWN,
							.value = 2
						}
					},
					.length = 1,
					.delay = 0,
					.keypress = 0 // 마우스 버튼 누름 값
				}
			},
			[ENC_CCW] = {   // scroll down
				.type = BUTTON_MOUSE,
				.function.mouse = {
					.mouse_event_sequence = {
						{
							.type = SCROLL_UP,
							.value = 2
						}
					},
					.length = 1,
					.delay = 0,
					.keypress = 0 // 마우스 버튼 누름 값
				}
			},
			[BTN_ENC] = {
				.type = BUTTON_FUNCTION,
				.function.functionPointer = keyboard_press_enc,
			},
		}
	},

	{	// Function key over F12.
		.button = { // 
			[BTN_1] = {
				.type = BUTTON_SEQUENCE,
				.function.sequence = {
				.sequence = {'a'},
					.length = 1,            // 시퀀스 길이
					.delay = 0             // 지연 없음
				}
			},
			[BTN_2] = {
				.type = BUTTON_SEQUENCE,
				.function.sequence = {
					.sequence = {'b'},
					.length = 1,
					.delay = 0
				}
			},
			[BTN_3] = {
				.type = BUTTON_SEQUENCE,
				.function.sequence = {
					.sequence = {'c'},
					.length = 1,
					.delay = 0
				}
			},
			[ENC_CW] = {
				.type = BUTTON_MOUSE,
				.function.mouse = {
					.mouse_event_sequence = {
						{
							.type = SCROLL_UP,
							.value = 1
						}
					},
					.length = 1,
					.delay = 0,
					.keypress = KEY_LEFT_CTRL
				}
			},
			[ENC_CCW] = {
				.type = BUTTON_MOUSE,
				.function.mouse = {
					.mouse_event_sequence = {
						{
							.type = SCROLL_DOWN,
							.value = 1
						}
					},
					.length = 1,
					.delay = 0,
					.keypress = KEY_LEFT_CTRL
				}
			},
			[BTN_ENC] = {
				.type = BUTTON_FUNCTION,
				.function.functionPointer = keyboard_press_enc,
			},
		}
	},

	{   // Automatic keyboard
		.button = { // 
			[BTN_1] = {
				.type = BUTTON_AUTO_KEYBOARD,
				.function.sequence = {
				.sequence = {KEY_LEFT_CTRL}, // Ctrl+C (복사)
					.length = 1,
					.delay = 5000
				}
			},
			[BTN_2] = {
				.type = BUTTON_AUTO_MOUSE,
				.function.mouse = { //multi click
					.mouse_event_sequence = 
					{
						{
							.type = UP,
							.value = 40
						},
						{
							.type = RIGH,
							.value = 40
						},
						{
							.type = DOWN,
							.value = 40
						},
						{
							.type = LEFT,
							.value = 40
						}
					},
					.length = 4,
					.delay = 5000,
					.keypress = 0 // 마우스 버튼 누름 값
				}
			},
			[BTN_3] = {
				.type = BUTTON_NULL,
			},
			[ENC_CW] = {
				.type = BUTTON_MOUSE,
				.function.mouse = {
					.mouse_event_sequence = {
						{
							.type = SCROLL_UP,
							.value = 1
						}
					},
					.length = 1,
					.delay = 0,
					.keypress = 0 // 마우스 버튼 누름 값
				}
			},
			[ENC_CCW] = {
				.type = BUTTON_MOUSE,
				.function.mouse = {
					.mouse_event_sequence = {
						{
							.type = SCROLL_DOWN,
							.value = 1
						}
					},
					.length = 1,
					.delay = 0,
					.keypress = 0 // 마우스 버튼 누름 값
				}
			},
			[BTN_ENC] = {
				.type = BUTTON_FUNCTION,
				.function.functionPointer = keyboard_press_enc,
			},
		}
	},
	{   //Menu configuration
		.button = { // 메뉴 구성
			[BTN_1] = {
				.type = BUTTON_NULL,
			},
			[BTN_2] = {
				.type = BUTTON_NULL,
			},
			[BTN_3] = {
				.type = BUTTON_NULL,
			},
			[ENC_CW] = {
				.type = BUTTON_FUNCTION,
				.function.functionPointer = button_menu_up,
			},
			[ENC_CCW] = {
				.type = BUTTON_FUNCTION,
				.function.functionPointer = button_menu_down,
			},
			[BTN_ENC] = {
				.type = BUTTON_FUNCTION,
				.function.functionPointer = keyboard_press_enc,
			},
		}
	},
};