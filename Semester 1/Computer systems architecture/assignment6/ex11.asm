bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
    a DD 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783A2Bh, 7C7A8BFFh
    len equ ($-a)/4
    b1 times len DB 0 
    b2 times len DB 0
   
; Given an array A of doublewords, build two arrays of bytes:  
; - array B1 contains as elements the higher part of the higher words from A
; - array B2 contains as elements the lower part of the lower words from A   
   
segment code use32 class=code

        start:
        
            MOV ECX,len
            MOV ESI,a
            JECXZ sfarsit
            MOV EDI,b2
            
            solve_1:
                LODSD 
                STOSB
            LOOP solve_1 
            
            CLD
            MOV ECX,len
            MOV ESI,a
            JECXZ sfarsit
            MOV EDI,b1
            
            solve_2:
                LODSD
                SHR EAX,24
                STOSB
            LOOP solve_2
            
            sfarsit:
              
                push dword(0)
                call [exit]
            
