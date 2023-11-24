bits 32
global start

extern exit,scanf,printf
import exit msvcrt.dll

import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data
    
    number dd 0
    format db "%d",0
    zero dd 0
    result dd 66000
   
segment code use32 class = code

    start:
    
        mov ECX,1
        
        solve:
        
            push dword number
            push dword format
            call [scanf]
            add ESP,4*2
            
            mov EBX,[number]
            cmp EBX,[zero]
            JE end_of_loop
            
            cmp EBX,[result]
            jg do_not_change
            mov [result],EBX
            
            do_not_change:
            inc ECX
        
        loop solve
        
        end_of_loop:
        
            push dword [result]
            push dword format
            call [printf]
            add ESP,4*2
            
            push dword(0)
            call [exit]
            