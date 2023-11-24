bits 32                         

global MMCfactorial

;MMCfactorial(int):int
;                - 1 parameter N:integer
;                - calculates factorial of N
;                - return value in EAX: integer 
;                - uses/modifies eax, ecx, edx 
MMCfactorial:


	mov eax, 1
	mov ecx, [esp + 4]
	
	.repet: 
		mul ecx
	loop .repet
    
   
    
	ret 4 ; argument 4 from ret means free 4 bytes in the stack (one dword)