bits 32
global start

extern exit,scanf,printf
import exit msvcrt.dll

import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data

    format db "number in decimal= %d",0
    n dd 467h
    
segment code use32 class = code

    start:
        
        push dword [n]
        push dword format
        call [printf]
        add ESP,4*2
        
        push dword(0)
        call [exit]