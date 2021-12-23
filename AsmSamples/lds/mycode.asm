; create a 32 bit number
mov [0020h], 1234h 
mov [0022h], 5678h    

mov di, 0020h

lds bx, [di]  ; transfers the 32 bit number into bx and ds registers