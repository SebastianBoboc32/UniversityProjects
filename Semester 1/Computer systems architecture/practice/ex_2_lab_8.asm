bits 32
global start

extern exit,printf,scanf
import exit msvcrt.dll

import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data

    a dd 0
    b dd 0
    format db "%d",0
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

            mov EAX,[a]
            cdq
            idiv dword [b]
            mov [result],EAX
            
            push dword [result]
            push dword format
            call [printf]
            add ESP,4*2
            
            push dword(0)
            call [exit]
            