bits 32
global start
%include "vrf_property.asm"


extern exit,scanf,fprintf,strlen,fopen,fclose,strlen,fread,printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import strlen msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import strlen msvcrt.dll
import fread msvcrt.dll

segment data use32 class = data

    n dd 0
    cuvant times 100 db 0
    file_descriptor dd -1
    acces_mode db "w",0
    file_name db "fisier.txt",0
    format_dec db "%d",0
    format_string db "%s",0
    format_str db "%s",10,0
    first_letter db 0
    last_letter db 0
    
segment code use32 class = code
    
    start:
        push dword acces_mode
        push dword file_name
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final
        mov [file_descriptor],eax
        
        push dword n
        push dword format_dec
        call [scanf]
        add esp,4*2
        
        mov ecx,1
        
        solve:
        
        pushad
        push dword cuvant
        push dword format_string
        call [scanf]
        add esp,4*2 
        cmp byte [cuvant],'#'
        je final
        popad
        
        pushad
        push dword cuvant
        call [strlen]
        add esp,4*1
        cmp eax,[n]
        jne _do_not_print
        mov esi,cuvant
        mov edx,eax
        call _vrf_property
        cmp EBX,1
        jne _do_not_print
        popad
        
        pushad
        push dword cuvant
        push dword format_str
        push dword [file_descriptor]
        call [fprintf]
        add esp,4*3
        popad
        
        _do_not_print:
        inc ecx
        loop solve
        
        push dword [file_descriptor]
        call [fclose]
        add esp,4*1
        
        final:
            push dword(0)
            call [exit]
        