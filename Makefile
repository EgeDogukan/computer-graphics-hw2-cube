# Compiler
CPP = g++

# Compiler flags
CPP_FLAGS = -g -Wall -Wextra -std=c++11 -w

# Include directories
INCLUDES = -I../include -I/opt/homebrew/Cellar/glfw/3.4/include -I/opt/homebrew/Cellar/glew/2.2.0_1/include

# Libraries
LIBS = -lGLEW -lglfw -framework OpenGL -L/opt/homebrew/Cellar/glfw/3.4/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib

# Source
SRCS = main_fixedAxis.cpp InitShader.cpp

#
OBJS = $(SRCS:.cpp=.o)

# Name of the program
TARGET = program

# Default rule
all: $(TARGET)

# Rule to compile .cpp files to object files
%.o: %.cpp
	$(CPP) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CPP) $(CPP_FLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
