#include <X11/Xlib.h>

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
	kp.keycode = XKeysymToKeycode (dpy, XStringToKeysym(str));
	kp.type = KeyPress;

	XSendEvent (dpy, kp.window, False, 0, (XEvent *)(&kp));
	XFlush(dpy);
	
	return 1;
}
