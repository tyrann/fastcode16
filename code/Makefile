# based on the makefile of google test https://github.com/google/googletest/tree/master/googletest/make/Makefile

SOURCES = sample1.c sample1_unittest.c bigint.c bigint_unittest.c logging.c

OBJECTS = $(SOURCES:.c=.o)

VPATH = ./src:./test:./src/logging

GTEST_DIR = ./lib/googletest

BIN_DIR = ./bin

OBJ_DIR = ./obj

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

EXEC = $(BIN_DIR)/unittests

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(EXEC)

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

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/unittests : $(OBJ_DIR)/gtest_main.a $(addprefix $(OBJ_DIR)/, $(OBJECTS)) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

$(BIN_DIR):
	 mkdir $(BIN_DIR)

$(OBJ_DIR):
	 mkdir $(OBJ_DIR)

.PHONY: clean
clean :
	rm -r ./obj
	rm -r ./bin
