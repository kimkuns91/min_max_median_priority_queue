CC=gcc
CFLAGS=-Wall -O2
TARGET=pq

all: $(TARGET)

$(TARGET): pq.c
	$(CC) $(CFLAGS) -o $(TARGET) pq.c

clean:
	rm -f $(TARGET) pq.out result.diff
