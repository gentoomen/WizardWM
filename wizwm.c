#include "wizwm.h"

int main(int argc, char **argv)
{
	/* Open a connection to the X server */
	xcb_connection_t *connection = xcb_connect(NULL, NULL);
	if (!connection) {
		fprintf(stderr, "%s", "ERROR: Can't connect to the X server!\n");
		return 1;
	}
	
	return 0;
}
