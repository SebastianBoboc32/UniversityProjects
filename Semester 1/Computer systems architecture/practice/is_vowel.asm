is_vowel:
    mov esi,vowels
    mov ecx,5
    vrf:
        lodsb
        cmp al,bl
        je valid
    loop vrf
    ret
        
    valid:
        mov bl,1
        ret
    
; modifies al,bl,esi,ecx    