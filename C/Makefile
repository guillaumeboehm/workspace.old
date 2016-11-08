#OBJS specifies wich files to compile as part of the project
OBJS = main.c suite.c ssuite.c

#CC specifies which compiler to use
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
COMPILER_FLAGS = -std=c99

#LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = 

#OBJ_NAME specifies the name of the executable
OBJ_NAME = td1

#This is the target that compiles the executable
main : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm *.o main

#archive :
