#ifndef MATH
#define MATH 1

#include "../drivers/screen.h"

#define NUM_LIST_PTR 0xB8FA0

/**
 * Returns the length of the input string, str
 */
int strLen(const char* str);

/**
 * Returns 10 raised the input power, 10^(power)
 */
int pow10(int power);

/**
 * Checks if the input character, c, is numeric
 */
char isNum(const char c);

/**
 * Returns the degree of the input number, num, in decimal
 */
int numDegree(int num);

/**
 * Converts the input string, str, to an integer
 */
int str2Num(const char* str);

/**
 * Converts the input integer, num, to a string
 */
char* num2Str(int num);

/**
 * Returns a list of the two input arguments for math commands
 *
 * Takes in the entire command, parses the inputs, converts them to integers,
 * then stores them in the heap under the screen as a dynamic list of integers
 */
int* getNums(const char* command, char offset);

/**
 * Adds the two positive integer inputs to the 'add' command and prints the
 * result to the screen
 */
void add(const char* command);

/**
 * Subtracts the two positive integer inputs to the 'sub' command and prints the
 * result to the screen
 *
 * Requirement: input1 >= input2; thus, result must be positive
 */
void sub(const char* command);

/**
 * Multiplies the two positive integer inputs to the 'mul' command and prints
 * the result to the screen
 */
void mul(const char* command);

/**
 * Divides the two positive integer inputs to the 'div' command and prints the
 * result to the screen
 *
 * Requirement: input2 > 0; Zero division error
 */
void div(const char* command);

#endif /* MATH */
