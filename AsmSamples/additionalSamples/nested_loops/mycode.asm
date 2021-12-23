; nested for loop example
org 100h
     
mov ax, 0
mov bx, 0
mov dx, 0

mov cx, 4      
l0: 
    push cx
    mov cx, 3
        l1:    
            push cx
            mov cx, 2
            l2:  
                inc ax
                loop l2
            pop cx            
            inc bx
        loop l1
    pop cx  
    inc dx    
loop l0  
; end of loops   
hlt



 