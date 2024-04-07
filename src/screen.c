#include <unistd.h>
#include <sys/ioctl.h>

#include "includes.h"

int getWindowsSize(int *rows, int *cols)
{
		struct winsize ws;

		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
			return -1;
		} else {
			*cols = ws.ws_col;
			*rows = ws.ws_row;
			return 0;
		}
}

void drawLeftMargin()
{
	for (int i = 0; i < editorConf.screenRows; i++) {
		write(STDOUT_FILENO, "~",1);
		if (i < editorConf.screenRows - 1) {
			write(STDOUT_FILENO, "\r\n",3);
		}
	}
}

void refreshScreen()
{
	//getWindowsSize
	getWindowsSize(&editorConf.screenRows, &editorConf.screenCols);
	//clear screen
	write(STDOUT_FILENO, "\x1b[2J", 4);
	//reposition cursor to the top
	write(STDOUT_FILENO, "\x1b[H", 3);
	
	drawLeftMargin();

	//reposition cursor to the top
	write(STDOUT_FILENO, "\x1b[H", 3);
}
