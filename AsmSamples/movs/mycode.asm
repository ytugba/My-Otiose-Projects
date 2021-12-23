data1 DW 1234H  ; define data1

lea si, data1   
mov di, 1bh   
movsb   ; transfer a byte from data segment to extra segment


lea si, data1   
mov di, 1bh   
movsw  ; transfer a word from data segment to extra segment