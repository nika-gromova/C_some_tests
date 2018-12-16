CC := gcc
PARAMS := -std=gnu99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	PARAMS += -g3
endif
ifeq ($(mode), drmemory)
	PARAMS += -ggdb
endif

app.exe: main.o io.o my_list.o
	$(CC) -o $@ $^
	
test.exe: test.o io.o my_list.o
	$(CC) -o $@ $^

main.o: main.c io.h my_struct.h defines.h
	$(CC) $(PARAMS) -c $<
	
test.o: test.c io.h my_struct.h defines.h
	$(CC) $(PARAMS) -c $<

io.o: io.c io.h my_struct.h defines.h my_list.h
	$(CC) $(PARAMS) -c $<
	
my_list.o: my_list.c my_list.h my_struct.h
	$(CC) $(PARAMS) -c $<

clean:
	rm *.o *.exe
	
ftest: app.exe
	./app.exe in_2.txt
	fc out.txt out_1.txt