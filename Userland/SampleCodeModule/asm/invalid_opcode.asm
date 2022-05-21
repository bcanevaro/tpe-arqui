GLOBAL invalid_opcode

section .text

invalid_opcode:
    enter 0, 0

    ud2

    leave
    ret