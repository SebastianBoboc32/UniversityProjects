
_vrf_property:
   lodsb
   mov byte [first_letter],al
   all_letters:
    lodsb
    dec edx
    cmp edx,1
    jne all_letters
    cmp byte [first_letter],al
    jne return
    mov ebx,1
    return:
        ret
    
    