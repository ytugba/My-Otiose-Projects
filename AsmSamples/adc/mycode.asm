;32 bit addition with adc

mov ax, 0xffffh
mov cx, 1h   


add ax,cx; this generates a carry

mov bx,1234h
mov dx,1h  

adc bx, dx; bx=bx+dx+carry

  
