PROJECT         := $(shell basename $(CURDIR))

MAKE            ?= make
MINGW-MAKE      ?= mingw32-make

DEBUG           ?= 0
STATIC          ?= 0
VERBOSE         ?= 0
WIN             ?= 0

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

OUT_DIR          = bin
OBJ_DIR          = obj
SRC_DIR          = src
INC_DIR          = include

CXX_SRC_FILES   := $(wildcard $(SRC_DIR)/*.cpp) \
				   $(wildcard $(SRC_DIR)/*/*.cpp)
CC_SRC_FILES    := $(wildcard $(SRC_DIR)/*.c) \
				   $(wildcard $(SRC_DIR)/*/*.c)

OBJ_FILES       := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/$(TARGET)/%.o,$(CXX_SRC_FILES)) \
                   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/$(TARGET)/%.o,$(CC_SRC_FILES))

LIBS            := -I$(INC_DIR) -L$(SRC_DIR)
COMMONFLAGS      = -Wall -Wextra -Winit-self -Wuninitialized -Wpointer-arith -Wcast-align -Wunreachable-code --ansi -Wpedantic
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

MKDIR           := mkdir -p
RM              := rm -r

default_target: directories all

all: $(OUT_DIR)/$(TARGET)/$(PROJECT)

WIN:
	$(PREFIX)$(MINGW-MAKE) STATIC=1

directories:
	$(PREFIX)$(MKDIR) $(OUT_DIR)/$(TARGET) \
					  $(OBJ_DIR)/$(TARGET) \

$(OBJ_DIR)/$(TARGET)/%.o: $(SRC_DIR)/%.c
	@echo [CC] $@
	$(PREFIX)$(CC)  $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(TARGET)/%.o: $(SRC_DIR)/%.cpp
	@echo [CXX] $@
	$(PREFIX)$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT_DIR)/$(TARGET)/$(PROJECT): $(OBJ_FILES)
	@echo [CXX] $@
	$(PREFIX)$(CXX) $(CXXFLAGS) -o $@ $^


rmdirectories:
	-$(PREFIX)$(RM) $(OUT_DIR) 2> /dev/null
	-$(PREFIX)$(RM) $(OBJ_DIR) 2> /dev/null

clean: rmdirectories

loc:
	-find . -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp'| xargs wc -l

doxy:
	@-doxygen
