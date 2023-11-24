bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data:
    a db 128
    b db 2
;128*2   
segment code use32 class=code:

        start:
            mov AL,[a]
            mov BL,[b]
            mul BL
            push dword(0)
            call [exit]
            