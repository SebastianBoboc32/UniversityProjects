bits 32
global start

extern exit,scanf,printf
import exit msvcrt.dll

import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class= data

     a dd 23
     b dd 5
     format db "%d",0
     result dd 0
     modulo db "%",0
     format_char db "%c",0
     egal db "=",0
    
segment code use32 class = code

        start:
            
              mov EAX,[a]
              mov EDX,0
              div dword [b]
              mov [result],edx
              
              push dword [a]
              push dword format
              call [printf]
              add esp,4*2
              
              push dword [modulo]
              push dword format_char
              call [printf]
              add esp,4*2
              
              push dword [b]
              push dword format
              call [printf]
              add esp,4*2
              
              push dword [egal]
              push dword format_char
              call [printf]
              add esp,4*2
              
              push dword [result]
              push dword format
              call [printf]
              add esp,4*2
            
            push dword(0)
            call [exit]