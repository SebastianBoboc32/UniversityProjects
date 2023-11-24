bits 32
global start

extern fread,fscanf,printf,fopen,fclose,exit,strlen,fscanf
import fread msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import exit msvcrt.dll
import strlen msvcrt.dll
import fscanf msvcrt.dll

segment data use32 class = data
    file_name db "test_citire.txt",0
    acces_mode db "r",0
    file_descriptor dd -1
    len equ 100
    text times 100 db 0
    format db "%s",0
    lnt dd 0
    format_d db "%d",0
    numar db "7",0
    
segment code use32 class = code
    start:
        push dword acces_mode
        push dword file_name
        call [fopen]
        add esp,4*2
        
        cmp eax,-1
        je sfarsit
        mov [file_descriptor],eax
        
        
        
        ;push dword [file_descriptor]
       ; push dword len
        ;push dword 1
        ;push dword text
        ;call [fread]
        ;add esp,4*4
        
       ; pushad
       ; push text
        ;call [strlen]
        ;add esp,4*1
        ;mov dword [lnt],eax
        ;popad
       ; mov ecx,dword[lnt]
       ; push ecx
       ; push dword format_d
       ; call [printf]
       ; add esp,4*2
       
        ;mov edi,text
       ; my_loop:   
            ;push dword numar
            ;push dword format_d
            ;push dword [file_descriptor]
            ;call [fscanf]
            ;add esp,4*3
            ;cmp eax,-1
            ;je end_loop
            ;mov al,byte [numar]
            ;stosb
            ;jmp my_loop
            ;end_loop:
        
        mov edi,text
        mov al,byte[numar]
        cld
        stosb
        
        push dword text
        push dword format
        call [printf]
        add esp,4*2
        
        push dword [file_descriptor]
        call [fclose]
        add esp,4*1
        
        sfarsit:
            push dword(0)
            call [exit]