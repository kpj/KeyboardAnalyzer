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
  /*XGrabKey(
    dpy,
    XKeysymToKeycode(dpy, XStringToKeysym("a")),
    AnyModifier,
    DefaultRootWindow(dpy),
    1,
    GrabModeAsync,
    GrabModeAsync
  );*/
}
void ungrab(Display *dpy) {
	XUngrabKeyboard(dpy, CurrentTime);
  //XUngrabKey(dpy, AnyKey, AnyModifier, DefaultRootWindow(dpy));
}
