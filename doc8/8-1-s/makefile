CC=gcc
AR=$(CC)ar
EXEC=8-1-s
OBJS=8-1-s.o
all:$(EXEC)
$(EXEC):$(OBJS)
	$(CC) -o $@ $(OBJS) -lm
clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

