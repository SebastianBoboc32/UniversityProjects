bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
       e dw 55
       f dw 74
       a db 8
       b db 4
       
segment code use32 class=code

           ;55+74=129
           ; 2*8+3*4=28
           ;129*28=3612
        ;(e+f)*(2*a+3*b)
        start:
           
           mov al,[a]
           mov bl,2
           mul bl;ax=2a
           mov bx,ax;bx=2*a
           
           mov al,[b]
           mov cl,3
           mul cl;ax=3*b
           
           add ax,bx;ax=3*b+2*a
           mov bx,[e]
           add bx,[f];bx=e+f
           mul bx; dx:ax=(3*b+2*a)*(e+f)
           
           push dword(0)
           call[exit]
       