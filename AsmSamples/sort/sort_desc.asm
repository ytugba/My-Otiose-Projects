;      
org 100h
ARRAY DB 11h, 99h, 22h, 88h, 33h, 77h, 44h, 55h
count DW 8

mov cx, count ; cx=8
dec cx        ; cx=7
nextscan: mov bx, cx ; bx stores the number of comparisons
          mov si, 0                 
nextcomp: mov al, ARRAY[si]  
          mov dl, ARRAY[si+1]
          cmp al, dl
          jnc noswap
          mov ARRAY[si], dl
          mov ARRAY[si+1], al
noswap:   inc si
          dec bx  
          jnz nextcomp
          loop nextscan    ; cx is automatically decremented in loop
          

                                



