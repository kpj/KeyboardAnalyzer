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
int sendSpecEvent(Display *dpy, KeySym keysym, XEvent event) {
	XKeyEvent xkey = event.xkey;

	Window inFocus;
	int rev;
	XGetInputFocus(dpy, &inFocus, &rev);

	XKeyEvent kp;
	kp.window = inFocus;

	// trying to get MOD4 to work
	kp.root = event.xany.window;
	kp.subwindow = 0;
	kp.x = xkey.x;
	kp.y = xkey.y;
	kp.x_root = xkey.x_root;
	kp.y_root = xkey.y_root;

	kp.state = xkey.state; // key or button mask
	kp.keycode = XKeysymToKeycode(dpy, keysym);
	kp.type = xkey.type;

	printf("\nstate: %x\n", kp.state);
	printf("in focus: %x\n", inFocus);
	printf("from xk_event (xkey_subwin): %x\n", event.xkey.subwindow);
	printf("from xk_event (xkey_root): %x\n", event.xkey.root);
	printf("from xk_event (xkey_win): %x\n", event.xkey.window);
	printf("from xa_event (xany_win): %x\n\n", event.xany.window);

	XSendEvent(dpy, kp.window, False, 0, (XEvent *)(&kp));
	XFlush(dpy);

	return 1;
}
