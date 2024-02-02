MBALIGN equ 1<<0
MEMINFO equ 1<<1
VIDMODE equ 1<<2
FLAGS equ MBALIGN | MEMINFO | VIDMODE
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
WIDTH equ 1024
HEIGHT equ 768
BPP equ 128
TEXT equ 0
;Section for multiboot information
section .multiboot
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd TEXT
    dd WIDTH
    dd HEIGHT
    dd BPP


section .bss
    align 16
global memory_stack_bottom:function
memory_stack_bottom:
    resb 16777216
global memory_stack_top:function
memory_stack_top:

section .text
    global _start:function (_start.end - _start)
    _start:
        ;Move esp register to top of memory stack
        mov esp, memory_stack_top
        push ebx
        ;Enter protected mode
        cli
        extern gdtp
        ;Load the global descriptor table
        lgdt [gdtp]
        mov eax, cr0
        or al, 1
        mov cr0, eax
        extern initiate_mini_kernel
        ;Start the mini kernel
        call initiate_mini_kernel
        cli
        hlt
.end: