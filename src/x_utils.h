void grab(Display *dpy);
void ungrab(Display *dpy);

int sendKeyToFocus(Display *dpy, char *str);
int sendEvent(Display *dpy, XEvent event);
int sendSpecEvent(Display *dpy, KeySym keysym, XEvent event);
