#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>


int fixStr(char *str) {
	if(! (strlen(str) > 1 || isprint(str[0])) ) {
		str[0] = '|';
	}
	return 1;
}
