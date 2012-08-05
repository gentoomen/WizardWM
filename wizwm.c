#include <stdio.h>

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

	/* There can be only one! */
	if(detect_window_manager(disp, scr))
	{
	     printf("Another window manager is currntly running\n");
	     return 1;
	}
	
	return 0;
}

static xcb_window_t detect_window_manager(xcb_connection_t *connection, xcb_screen_t *screen)
{
     /* Section 4.3 of the ICCCM standard states that a window manager should */
     /* own the selection named WM_Sn, where n is the screen number.          */
     /* char atom_name[6]; */
     /* sprintf(atom_name, "WM_S%d", screen->root); */
     
     /* Currently only uses screen 0. */
     const char *atom_name = "WM_S0";

     /* This should probably be made it's own function for convenience. */
     xcb_intern_atom_cookie_t atom_cookie = xcb_intern_atom(connection, 0, strlen(atom_name), atom_name);
     xcb_intern_atom_reply_t *atom_reply = xcb_intern_atom_reply(connection, atom_cookie, NULL);
     xcb_atom_t selection = atom_reply->atom;

     /* Get selection owner. */
     xcb_get_selection_owner_cookie_t selection_owner_cookie = xcb_get_selection_owner(connection, selection);
     xcb_get_selection_owner_reply_t *selection_owner_reply = xcb_get_selection_owner_reply(connection, selection_owner_cookie, NULL);
     xcb_window_t selection_owner = 0;
     if(selection_owner_reply)
	  selection_owner = selection_owner_reply->owner;

     free(atom_reply);
     free(selection_owner_reply);

     return selection_owner;
}
