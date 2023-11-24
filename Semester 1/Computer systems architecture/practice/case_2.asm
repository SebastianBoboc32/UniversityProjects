%include "is_vowel.asm"

solve_case_2:
    mov esi,string
    mov edi,new_string
    
    solve:
        lodsb
        pushad
        mov bl,al
        call is_vowel
        mov byte [one],bl
        popad
        mov esi,string
        mov edi,new_string
        cmp byte [one],1
        jne do_not_add_p
        je add_p
        add_p:
            mov dl,al
            stosb
            mov al,byte [p]
            stosb
            mov al,dl
            stosb
        do_not_add_p:
            stosb
        
    loop solve
    ret
        
    ;modifies esi,edi,bl,al