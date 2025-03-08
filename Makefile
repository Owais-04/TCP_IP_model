CXX = g++

CXXFLAGS = -Wall -std=c++17

TARGET = main

# Object files for modular compilation
OBJS = main.o device.o

all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp into main.o
main.o: main.cpp device.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile device.cpp into device.o
device.o: device.cpp device.h
	$(CXX) $(CXXFLAGS) -c device.cpp

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)
