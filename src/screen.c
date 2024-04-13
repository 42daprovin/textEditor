#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "includes.h"

void appendToBuffer(aBuffer *buff, char *s, int l)
{
	//realloc buffer
	buff->data = (char*)realloc(buff->data, buff->len + l);	

	//malloc security
	if (buff->data == NULL)
		die("realloc");

	//append to the buffer
	memcpy(&(buff->data[buff->len]), s, l);
	//new len
	buff->len = buff->len + l;
}

void freeBuffer(aBuffer *buff)
{
	free(buff->data);
}

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

void drawLeftMargin(aBuffer *buffer)
{
	for (int i = 0; i < editorConf.screenRows; i++) {
		appendToBuffer(buffer,"~",1);
		if (i < editorConf.screenRows - 1) {
			appendToBuffer(buffer,"\r\n",2);
		}
	}
}

void clearScreen() {
	write(STDOUT_FILENO, "\x1b[H", 3 );	
	write(STDOUT_FILENO, "\x1b[2J", 4);
}

void repositionCursor(aBuffer *buffer) {
	char *escSec = "\x1b[";
	char *xPos;
	char *yPos;
	char *command;
	char *aux;

	xPos = itoa(editorConf.cX);	
	if (xPos == NULL)
		die("itoa");

	yPos = itoa(editorConf.cY);
	if (yPos == NULL)
		die("itoa");

	command = strjoin(escSec, yPos);
	aux = command;
	command = strjoin(command, ";");
	free(aux);
	aux = command;
	command = strjoin(command, xPos);
	free(aux);
	aux = command;
	command = strjoin(command, "H");
	free(aux);

	appendToBuffer(buffer, command, strlen(command));
	free(command);
}

void refreshScreen()
{
	//init buffer
	aBuffer buffer;
	buffer.data = NULL;
	buffer.len = 0;
	//getWindowsSize
	getWindowsSize(&editorConf.screenRows, &editorConf.screenCols);
	//clear screen
	appendToBuffer(&buffer, "\x1b[H", 3);
	appendToBuffer(&buffer,"\x1b[2J", 4);
	//reposition cursor to the top
	appendToBuffer(&buffer, "\x1b[H", 3);

	drawLeftMargin(&buffer);

	//move cursor to its current position
	repositionCursor(&buffer);

	//print buffer
	write(STDOUT_FILENO, buffer.data, buffer.len);
	//free buffer
	freeBuffer(&buffer);
}
