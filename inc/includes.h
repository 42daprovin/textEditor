#ifndef INCLUDES_H
#define INCLUDES_H

#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define DOWN_ARROW 66
#define UP_ARROW 65
#define LEFT_ARROW 68
#define RIGHT_ARROW 67

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
