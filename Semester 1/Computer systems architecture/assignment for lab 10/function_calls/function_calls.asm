bits 32
global start

extern exit,printf,scanf

import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class = data

    message_1 db "number in hexa:",10,13,0
    format_1 db "%x",0
    message_2 db "number in decimal: ",10,13,0
    format_2 db "%d",0
    x dd 0
    
segment code use32 class = code

    start:
        push dword message_1
        call [printf]
        add ESP,4*1
        
        push dword x
        push dword format_1
        call [scanf]
        add ESP,4*2
        
        push dword message_2
        call [printf]
        add ESP,4*1
        
        push dword [x]
        push dword format_2
        call [printf]
        add ESP,4*2
        
        push dword 0
        call [exit]
        