# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`

# Source files
SRCS := $(wildcard *.cpp)

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable
TARGET = wx_HexEditor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
