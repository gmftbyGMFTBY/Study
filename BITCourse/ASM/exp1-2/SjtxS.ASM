; ���ݶ�
data segment
 p1     db"system ready!$"
 p2     db"GoodBye!$"
 p3     db"communication error!$"
 p4     db"send: $"
 p5     db"recv: $" 
data ends

; �����
code    segment
        assume  cs:code,ds:data

; ������
main proc far
start:
     push   ds        ; �����λ�ַ
     xor    ax,ax      ; ���ax
     push   ax        ; 0
     mov    ax,data    ; �������ݶ�
     mov    ds,ax

     ;������Ҫ�Լ�д������1==========================
     ;дLCR
     mov    dx,3fbh
     mov    al,00011010b
     out    dx,al

     ;д��Ƶϵ��
     mov    dx,3fbh
     mov    al,80h
     out    dx,al

     mov    dx,3f8h
     mov    al,0ch
     out    dx,al
     mov    dx,3f9h
     mov    al,00h
     out    dx,al

     mov    dx,3fbh
     mov    al,00001010b
     out    dx,al

     ;ΪFIFO��DLλ��д��
     mov    al,87h
     mov    dx,03fah
     out    dx,al
     ;1============================================

     ; дè, loop �Է�����ģʽ
     mov    dx,3fch
     mov    al,03h
     out    dx,al

     ; д���ж������Ĵ���,ȫ����ֹ
     mov    dx,3f9h
     mov    al,0fh
     out    dx,al
    
     ; ��ӡ�ַ��� system ready
     call   back
     mov    dx,offset p1
     mov    ah,9
     int    21h
     call   back
     
     ;������Ҫ�Լ�д������2====================
     ;���Ͳ���
     ;��������״̬�ж�
     ;����������
     ;����������
     send:
        ; �����·�Ĵ����Ƿ��д���
        mov     dx,3fdh
        in      al,dx
        test    al,1EH
        jnz     error

        ; OE����Ƿ���Է�������
        test    al,20h
        jz      receive 

        ; ���ͼ�������
        ; show the `send` string and get the character fromt he keyboard

	    mov	    dl,0ffh
	    mov	    ah,06h
	    int 	21h
	    jz	    receive
            
	    mov     dx,3f8h
        out     dx,al
     ;2==========================================

     ; ���� * �˳�
     cmp    al,'*'
     jz     stop

     ; �������Ļ
     call   back
     mov    dx,offset p4
     mov    ah,9
     int    21h

     mov    bx,7
     mov    ah,14
     int    10h

    ;�������Լ�д������3=======================
    ;���ղ���
    ;��������״̬�ж�
    ;����״̬�ж�

    receive:
        mov     dx,3fdh
        in      al,dx
        test    al,01h
        jz      send

        test    al,04h
        jnz     error
        
        ; ��������
        mov     dx,3f8h
        in      al,dx
    ;3=======================================

    ; ���յ� * ���˳�
    cmp    al,'*'
    jz     stop

    ; show the recv string and receive the character
    call    back
    mov     dx,offset p5
    mov     ah,9
    int     21h

    mov     bx,7
    mov     ah,14
    int     10h
    
    jmp     send


    ; something wrong, back to the send loop
    error:
        call    back
        mov     dx,offset p3
        mov     ah,9
        int     21h
        jmp     send
    stop:
        ; show the goodbye string for the user
        mov     dx,offset p2
        mov     ah,9
        int     21h
        ret
main endp


; print \n\b
back    proc     near
    push    ax
    push    dx
    mov     dl,0dh
    mov     ah,2
    int     21h
    mov     dl,0ah
    mov     ah,2
    int     21h
    pop     dx
    pop     ax
    ret
back endp

code ends
     end start