bits 32
global start

extern exit,fopen,fclose,fscanf,printf

import exit msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data

    n dd 0
    number dd 0
    base dw 8
    accmode db "r",0
    file_name db "file1.txt",0
    file_desciptor db -1
    format db "%d",0
    space db " ",0
    output dd 0
    ten db 10
    aux1 dw 0
    aux2 dw 0
    char db "%c",0
    
segment code use32 class = code

    start:
        
        push dword accmode
        push dword file_name
        call [fopen]
        add esp,4*2
        
        cmp EAX,0
        je _end
        mov [file_desciptor],EAX
        
        push dword n
        push dword format
        push dword [file_desciptor]
        call [fscanf]
        add ESP,4*3
        
        mov ECX,[n]
        
        solve:
            pushad
            push dword number
            push dword format
            push dword [file_desciptor]
            call [fscanf]
            add ESP,4*3
            popad
            
            mov EBX,ECX
            mov ECX,1
            
            mov [output],dword 0
            mov AX,[number]
            mov DX,[number+4] ; DX:AX = number
            
            construct_base_8:
               
                mov AX,[number]
                mov DX,[number+4]
                div word [base]
                mov [aux1],AX
                mov [aux2],DX
                mov AX,[output]
                mul word [ten]
                add AX,[aux2]  ; AX = (number%8)*10
                mov [output],AX 
                mov AX,[aux1]
                mov [number],AX
                cmp AX,0
                je end_of_construct_base_8
                inc ECX
            loop construct_base_8    
            
            end_of_construct_base_8:
            
                mov ECX,EBX
                pushad
                
                push dword [output]
                push dword format
                call [printf]
                add ESP,4*2
                
                push dword [space]
                push dword char
                call [printf]
                add ESP,4*2
                
                popad
        cmp ECX,0
        jnz solve
        
        _end:
        
            push dword [file_desciptor]
            call [fclose]
            add ESP,4*1
            push dword(0)
            call [exit]