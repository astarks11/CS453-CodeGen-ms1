
.text
_foo:
        la $sp, -8($sp)
        sw $fp, 4($sp)
        sw $ra, 0($sp)
        la $fp, 0($sp)
        la $sp, -4($sp)

        lw $t0, 8($fp)
        sw $t0, _foo_y

        lw $t0, _foo_y
        la $sp, -4($sp)
        sw $t0, 0($sp)

        jal _print_int
        la $sp, 4($sp)

        la $t0, _StrLbl0
        la $sp, -4($sp)
        sw $t0, 0($sp)

.data
_StrLbl0: .asciiz "\n"
.text

        jal _print_string
        la $sp, 4($sp)

        la $sp, 0($fp)
        lw $ra, 0($sp)
        lw $fp, 4($sp)
        la $sp, 8($sp)
        jr $ra


.data
.align 2
_foo_y: .space 4
.text

_main:
        la $sp, -8($sp)
        sw $fp, 4($sp)
        sw $ra, 0($sp)
        la $fp, 0($sp)
        la $sp, -4($sp)

        li $t0, 123
        sw $t0, -4($fp)

        lw $t1, -4($fp)
        sw $t1, _x

        lw $t0, _x
        la $sp, -4($sp)
        sw $t0, 0($sp)

        jal _foo
        la $sp, 4($sp)

        la $sp, 0($fp)
        lw $ra, 0($sp)
        lw $fp, 4($sp)
        la $sp, 8($sp)
        jr $ra


.data
.align 2
_main_tmp0_: .space 4
.text

main:
        j _main

_print_int:
        li $v0, 1
        lw $a0, 0($sp)
        syscall
        jr $ra

_print_string:
        li $v0, 4
        lw $a0, 0($sp)
        syscall
        jr $ra
.data
.align 2
_x: .space 4
