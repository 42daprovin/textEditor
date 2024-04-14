#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#include "includes.h"

int readKeyPressed()
{
	int nread;
	char c;

	while ((nread = read(STDIN_FILENO, &c, 1) != 1)) {
		if (nread == -1 && errno != EAGAIN)
			die("read");
	}

	//read esc seq
	if (c == '\x1b') {
		char seq[3];

		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return '\x1b';
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return '\x1b';

		if (seq[0] == '[') {
			switch (seq[1]) {
				case 'A':
					return UP_ARROW;
				case 'B':
					return DOWN_ARROW;
				case 'C':
					return RIGHT_ARROW; 
				case 'D':
					return LEFT_ARROW;
			}
		}
		
		return '\x1b';
	}

	return c;
}


void processKeyPressed()
{
	int keyCode;

	keyCode = readKeyPressed();

	//exit on ctrl-q
	switch (keyCode) {
		case CTRL_KEY('q'):
			clearScreen();
			exit(0);
			break;
		case DOWN_ARROW:
			moveCursorDown();
			break;
		case UP_ARROW:
			moveCursorUp();
			break;
		case RIGHT_ARROW:
			moveCursorRight();
			break;
		case LEFT_ARROW:
			moveCursorLeft();
			break;
	}
}

int main()
{
	//enable raw mode
	enableRawMode();
	initEditor();

	//main loop
	while (1) {
		refreshScreen();
		processKeyPressed();
	}

	return 0;
}
