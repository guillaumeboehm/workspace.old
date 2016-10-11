#OBJS specifies wich files to compile as part of the project
OBJS = 01_hello_SDL.cpp

#CC specifies which compiler to use
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of the executable
OBJ_NAME = 01_hello_SDL

#This is the target that compiles the executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)