# ============================================================================
#  Name        : Makefile
#  Since       : 28/11/2013
#  Author      : Alberto Realis-Luc <alberto.realisluc@gmail.com>
#  Web         : http://www.alus.it/
#  Version     : 0.0.1
#  Copyright   : (C) 2014 Alberto Realis-Luc
#  License     : GNU GPL v2
#  Repository  : https://github.com/TCASP/TCASP.git
#  Last change : 29/11/2014
#  Description : Makefile for TCASP
# ============================================================================
#
# If you're using Debian... you're right!
# Install the following packges: avr-libc avrdude gcc-avr gdb-avr
# Headers are here: /usr/lib/avr/include
# Libs are here: /usr/lib/avr/lib
#
# On command line:
# 	make all = Make software.
# 	make clean = Clean out built project files.
# 	make program = Download the hex file to the device, using avrdude
# To rebuild project do "make clean" then "make all".
# Using Eclipse it is possible to use another configuration to call the taget <program> to program directly the HEX on the MCB board
# The windows driver for the Atmel AVR USB programmer can be found in the directory: utils\libusb\bin of WinAVR
# ============================================================================

# Directory and paths configuration (useful on Windows...)
# DIRAVR = 
# DIRAVRBIN = $(DIRAVR)/bin
# DIRAVRUTILS = $(DIRAVR)/utils/bin
# DIRINC = .
# DIRLIB = $(DIRAVR)/avr/lib

# Compiler and other tools
CC = avr-gcc
CXX = avr-g++
AR = avr-ar
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
NM = avr-nm
AVRDUDE = avrdude

# Version string
VERSION = 0.0.1

# Source paths
SRC = src/

# Binary paths (output folder)
BIN = bin/

# Bootlader address
MT_BOOTLOADER_ADDRESS = F800 

# MCU type
MCU = atmega328p

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# Target file name (without extension).
TARGET = TCASP

# List of C++ source files of TCASP
CPP_SRC = \
	tcas.cpp \
	tcasalg.cpp \
	vector.cpp \
	aircraft.cpp

# List of TCASP objects
OBJ = $(patsubst %.cpp, $(BIN)%.cpp.o, $(CPP_SRC))

# Libraries path
LIBS = $(SRC)libs/

# List of libraries source files
LIBS_SRC = \
	RFM69.cpp \
	serLCD.cpp \
	SoftwareSerial.cpp \
	SPI.cpp \
	TinyGPS.cpp

# List of libraries objects
LIBS_OBJ = $(patsubst %.cpp, $(BIN)%.cpp.o, $(LIBS_SRC))

#Path of Arduino core sources
CORE = $(SRC)core/

# List of C source files of Arduino core
CORE_C_SRC = \
	malloc.c \
	WInterrupts.c \
	wiring.c \
	wiring_analog.c \
	wiring_digital.c \
	wiring_pulse.c \
	wiring_shift.c

# List of C++ source files of Arduino core
CORE_CPP_SRC = \
	CDC.cpp \
	HardwareSerial.cpp \
	HID.cpp \
	IPAddress.cpp \
	main.cpp \
	new.cpp \
	Print.cpp \
	Stream.cpp \
	Tone.cpp \
	USBCore.cpp \
	WMath.cpp \
	WString.cpp

#Lists of Arduino core objects
CORE_OBJ = $(patsubst %.c, $(BIN)%.c.o, $(CORE_C_SRC))
CORE_OBJ += $(patsubst %.cpp, $(BIN)%.cpp.o, $(CORE_CPP_SRC))

# List of include paths
INCLUDES = \
-I$(SRC) \
-I$(CORE) \
-I$(LIBS)

# Optimization level, can be [0, 1, 2, 3, s]. 
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# C Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS = -mmcu=$(MCU)
#CFLAGS += -g$(DEBUG)
CFLAGS += -g
CFLAGS += -O$(OPT)
#CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall
#CFLAGS += -Wstrict-prototypes
#CFLAGS += -Wa,-adhlns=$(@:.o=.lst)
#CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
#CFLAGS += $(CSTANDARD)
CFLAGS += $(INCLUDES)

# C++ compiler flags
CPPFLAGS = $(CFLAGS)
CPPFLAGS += -fno-exceptions

# Defines
DEFS = -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=104

# Linker flags
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
#  -lm: math lib
LFLAGS = -O$(OPT) -Wl,--gc-sections -mmcu=$(MCU)
LLIBS = -L$(BIN) -lm


