#include "lwm.h"

/* GTK+ 1.2 is used in this function, instead of simply Xlib */
void create_wm_menu()
{
	/* Labels for buttons */
	char* button_labels[MENU_SIZE];
	button_labels[XTERM] 		= "New Xterm";
	button_labels[TOP_LEFT] 	= "Top Left";
	button_labels[TOP_RIGHT] 	= "Top Right";
	button_labels[BOTTOM_LEFT] 	= "Bottom Left";
	button_labels[BOTTOM_RIGHT] = "Bottom Right";
	button_labels[TOP_HALF] 	= "Top Half";
	button_labels[BOTTOM_HALF] 	= "Bottom Half";
	button_labels[LEFT_HALF] 	= "Left Half";
	button_labels[RIGHT_HALF] 	= "Right Half";
	button_labels[FULLSCREEN] 	= "Fullscreen";
	button_labels[MINIMIZE]		= "Minimize";
	button_labels[DELETE] 		= "Delete Window";
	button_labels[CIRCULATE]	= "Circulate";
	button_labels[EXIT] 		= "Exit";

	/* Map index of buttons to their respective functions */
	void* menu_functions[MENU_SIZE];
	menu_functions[XTERM] 			= new_xterm;
	menu_functions[TOP_LEFT] 		= top_left;
	menu_functions[TOP_RIGHT] 		= top_right;
	menu_functions[BOTTOM_LEFT] 	= bottom_left;
	menu_functions[BOTTOM_RIGHT] 	= bottom_right;
	menu_functions[TOP_HALF] 		= top_half;
	menu_functions[BOTTOM_HALF] 	= bottom_half;
	menu_functions[LEFT_HALF] 		= left_half;
	menu_functions[RIGHT_HALF] 		= right_half;
	menu_functions[FULLSCREEN] 		= fullscreen;
	menu_functions[MINIMIZE]		= minimize;
	menu_functions[DELETE] 			= delete_window;
	menu_functions[CIRCULATE]		= circulate;
	menu_functions[EXIT] 			= exit_wm;

	/* Windows that make up the window manager menu */
	GtkWidget* buttons[MENU_SIZE];
	GtkWidget* menu_box = 0;
	GtkWidget* window 	= 0;

	/* Create parent window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), WM_TITLE);
	gtk_widget_set_usize(window, screen_width, WM_HEIGHT);
	gtk_widget_set_uposition(window, 0, screen_height-WM_HEIGHT);
	gtk_container_set_border_width(GTK_CONTAINER(window), 1);

	/* Create horizontal box inside window, where buttons will be packed */
	menu_box = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), menu_box);

	/* Create buttons and link them to their respective functions */
	for(int i = XTERM; i < MENU_SIZE; ++i)
	{
		buttons[i] = gtk_button_new_with_label(button_labels[i]);
		gtk_signal_connect(GTK_OBJECT(buttons[i]), "clicked", GTK_SIGNAL_FUNC(menu_functions[i]), NULL);
		gtk_box_pack_start(GTK_BOX(menu_box), buttons[i], TRUE, TRUE, 0);
	}

	/* make windows visible and run GTK+ */
	gtk_widget_show_all(window);
	gtk_main();
}

void config_window(int tile_id)
{
	/* Give user enough time to move cursor towards window to be resized */
	sleep(SLEEP_TIMER);

	/* Get window data based on where cursor is */
	XQueryPointer(display, root_window, &root_return, &current_window, &root_x_return, &root_y_return,
			&win_x_return, &win_y_return, &mask_return);

	switch(tile_id)
	{
	case TOP_LEFT:
		changes.x = 0;
		changes.y = 0;
		changes.height = screen_height >> 1; /* Bitwise operation to divide by 2 */
		changes.width = screen_width >> 1;
		break;
	case TOP_RIGHT:
		changes.x = screen_width >> 1;
		changes.y = 0;
		changes.height = screen_height >> 1;
		changes.width = screen_width >> 1;
		break;
	case BOTTOM_LEFT:
		changes.x = 0;
		changes.y = screen_height >> 1;
		changes.height = (screen_height >> 1) - WM_HEIGHT;
		changes.width = screen_width >> 1;
		break;
	case BOTTOM_RIGHT:
		changes.x = screen_width >> 1;
		changes.y = screen_height >> 1;
		changes.height = (screen_height >> 1) - WM_HEIGHT;
		changes.width = screen_width >> 1;
		break;
	case TOP_HALF:
		changes.x = 0;
		changes.y = 0;
		changes.height = screen_height >> 1;
		changes.width = screen_width;
		break;
	case BOTTOM_HALF:
		changes.x = 0;
		changes.y = screen_height >> 1;
		changes.height = (screen_height >> 1) - WM_HEIGHT;
		changes.width = screen_width;
		break;
	case LEFT_HALF:
		changes.x = 0;
		changes.y = 0;
		changes.height = screen_height - WM_HEIGHT;
		changes.width = screen_width >> 1;
		break;
	case RIGHT_HALF:
		changes.x = screen_width >> 1;
		changes.y = 0;
		changes.height = screen_height - WM_HEIGHT;
		changes.width = screen_width >> 1;
		break;
	case FULLSCREEN:
		changes.x = 0;
		changes.y = 0;
		changes.height = screen_height - WM_HEIGHT;
		changes.width = screen_width;
		break;
	case MINIMIZE:
		XGetWindowAttributes(display, current_window, &attributes);
		changes.x = attributes.x;
		changes.y = attributes.y;
		changes.height = MIN_SIZE;
		changes.width = MIN_SIZE;
		break;
	case DELETE:
		/* Destroy window and its subwindows */
		XDestroyWindow(display, current_window);
		XSync(display, False);
		return;
	}

	XConfigureWindow(display, current_window, CWX, &changes);
	XConfigureWindow(display, current_window, CWY, &changes);
	XConfigureWindow(display, current_window, CWHeight, &changes);
	XConfigureWindow(display, current_window, CWWidth, &changes);

	/* This is important */
	XSync(display, False);
}

/*****************************************************
 * Below are functions directly triggered by buttons *
 *****************************************************/

/* Create a new terminal with Ubuntu colours at the top left corner of the screen */
void new_xterm(){system("xterm -bg purple4 -fg green3 -geometry 32x16+0+0 &");}

/* Tell config_window(int) what to do to the window */
void top_left(){config_window(TOP_LEFT);}
void top_right(){config_window(TOP_RIGHT);}
void bottom_left(){config_window(BOTTOM_LEFT);}
void bottom_right(){config_window(BOTTOM_RIGHT);}
void top_half(){config_window(TOP_HALF);}
void bottom_half(){config_window(BOTTOM_HALF);}
void left_half(){config_window(LEFT_HALF);}
void right_half(){config_window(RIGHT_HALF);}
void fullscreen(){config_window(FULLSCREEN);}
void minimize(){config_window(MINIMIZE);}
void delete_window(){config_window(DELETE);}

/* Raise lowest window */
void circulate()
{
	XCirculateSubwindows(display, root_window, RaiseLowest);
	XSync(display, False);
}

/* Exit window manager menu */
void exit_wm(){gtk_main_quit();}
