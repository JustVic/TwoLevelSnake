#OBJS specifies which files to compile as part of the project
OBJS = main.cpp gameengine.cpp rendermanager.cpp intro.cpp menu.cpp highscore.cpp singleplayer.cpp kiss_sdl/kiss_draw.c kiss_sdl/kiss_general.c kiss_sdl/kiss_posix.c kiss_sdl/kiss_widgets.c

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -Wall -std=c++17 -I.

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
#-L./kiss_sdl/ -lkisssdl
KISS_DIR = kiss_sdl
KISS_SDL = $(KISS_DIR)/kisssdl.a

#INCLUDES = -I includes -I kiss_sdl

#INCLUDES = -I./
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

