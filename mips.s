
.text
_foo:
        la $sp, -8($sp)
        sw $fp, 4($sp)
        sw $ra, 0($sp)
        la $fp, 0($sp)
        la $sp, -4($sp)

        lw $t0, _a
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

        lb $t0, _b
        la $sp, -4($sp)
        sw $t0, 0($sp)

        jal _print_int
        la $sp, 4($sp)

        la $t0, _StrLbl1
        la $sp, -4($sp)
        sw $t0, 0($sp)

.data
_StrLbl1: .asciiz "\n"
.text

        jal _print_string
        la $sp, 4($sp)

        lw $t0, _c
        la $sp, -4($sp)
        sw $t0, 0($sp)

        jal _print_int
        la $sp, 4($sp)

        la $t0, _StrLbl2
        la $sp, -4($sp)
        sw $t0, 0($sp)

.data
_StrLbl2: .asciiz "\n"
.text

        jal _print_string
        la $sp, 4($sp)

        lb $t0, _d
        la $sp, -4($sp)
        sw $t0, 0($sp)

        jal _print_int
        la $sp, 4($sp)

        la $t0, _StrLbl3
        la $sp, -4($sp)
        sw $t0, 0($sp)

.data
_StrLbl3: .asciiz "\n"
.text

        jal _print_string
        la $sp, 4($sp)

        lw $t0, _e
        la $sp, -4($sp)
        sw $t0, 0($sp)

        jal _print_int
        la $sp, 4($sp)

        la $t0, _StrLbl4
        la $sp, -4($sp)
        sw $t0, 0($sp)

.data
_StrLbl4: .asciiz "\n"
.text

        jal _print_string
        la $sp, 4($sp)

        la $sp, 0($fp)
        lw $ra, 0($sp)
        lw $fp, 4($sp)
        la $sp, 8($sp)
        jr $ra


.data
.text

_main:
        la $sp, -8($sp)
        sw $fp, 4($sp)
        sw $ra, 0($sp)
        la $fp, 0($sp)
        la $sp, -4($sp)

        li $t0, 10
        sw $t0, -4($fp)
        sw $t0, _main_tmp0_

        lw $t1, _main_tmp0_
        sw $t1, _a

        li $t0, 11
        sw $t0, -4($fp)
        sw $t0, _main_tmp1_

        lw $t1, _main_tmp1_
        sb $t1 _b

        li $t0, 12
        sw $t0, -4($fp)
        sw $t0, _main_tmp2_

        lw $t1, _main_tmp2_
        sw $t1, _c

        li $t0, 13
        sw $t0, -4($fp)
        sw $t0, _main_tmp3_

        lw $t1, _main_tmp3_
        sb $t1 _d

        li $t0, 14
        sw $t0, -4($fp)
        sw $t0, _main_tmp4_

        lw $t1, _main_tmp4_
        sw $t1, _e

        jal _foo
        la $sp, 4($sp)

        la $sp, 0($fp)
        lw $ra, 0($sp)
        lw $fp, 4($sp)
        la $sp, 8($sp)
        jr $ra


.data
.align 2
_main_tmp4_: .space 4
.align 2
_main_tmp3_: .space 4
.align 2
_main_tmp2_: .space 4
.align 2
_main_tmp1_: .space 4
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
_e: .space 4
.align 2
_d: .space 4
.align 2
_c: .space 4
.align 2
_b: .space 4
.align 2
_a: .space 4
