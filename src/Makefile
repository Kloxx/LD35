CC = g++
DEBUG = yes
ifeq ($(DEBUG),yes)
	CFLAGS = -w -Wl,-subsystem,windows -g -std=gnu++0x
else
	CFLAGS = -w -Wl,-subsystem,windows
endif

OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin

INCLUDE_PATHS = -IC:/MinGW/include
LIBRARY_PATHS = -LC:/MinGW/lib
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lopengl32 -lglew32
EXEC = ../LD35.exe
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(EXEC)

../LD35.exe: $(OBJ)
	$(CC) -o $@ $^ $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LDFLAGS)

Input.o: Input.cpp common.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
Character.o: Character.cpp common.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
NPC.o: NPC.cpp common.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
Floor.o: Floor.cpp common.h
	$(CC) -o $@ -c $< $(CFLAGS)	
	
Level.o: Level.cpp common.h Input.h Character.h Floor.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
SceneOpenGL.o: SceneOpenGL.cpp common.h Input.h Character.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.cpp SceneOpenGL.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
.PHONY: clean mrproper
	
clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf $(EXEC)