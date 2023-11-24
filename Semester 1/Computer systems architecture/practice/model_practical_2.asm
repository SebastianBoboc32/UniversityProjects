bits 32
global start
%include "case_1.asm"
%include "case_2.asm"

extern printf,scanf,exit,strlen
import printf msvcrt.dll
import scanf msvcrt.dll
import exit msvcrt.dll
import strlen msvcrt.dll

segment data use32 class = data
    number db 0
    string times 100 db 0
    new_string times 300 db 0
    p db "p",0
    format_number db "%d",0
    format_string db "%s",0
    two db 2
    twenty db 20
    vowels db "a","e","i","o","u",0
    one db 0

segment code use32 class = code

    start:
        push dword number
        push dword format_number
        call [scanf]
        add esp,4*2
        
        push dword string
        push dword format_string
        call [scanf]
        add esp,4*2
        
        push dword string
        call [strlen]
        add esp,4*1
        
        mov ecx,eax
        
        mov ax,0
        mov al,[number]
        div byte [two]
        cmp ah,1
        JNE case_even
        JE case_odd
        
        case_even:
            call solve_case_1
            push dword string
            push dword format_string
            call [printf]
            add esp,4*2
    
        
        case_odd:
            call solve_case_2
            push dword new_string
            push dword format_string
            call [printf]
            add esp,4*2

            
        push dword(0)
        call [exit]
        
        
        
        