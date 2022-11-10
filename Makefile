DIRS := *.c entities/*.c systems/*.c data/*.c
CFILES := $(foreach DIR, $(DIRS), $(wildcard src/$(DIR)))
OFILES := $(patsubst src/%.c, build/%.o, $(CFILES))

INCLUDES = -I/usr/local/include -I./libs/glad/include -I./libs/cglm/include -I./libs/stb/include

all: game

ifeq ($(OS), Windows_NT)

build/%.o: src/%.c
	gcc -c $(INCLUDES) -IC:/MinGW/include -Wall -o $@ $<

game: $(OFILES)
	gcc -o game.exe $(OFILES) -LC:/MinGW/lib -lsynge -lglfw3 -lgdi32 -lopengl32

else

init:
	mkdir -p build
	mkdir -p build/systems
	mkdir -p build/data

build/%.o: src/%.c
	gcc -c $(INCLUDES) -Wall -o $@ $<

game: init $(OFILES)
	gcc -o game $(OFILES) -L/usr/local/lib -lglfw -lsynge
	
clean:
	rm -r build game

endif