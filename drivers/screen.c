#include "screen.h"

void print(const char* str)
{
	unsigned int i = 0;
	while (str[i] != '\0') {
    vidPtr[currLoc++] = str[i++];
    vidPtr[currLoc++] = DEFAULT_COLOR;
	}
}

void printPrompt(void)
{
	// Print the prompt in color
	unsigned int i = 0;
	while (PROMPT[i] != '$') {
		vidPtr[currLoc++] = PROMPT[i++];
		vidPtr[currLoc++] = PROMPT_COLOR_1;
	} while (PROMPT[i] != '\0' || i < PROMPT_LEN/2) {
		vidPtr[currLoc++] = PROMPT[i++];
		vidPtr[currLoc++] = PROMPT_COLOR_2;
	}

  // Clear the rest of the line after the prompt
  while (currLoc < LINESIZE*(lineNum+1)) {
		vidPtr[currLoc++] = ' ';
		vidPtr[currLoc++] = DEFAULT_COLOR;
	} currLoc = LINESIZE*lineNum + PROMPT_LEN;
}

void showPrompt(void)
{
	if (currLoc > LINESIZE*(lineNum+1)) lineNum++; // keep line consistent

	newline(2);  // clear command count
	printPrompt();

	storedChar = vidPtr[currLoc]; // store the current char
	showCursor();

	runState = 0; // reset the run state (no command running)
}

void clearScreen(void)
{
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidPtr[i++] = ' ';
		vidPtr[i++] = DEFAULT_COLOR;
	}

	currLoc = 0; lineNum = 0; // set cursor to top of the screen
}

void shiftScreen(void)
{
	const int end = LINESIZE*(LINES-1); // Second to last line
	for (int i = 0; i < end; i++)
		vidPtr[i] = vidPtr[i+LINESIZE];
	lineNum--; // update the current line number
}

void fillLine(void)
{
	while (currLoc < LINESIZE*lineNum) {
		vidPtr[currLoc++] = ' ';
		vidPtr[currLoc++] = DEFAULT_COLOR;
	}
}

void newline(const char runState)
{
	lineNum++; // move to the next line
	fillLine();

	if (lineNum == LINES || lineNum > LINES) shiftScreen();

	// update current location
	currLoc = LINESIZE*lineNum;
	if (runState == 0) { // place cursor after prompt
		currLoc = currLoc + PROMPT_LEN;
	} else if (runState == 2) {
		commandLen = 0; // reset command length count
	}
}

void showCursor(void)
{
  vidPtr[currLoc++] = ' ';
  vidPtr[currLoc--] = CURSOR_COLOR;
}

void restoreChar(void)
{
  vidPtr[currLoc++] = storedChar;
  vidPtr[currLoc--] = DEFAULT_COLOR;
}
