#include <stdio.h>
#include <stdlib.h>

#include "includes.h"

void die(const char *s) {
	clearScreen();
	perror(s);
	exit(1);
}
