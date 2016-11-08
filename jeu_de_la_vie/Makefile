#OBJS specifies wich files to compile as part of the project
OBJS = main.c grille.c io.c jeu.c

#CC specifies which compiler to use
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
COMPILER_FLAGS = -std=c99

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = 

#OBJ_NAME specifies the name of the executable
OBJ_NAME = main

#This is the target that compiles the executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm *.o main
