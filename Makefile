CXX = g++

CXXFLAGS = 

TARGET = main

# Object files for modular compilation
OBJS = main.o device.o hub.o topology.o

all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp into main.o
main.o: main.cpp device.h hub.h topology.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile device.cpp into device.o
device.o: device.cpp device.h
	$(CXX) $(CXXFLAGS) -c device.cpp

# Compile hub.cpp into hub.o
hub.o: hub.cpp hub.h
	$(CXX) $(CXXFLAGS) -c hub.cpp

# Compile topology.cpp into topology.o
topology.o: topology.cpp topology.h
	$(CXX) $(CXXFLAGS) -c topology.cpp

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)
