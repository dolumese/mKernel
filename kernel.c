#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "utils/idt.h"
#include "utils/macros.h"
#include "utils/math.h"


/**
 * Checks whether the two strings, c1 and c2, are equal
 */
char equal(const char* c1, const char* c2)
{
	while (*c1 == *c2 && *c1 != '\0') {
		c1++; c2++;
	} return *c1 == *c2;
}

/**
 * Parses the screen and returns the command as a string
 */
char* getCommand(void)
{
	char* output = ".";
	const unsigned int start = LINESIZE*(lineNum-1) + PROMPT_LEN;

	for (unsigned int i = 0; i < commandLen; i++) {
		output[i] = vidPtr[start + i*2];
	} output[commandLen] = '\0';

	return output;
}

/**
 * Checks whether the input command, c1, is equal to the reference command, c2
 *
 * The length of the command, len, is used to allow for commands with arguments,
 * len == 0 -> command has no input arguments
 * len > 0 -> command is of len, and has input arguments
 */
char checkCommand(const char* c1, const char* c2, const unsigned char len)
{
	if (len == 0) return equal(c1, c2);

	for (int i = 0; i < len; i++) {
		if (*c1 != *c2 || *c1 == '\0') break;
		c1++; c2++;
	} return *c1 == *c2;
}

/**
 * Prints the input text to the 'echo' command to the screen
 */
void echo(const char* command)
{
	char* echoOut = ".";
	const char offset = 5; // len('echo') + 1

	for (unsigned int i = offset; command[i] != '\0'; i++) {
		echoOut[i-offset] = command[i];
	} echoOut[commandLen-offset] = '\0';

	print(echoOut);
}

/**
 * Initializes the Interrupt Directory Table, the keyboard driver and the screen
 */
void init(void)
{
	idtInit();
	kbInit();

	clearScreen();
	print(START_STR);
	newline(runState); currLoc = LINESIZE*lineNum;

	showPrompt();
}

/**
 * The kernal main function: runs the kernel's command line interface
 */
void kmain(void)
{
	const char* command = "";

	init();

	do {
		if (runState == 0) continue; // Command has not yet be entered

		// Determine the command from the input and run it accordingly
		command = getCommand();
		if (checkCommand(command, "help", 0) || checkCommand(command, "h", 0)) {
			print("Welcome to my kernel. The available commands include:"); newline(runState);
			print("** General **"); newline(runState);
			print(" - help    display this help utility"); newline(runState);
			print(" - h       short for `help`"); newline(runState);
			print(" - hello   display an introduction to this simple OS"); newline(runState);
			print(" - clear   clear the screen"); newline(runState);
			print(" - pwd     display the current directory"); newline(runState);
			print(" - echo    display a line of text ['echo {text}']"); newline(runState);
			newline(runState);
			print("** Math **"); newline(runState);
			print("Math commands are run as follows: ['command ## ##']"); newline(runState);
			print(" - add    add two positive numbers"); newline(runState);
			print(" - sub    subtract two positive numbers"); newline(runState);
			print(" - mul    multiply two positive numbers"); newline(runState);
			print(" - div    integer divide two positive numbers"); newline(runState);
		} else if (checkCommand(command, "hello", 0)) {
			print("Hello, I am a simple kernel created for educational purposes. I am still in deve"); newline(runState);
			print("lopment.");
		} else if (checkCommand(command, "clear", 0)) {
			clearScreen();
		} else if (checkCommand(command, "pwd", 0)) {
			print("/home/popcorn/");
		} else if (checkCommand(command, "echo ", 4)) {
			echo(command);
		} else if (checkCommand(command, "add ", 3)) {
			add(command);
		} else if (checkCommand(command, "sub ", 3)) {
			sub(command);
		} else if (checkCommand(command, "mul ", 3)) {
			mul(command);
		} else if (checkCommand(command, "div ", 3)) {
			div(command);
		} else if (checkCommand(command, "echo", 0)) {
			print(" ");
		} else {
			print(" ");
		}

		showPrompt();
	} while(1); /* run forever */
}
