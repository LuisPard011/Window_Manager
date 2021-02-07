#ifndef LWM_H
#define LWM_H

/* Includes */
#include <gtk/gtk.h>
#include <X11/Xlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* sleep(unsigned int) */

/* Used to iterate and allocate button related operations */
enum menu_options
{
	XTERM,
	TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT,	/* Quarters */
	TOP_HALF, BOTTOM_HALF, LEFT_HALF, RIGHT_HALF,	/* Halves */
	FULLSCREEN,
	MINIMIZE,
	DELETE,
	CIRCULATE,
	EXIT,
	MENU_SIZE
};

/* Size of minimized windows */
#define MIN_SIZE 	50
/* Amount of time to give user to move pointer to window desired to modify */
#define SLEEP_TIMER	1
/* Height of window manager menu bar */
#define WM_HEIGHT 	25
/* Title to be displayed in title bar created by a window manager such as twm */
#define WM_TITLE	"Luis's Window Manager"

/* Create window manager menu bar */
void create_wm_menu();
/* Configure window depending on (int) argument passed in */
void config_window(int);

/* Functions directly linked to buttons */
void new_xterm();
void top_left();
void top_right();
void bottom_left();
void bottom_right();
void top_half();
void bottom_half();
void left_half();
void right_half();
void fullscreen();
void minimize();
void circulate();
void delete_window();
void exit_wm();

/* Variables used throughout the program */
Display* display;
Window root_window, current_window;
XWindowAttributes attributes;
XWindowChanges changes;
int screen_number, screen_height, screen_width;

/* Dummy variables used only in the process of calling XQueryPointer(...) */
Window root_return;
int root_x_return, root_y_return, win_x_return, win_y_return;
unsigned int mask_return;

#endif
