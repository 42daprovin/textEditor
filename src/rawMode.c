#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "includes.h"

editorConfiguration editorConf;

void initEditor() {
	if (getWindowsSize(&editorConf.screenRows, &editorConf.screenCols) == -1)
		die("getWindowsSize");
}

void disableRawMode() {
	//load users original terminal atributes
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &editorConf.orig_termios) == -1)
		die("tcsetattr");
}

void enableRawMode() {
	struct termios raw;

	//save users terminal atributes
	if (tcgetattr(STDIN_FILENO, &editorConf.orig_termios))
		die("tcgetattr");
	//calls the function when the program exits
	atexit(disableRawMode);
	
	raw = editorConf.orig_termios;
	//dissable some flags:
	//	ECHO->prevent to echo what you write
	//	ICANON->disable send input on enter, now input is sended with every key pressed
	//	ISIG->disable CTRL-C and CTRL-Z
	//	IXON->disable CTRL-S and CTRL-Q
	//	IEXTEN->disable CTRL-V
	//	ICRNL->disable translate '\r' into '\n'
	//	OPOST->disable translate '\n' into '\r\n'
	raw.c_iflag &= ~(IXON | ICRNL);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	//more traditional flags to set in raw mode
	raw.c_iflag &=(BRKINT | INPCK | ISTRIP);
	raw.c_cflag |= (CS8);
	//control chareacters: 
	//	VMIN->minimum number of bytes of input needed before read
	//	VTIME->max time to wait before read, read returns 0 ir timeout
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}
