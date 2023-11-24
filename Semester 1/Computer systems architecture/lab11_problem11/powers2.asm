bits 32
global power_2

segment data use32 class = data
    two dd 2

power_2:
    
    mov ECX,[ESP+4]; power_2 -> returns 2^x, x= ECX
    mov EAX,1       ; EAX = 2^x
    jecxz _end
    
    solve_1:
        mul dword [two]
    loop solve_1
    
    _end:
        ret 4
    
 ;modifies ECX,EDX,EAX 