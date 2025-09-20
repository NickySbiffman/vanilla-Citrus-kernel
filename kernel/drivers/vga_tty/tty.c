#define VGA_BUFFER 0xB8000
#define COLS 	   80
#define ROWS 	   25
#define DEFAULT_CA 0x07

#include "tty.h"

ui8 curr_atr = DEFAULT_CA;

//start cursor position, x = 0, y =0
static ui32 c_col = 0;
static ui32 c_row = 0;

void outb(ui16 port, ui8 val)
{
	__asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}


void move_cursor(int row, int col) 
{
	c_row = row;
	c_col = col;
	
	int pos = row * COLS + col;
	outb(0x3D4, 0x0E);
	outb(0x3D5, (pos >> 8) & 0xFF);
	
	outb(0x3D4, 0x0F);
	outb(0x3D5, pos & 0xFF);
}

void print_newline()
{
	c_col = 0;
	c_row++;
}

void putchk(char c)
{
	volatile ui16 *vga = (volatile ui16 *) VGA_BUFFER;
	
	switch (c) {
		case '\n':
			print_newline();
			break;
		case '\r':
			c_col = 0;
			break;
		default:
			if (c >= ' ') {
				ui32 idx = c_row * COLS + c_col;
				vga[idx] = (curr_atr << 8) | c;
				c_col++;
				move_cursor(c_row, c_col);
			}
			break;
	}


	if (c_col >= COLS) {
		c_col = 0;
		c_row++;
	}
}

void putsk(const char *str)
{
	while (*str) {
		putchk(*str++);
	}
	
	if (*str == '\0') {
		return;
	}
}


void cleark() 
{
	for (int i = 0; i < COLS * ROWS; ++i) {
		putchk(' ');
	}
}
