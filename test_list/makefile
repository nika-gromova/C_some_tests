CC := gcc
PARAMS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: main.o my_list.o
	$(CC) -o $@ $^
	
main.o: main.c my_list.h list_struct.h
	$(CC) $(PARAMS) -c $<

my_list.o: my_list.c my_list.h list_struct.h
	$(CC) $(PARAMS) -c $<

clean:
	rm *.exe *.o