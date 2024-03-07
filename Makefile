.PHONY: create_build_dir server builder clean call_method get_set

all: create_build_dir server call_method builder get_set

create_build_dir:
	if [ ! -d build ]; then mkdir build; fi

server:
	gcc -o build/server src/dbus-server.c `pkg-config --libs --cflags gio-2.0`

call_method:
	gcc -o build/call_method src/dbus-call-method.c `pkg-config --cflags --libs gio-2.0`

builder:
	gcc -o build/gbuilder src/builder-example.c `pkg-config --cflags --libs gio-2.0`

get_set:
	gcc -o build/get-set src/dbus-get-set-prop.c `pkg-config --cflags --libs gio-2.0`


clean:
	rm -rf build