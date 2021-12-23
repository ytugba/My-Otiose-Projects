; find the largest element in an array and store it in dx
org 100h   

ARRAY DB 11h, 22h, 88h, 99h, 33h, 77h, 44h, 55h
count DW 8   
  
cld; auto-increment  
mov cx, count
mov si, offset ARRAY 
mov bx, 0; compare all with bx and store the temp result therein. 

l0: lodsb 
    cmp ax,bx 
    jb continue:
    mov bx, ax    
continue:     
    loop l0      
    mov dx, bx
hlt   
 