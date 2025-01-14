CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I/usr/include/catch2 -Wall -Wextra -pedantic
SRC_DIR = src
TESTS_DIR = tests
BIN_DIR = $(TESTS_DIR)/bin
OBJECTS = $(SRC_DIR)/ComplexNumber.cpp $(SRC_DIR)/ComplexVector.cpp $(SRC_DIR)/ComplexMatrix.cpp $(SRC_DIR)/CXLibrary.cpp
TESTS = $(wildcard $(TESTS_DIR)/*.cpp)
EXECUTABLES = $(TESTS:$(TESTS_DIR)/%.cpp=$(BIN_DIR)/%)

.PHONY: all clean run-tests

all: $(EXECUTABLES)

$(BIN_DIR)/%: $(TESTS_DIR)/%.cpp $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

run-tests: $(EXECUTABLES)
	@for test in $(EXECUTABLES); do \
		echo "Running $$test..."; \
		$$test || exit 1; \
	done

clean:
	rm -rf $(BIN_DIR)