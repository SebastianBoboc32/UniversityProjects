print_letter:
     mov eax,0
     mov al,byte [char]
     push eax
     push dword format
     push dword [fd_output]
     call [fprintf]
     add esp,4*3
     ret