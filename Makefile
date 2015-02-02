CC=gcc
DEFAULT_CFLAGS:=-lm -g -Wall -Wextra -pedantic
CFLAGS?=
CFLAGS += $(DEFAULT_CFLAGS)
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))
OUT=pc

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) -o $(OUT) $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OUT)

thing:
	echo $(CC)
