PROJECT         := $(shell basename $(CURDIR))

MAKE            ?= make

DEBUG           := 0
STATIC          := 0
VERBOSE         := 0
WIN             := 0
CROSS           :=
CROSSSUFFIX     :=

ifndef HOSTPLATFORM
    HOSTPLATFORM := UNKNOWN
    ifeq ($(findstring Windows,$(OS)),Windows)
        HOSTPLATFORM := WINDOWS
    else
        uname := $(strip $(shell uname -s))
        ifeq ($(findstring Linux,$(uname)),Linux)
            HOSTPLATFORM := LINUX
        else ifeq ($(findstring MINGW,$(uname)),MINGW)
            HOSTPLATFORM := WINDOWS
        else ifeq ($(findstring MSYS,$(uname)),MSYS)
            HOSTPLATFORM := WINDOWS
        endif
    endif
endif

ifndef PLATFORM
    PLATFORM := $(HOSTPLATFORM)
endif


ifneq ($(DEBUG), 0)
    TARGET      := Debug
else
    TARGET      := Release
endif

ifneq ($(VERBOSE), 0)
    PREFIX      := 
else
    PREFIX      := @
endif

OUT_DIR         := bin
OBJ_DIR         := obj
SRC_DIR         := src
INC_DIR         := include

OUT_EXT         :=
OBJ_EXT         := .o

ifeq ($(PLATFORM),WINDOWS)
	OUT_EXT     := .exe
	STATIC      := 1
	ifneq ($(HOSTPLATFORM),WINDOWS)
		CROSS       := i686-w64-mingw32-
	endif
endif

CXX_SRC_FILES   := $(wildcard $(SRC_DIR)/*.cpp) \
				   $(wildcard $(SRC_DIR)/*/*.cpp)
CC_SRC_FILES    := $(wildcard $(SRC_DIR)/*.c) \
				   $(wildcard $(SRC_DIR)/*/*.c)

OBJ_FILES       := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT),$(CXX_SRC_FILES)) \
                   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT),$(CC_SRC_FILES))

LIBS            := -I$(INC_DIR) -L$(SRC_DIR)
COMMONFLAGS     := -Wall -Wextra -Winit-self -Wuninitialized -Wpointer-arith -Wcast-align -Wunreachable-code --ansi -Wpedantic
COMMONFLAGS     += $(FLAGS) $(LIBS)

ifneq ($(STATIC), 0)
    COMMONFLAGS += -static
endif

ifneq ($(DEBUG), 0)
    COMMONFLAGS += -g -DDEBUG
else
    COMMONFLAGS += -O3
endif
CFLAGS          := $(COMMONFLAGS) --std=c11
CXXFLAGS        := $(COMMONFLAGS) --std=c++11

CC              := $(CROSS)gcc$(CROSSSUFFIX)
CXX             := $(CROSS)g++$(CROSSSUFFIX)

MKDIR           := mkdir -p
RM              := rm -r

default_target: directories all

all: $(OUT_DIR)/$(TARGET)/$(PROJECT)$(OUT_EXT)

directories:
	$(PREFIX)$(MKDIR) $(OUT_DIR)/$(TARGET) \
					  $(OBJ_DIR)/$(TARGET) \
					  $(OBJ_DIR)/$(TARGET)/base \
  					  $(OBJ_DIR)/$(TARGET)/items \

$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT): $(SRC_DIR)/%.c
	@echo [CC] $@
	$(PREFIX)$(CC)  $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT): $(SRC_DIR)/%.cpp
	@echo [CXX] $@
	$(PREFIX)$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT_DIR)/$(TARGET)/$(PROJECT)$(OUT_EXT): $(OBJ_FILES)
	@echo [CXX] $@
	$(PREFIX)$(CXX) $(CXXFLAGS) -o $@ $^


rmobj:
	-$(PREFIX)$(RM) $(OBJ_DIR) 2> /dev/null

clean: rmobj

test: default_target
	@echo exit | ./$(OUT_DIR)/$(TARGET)/$(PROJECT) > /dev/null # launches the binary and exits immediately

loc:
	-find . -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp'| xargs wc -l

doxy:
	@-doxygen
