#ifndef SCREEN
#define SCREEN 1

#include "keyboard.h"
#include "../utils/macros.h"

/**
 * Prints the input string to the screen
 */
void print(const char* str);

/**
 * Prints the prompt text to the screen in color
 */
void printPrompt(void);

/**
 * Displays the prompt to the screen with neccesary surrounding formatting
 */
void showPrompt(void);

/**
 * Clears the screen and resets the cursor to the top of the screen
 */
void clearScreen(void);

/**
 * Shifts the contents of the screen up when the end of the screen buffer is
 * reached
 */
void shiftScreen(void);

/**
 * Fills the rest of the current line with space space, clearing any unwanted
 * characters of the line
 */
void fillLine(void);

/**
 * Makes a new line and shifts the cursor
 *
 * runState == 0 -> [no command running] place cursor after prompt
 * runState == 1 -> [command running] nothing special
 * runState == 2 -> [command just ran] reset the command length to 0
 */
void newline(const char runState);

/**
 * Display the cursor block at the current location
 */
void showCursor(void);

/**
 * Restore the character at the current location after cursor block has been
 * moved
 */
void restoreChar(void);

#endif /* SCREEN */
