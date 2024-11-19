CC = gcc
CFLAGS = -O3 -g
LDFLAGS = -L. -lppm
TARGET = test mandel

.PHONY: all clean

all: $(TARGET)

libppm.so: ppm.c
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@

test: main.c libppm.so
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) -I.

mandel: mandel.c libppm.so
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) -I.

clean:
	rm -f $(TARGET) *.so
