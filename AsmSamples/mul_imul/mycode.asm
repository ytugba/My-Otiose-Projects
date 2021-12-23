;8 bit multiplication
mov al, 2
mov bl, 4
mul bl  ; note that carry flag is 0

;8 bit multiplication, 16 bit result
mov al, 0xffh
mov bl, 0x2h
mul bl  ; note that carry flag is 1

;16 bit multiplication, 16 bit result
mov ax, 0xffffh
mov bx, 0xffffh
mul bx  
; note that carry flag is 1 and dx stores a value

;signed multiplication
mov al, -2
mov bl, 4

imul bl  ; hexadecimal for -8