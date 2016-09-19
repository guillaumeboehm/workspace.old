#OBJS specifies wich files to compile as part of the project
OBJS = main.cpp level.cpp

#CC specifies which compiler to use
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
#COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

#OBJ_NAME specifies the name of the executable
OBJ_NAME = game

#This is the target that compiles the executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)