print_ascii:
     mov eax,0
     mov al,byte [char]
     push eax
     push dword format_d
     push dword [fd_output]
     call [fprintf]
     add esp,4*3
     ret