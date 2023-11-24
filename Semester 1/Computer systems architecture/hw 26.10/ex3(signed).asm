bits 32
global start

extern exit
import exit msvcrt.dll

;(a+b)/(2-b*b+b/c)-x

segment data use32 class=data

    a dd 700
    b db 18
    c db 15
    x dq 0c6bfh;x=50879(10)
    ;a+b=718
    ;b/c=1
    ;b*b=324
    ;2-b*b+b/c=-321
    ;(a+b)/(2-b*b+b/c)=-2
    ;(a+b)/(2-b*b+b/c)-x=-50881
    
segment code use32 class=code

    start:
       
        MOV AL,[b]
        CBW
        CWDE
        ADD EAX,[a];EAX=a+b
        
        PUSH EAX;a+b
        
        MOV AL,[b]
        IMUL byte [b]
        
        PUSH AX;b*b
        
        MOV AL,[b]
        CBW
        IDIV byte [c];AL=b/c
        CBW
        POP CX;CX=b*b
        mov BX,AX;BX=b/c
        MOV Al,2
        cbw
        SUB AX,CX
        ADD AX,BX; AX=2-b*b+b/c
        PUSH AX
        POP BX ;BX=2-b*b+b/c
        
        POP AX;   DX:AX=a+b
        POP DX
        
        IDIV BX ; DX=DX:AX%BX   AX=DX:AX/BX
        
        CWDE ;EAX=(a+b)/(2-b*b+b/c)
        CDQ  ; EDX:EAX=(a+b)/(2-b*b+b/c)
        
        MOV EBX,[x]
        MOV ECX,[x+4]
        
        SUB EAX,EBX
        SBB EDX,ECX  ;EDX:EAX=(a/b)/(2-b*b+b/c)-x
        
        
        push dword(0)
        call[exit]
        