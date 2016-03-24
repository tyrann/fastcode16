# based on the makefile of google test https://github.com/google/googletest/tree/master/googletest/make/Makefile

GTEST_DIR = ./lib/googletest

USER_DIR = ./src

TEST_DIR = ./test

BIN_DIR = ./bin

OBJ_DIR = ./obj

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

TESTS = $(BIN_DIR)/sample1_unittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS)

clean :
	rm -r ./obj
	rm -r ./bin

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $@

$(OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $@

$(OBJ_DIR)/gtest.a : $(OBJ_DIR)/gtest-all.o | $(OBJ_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/gtest_main.a : $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gtest_main.o | $(OBJ_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/sample1.o : $(USER_DIR)/sample1.c $(USER_DIR)/sample1.h $(GTEST_HEADERS)  | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1.c -o $@

$(OBJ_DIR)/sample1_unittest.o : $(TEST_DIR)/sample1_unittest.c \
                     $(USER_DIR)/sample1.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(TEST_DIR)/sample1_unittest.c -o $@

$(BIN_DIR)/sample1_unittest : $(OBJ_DIR)/sample1.o $(OBJ_DIR)/sample1_unittest.o $(OBJ_DIR)/gtest_main.a | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

$(BIN_DIR):
	 mkdir $(BIN_DIR)

$(OBJ_DIR):
	 mkdir $(OBJ_DIR)
