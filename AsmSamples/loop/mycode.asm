; multiplies each element of BLOCK1 by 2 and stores the result in BLOCK2
;      
org 100h
BLOCK1 DW 1h, 2h, 3h, 4h
BLOCK2 DW 4 DUP(?)
                                
cld; clear direction flag (auto-increment)
mov cx, 4
mov si, offset BLOCK1
mov di, offset BLOCK2
            
l1:   lodsw 
      mov dx, 2        
      mul dx
      stosw
      loop l1   
hlt



 