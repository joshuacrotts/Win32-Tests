#OBJS specifies which files to compile as part of the project
OBJS = src/*.c lib/stds/src/*.c

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\MinGW\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\MinGW\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresszzes all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Werror -Wfloat-conversion -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lgdi32 -lmsimg32

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Game

#This is the target that compiles our executable
#
# -g -O -c generates .o files.
# -shared -o
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)