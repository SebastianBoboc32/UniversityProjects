bits 32
global start

extern fscanf,fprintf,exit,fopen,fclose
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

print_letter:
     mov eax,0
     mov al,byte [char]
     push eax
     push dword format
     push dword [fd_output]
     call [fprintf]
     add esp,4*3
     ret 

print_ascii:
     mov eax,0
     mov al,byte [char]
     push eax
     push dword format_d
     push dword [fd_output]
     call [fprintf]
     add esp,4*3
     ret   


segment data use32 class = data
    fd_input dd -1
    fd_output dd -1
    acces_mode_in db "r",0
    acces_mode_out db "w",0
    format db "%c",0
    file_name_input db "input.txt",0
    file_name_output db "output.txt",0
    char db  0
    format_d db "%d",0
    z db "z",0
    a db "a",0
    
segment code use32 class = code
    start:
    
        push dword acces_mode_in
        push dword file_name_input
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final_f
        mov [fd_input],eax
        
        push dword acces_mode_out
        push dword file_name_output
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final_f
        mov [fd_output],eax
        
        my_loop:
        
            pushad
            push dword char
            push dword format
            push dword [fd_input]
            call [fscanf]
            add esp,4*3
            cmp eax,-1
            je final
            popad
            
            mov cl,byte[char]
            cmp cl,byte[a]
            jb do_not_convert
            cmp cl,byte[z]
            jbe convert
            
            do_not_convert: 
                pushad
                call print_letter
                popad
                jmp my_loop
                
             convert:
                pushad
                call print_ascii
                popad
            jmp my_loop
         
        final:
            push dword [fd_input]
            call [fclose]
            add esp,4
            push dword [fd_output]
            call [fclose]
            add esp,4
            push dword(0)
            call [exit]
            
        final_f:
                push dword(0)
                call [exit]
                
  