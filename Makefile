.PHONY: server

all: server

server:
	mkdir build
	gcc -o build/server dbus-server.c `pkg-config --libs --cflags gio-2.0`