bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    
    a db 11
    b dw 104
    c dd 600
    d dq 0f5bch;d=62908(10)
    ;a+b+c=115+600=715
    ;a+a=22
    ;d-(a+b+c)=62908-715=62193
    ;d-(a+b+c)-(a+a)=62193-22=62171
    
;d-(a+b+c)-(a+a)    
    
segment code use32 class=code
    
    start:
        
        MOV AL,[a]
        cbw
        ADD AX,[b]
        cwde
        ADD EAX,[c]
        
        PUSH EAX
        
        MOV AL,[a]
        ADD AL,byte [a]
        cbw
        cwde
        POP EBX ; EBX=a+b+c
        MOV ECX,EAX; ECX=a+a
        
        MOV EAX,[d]
        MOV EDX,[d+4] ; EDX:EAX=d
        
        push ECX
        
        mov ECX,0
        
        SUB EAX,EBX
        SBB EDX,ECX ; EDX:EAX=d-(a+b+c)
        
        POP EBX
        mov ECX,0 ; ECX:EBX=a+a
        
        SUB EAX,EBX
        SBB EDX,ECX ; EDX:EAX=d-(a+b+c)-(a+a)
        
        push dword(0)
        call[exit]