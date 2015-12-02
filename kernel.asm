; Linker stuff
bits 32
section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002+0x00)

; Calling C
global start
extern _kmain ; Main method in C
start:
    cli
    call _kmain
    hlt