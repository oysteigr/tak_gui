CC     = gcc -Wall #-Wextra -ansi -std=c99
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`
OBJECTS = tak_gui.o frames.o  load_save.o callbacks.o window.o

tak_gui: $(OBJECTS)
	$(CC) $(OBJECTS) -o tak_gui $(CFLAGS) 

%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
clean :
	rm $(OBJECTS)

