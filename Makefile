CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -MMD -MP -ggdb

IM_CXXFLAGS?=$(shell Magick++-config --cxxflags)
IM_LDFLAGS?=$(shell Magick++-config --ldflags)
IM_LIBS?=$(shell Magick++-config --libs)

BUILD_DIR	:= build
SRC_DIR		:= src
INCLUDE_DIR	:= include
LIB_DIR		:= lib

PCH_OUT := PCH.h.gch
PCH_SRC := PCH.h

SRCS := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

LIBRARIES	:= -lrgbmatrix -lpthread -lX11 
EXECUTABLE	:= prot_os

all: $(BUILD_DIR)/$(EXECUTABLE)

run: clean all
	clear
	./$(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(BUILD_DIR)/$(SRC_DIR)/$(PCH_OUT) $(OBJS)
	$(CXX) $(OBJS) -L$(LIB_DIR) -o $@ $(LIBRARIES) $(IM_LIBS)

$(BUILD_DIR)/$(SRC_DIR)/$(PCH_OUT): $(SRC_DIR)/$(PCH_SRC)
	mkdir -p $(dir $@)
	cp $(SRC_DIR)/$(PCH_SRC) $(BUILD_DIR)/$(SRC_DIR)/$(PCH_SRC)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(IM_CXXFLAGS) $(IM_LDFLAGS) -include $(BUILD_DIR)/$(SRC_DIR)/$(PCH_SRC) -I$(INCLUDE_DIR) -I$(SRC_DIR) -Dcimg_use_magick -c $< -o $@

clean:
	-rm -r $(BUILD_DIR)/*
