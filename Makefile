# GENERAL VARIABLES
NAME            := $(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")
TARGET          ?= release
DEBUG           := 0
ifeq ($(TARGET),debug)
	DEBUG       := 1
endif

PRETTY_OUTPUT   := 1
STD             := c++17
STATIC          := 0


# COMMAND VARIABLES
RM              := rm -r
MKDIR           := mkdir -p
DOXYGEN         := doxygen
PKGCONFIG       := pkg-config

# CROSS COMPILATION SETUP
CROSS           := 

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

# CROSS COMPILATION ADAPTATION
OBJ_EXT         := .o
NULL            := /dev/null

ifeq ($(PLATFORM),WINDOWS)
	OUT_EXT     := .exe
	STATIC      := 1
	ifneq ($(HOSTPLATFORM),WINDOWS)
		CROSS   := i686-w64-mingw32.static-
	endif
endif

# DIRECTORIES
BIN_DIR         := bin
OBJ_DIR         := obj

SRC_DIR         := src
INC_DIR         := inc

FILES           := $(filter-out $(BIN_DIR) $(OBJ_DIR), $(wildcard *))

# FLAGS
COMMONFLAGS     :=
ifneq ($(STATIC), 0)
    COMMONFLAGS += -static
endif
ifneq ($(DEBUG), 1)
	COMMONFLAGS += -O2
else
	COMMONFLAGS += -ggdb3 -Og
endif
CFLAGS          := $(COMMONFLAGS)
CXXFLAGS        := $(COMMONFLAGS)
WARNFLAGS       := -Wall -Wextra -Wpedantic -Winit-self -Wuninitialized -Wpointer-arith -Wcast-align -Wunreachable-code
LIBS            := 
BINFLAGS        := $(LIBS)
INCLUDEFLAGS    := -I${INC_DIR}
DEFINES         :=
ifeq ($(DEBUG), 1)
	DEFINES     += -DDEBUG
endif

# OBJECT FILES
CXX_SRC_FILES   := $(wildcard   $(SRC_DIR)/*.cpp) \
				   $(wildcard   $(SRC_DIR)/*/*.cpp) \
				   $(wildcard   $(SRC_DIR)/*/**.cpp)
CXX_SRC_FILES   := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CXX_SRC_FILES))

CC_SRC_FILES    := $(wildcard   $(SRC_DIR)/*.c) \
				   $(wildcard   $(SRC_DIR)/*/*.c) \
				   $(wildcard   $(SRC_DIR)/*/*/*.c)
CC_SRC_FILES    := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CC_SRC_FILES))


OBJ_FILES       := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT), $(CXX_SRC_FILES)) \
				   $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT), $(CC_SRC_FILES))

TEST_FILES      := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/$(TARGET)/test_%$(OUT_EXT), $(CXX_SRC_FILES)) \
				   $(patsubst $(SRC_DIR)/%.c,  $(BIN_DIR)/$(TARGET)/test_%$(OUT_EXT), $(CC_SRC_FILES))


# TARGETS
default: $(BIN_DIR)/$(TARGET)/$(NAME)$(OUT_EXT)

all: $(BIN_DIR)/$(TARGET)/$(NAME)$(OUT_EXT) docs test

$(BIN_DIR)/$(TARGET):
	${MKDIR} $@

$(OBJ_DIR)/$(TARGET):
	${MKDIR} $@

$(BIN_DIR)/$(TARGET)/$(NAME)$(OUT_EXT): $(OBJ_FILES) | $(BIN_DIR)/$(TARGET)
	${LINK_STATUS}
	${RECIPE_IF} ${CROSS}${CXX} -o$@ $^ -std=${STD} ${CXXFLAGS} ${WARNFLAGS} ${STATICFLAGS} ${INCLUDEFLAGS} ${DEFINES} ${BINFLAGS} ${RECIPE_RESULT_LINK}

