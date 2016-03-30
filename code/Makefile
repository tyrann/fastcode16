# based on the makefile of google test https://github.com/google/googletest/tree/master/googletest/make/Makefile

include Makefile_generic

TMP = $(SOURCES:.c=.o)
OBJECTS = $(TMP:.cc=.o)

OBJECTS_MEMORYTEST_POINTS = $(SOURCES_MEMORYTEST_POINTS:.c=.o)
OBJECTS_MEMORYTEST_EC_PARAMETER = $(SOURCES_MEMORYTEST_EC_PARAMETER:.c=.o)

# Paths
GTEST_DIR = ./lib/googletest

BIN_DIR = ./bin

OBJ_DIR = ./obj

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# compiler options

CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -DLOG_LEVEL=0

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

# targets

EXEC = $(BIN_DIR)/unittests  $(BIN_DIR)/memorytest_points $(BIN_DIR)/memorytest_parameter

all : $(EXEC)

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

$(OBJ_DIR)/%.o: %.cc | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/unittests : $(OBJ_DIR)/gtest_main.a $(addprefix $(OBJ_DIR)/,$(OBJECTS)) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

$(BIN_DIR)/memorytest_points : $(addprefix $(OBJ_DIR)/,$(OBJECTS_MEMORYTEST_POINTS)) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/memorytest_parameter : $(addprefix $(OBJ_DIR)/,$(OBJECTS_MEMORYTEST_EC_PARAMETER)) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR):
	 mkdir $(BIN_DIR)

$(OBJ_DIR):
	 mkdir $(OBJ_DIR)

.PHONY: clean
clean :
	rm -r ./obj
	rm -r ./bin
