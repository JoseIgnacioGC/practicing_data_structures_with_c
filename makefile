# Compiler and flags
COMPILER = clang
C_FLAGS = -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer
LD_FLAGS = -fsanitize=address
FAST_FLAGS = -Wall -Wextra
OPTIMIZED_FLAGS = -Wall -Wextra -O3

# Source files
SRC_DIR = src
SRCS = main.c $(SRC_DIR)/linked_list.c $(SRC_DIR)/string.c

# Commands
ECHO_RUN = @echo Running `$(TARGET)` && @echo.

# Directories
BUILD_DIR = build

# Target
TARGET = $(BUILD_DIR)/main.exe

# Default target
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	@mkdir $@

# Compile main.c
$(TARGET): $(SRCS) | $(BUILD_DIR)
	$(COMPILER) $(C_FLAGS) main.c $(LD_FLAGS) -o $@

# Compile without memory guards (faster)
build_fast: $(SRCS) | $(BUILD_DIR)
	$(COMPILER) $(FAST_FLAGS) main.c -o $(TARGET)

build_optimized: $(SRCS) | $(BUILD_DIR)
	$(COMPILER) $(OPTIMIZED_FLAGS) main.c -o $(TARGET)

# Run the program
run:
	@$(MAKE) $(TARGET) --no-print-directory
	$(ECHO_RUN)
	@$(TARGET)

# Run the program (fast version)
run_fast:
	@$(MAKE) build_fast --no-print-directory
	$(ECHO_RUN)
	@$(TARGET)

run_optimized:
	@$(MAKE) build_optimized --no-print-directory
	$(ECHO_RUN)
	@$(TARGET)

# Clean build files
clean:
	rmdir /s /q $(BUILD_DIR) 2>nul || exit 0

.PHONY: all clean run build_fast run_fast