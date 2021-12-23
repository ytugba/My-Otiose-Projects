;xchg example
mov si, 1ah
mov [si], 1234h

mov ax, 5678h

xchg ax, [si]
mov bx, [si]