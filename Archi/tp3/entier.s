.data

instruct: .asciiz "entrer un entier : "

.text
.globl __start

__start:

la $a0 instruct
li $v0 4
syscall

li $v0 5
syscall
move $a0 $v0
li $v0 1
syscall

j Exit

Exit:
li $v0 10
syscall
