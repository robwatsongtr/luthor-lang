CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = main.cpp src/lexer.cpp src/parser.cpp src/interpreter.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = luthor

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
