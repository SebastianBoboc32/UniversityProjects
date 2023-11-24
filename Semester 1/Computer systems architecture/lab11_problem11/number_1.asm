bits 32
global transform

extern power_2

segment data use32 class = data
    result dd 0
    one db "1"

transform:
         mov EBX,0 ; EBX = the power of two that needs to be added to the result
         mov [result],EBX
         jecxz _final
         create_number:
         mov eax,0
         mov al,[esi+ecx-1]
         cmp al,[one]
         jne _do_not_add
         pushad
         push EBX
         call power_2
         add [result], EAX
         popad
         _do_not_add:
            inc EBX
            dec ecx
            cmp ECX,0
            jge create_number
         _final:
               mov EAX,[result]
               ret 
         
        
        