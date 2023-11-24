bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
       a dw 40
       b dw 37
       c dw 55
       d dw 29

segment code use32 class=code
    ; (b-c) + (d-a)
    start:
    
        mov AX,[b]
        sub AX,[c]
        
        mov BX,[d]
        sub BX,[a]
        
        add AX,BX
    
        push dword(0)
        call[exit]
