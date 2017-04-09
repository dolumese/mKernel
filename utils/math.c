#include "math.h"

int strLen(const char* str)
{
	int len = 0;

	while (str[len] != '\0') len++;

	return len;
}

int pow10(int power)
{
	int result = 1;

	while (power > 0) {
		result = result * 10;
		power--;
	}

	return result;
}

char isNum(const char c)
{
  // 0 -> [48] & 9 -> [57]
	return c > 47 && c < 58;
}

int numDegree(int num)
{
	int degree = 1;

	while (num > 9) {
		num = num/10;
		degree++;
	}

	return degree;
}

int str2Num(const char* str)
{
	int num = 0;

	for (int i = strLen(str); i > 0; i--) {
		if (!isNum(*str)) return -1;

    // Shift the char in ascii to its decimal number
		num = num + ((*str - 48) * pow10(i-1));
		str++;
	}

	return num;
}

char* num2Str(int num)
{
	char* str = ".";
	int degree = numDegree(num);

	for (int i = degree; i > 0; i--) {
    // Shift the decimal number to its ascii value
		str[i-1] = (num % 10) + 48;
		num = num / 10;
	} str[degree] = '\0';

	return str;
}

int* getNums(const char* command, char offset)
{
  // declare nums ptr below the screen
	int* nums = (sizeof(int) * 2) + ((int*) NUM_LIST_PTR);

	char* num_str = ".";
	int i = 0;

	for (; command[i + offset] != ' '; i++) {
		num_str[i] = command[i + offset];
	} num_str[i] = '\0';

	nums[0] = str2Num(num_str); // 1st input as an integer
	offset = offset + i + 1;
	num_str = ".";

	for (i = 0; command[i + offset] != '\0'; i++) {
		num_str[i] = command[i + offset];
	} num_str[i] = '\0';

	nums[1] = str2Num(num_str); // 2nd input as an integer

	return nums;
}

void add(const char* command)
{
	if (strLen(command) < 7) { // min command length -> len('add # #') == 7
		print("Invalid input: Input was too short"); return;
	}

	char offset = 4; // len('add') + 1
	int* nums = getNums(command, offset);

	if (nums[0] < 0 || nums[1] < 0) {
		print("Invalid input: Input was not numeric"); return;
	}

	print(num2Str(nums[0] + nums[1]));
}

void sub(const char* command)
{
  if (strLen(command) < 7) { // min command length -> len('sub # #') == 7
		print("Invalid input: Input was too short"); return;
	}

	char offset = 4; // len('sub') + 1
	int* nums = getNums(command, offset);

	if (nums[0] < 0 || nums[1] < 0) {
		print("Invalid input: Input was not numeric"); return;
	} else if ((nums[0] - nums[1]) < 0) {
		print("Error: Negative numbers not supported"); return;
	}

	print(num2Str(nums[0] - nums[1]));
}

void mul(const char* command)
{
  if (strLen(command) < 7) { // min command length -> len('mul # #') == 7
		print("Invalid input: Input was too short"); return;
	}

	char offset = 4; // len('mul') + 1
	int* nums = getNums(command, offset);

	if (nums[0] < 0 || nums[1] < 0) {
		print("Invalid input: Input was not numeric"); return;
	}

	print(num2Str(nums[0] * nums[1]));
}

void div(const char* command)
{
  if (strLen(command) < 7) { // min command length -> len('div # #') == 7
		print("Invalid input: Input was too short"); return;
	}

	char offset = 4; // len('div') + 1
	int* nums = getNums(command, offset);

	if (nums[0] < 0 || nums[1] < 0) {
		print("Invalid input: Input was not numeric"); return;
	} else if (nums[1] == 0) {
		print("Error: Zero division"); return;
	}

	print(num2Str(nums[0] / nums[1]));
}
