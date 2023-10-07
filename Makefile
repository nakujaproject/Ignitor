# Compiler and flags
CC = g++
CFLAGS = -std=c++11

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test

# Common source files
COMMON_SOURCES = \
    $(SRC_DIR)/main.cpp \
    $(SRC_DIR)/utilities.cpp \
    $(INCLUDE_DIR)/utilities.h

# Targets
FreeRTOS_Project: $(COMMON_SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(COMMON_SOURCES) -Lpath/to/FreeRTOS/Source -lFreeRTOS

STM32Cube_Project: $(COMMON_SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(COMMON_SOURCES) -Lpath/to/STM32Cube_FW/Drivers/STM32xxxx_HAL_Driver/Src -lSTM32Cube

BareMetal_Project: $(COMMON_SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(COMMON_SOURCES)

MbedOS_Project: $(COMMON_SOURCES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(COMMON_SOURCES) -Lpath/to/MbedOS/Lib -lMbedOS

# Clean
clean:
	rm -f FreeRTOS_Project STM32Cube_Project BareMetal_Project MbedOS_Project
