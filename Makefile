.PHONY: create_build_dir server

all: create_build_dir server

create_build_dir:
	if [ ! -d build ]; then mkdir build; fi

server:
	gcc -o build/server src/dbus-server.c `pkg-config --libs --cflags gio-2.0`

client:
	gcc -o build/client src/dbus-client.c `pkg-config --cflags --libs gio-2.0`