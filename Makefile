CC := gcc
CFLAGS := -g -O2 -Wall -Wextra -Wno-unused-parameter

override CFLAGS += -fPIC

prefix := /usr

LIBXFCE4PANEL_CFLAGS = $(shell pkg-config --cflags libxfce4panel-2.0)
LIBXFCE4PANEL_LIBS := $(shell pkg-config --libs libxfce4panel-2.0)

libhexclock.so: hexclock.o
libhexclock.so: LIBS := $(LIBS) $(LIBXFCE4PANEL_LIBS)
libhexclock.so: CFLAGS := $(CFLAGS) $(LIBXFCE4PANEL_CFLAGS)
libhexclock.so: LDFLAGS := $(LDFLAGS) -Wl,--no-undefined

install: libhexclock.so hexclock.desktop
	install -m 755 -D libhexclock.so -t $(DESTDIR)$(prefix)/lib/xfce4/panel/plugins/
	install -m 644 -D hexclock.desktop -t $(DESTDIR)$(prefix)/share/xfce4/panel/plugins/

%.o:: %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

%.so::
	$(CC) $(LDFLAGS) -shared -o $@ $^ $(LIBS)
