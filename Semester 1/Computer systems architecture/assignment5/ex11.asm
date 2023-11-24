bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    str1 db 10,4,6,7,9,11
    lenstr1 equ $-str1
    str2 times lenstr1 db 0
    str3 times lenstr1 db 0
    two db 2
    
segment code use32 class=code

        start:
            mov ecx,lenstr1
            mov esi,0
            mov edi,0
            jecxz sfarsit
            
            repeta1:
                ;constructing the string with even elements
                mov al,[str1+esi]
                cbw
                div byte [two]
                cmp ah,1
                je nrimpar
                   mov al,[str1+esi]
                   mov [str2+edi],al
                   inc edi
                nrimpar:
                    inc esi
            loop repeta1
            
            mov ecx,lenstr1
            mov esi,0
            mov edi,0
            ;jecxz sfarsit
            
            repeta2:
                ;constructing the string with odd elements
                mov al,[str1+esi]
                cbw
                div byte [two]
                cmp ah,1
                jne nrpar
                    mov al,[str1+esi]
                    mov [str3+edi],al
                    inc edi
                nrpar:
                    inc esi
            loop repeta2        
            sfarsit:
        
                push dword(0)
                call[exit]