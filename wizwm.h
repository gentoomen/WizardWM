/* Main header file for WizardWM */
#ifndef WIZWM_H_	// prevent multiple inclusion with PREPROCESSER MAGIKS
#define WIZWM_H_

/* Standard library */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* XCB header files */
#include <xcb/xcb.h>

/* ORIGINAL MACROS DO NOT STEAL! */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Detect presence of another window manager. */
static xcb_window_t detect_window_manager(xcb_connection_t *connection, xcb_screen_t *screen, int index);

/* Select events for the root window so that window management can begin. */
static void init(xcb_connection_t *connection, xcb_screen_t *screen);

#endif
