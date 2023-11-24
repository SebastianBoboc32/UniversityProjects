bits 32
global start
%include "vrf_property.asm"

extern exit
import exit msvcrt.dll

segment data use32 class = data
    cuvant db "a","n","a",0
    first_letter db 0
    last_letter db 0
  
segment code use32 class = code
    start:
        mov esi,cuvant
        call _vrf_property
        push dword(0)
        call [exit]