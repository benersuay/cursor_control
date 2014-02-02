#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

void mouseClick(int button)
{
	Display *display = XOpenDisplay(NULL);

	XEvent event;
	
	if(display == NULL)
	{
		fprintf(stderr, "Hata!\n");
		exit(EXIT_FAILURE);
	}
	
	memset(&event, 0x00, sizeof(event));
	
	event.type = ButtonPress;
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	
	XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	
	event.xbutton.subwindow = event.xbutton.window;
	
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		
		XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
	}
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Hata 2!\n");
	
	XFlush(display);
	
	usleep(100000);
	
	event.type = ButtonRelease;
	event.xbutton.state = 0x100;
	
	if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Hata 2!\n");
	
	XFlush(display);
	
	XCloseDisplay(display);
}

void move_mouse(int delta_x, int delta_y){

    Display *display = XOpenDisplay(0);
    Window root = DefaultRootWindow(display);
    XWarpPointer(display, None, root, 0, 0, 0, 0, delta_x, delta_y);
    XCloseDisplay(display);
}

int main() {
     int delta_x = 500, delta_y = 160;
     for(int i=0;i<20;i++){
       move_mouse(delta_x, delta_y);
       delta_x++; delta_y++;
       usleep(100000);
     }
     mouseClick(0);
     return 0;
}
