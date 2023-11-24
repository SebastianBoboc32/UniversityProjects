bits 32
global start

extern exit,scanf,fprintf,fopen,fclose

import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class = data

    accmode db "w",0
    filename db "output_file.txt",0
    fd db -1
    character dd 0
    format db "%d",0
    ;end_criteria db 36
    ;aux dd 0
    
segment code use32 class = code

    start:
        push dword accmode
        push dword filename
        call [fopen]
        add esp,4*2
        
        cmp EAX,0
        je end_
        mov [fd],EAX
        
        push dword character
        push dword format
        call [scanf]
        add ESP,4*2
        
        push dword [character]
        push dword format
        push dword [fd]
        call [fprintf]
        add ESP,4*3
        
      ;  mov ECX,10
        
       ; _solve:
        
           ; mov [aux],ECX
           ; push dword character
           ; push dword format
          ;  call [scanf]
           ; add ESP,4*2
            
           ; mov EDX,character
           ; cmp EDX,end_criteria
            ;mov ECX,[aux]
           ; jne print_value
            ;je _end
            
            ;print_value:
                
               ; push dword character
               ; push dword format
               ; push dword [fd]
               ; call [fprintf]
               ; add ESP,4*3
               ; mov ECX,[aux]
               ; inc ECX

        ;loop _solve
        
        
        
        end_:
            push dword [fd]
            call [fclose]
            add ESP,4
            push dword(0)
            call [exit]