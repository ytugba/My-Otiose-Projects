;      
org 100h
BLOCK1 DW 1h, 2h, 3h, 4h
BLOCK2 DW 4 DUP(?)
                                
cld; clear direction flag (auto-increment)  

mov cx, 4  
mov bx,0  

mov si, offset BLOCK1
mov di, offset BLOCK2  

;push to stack
l1: lodsw
push ax    
inc bx
loop l1
        
mov cx, bx
;pop from stack
l2: pop ax
stosw    
loop l2


