KERN_DIR := kernel
OBJ_DIR := $(KERN_DIR)/build
ISO_DIR := $(KERN_DIR)/iso

CC := x86_64-elf-gcc
AS := x86_64-elf-as
NASM := nasm
LD := x86_64-elf-ld
GRUB_MKRESCUE := grub-mkrescue

# flags
CFLAGS := -ffreestanding -Wall -Wextra -m64 -I$(KERN_DIR)/include \
          -std=c99 -fno-stack-protector -mno-red-zone -fno-pie -fno-pic -Werror=implicit-function-declaration
LDFLAGS := -T linker.ld -nostdlib --allow-multiple-definition -no-pie

C_SRCS := $(shell find $(KERN_DIR) -name '*.c')
ASM_SRCS_NASM := $(shell find $(KERN_DIR) -name '*.asm')
ASM_SRCS_GAS := $(shell find $(KERN_DIR) -name '*.S')

C_OBJS := $(patsubst $(KERN_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SRCS))
ASM_OBJS_NASM := $(patsubst $(KERN_DIR)/%.asm, $(OBJ_DIR)/%.o, $(ASM_SRCS_NASM))
ASM_OBJS_GAS := $(patsubst $(KERN_DIR)/%.S, $(OBJ_DIR)/%.o, $(ASM_SRCS_GAS))

ALL_OBJS := $(C_OBJS) $(ASM_OBJS_NASM) $(ASM_OBJS_GAS)

# kernel
KERNEL_ELF := $(ISO_DIR)/boot/kernel.elf

.PHONY: all clean iso run debug

all: $(KERNEL_ELF) iso

# build C -> .c
$(OBJ_DIR)/%.o: $(KERN_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC		$<"

# build gnu asm -> .o
$(OBJ_DIR)/%.o: $(KERN_DIR)/%.S
	@mkdir -p $(dir $@)
	$(AS) --64 $< -o $@
	@echo "AS		$<"

# build NASM -> .o
$(OBJ_DIR)/%.o: $(KERN_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(NASM) -f elf64 $< -o $@
	@echo "NASM		$<"

# lonk kernel
$(KERNEL_ELF): $(ALL_OBJS) linker.ld
	@mkdir -p $(ISO_DIR)/boot
	$(LD) $(LDFLAGS) -o $@ $(filter %.o,$^)
	@echo "LD		$@"

# create ISO
iso: $(KERNEL_ELF)
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	@$(GRUB_MKRESCUE) -o kernel.iso $(ISO_DIR)
	@echo "ISO		kernel.iso"

clean:
	@rm -rf $(OBJ_DIR) $(ISO_DIR) kernel.iso

run: all
	@qemu-system-x86_64 -cdrom kernel.iso -m 2048M -hda ../hda.img -boot d

debug: all
	@qemu-system-x86_64 -cdrom kernel.iso -m 2048M -d int
