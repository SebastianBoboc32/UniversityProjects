bits 32
global start

extern transform
extern exit,scanf,printf,strlen
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import strlen msvcrt.dll

segment data use32 class = data
    sir dd 0
    nr dd 0
    format_s dd "%s",0
    format_d dd "%d",0
    format_c dd "%c",0
    format_x dd "%x",0
    len dd 0
    EBX_aux dd 0
segment code use32 class = code
    
    start:
           push dword nr
           push dword format_d
           call [scanf]
           add esp,4*2
           mov ebx,[nr]
           solve:
           
                 pushad
                 push dword sir
                 push dword format_s
                 call [scanf]
                 add esp,4*2
                 popad
                 
   
                 push dword sir
                 call [strlen]
                 add esp,4

                 
                 mov ecx,eax  ; ECX=len(sir)
               
                      
                 ;mov [len],ecx
                 mov [EBX_aux],EBX
                 mov esi,sir
                 
                 cld
                 pushad
                 call transform
                 push EaX
                 push dword format_x
                 call [printf]
                 add esp,4*2
              
                 
                 popad
                 mov EBX,[EBX_aux]
                 dec EBX
                 cmp EBX,0
                 jne solve
        
        
        
        push dword(0)
        call [exit]