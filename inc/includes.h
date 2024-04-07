#ifndef INCLUDES_H
#define INCLUDES_H

#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)

typedef struct	editorConf_s
{
	int screenRows;
	int screenCols;
	struct termios orig_termios;
}								editorConfiguration;

//global variable with the editor configuration
extern editorConfiguration editorConf;

void enableRawMode();
void die(const char *s);
void refreshScreen();
int getWindowsSize(int *rows, int *cols);
void initEditor();


#endif
