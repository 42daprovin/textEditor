#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#include "includes.h"

char readKeyPressed()
{
	int nread;
	char c;

	while ((nread = read(STDIN_FILENO, &c, 1) != 1)) {
		if (nread == -1 && errno != EAGAIN)
			die("read");
	}

	return c;
}


void processKeyPressed()
{
	char keyCode;

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
