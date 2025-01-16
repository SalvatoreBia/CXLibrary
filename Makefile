CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -pedantic
SRC_DIR = src
TESTS_DIR = test
BIN_DIR = $(TESTS_DIR)/bin
OBJECTS = $(SRC_DIR)/ComplexNumber.cpp $(SRC_DIR)/ComplexVector.cpp $(SRC_DIR)/ComplexMatrix.cpp $(SRC_DIR)/CXLibrary.cpp $(SRC_DIR)/ComplexTensor.cpp
TESTS = $(wildcard $(TESTS_DIR)/*.cpp)
EXECUTABLES = $(TESTS:$(TESTS_DIR)/%.cpp=$(BIN_DIR)/%)

CATCH2_INCLUDE_DIR = $(shell whereis -b catch2 | awk '{print $$2}')

CXXFLAGS += -I$(CATCH2_INCLUDE_DIR)

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
