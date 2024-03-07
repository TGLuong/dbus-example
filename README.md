# Dus Example

### Building:
make sure you have installed `build-essential`, `pkg-config`, `libglib2.0-dev`
``` bash
sudo apt install libglib2.0-dev libglib2.0-dev libglib2.0-dev
```
For building all example, try run:
``` bash
make all
```
All example was placed in `build` directory

### Test Dbus Server with `dbus`

For get property
``` bash
gdbus call -e -d com.gialuong.TestServer -o / -m org.freedesktop.DBus.Properties.Get com.gialuong.TestInterface status
```

For set property
``` bash
gdbus call -e -d com.gialuong.TestServer -o / -m org.freedesktop.DBus.Properties.Set com.gialuong.TestInterface status "<uint32 10>"
```