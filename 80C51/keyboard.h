#ifndef ___KEYBOARD_H
#define ___KEYBOARD_H

typedef enum {
	ARROW_NEUTRAL,
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT
} Arrow;

Arrow KEYBOARD_readArrows(unsigned char *keyboard);

#ifdef TEST
int testKeyboard();
#endif

#endif

