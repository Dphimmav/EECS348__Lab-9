CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.
LDFLAGS = -lgtest -lgtest_main -pthread

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TEST_SRC = tests/tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

TARGET = matrix_operations
TEST_TARGET = matrix_tests

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ) matrix.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)

.PHONY: all test clean