data1 DW 1234H  ; define data1
data2 DW 5678H  ; define data2

;difference of lea and mov   
lea di, data2
lea bx,[di]
mov cx,[di] 

;this is the same as lea
mov cx, offset data2


lea si, data1   ; address data1 with si
mov di, offset data2 ; address data2 with di
mov bx,[si]  ; exchange data1 and data2
mov cx, [di]
mov [si], cx
mov [di], bx 
               
; check the data contents of memory locations           
mov ax, [si]
mov bx, [di]



