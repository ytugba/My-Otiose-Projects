;xlat example  
;indices: 0    1    2    3  
TABLE DB 3FH, 06H, 5BH, 4FH  
;DB 66H, 6DH, 7DH, 27H ; these lines are commented since this is not supported by the emulator in 8086 mode
;DB 7FH, 6FH     

mov al, 1  ; try with 0 to 3
mov bx, offset TABLE
xlat 





