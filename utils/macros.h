#ifndef MACROS
#define MACROS 1

/* 25 lines each with 80 columns; element [2 bytes]: char & format */
#define LINES 25
#define COLUMNS 80
#define BYTES_PER_CHAR 2
#define LINESIZE BYTES_PER_CHAR * COLUMNS
#define SCREENSIZE LINESIZE * LINES

#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8E
#define LOW16(kAddress)  (unsigned long) ((kAddress) & 0xFFFF)
#define HIGH16(kAddress) (unsigned long) (((kAddress) & 0xFFFF0000) >> 16)

#define BACKSPACE_KEY_CODE 0x0E /* 14 */
#define ENTER_KEY_CODE 0x1C     /* 28 */
#define CONTROL_CODE 0x1D       /* 29 */
#define LSHIFT_KEY_CODE 0x2A    /* 42 */
#define RSHIFT_KEY_CODE 0x36    /* 54 */
#define UP_KEY_CODE 0x48        /* 72 */
#define LEFT_KEY_CODE 0x4B      /* 75 */
#define RIGHT_KEY_CODE 0x4D     /* 77 */
#define DOWN_KEY_CODE 0x50      /* 80 */

#define CURSOR_COLOR 0x77    /* light gray */
#define DEFAULT_COLOR 0x07   /* light gray on black */
#define PROMPT_COLOR_1 0x0B  /* light blue on black */
#define PROMPT_COLOR_2 0x0C  /* light red on black */

#define START_STR "Welcome to ma kernel w/ some keyboard support. Enter 'help' for some help."
#define PROMPT "[popcorn] $ "
#define PROMPT_LEN 12*2

#endif /* MACROS */
