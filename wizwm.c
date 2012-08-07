#include "screen.h"

int main(int argc, char **argv)
{
	xcb_connection_t *connection = connect_to_x_server();

	/* Iterate over each screen and attempt to manage it */
	/* This is quite verbose but I can't find a more elegant way to do it */
	const xcb_setup_t *setup = xcb_get_setup(connection);
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	for(int i = 0; i < xcb_setup_roots_length(setup); ++i) {
		xcb_screen_t *screen = iter.data;

		/* There can be only one! */
		if(detect_window_manager(connection, screen, i)) {
			fprintf(stderr, "Another window manager is currntly running on screen %d\n", i);
			return 1;
		}

		printf("Screen %d are belong to us\n", i);
		init(connection, screen);
		xcb_screen_next(&iter);
	}

	return 0;
}
