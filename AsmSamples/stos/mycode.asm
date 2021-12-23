;stos example
mov di, 10h  
mov ax, 1234h
stosb ; write contents of ax as byte to the extra segment address indexed by di    

mov di, 20h  
mov ax, 1234h
stosw ; write contents of ax as word to the extra segment address indexed by di  