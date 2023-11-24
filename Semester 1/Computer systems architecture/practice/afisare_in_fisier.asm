bits 32
global start

extern scanf,fprintf,exit,fopen,fclose,gets,strlen
import scanf msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import gets msvcrt.dll
import strlen msvcrt.dll

segment data use32 class = data
    file_descriptor dd -1
    file_name db "file_test.txt",0
    acces_mode db "w",0
    sir times 781 db 0
    format db "%s",0
    numar db 0
    format_x db "%x",0
    format_d db "%d",0
segment code use32 class = code
    
    start:
        push dword acces_mode
        push dword file_name
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je sfarsit
        
        mov [file_descriptor],eax
        
        push dword sir
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword sir
        push dword format
        call [gets]
        add esp,4*2
        
        push dword sir
        call [strlen]
        add esp,4*1
        
        push dword [eax]
        push dword format_d
        push dword [file_descriptor]
        call [fprintf]
        add esp,4*3
        
        push dword [file_descriptor]
        call [fclose]
        add esp,4*1
        
        
        
        
        sfarsit:
            push dword(0)
            call [exit]
    