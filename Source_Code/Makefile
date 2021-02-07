all:
	cc -Wall -o lwm main.c lwm.c `pkg-config --cflags --libs x11` `gtk-config --cflags --libs`

clean:
	rm -f lwm
