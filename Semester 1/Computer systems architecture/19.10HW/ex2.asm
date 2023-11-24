bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
     a db 17
     b db 11
     c db 9
     d db 8
     
;(a+c-d)+d-(b+b+c)     
segment code use32 class=code  
    
      start:
        
           mov AL, [a]
           add AL,[c]
           sub AL,[d]
           
           mov BL,[d]
           
           mov CL,[b]
           add CL,[b]
           sub CL,[c]
           
           add AL,BL
           sub AL,CL
           
           push dword(0)
           call [exit]  