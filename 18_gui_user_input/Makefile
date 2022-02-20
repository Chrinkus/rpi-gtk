CC = gcc
CFLAGS = `pkg-config --cflags gtk+-2.0`
LDFLAGS = `pkg-config --libs gtk+-2.0`
OUT = gtktest.out

$(OUT): ch18.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm $(OUT)

.PHONY:
	clean

