bits 32
global start

extern exit
import exit msvcrt.dll

;(d-c)+(b-a)-(b+b+b)

segment data use32 class=data
    a db 7
    b dw 55
    c dd 160
    d dq 1f4ah
    ; d=8010(10)
    ; d-c=8010-160=7850
    ; b-a=48
    ; b+b+b=165
    ; (d-c)+(b-a)=7898
    ; (d-c)+(b-a)-(b+b+b)=7733
    
segment code use32 class=code

    start:
        MOV EAX,[d]
        MOV EDX,[d+4] 
        ; EDX:EAX=d
        
        MOV ECX,[c]
        MOV EBX,0 
        ; EBX:ECX=c
        
        SUB EAX,ECX
        SBB EDX,EBX ; EDX:EAX=d-c
        
        PUSH EDX
        PUSH EAX
        
        MOV BX,[b]
        MOV AL,[a]
        MOV AH,0
        SUB BX,AX ; BX=b-a
        
        POP EAX
        POP EDX  ; EDX:EAX=d-c
        
        MOV CX,BX
        MOV EBX,0
        MOV EBX,ECX
        MOV ECX,0  ; ECX:EBX=b-a
        
        ADD EAX,EBX
        ADC EDX,ECX ; EDX:EAX=(d-c)+(b-a)
        
        MOV BX,[b]
        ADD BX,word[b]
        ADD BX,word[b] ; BX=b+b+b
        
        PUSH BX
        MOV EBX,0
        POP CX
        MOV BX,CX
        MOV ECX,0 ; ECX:EBX=b+b+b
        
        SUB EAX,EBX
        SBB EDX,ECX ; EDX:EAX=(d-c)+(b-a)-(b+b+b)
        
        push dword(0)
        call [exit]
    
    