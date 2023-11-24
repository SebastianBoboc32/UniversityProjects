bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data

        a dq 11223344f5667788h
        b dq 0abcdef1a2b3c4d5eh
        
segment code use32 class=code
            
        start:
            mov EAX,[a];  EAX=f5667788
            mov EDX,[a+4];EDX=11223344
           
            
            mov ECX,[b];  ECX=abcdef1a
            mov EBX,[b+4];EBX=2b3c4d5e
            
            add EAX,ECX; EAX=EAX+ECX and set CF to 1/0
            adc EDX,EBX; EDX=EDX+EBX+CF
            
            push dword(0)
            call[exit]