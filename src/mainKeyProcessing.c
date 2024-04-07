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
			exit(0);
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
