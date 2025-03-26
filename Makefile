CXX = g++

CXXFLAGS = 

TARGET = main

# Object files for modular compilation
OBJS = main.o device.o hub.o bus.o topology.o switch.o  

all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp into main.o
main.o: main.cpp device.h hub.h bus.h topology.h switch.h  prompt.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile device.cpp into device.o
device.o: device.cpp device.h
	$(CXX) $(CXXFLAGS) -c device.cpp

# Compile hub.cpp into hub.o
hub.o: hub.cpp hub.h
	$(CXX) $(CXXFLAGS) -c hub.cpp

# Compile bus.cpp into bus.o
bus.o: bus.cpp bus.h
	$(CXX) $(CXXFLAGS) -c bus.cpp

# Compile topology.cpp into topology.o
topology.o: topology.cpp topology.h
	$(CXX) $(CXXFLAGS) -c topology.cpp

# Compile switch.cpp into switch.o
switch.o: switch.cpp switch.h
	$(CXX) $(CXXFLAGS) -c switch.cpp




# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)
