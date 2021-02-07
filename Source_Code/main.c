/*********************************************************************************************
 * Luis's Window Manager                                                                     *
 *                                                                                           *
 * To compile program, the following 3 binary packages are required:                         *
 *  1. gtk+-1.2.10nb16                                                                       *
 *    - GTK+ libraries                                                                       *
 *  2. pkg-config-0.29.1                                                                     *
 *    - Help with compilation                                                                *
 *  3. x11-links-1.02                                                                        *
 *    - Link X11 headers                                                                     *
 *                                                                                           *
 * To install binary package: pkgin in package_name                                          *
 *                                                                                           *
 * Operation instructions:                                                                   *
 *    - There is a macro defined as SLEEP_TIMER that is set to 1 second by default           *
 *    - This is the amount of time the user has to move the mouse pointer                    *
 *      over to the window they wish to tile, minimize or delete                             *
**********************************************************************************************/

#include "lwm.h"

int main(int argc, char** argv)
{
	/* Establish connection between program and X server */
	display = XOpenDisplay(NULL);
	if(display == NULL)
	{
		printf("Program couldn't connect to X server\n");
		return EXIT_FAILURE;
	}

	/* Initialize variables with wanted values */
	screen_number = DefaultScreen(display);
	root_window = XRootWindow(display, screen_number);
	screen_height = DisplayHeight(display, screen_number);
	screen_width = DisplayWidth(display, screen_number);

	/* Print values to console for debugging purposes */
//	printf("screen_number = %d\nscreen_height = %d\nscreen_width = %d\n", screen_number, screen_height, screen_width);

	/* Initialize GTK+ toolkit */
	gtk_init(&argc, &argv);

	/* Create window manager menu */
	create_wm_menu();

	/* Close connection to X server */
	XCloseDisplay(display);

	return EXIT_SUCCESS;
}
