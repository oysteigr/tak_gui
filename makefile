CC     = gcc -Wall #-Wextra -ansi -std=c99
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`
OBJECTS_M = Debug/tak_gui.o Debug/frames.o  Debug/load_save.o Debug/callbacks.o Debug/window.o Debug/shortcuts.o
OBJECTS = tak_gui.o frames.o  load_save.o callbacks.o window.o shortcuts.o

all: $(OBJECTS_M)
	$(CC) $(OBJECTS_M) -o tak_gui $(CFLAGS)
	cp tak_gui Debug/

Debug/%.o : src/%.c
	$(CC) $(CFLAGS) -c $<
	mv *.o Debug/
clean :
	rm $(OBJECTS_M)
	rm Debug/tak_gui

