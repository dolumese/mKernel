#ifndef KEYBOARD
#define KEYBOARD 1

#include "screen.h"
#include "../utils/macros.h"

#define VIDEO_PTR 0xB8000

/* --- Variable definition --- */
unsigned int currLoc;    //<<< current cursor location
unsigned int commandLen; //<<< length of the current command
unsigned int lineNum;    //<<< the current line number
char* vidPtr;            //<<< video memory begins at address 0xB8000
char keycode;            //<<< key press code
char shiftState;         //<<< allow for use of shift
char storedChar;         //<<< allow for storing current char
char runState;           //<<< running a command?

/* --- Externals definition --- */
extern unsigned char kbMap[128];
extern unsigned char shift_kbMap[128];
extern void kbHandler(void);
extern char rPort(unsigned short port); //<<< read port
extern void wPort(unsigned short port, unsigned char data); //<<< write port


/* --- Function definition --- */
/**
 * Initializes driver to allow for keyboard input
 */
void kbInit(void);

/**
 * Handles special keycodes separately
 * These include ENTER, SHIFT, arrow-keys, etc.
 */
char specialKey(const unsigned char keycode);

/**
 * Handles keyboard input and displays characters to the screen upon key press
 */
void kbHandlerMain(void);

#endif /* KEYBOARD */
