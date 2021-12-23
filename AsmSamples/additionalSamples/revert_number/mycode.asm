;revert the hexadecimal digits of a word stored in ax
;given 0xabcd, we need to get 0xdcba
;note that we cannot simply rotate the number to left or right 16 times
;since this would give the original number.

org 100h  

mov ax, 0xabcd
call revert
hlt   

revert proc    
       ; we need to swap the most significant byte with the least significant byte
       xchg al, ah
       ; then we need to rotate each byte 4 times
       mov cl, 4
       ror al, cl
       ror ah, cl    
       ret
endp
 