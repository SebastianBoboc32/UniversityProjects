bits 32
global start

extern exit,fopen,fclose,scanf,fprintf

import exit msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class = data

    fd db -1
    acces_mode db "w",0
    filename db "file.txt",0
    char dd 0
    format db "%c",0
    end_criteria dd "$",0
    aux dd 0
    
segment code use32 class = code

    start:
    
        push dword acces_mode
        push dword filename
        call [fopen]
        add ESP,4*2
        
        cmp EAX,0
        je end_
        mov [fd],EAX
        
        mov ECX,1
        
        solve:
            mov [aux],ECX
            push dword char
            push dword format
            call [scanf]
            add ESP,4*2
            
            mov ECX,[aux]
            mov EBX,[char]
            cmp EBX,[end_criteria]
            je end_
            
            push dword [char]
            push dword format
            push dword [fd]
            call [fprintf]
            add ESP,4*3
            inc ECX
            
        loop solve
        
        end_:
            
            push dword [fd]
            call [fclose]
            
            push dword(0)
            call [exit]
    