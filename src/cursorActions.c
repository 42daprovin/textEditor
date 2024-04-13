#include "includes.h"

void moveCursorUp() {
	if (editorConf.cY > 1)
		editorConf.cY -= 1;
}

void moveCursorDown() {
	if (editorConf.cY < editorConf.screenRows)
		editorConf.cY += 1;
}

void moveCursorLeft() {
	if (editorConf.cX > 2)
		editorConf.cX -= 1;
}

void moveCursorRight() {
	if (editorConf.cX < editorConf.screenCols)
		editorConf.cX += 1;
}
