bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class = data


segment code use32 class = code

    start:
        mov ch,62h
        mov dh, 200
        sub ch,dh
        push dword(0)
        call [exit]