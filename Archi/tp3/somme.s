.data

instruct: .asciiz "entrer l'entier 1 : "
instruct2: .asciiz "entrer l'entier 2 : "

.text
.globl __start

__start:

#lis l'entier 1
la $a0 instruct
li $v0 4
syscall

li $v0 5
syscall

move $t0 $v0

#lis l'entier 2
la $a0 instruct
li $v0 4
syscall

li $v0 5
syscall

move $a0 $v0

#fait la somme
add $a0 $a0 $t0

j Display

j Exit

Display:
#affiche l'entier
li $v0 1
syscall
jr $ra

Exit:
li $v0 10
syscall
