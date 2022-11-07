UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	COMPILER = gcc
 	FLAGS = -std=c99 -Wextra -pedantic-errors
 	GL_FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
 	GLAD_FLAGS = -ldl
endif
 
all: main
 
main: main.c glad.o
	$(COMPILER) $(FLAGS) $(FILES) -o main main.c glad.o $(GL_FLAGS) $(GLAD_FLAGS)

glad.o: glad.c
	$(COMPILER) -c glad.c

.PHONY: clean run
clean:
	rm main
 
run: main 
	./main
 
