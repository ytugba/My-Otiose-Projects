; find how many odd and even numbers are in an array 
;store the count for odd in bx, and for even in dx

org 100h   

ARRAY DW 8, 11, 43, 56, 507, 608, 0, 123, 17, 13
count DW 10   
  
cld; auto-increment  
mov cx, count
mov si, offset ARRAY   

mov bx, 0; count for odd numbers 
mov dx, 0; count for even numbers

;main loop- through all elements
l0: lodsw ; load as word, since they are stored as words
    shr ax, 1; shift right the ax by 1 bit so that the least significant bit will be copied to cf
    jnc even: ; if carry is 1 then odd, otherwise even
    inc bx
    jmp cnt
even: inc dx     
cnt:  ;continue
    loop l0
mov ax, 0; clear ax
hlt 



