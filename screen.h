#ifndef SCREEN_H_
#define SCREEN_H_

/* Standard library */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* XCB header files */
#include <xcb/xcb.h>

/* Attempts to connect to X server specified by screenname and exits upon failure. */
xcb_connection_t *connect_to_x_server(const char *screenname);

/* Detect presence of another window manager. */
xcb_window_t detect_window_manager(xcb_connection_t *connection, xcb_screen_t *screen, int index);

/* Select events for the root window so that window management can begin. */
void init(xcb_connection_t *connection, xcb_screen_t *screen);

#endif
