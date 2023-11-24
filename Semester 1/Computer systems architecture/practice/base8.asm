bits 32
global start

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class = data

    sir db "1011"
    len equ $-sir
    format db "%c",0
    space db " ",0

segment code use32 class = code

    start:
           mov esi,sir+len-1
           std
           mov ecx,len
           
           repeta:
                lodsb
                cwde
                pushad
                push eax
                push dword format
                call [printf]
                add esp,4*2
                popad
           loop repeta     
         
         
         push dword(0)
         call [exit]
            
            