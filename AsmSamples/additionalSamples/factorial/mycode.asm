; factorial example for a number stored in dl
org 100h

mov al, 1
mov dl, 4

mov cx, dx
l0:
    mul cl     
    loop l0     
hlt   
 