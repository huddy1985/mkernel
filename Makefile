FLAGS			:=
LIBS 			:=
CC				:= gcc
AR				:= ar
LD				:= ld
ARCH			:= elf_i386
FLARCH		:= elf32
LDFLAGS	:= scripts/link.ld
FLAGS			:= -fno-stack-protector
ASM			:= nasm

SRC				= $(wildcard src/*.c)
ASM_SRC	= $(wildcard src/*.asm)
STD_INC		= ./include
STD_SRC	= ./src/std
SRC 			+= $(wildcard $(STD_SRC)/*.c)
OBJ				= $(patsubst %.c, %.o, $(SRC))
OBJ 				+= $(patsubst %.asm, %.o, $(ASM_SRC))

QEMU			:= qemu-system-i386

TARGET 		= kernel

$(TARGET): $(OBJ)
	@echo $(OBJ)
	@echo "src -->" $(SRC)
	$(LD) -m $(ARCH) -T $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	@echo "compiling $< ==> $@"
	$(CC) -m32 -c $< -o $@ $(FLAGS) -I$(STD_INC)

%.o: %.asm
	$(ASM) -f $(FLARCH) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJ)

run:
	$(QEMU) -$(TARGET) $(TARGET)
