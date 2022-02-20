CC = gcc
CFLAGS = `pkg-config --cflags gtk+-2.0`
LDFLAGS = `pkg-config --libs gtk+-2.0`

gtktest.out: ch14.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

