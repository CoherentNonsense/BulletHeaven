DIRS := *.c entities/*.c systems/*.c
CFILES := $(foreach DIR, $(DIRS), $(wildcard src/$(DIR)))
OFILES := $(patsubst src/%.c, build/%.o, $(CFILES))

INCLUDES = -I/usr/local/include -I./libs/glad/include -I./libs/cglm/include -I./libs/stb/include

all: game

init:
	mkdir -p build
	mkdir -p build/systems

build/%.o: src/%.c
	gcc -c $(INCLUDES) -Wall -o $@ $<

game: init $(OFILES)
	gcc -o game $(OFILES) -L/usr/local/lib -lglfw -lsynge
	
clean:
	rm -r build game
