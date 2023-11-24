bits 32
global start

extern exit,scanf,printf
import exit msvcrt.dll

import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class= data

    format db "%d",0
    a dw 0
    b dw 0
    result dd 0
    
segment code use32 class = code

        start:
            
            push dword a
            push dword format
            call [scanf]
            add ESP,4*2
            
            push dword b
            push dword format
            call [scanf]
            add ESP,4*2
            
            mov AX,[a]
            mul word [b]
            
            push DX
            push AX
            pop dword [result]
            
            push dword [result]
            push dword format
            call [printf]
            add ESP,4*2
            
            push dword(0)
            call [exit]