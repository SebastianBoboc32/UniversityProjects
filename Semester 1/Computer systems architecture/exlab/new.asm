bits 32

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dd 125
    b db 120
    c dw 12
    d db 2
    e dq 80
    
segment code use32 class=code
;a+b/c -d*2-e
        start:
             mov AL,[b]
             cbw
             cwd
             
             idiv word [c];AX=DX:AX/c DX=DX:AX%c
             mov BX,AX
             
             mov AL,2
             imul byte[d]
             
             sub BX,AX
             
             mov AX,BX
             cwde
             
             mov EBX,[a]
             
             add EAX,EBX
             
             ;mov EAX,EBX
             cdq
             
             sub EAX,[e]
             sbb EDX,[e+4]
             
             push dword(0)
             call[exit]