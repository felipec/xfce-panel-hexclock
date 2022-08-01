CC := gcc
CFLAGS := -g -O2 -Wall -Wextra -Wno-unused-parameter

override CFLAGS += -fPIC

LIBXFCE4PANEL_CFLAGS = $(shell pkg-config --cflags libxfce4panel-2.0)
LIBXFCE4PANEL_LIBS := $(shell pkg-config --libs libxfce4panel-2.0)

libhexclock.so: hexclock.o
libhexclock.so: LIBS := $(LIBS) $(LIBXFCE4PANEL_LIBS)
libhexclock.so: CFLAGS := $(CFLAGS) $(LIBXFCE4PANEL_CFLAGS)
libhexclock.so: LDFLAGS := $(LDFLAGS) -Wl,--no-undefined

%.o:: %.c
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

%.so::
	$(CC) $(LDFLAGS) -shared -o $@ $^ $(LIBS)
