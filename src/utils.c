#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <X11/Xlib.h>
//#include <X11/keysymdef.h>

#include "utils.h"

int fixStr(char *str, KeySym keysym) {
	if(! (strlen(str) > 1 || isprint(str[0])) ) {
		char *tmp = (char*) malloc(sizeof(char) * SPECHARLEN);
		switch (keysym) {
			case 0xff0d: // XK_Return
				str[0] = 'R';
				break;
			case 0xff08: // XK_BackSpace
				str[0] = 'B';
				break;
			case 0xffff: // XK_Delete
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
