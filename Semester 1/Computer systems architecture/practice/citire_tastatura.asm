bits 32
global start

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class = data
    numar_1 db 0
    numar_2 db 0
    sir times 10 db 0
    caracter db 0
    format_d db "%d",0
    format_x db "%x",0
    format_c db "%c",0
    format_s db "%s",0
    
segment code use32 class = code
    
    start:
        ;push dword numar_1
       ; push dword format_d
       ; call [scanf]
       ; add esp,4*2
        
        ;push dword numar_2
       ; push dword format_d
        ;call [scanf]
        ;add esp,4*2
        
        ;push dword caracter
        ;push dword format_c
       ; call [scanf]
       ; add esp,4*2
        
        push dword sir
        push dword format_s
        call [scanf]
        add esp,4*2
        
       ; push dword [numar_1]
        ;push dword format_d
        ;call [printf]
       ; add esp,4*2
        
        ;push dword [numar_2]
        ;push dword format_x
        ;call [printf]
        ;add esp,4*2
        
       ; push dword [caracter]
        ;push dword format_c
        ;call [printf]
        ;add esp,4*2
        
        push dword sir
        push dword format_s
        call [printf]
        add esp,4*2
        
        push dword(0)
        call [exit]