#ifndef INCLUDES_H
#define INCLUDES_H

#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)

#define DOWN_ARROW 1001
#define UP_ARROW 1002
#define LEFT_ARROW 1003
#define RIGHT_ARROW 1004

typedef struct	editorConf_s
{
	int cX;
	int cY;
	int screenRows;
	int screenCols;
	struct termios orig_termios;
}								editorConfiguration;

typedef struct	aBuffer_s
{
	char *data;
	int	len;
}								aBuffer;

//global variable with the editor configuration
extern editorConfiguration editorConf;

void enableRawMode();
void die(const char *s);
void refreshScreen();
int getWindowsSize(int *rows, int *cols);
void initEditor();
void clearScreen();
char *itoa(int n);
char *strjoin(char *s1, char *s2);
void moveCursorUp();
void moveCursorDown();
void moveCursorLeft();
void moveCursorRight();

#endif
