# based on the makefile of google test https://github.com/google/googletest/tree/master/googletest/make/Makefile

SOURCES = sample1.c sample1_unittest.cc

TMP = $(SOURCES:.c=.o)
OBJECTS = $(TMP:.cc=.o)

# Paths

VPATH = ./src:./test

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

EXEC = unittests

all : $(EXEC)

gtest-all.o : $(GTEST_SRCS_) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $(OBJ_DIR)/$@

gtest_main.o : $(GTEST_SRCS_) | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $(OBJ_DIR)/$@

gtest.a : gtest-all.o | $(OBJ_DIR)
	$(AR) $(ARFLAGS) $(OBJ_DIR)/$@ $(addprefix $(OBJ_DIR)/,$^)

gtest_main.a : gtest-all.o gtest_main.o | $(OBJ_DIR)
	$(AR) $(ARFLAGS) $(OBJ_DIR)/$@ $(addprefix $(OBJ_DIR)/,$^)

%.o: %.cc | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $(OBJ_DIR)/$@

%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

unittests : gtest_main.a $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $(addprefix $(OBJ_DIR)/, $^) -o $(BIN_DIR)/$@

$(BIN_DIR):
	 mkdir $(BIN_DIR)

$(OBJ_DIR):
	 mkdir $(OBJ_DIR)

.PHONY: clean
clean :
	rm -r ./obj
	rm -r ./bin
