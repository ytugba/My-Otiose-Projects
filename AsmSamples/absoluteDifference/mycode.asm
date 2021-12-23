;takes the absolute difference of ax and bx
;stores the result in dx

mov ax, 1234h
mov bx, 5678h

cmp ax, bx
jc DIFF2; jump if carry==1
DIFF1: mov dx, ax
       sub dx, bx
       jmp DONE
DIFF2: mov dx, bx
       sub dx, ax
DONE:ret ;---- 