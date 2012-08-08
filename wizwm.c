#include "screen.h"

int main(int argc, char **argv)
{
	xcb_connection_t *connection = connect_to_x_server(argv[1]); /* argv[1] will be NULL if argc==1 */

	/* Iterate over each screen and attempt to manage it */
	/* This is quite verbose but I can't find a more elegant way to do it */
	const xcb_setup_t *setup = xcb_get_setup(connection);
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	for(int i = 0; i < xcb_setup_roots_length(setup); ++i) {
		xcb_screen_t *screen = iter.data;

		/* There can be only one! */
		if(detect_window_manager(connection, screen, i)) {
			fprintf(stderr, "Another window manager is currently running on screen %d\n", i);
			return 1;
		}

		printf("Screen %d are belong to us\n", i);
		init(connection, screen);
		xcb_screen_next(&iter);
	}

	xcb_flush(connection);

	/* Wait for events */
	xcb_generic_event_t *event;
	while((event = xcb_wait_for_event(connection))) {
		free(event);
	}

	xcb_disconnect(connection);

	return 0;
}