$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT): $(SRC_DIR)/%.cpp | $(OBJ_DIR)/$(TARGET)
	${COMPILE_STATUS}
	${RECIPE_IF} ${CROSS}${CXX} -c  -o$@ $< -std=${STD} ${CXXFLAGS} ${WARNFLAGS} ${STATICFLAGS} ${INCLUDEFLAGS} ${DEFINES} ${RECIPE_RESULT_COMPILE}

$(OBJ_DIR)/$(TARGET)/%$(OBJ_EXT): $(SRC_DIR)/%.c | $(OBJ_DIR)/$(TARGET)
	${COMPILE_STATUS}
	${RECIPE_IF} ${CROSS}${CC} -c -o$@ $< -std=${STD} ${CFLAGS} ${WARNFLAGS} ${STATICFLAGS} ${INCLUDEFLAGS} ${DEFINES} ${RECIPE_RESULT_COMPILE}

clean:
	-${RM} ${BIN_DIR} ${OBJ_DIR} ${NAME}.tar 2> ${NULL}

docs: Doxyfile
	-${DOXYGEN}

loc:
	-find ${SRC_DIR} ${INC_DIR} -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' -type f | xargs wc -l


# TAR
tar: ${NAME}.tar

dist: tar

${NAME}.tar:
	${ARCHIVE_STATUS}
	$(RECIPE_IF) tar -cf $@ ${FILES} $(RECIPE_RESULT_ARCHIVE)

.PHONY: default all clean docs loc tar dist


ifeq ($(PRETTY_OUTPUT),1)
.SILENT:
RECIPE_IF = if
COMPILE_STATUS = printf "\033[K\033[0mBuilding object \033[1m$@\033[0m...\033[0m\r"
COMPILE_OK = printf "\033[K\033[0;32mBuilt object \033[1;32m$@\033[0;32m \033[0m\n"
COMPILE_FAILED = printf "\033[K\033[0;31mFailed building \033[1;31m$@\033[0;31m from\033[0m \033[1;31m$<\033[0;31m!\033[0m\n"; exit 1
RECIPE_RESULT_COMPILE = ; then $(COMPILE_OK); else $(COMPILE_FAILED); fi
ARCHIVE_STATUS = printf "\033[K\033[0mCreating library archive \033[1m$@\033[0m...\033[0m\r"
ARCHIVE_OK = printf "\033[K\033[0;32mCreated library archive \033[1;32m$@\033[0;32m \033[0m\n"
ARCHIVE_FAILED = printf "\033[K\033[0;31mFailed creating library archive \033[1;31m$@\033[0;31m from\033[0m \033[1;31m$<\033[0;31m!\033[0m\n"; exit 1
RECIPE_RESULT_ARCHIVE = ; then $(ARCHIVE_OK); else $(ARCHIVE_FAILED); fi
LINK_STATUS = printf "\033[K\033[0;0mLinking \033[1m$@\033[0;0m...\033[0m\r"
LINK_OK = printf "\033[K\033[0;32mLinked \033[1;32m$@\033[0;32m \033[0m\n"
LINK_FAILED = printf "\033[K\033[0;31mFailed linking \033[1;31m$@\033[0;31m!\nIf the build options, environment, or system packages have changed, run \'\033[1;31mmake clean\033[0;31m\' and try again.\033[0m\n"; exit 1
RECIPE_RESULT_LINK = ; then $(LINK_OK); else $(LINK_FAILED); fi
else
RECIPE_IF =
BUILD_STARTED =
COMPILE_STATUS =
COMPILE_OK = true
COMPILE_FAILED = false; exit 1
RECIPE_RESULT_COMPILE =
ARCHIVE_STATUS =
ARCHIVE_OK = true
ARCHIVE_FAILED = false; exit 1
RECIPE_RESULT_ARCHIVE =
LINK_STATUS =
LINK_OK = true
LINK_FAILED = false; exit 1
RECIPE_RESULT_LINK =
endif
