#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <X11/Xlib.h>

#define XK_LATIN1 
#define XK_MISCELLANY 
#include <X11/keysymdef.h>

#include "utils.h"

int fixStr(char *str, KeySym keysym) {
	if(! (strlen(str) > 1 || isprint(str[0])) ) {
		char *tmp = (char*) malloc(sizeof(char) * SPECHARLEN);
		switch (keysym) {
			case XK_Return:
				str[0] = '\n';
				break;
			case XK_Tab:
				str[0] = '\t';
				break;
			case XK_BackSpace:
				str[0] = '\v'; // so we see deleted characters
				break;
			case XK_Delete:
				str[0] = 'D';
				break;
			default:
				str[0] = '|';
				break;
		}
		tmp[SPECHARLEN-1] = '\0';
	}
	return 1;
}
