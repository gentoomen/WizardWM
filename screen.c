#include "screen.h"

xcb_window_t detect_window_manager(xcb_connection_t *connection, xcb_screen_t *screen, int index)
{
	/* Section 4.3 of the ICCCM standard states that a window manager should */
	/* own the selection named WM_Sn, where n is the screen number.          */
	char atom_name[6];
	sprintf(atom_name, "WM_S%d", index);

	/* This should probably be made it's own function for convenience. */
	xcb_intern_atom_cookie_t atom_cookie = xcb_intern_atom(connection, 0, strlen(atom_name), atom_name);
	xcb_intern_atom_reply_t *atom_reply = xcb_intern_atom_reply(connection, atom_cookie, NULL);
	xcb_atom_t selection = atom_reply->atom;

	/* Get selection owner. */
	xcb_get_selection_owner_cookie_t selection_owner_cookie = xcb_get_selection_owner(connection, selection);
	xcb_get_selection_owner_reply_t *selection_owner_reply = xcb_get_selection_owner_reply(connection, selection_owner_cookie, NULL);
	xcb_window_t selection_owner = 0;
	if(selection_owner_reply) {
		selection_owner = selection_owner_reply->owner;
	}

	free(atom_reply);
	free(selection_owner_reply);

	return selection_owner;
}

void init(xcb_connection_t *connection, xcb_screen_t *screen)
{
	/**
	 * Select for events The substructure redirect event is the really
	 * important one. Only one X client can select for that event.
	 */
	const uint32_t events[] = {
		XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |
		XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY |
		XCB_EVENT_MASK_ENTER_WINDOW |
		XCB_EVENT_MASK_LEAVE_WINDOW |
		XCB_EVENT_MASK_STRUCTURE_NOTIFY |
		XCB_EVENT_MASK_PROPERTY_CHANGE |
		XCB_EVENT_MASK_BUTTON_PRESS |
		XCB_EVENT_MASK_BUTTON_RELEASE |
		XCB_EVENT_MASK_POINTER_MOTION |
		XCB_EVENT_MASK_FOCUS_CHANGE |
		XCB_EVENT_MASK_KEY_PRESS
	};

	xcb_change_window_attributes(connection, screen->root, XCB_CW_EVENT_MASK, events);
}

xcb_connection_t *connect_to_x_server(const char *displayname)
{
	/* Attempt to connect to X server, exit with error if unsuccessful */
	xcb_connection_t *connection = xcb_connect(displayname, NULL);
	if (xcb_connection_has_error(connection)) {
		fprintf(stderr, "Failed to connect to X server\n");
		exit(1);
	}

	return connection;
}
