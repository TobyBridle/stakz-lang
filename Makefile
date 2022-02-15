exec = a
sources = $(wildcard src/*.c)
objects = $(sources: .c=.o)
ifeq ($(OS),Windows_NT)
	flags = -g -Wall -lm -fPIC
else
	flags = -g -Wall -lm -ldl -fPIC -rdynamic
endif

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

#%.o %.c includes/%.h
	#gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/includes/*.h
	