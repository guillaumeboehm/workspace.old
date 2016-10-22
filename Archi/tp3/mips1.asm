.data

hello: .asciiz "Salut, mec!\n"

.text
.globl __start

__start:
la $a0 hello
li $v0 4
syscall

j Exit

Exit:
li $v0 10
syscall
