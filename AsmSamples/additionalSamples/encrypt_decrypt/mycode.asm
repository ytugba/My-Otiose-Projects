; this code encyrpts a hexadecimal digit stored in dx and decrypts it back to its original value 

; xlat operation: set AL to DS:[BX + unsigned AL]

org 100h  

jmp start
;  
;indices:  0,  1, 2,  3,  4,  5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15  
TABLE1 DB  1,  3, 5,  7,  9, 0xb, 0xc, 0xd, 0xe, 0xf, 0,   2,   4,   6,   8,   0xa
TABLE2 DB 0xa, 0,0xb, 1, 0xc, 2,  0xd,  3,  0xe,  4,  0xf, 5,   6,   7,   8,    9
;          0   1  2   3   4   5   6     7    8    9   10   11   12   13   14   15

start:
mov dx, 0xc
call encrypt   

call decrypt

hlt

encrypt proc    
        mov ax, dx  
        mov bx, offset TABLE1
        xlat  
        mov dx, ax
        ret
encrypt  endp 

decrypt proc    
        mov ax, dx  
        mov bx, offset TABLE2
        xlat  
        mov dx, ax
        ret
decrypt  endp






