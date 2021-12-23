; automatically fills the first block by the given number of values and 
; then puts it into the second block in reverse order      
org 100h    
; allocate space for the blocks 
NUM DW 10    ; number of elements to be used
BLOCK1 DW 15 DUP(?) ; allocate a sufficiently large memory area for both blocks
BLOCK2 DW 15 DUP(?)
                                
cld; clear direction flag (auto-increment)  

mov bx, 0 ; used to generate incremental numbers 1,2,3...  
mov cx, NUM        
mov di, 0
;fill the first block
l0:inc bx
   mov BLOCK1[di], bx ;fill the word positions in the first block
   add di,2; next word position
   dec cx 
   cmp cx, 0 ; compare cx against 0
   jnz l0 ; this will stop jumping when cx becomes 0


; now reverse the block 
mov cx, NUM 

mov si, offset BLOCK1
mov di, offset BLOCK2  

;push to stack
l1: lodsw
push ax    
loop l1
        
mov cx, NUM
;pop from stack
l2: pop ax
stosw    
loop l2


