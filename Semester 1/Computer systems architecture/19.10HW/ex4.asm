bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

        a db 7
        b db 8
        c db 11
        d dw 22
        
segment code use32 class=code

    ;[(d/2)*(c+b)-a*a]/b
    ; 11*19-49=209-49=160
    ;160/8=20
    
    start:
        mov AX,[d];    AX=d
        mov BL,2
        div BL;        AL=d/2 AH=d%2
        mov CL,[c];    CL=c
        add CL,[b];    CL=c+b
        mul CL ;       AX=(d/2)*(c+b)
        
        mov BX,AX;     BX=(d/2)*(c+b)
        mov AL,[a];    AL=a
        mul byte [a];  AX=a*a
        sub BX,AX;     BX=(d/2)*(c-b)-a*a
        mov AX,BX;     AX=(d/2)*(c-b)-a*a
        
        div byte [b];  AL=[(d/2)*(c+b)-a*a]/b  AH=[(d/2)*(c+b)-a*a]%b
        
       push dword(0)
       call[exit]
       