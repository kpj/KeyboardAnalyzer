#include <X11/Xlib.h>
#include <ctype.h>

#define XK_LATIN1 
#define XK_MISCELLANY 
#include <X11/keysymdef.h>

void grab(Display *dpy) {
	XGrabKeyboard(
		dpy,
		DefaultRootWindow(dpy),
		0,
		GrabModeAsync,
		GrabModeAsync,
		CurrentTime
	);
}
void ungrab(Display *dpy) {
	XUngrabKeyboard(dpy, CurrentTime);
}

int sendKeyToFocus(Display *dpy, char *str) {
	Window inFocus;
	int rev;
	XGetInputFocus(dpy, &inFocus, &rev);

	XKeyEvent kp;
	kp.window = inFocus;
	kp.state = 0;
	kp.keycode = XKeysymToKeycode(dpy, XStringToKeysym(str));
	kp.type = KeyPress;

	XSendEvent(dpy, kp.window, False, 0, (XEvent *)(&kp));
	XFlush(dpy);
	
	return 1;
}
int sendEvent(Display *dpy, XEvent event) {
	XSendEvent(dpy, event.xany.window, False, 0, &event);
	XFlush(dpy);
	return 1;
}
int sendSpecEvent(Display *dpy, KeySym keysym, XKeyEvent xkey) {
	Window inFocus;
	int rev;
	XGetInputFocus(dpy, &inFocus, &rev);

	XKeyEvent kp;
	kp.window = inFocus;
	kp.state = xkey.state; // key or button mask
	kp.keycode = XKeysymToKeycode(dpy, keysym);
	kp.type = xkey.type;

	XSendEvent(dpy, kp.window, False, 0, (XEvent *)(&kp));
	XFlush(dpy);

	return 1;
}
