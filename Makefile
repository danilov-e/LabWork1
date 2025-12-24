PROJECT = run_tests

MAIN = lab1

OUTPUT_IMAGES = rotated_cw.bmp rotated_ccw.bmp blurred.bmp

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -pthread
GTEST_LIBS = -lgtest -lgtest_main -pthread

TEST_SRC = tests.cpp BMPHandler.cpp ImageOps.cpp
MAIN_SRC = main.cpp BMPHandler.cpp ImageOps.cpp

TEST_OBJ = $(TEST_SRC:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

.PHONY: all test main clean cleanall

all: $(MAIN) $(PROJECT)

$(PROJECT): $(TEST_OBJ)
	$(CXX) -o $@ $^ $(GTEST_LIBS)

$(MAIN): $(MAIN_OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

test: $(PROJECT)
	./$(PROJECT)

clean:
	rm -f $(TEST_OBJ) $(MAIN_OBJ) $(OUTPUT_IMAGES)

cleanall: clean
	rm -f $(PROJECT) $(MAIN)
