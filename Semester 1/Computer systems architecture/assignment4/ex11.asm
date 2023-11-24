;Given the byte A and the word B, compute the byte C as follows:
;the bits 0-3 are the same as the bits 2-5 of A
;the bits 4-7 are the same as the bits 6-9 of B.

bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
  
        a db 01001110b
        b dw 1011000111010111b
        c resb 1
        ; the bits 2-5 of A are 0011
        ; the bits 6-9 of B are 0111
        ; so the byte c should be 01110011->c=1(10)+2(10)+16(10)+32(10)+64(10)=19(10)+96(10)=115(10)
        
segment code use32 class=code

        start:
            
            mov al,[a]  ; al=01001110
            shr al,2    ; al=00010011
            ;mov bx,[b]  ; bx=1011000111010111
            shr word [b],2    ; b=0010110001110101
            mov cl,[b]   ; cl=01110101
            ; if al=00010011 and cl=01110101 we need to store the bits 0-3 from al and the bits
            ; 4-7 from cl temporarly in a register before moving the result into the byte c
            xor al,00010000b;al=00000011
            xor cl,00000101b; cl=01110000
            or al,cl ;al=01110011
            mov [c],al
            push dword(0)
            call [exit]
            
            