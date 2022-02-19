CC := gcc

CFLAGS := -std=c99 -Wall -Werror -I inc/ -g3

OBJS := actions.o input.o print.o hesh_table.o timemy.o

.PHONY : clean

app.exe : $(OBJS) main.o
	$(CC) $^ -o $@

%.o : src/%.c inc/*.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm *.o *.exe