#---------------- Programming Options (avrdude) ----------------

# Programming hardware. Type: avrdude -c ? to get a full listing.
#AVRDUDE_PROGRAMMER = avrispmkII
AVRDUDE_PROGRAMMER = arduino

# Programming port: com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = /dev/ttyACM0

AVRDUDE_WRITE_FLASH = -U flash:w:$(BIN)$(TARGET).hex:i
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(BIN)$(TARGET).eep

# Use the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn, see avrdude manual.
#AVRDUDE_ERASE_COUNTER = -y

# Use the following if you do /not/ wish a verification to be performed after programming the device.
#AVRDUDE_NO_VERIFY = -V

# Increase verbosity level.  Please use this when submitting bug reports about avrdude.
AVRDUDE_VERBOSE = -v -v

# Avrdude configuration file
AVRDUDE_CONFIG = avrdude.conf

# Avrdude speed
AVRDUDE_SPEED = 115200

# Avrdude flags
AVRDUDE_FLAGS = -p$(MCU) -P$(AVRDUDE_PORT) -c$(AVRDUDE_PROGRAMMER) -C$(AVRDUDE_CONFIG) -b$(AVRDUDE_SPEED)
AVRDUDE_FLAGS += $(AVRDUDE_VERBOSE)


# Dependencies
all: $(BIN)$(TARGET).hex

# Create bin directory if missing
$(OBJ): | $(BIN)
$(BIN):
	mkdir -p bin

# Build HEX file
$(BIN)$(TARGET).hex: $(BIN)$(TARGET).elf
	@echo **** Building HEX file: $@ ****
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@
	@echo *** Building EEP file: $(BIN)$(TARGET).eep ***
	$(OBJCOPY) -O $(FORMAT) -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $(BIN)$(TARGET).eep
#	@echo *** Creating extended listing LSS file: $(BIN)$(TARGET).lss ***
#	$(OBJDUMP) -h -S $< > $(BIN)$(TARGET).lss
#	@echo *** Creating symbol table SYM file: $(BIN)$(TARGET).sym ***
#	$(NM) -n $< > $(BIN)$(TARGET).sym

# Link all and build ELF file
$(BIN)$(TARGET).elf: $(OBJ) $(LIBS_OBJ) $(BIN)core.a
	@echo *** Linking: $@ ***
	$(CC) $(LFLAGS) $(OBJ) $(LIBS_OBJ) $(BIN)core.a $(LLIBS) -o $@

# Compile project C++ files
$(BIN)%.cpp.o: $(SRC)%.cpp
	@echo ** Compiling G++: $< **
	$(CXX) -c $(CPPFLAGS) $(DEFS) $< -o $@

# Compile project C files
$(BIN)%.c.o: $(SRC)%.c
	@echo ** Compiling GCC: $< **
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

# Compile libaries files
$(BIN)%.cpp.o: $(LIBS)%.cpp
	@echo ** Compiling library file: $< **
	$(CXX) -c $(CPPFLAGS) $(DEFS) $< -o $@

# Build Arduino core.a static library
$(BIN)core.a: $(CORE_OBJ)
	@echo *** Building Arduino core static library: $@ ***
	$(AR) rcs $(BIN)core.a $(BIN)wiring_digital.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)wiring_shift.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)wiring.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)WInterrupts.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)wiring_analog.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)wiring_pulse.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)malloc.c.o 
	$(AR) rcs $(BIN)core.a $(BIN)new.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)main.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)HardwareSerial.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)IPAddress.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)CDC.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)USBCore.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)Tone.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)HID.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)Print.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)Stream.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)WMath.cpp.o 
	$(AR) rcs $(BIN)core.a $(BIN)WString.cpp.o

# Compile Arduino core library C++ files
$(BIN)%.cpp.o: $(CORE)%.cpp
	@echo ** Compiling Arduino core library C++ file: $< **
	$(CXX) -c $(CPPFLAGS) $(DEFS) $< -o $@

# Compile Arduino core library C files
$(BIN)%.c.o: $(CORE)%.c
	@echo ** Compiling Arduino core library C file: $< **
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

# Clean project
clean:
	@echo **** Clean $(TARGET) project ****
	rm $(BIN)*

# Program Arduino board
program: $(BIN)$(TARGET).hex $(BIN)$(TARGET).eep
	@echo **** Uploading $(TARGET) on Arduino board ****
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)

