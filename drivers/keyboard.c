#include "keyboard.h"

/* --- Keyboad map initialization --- */
unsigned char kbMap[128] =
{
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key *//* 28 */
	0 /* Control */, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
	'\'', '`', 0 /* Left shift */, '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
	'm', ',', '.', '/', 0 /* Right shift */, '*', 0 /* Alt */, ' ',
	0 /* Caps lock */,
	0 /* 59 - F1 > */, 0,   0,   0,   0,   0,   0,   0,   0, 0 /* < F10 */,
  0 /* 69 - Num lock*/, 0 /* Scroll Lock */, 0 /* Home key */, 0 /* Up Arrow */,
	0 /* Page Up */, '-', 0 /* Left Arrow */, 0, 0 /* Right Arrow */, '+',
  0 /* 79 - End key*/, 0 /* Down Arrow */, 0 /* Page Down */, 0 /* Insert Key */,
  0 /* Delete Key */, 0, 0, 0, 0 /* F11 Key */, 0 /* F12 Key */,
  0, /* All other keys are undefined */
};

unsigned char shift_kbMap[128] =
{
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
	'(', ')', '_', '+', '\b',	'\t', 'Q', 'W', 'E', 'R',	/* 19 */
	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
	0 /* Control */, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
	'"', '~', 0 /* Left shift */, '|', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
	'M', '<', '>', '?',  0 /* Right shift */, '*', 0 /* Alt */, ' ',
	0 /* Caps lock */,
	0 /* 59 - F1 > */, 0,   0,   0,   0,   0,   0,   0,   0, 0 /* < F10 */,
	0 /* 69 - Num lock*/, 0 /* Scroll Lock */, 0 /* Home key */, 0 /* Up Arrow */,
	0 /* Page Up */, '-', 0 /* Left Arrow */, 0, 0 /* Right Arrow */, '+',
	0 /* 79 - End key*/, 0 /* Down Arrow */, 0 /* Page Down */, 0 /* Insert Key */,
	0 /* Delete Key */, 0, 0, 0, 0 /* F11 Key */, 0 /* F12 Key */,
	0, /* All other keys are undefined */
};


/* --- Variable initialization --- */
unsigned int currLoc = 0;
unsigned int commandLen = 0;
unsigned int lineNum = 0;
char* vidPtr = (char*) VIDEO_PTR;
char shiftState = 0;
char storedChar = 0;
char runState = 0;


/* --- Function initialization --- */

void kbInit(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	wPort(0x21 , 0xFD);
}

char specialKey(const unsigned char keycode)
{
  restoreChar();

  switch(keycode) {
    case BACKSPACE_KEY_CODE: /* clear current character */
			if (currLoc > (LINESIZE*lineNum + PROMPT_LEN)) {
      	vidPtr[--currLoc] = DEFAULT_COLOR;
      	vidPtr[--currLoc] = ' ';
			} break;
    case ENTER_KEY_CODE:     /* move to new line */
			runState = 1;
			newline(runState); break;
    case UP_KEY_CODE:        /* move cursor up */
    case DOWN_KEY_CODE:      /* move cursor down */
			break; /* Don't permit vertical cursor movement */
    case LEFT_KEY_CODE:      /* move cursor left - up till the prompt */
			if (currLoc > (LINESIZE*lineNum + PROMPT_LEN))
      	currLoc -= BYTES_PER_CHAR;
			break;
    case RIGHT_KEY_CODE:     /* move cursor right - up to the end of the line */
			if (currLoc < (LINESIZE*(lineNum+1) - BYTES_PER_CHAR))
      	currLoc += BYTES_PER_CHAR;
			break;
    case RSHIFT_KEY_CODE:    /* enable shift */
    case LSHIFT_KEY_CODE:
      shiftState = 1; break;
    default:
      return 0;
  }

  return 1;
}

void kbHandlerMain(void)
{
	unsigned char kbStatus;

	/* write EOI */
	wPort(0x20, 0x20);

	kbStatus = rPort(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
  if (kbStatus & 0x01) {
    keycode = rPort(KEYBOARD_DATA_PORT); /* Read the keycode */
    if (keycode < 0)
      return;

    if (specialKey(keycode) == 0) { // keycode is not special
      if (shiftState == 0) { // use standard key map
        vidPtr[currLoc++] = kbMap[(unsigned char) keycode];
      } else {               // use shifted key map
        vidPtr[currLoc++] = shift_kbMap[(unsigned char) keycode];
        shiftState = 0; // reset the shift state
      }

      vidPtr[currLoc++] = DEFAULT_COLOR;

			if (currLoc > LINESIZE*(lineNum+1)) lineNum++; // keep line consistent

			// Determine the current length of the command after the prompt
			commandLen = (currLoc - (LINESIZE*lineNum + PROMPT_LEN))/2;
    }

    storedChar = vidPtr[currLoc]; /* store the current char */
    showCursor();
  }
}
