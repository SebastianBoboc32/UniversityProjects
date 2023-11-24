bits 32
global start

extern exit
import exit msvcrt.dll

;(a+b)/(2-b*b+b/c)-x

segment data use32 class=data

    a dd 1756
    b db 22
    c db 5
    x dq 30
    ;a+b=1778
    ;b/c=4
    ;b*b=484
    ;2-b*b+b/c=2-484+5=-482+5=-477
    ;(a+b)/(2-b*b+b/c)=-3
    ;(a+b)/(2-b*b+b/c)-x=-33
    
segment code use32 class=code

    start:
       
        MOV AL,[b]
        MOV AH,0 ;converting byte AL to AX
        MOV BX,AX
        MOV EAX,0
        MOV AX,BX ; converting word AX to dword EAX
        ADD EAX,[a];EAX=a+b
        
        PUSH EAX;a+b
        
        MOV AL,[b]
        MUL byte [b]
        
        PUSH AX;b*b
        
        MOV AL,[b]
        MOV AH,0
        DIV byte [c];AL=b/c
        MOV AH,0
        POP CX;CX=b*b
        mov BX,AX;BX=b/c
        MOV Al,2
        MOV AH,0
        SUB AX,CX
        ADD AX,BX; AX=2-b*b+b/c
        PUSH AX
        POP BX ;BX=2-b*b+b/c
        
        POP AX;   DX:AX=a+b
        POP DX
        
        DIV BX ; DX=DX:AX%BX   AX=DX:AX/BX
        MOV CX,AX
        MOV EAX,0
        MOV AX,CX ;EAX=(a+b)/(2-b*b+b/c)
        MOV EDX,0  ; EDX:EAX=(a+b)/(2-b*b+b/c)
        
        MOV EBX,[x]
        MOV ECX,[x+4]
        
        SUB EAX,EBX
        SBB EDX,ECX  ;EDX:EAX=(a/b)/(2-b*b+b/c)-x
        
        
        push dword(0)
        call[exit]