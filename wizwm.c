#include "wizwm.h"

int main(int argc, char **argv)
{	
	xcb_connection_t *disp;
	xcb_screen_t *scr;
	xcb_drawable_t rt;
	
	/* Attempt to connect to X server, exit with error if unsuccessful */
	disp = xcb_connect(NULL, NULL);
	if (xcb_connection_has_error(disp))
		return 1;
	
	/* Get root of first screen. Currently only supports one screen. */
	scr = xcb_setup_roots_iterator(xcb_get_setup(disp)).data;
	rt = scr->root;
	
	return 0;
}
