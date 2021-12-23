; find the largest element in an array and store it in dx. 
;The array ends with an 0xaa end-of-block value.
org 100h   
;
ARRAY DB 11h, 22h, 88h, 99h, 33h, 77h, 44h, 55h, 0xaa
;  
cld; auto-increment  
mov si, offset ARRAY 
mov bx, 0; compare all with bx and store the temp result therein. 
l0: lodsb 
    cmp ax,0xaa 
    jz end
    cmp ax,bx 
    jb continue:
    mov bx, ax    
continue:     
    jmp l0 
end:       
    mov dx, bx
hlt   
 