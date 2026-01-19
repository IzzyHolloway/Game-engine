# En av oss satt på linux, och ville ha en makefile som funkar på alla OS

# Universal Makefile för Windows, Mac och Linux
# Automatisk detektering av operativsystem och SDL3



# DIN KÄLLKOD - var dina egna .cpp-filer finns
SRC_DIR = src
# FILNAMNET för ditt program som skall byggas, och VAR
OBJ_NAME = play
BUILD_DIR = build/debug

# Detektera operativsystem
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

# ALLA filer med filändelsen .cpp i foldern SRC_DIR
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Valbara kompileringsflaggor (options)
COMPILER_FLAGS = -std=c++23 -Wall -O0 -g

# ============ WINDOWS KONFIGURATION ============
ifeq ($(DETECTED_OS),Windows)
    CC = g++
    COMPILER_FLAGS += -DSDL_MAIN_HANDLED
    INCLUDE_PATHS = -Iinclude -IC:/msys64/ucrt64/include
    LIBRARY_PATHS = -Llib -LC:/msys64/ucrt64/lib
    # SDL3 för Windows
    LINKER_FLAGS = -lmingw32 -lstdc++exp -lSDL3 -lSDL3_image -lSDL3_ttf
    # SDL2 för Windows (avkommentera för SDL2)
    #LINKER_FLAGS = -lmingw32 -lstdc++exp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf
endif

# ============ MAC KONFIGURATION ============
ifeq ($(DETECTED_OS),Darwin)
    # Använd g++ (Clang) eller g++-14 (GCC-14)
    CC = g++
    # För GCC-14: avkommentera raden nedan
    #CC = g++-14
    
    # Mac ARM (Apple Silicon)
    INCLUDE_PATHS = -Iinclude -I/opt/homebrew/include
    LIBRARY_PATHS = -Llib -L/opt/homebrew/lib
    
    # Mac Intel (avkommentera för Intel Mac)
    #INCLUDE_PATHS = -Iinclude -I/usr/local/include
    #LIBRARY_PATHS = -Llib -L/usr/local/lib
    
    # SDL3 för Mac
    LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf
    # SDL2 för Mac (avkommentera för SDL2)
    #LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf
endif

# ============ LINUX KONFIGURATION ============
ifeq ($(DETECTED_OS),Linux)
    CC = g++
    INCLUDE_PATHS = -Iinclude -I/usr/local/include
    LIBRARY_PATHS = -Llib -L/usr/local/lib
    # SDL3 för Linux
    LINKER_FLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf
    # SDL2 för Linux (avkommentera för SDL2)
    #LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    MKDIR = mkdir -p $(BUILD_DIR)
    RM = rm -rf
endif

# ============ BUILD TARGET ============
all:
	$(MKDIR)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)

# ============ UTILITIES ============
clean:
	$(RM) $(BUILD_DIR)

.PHONY: all clean
