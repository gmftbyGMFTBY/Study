; 数据段
data segment
 p1     db"system ready!$"
 p2     db"GoodBye!$"
 p3     db"communication error!$"
 p4     db"send: $"
 p5     db"recv: $" 
data ends

; 代码段
code    segment
        assume  cs:code,ds:data

; 主函数
main proc far
start:
     push   ds        ; 保护段基址
     xor    ax,ax      ; 清空ax
     push   ax        ; 0
     mov    ax,data    ; 加载数据段
     mov    ds,ax

     ;下面是要自己写的内容1==========================
     ;写LCR
     mov    dx,3fbh
     mov    al,00011010b
     out    dx,al

     ;写分频系数
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

     ;为FIFO的DL位回写零
     mov    al,87h
     mov    dx,03fah
     out    dx,al
     ;1============================================

     ; 写猫, loop 自发自收模式
     mov    dx,3fch
     mov    al,03h
     out    dx,al

     ; 写入中断允许寄存器,全部禁止
     mov    dx,3f9h
     mov    al,0fh
     out    dx,al
    
     ; 打印字符串 system ready
     call   back
     mov    dx,offset p1
     mov    ah,9
     int    21h
     call   back
     
     ;下面是要自己写的内容2====================
     ;发送部分
     ;包括发送状态判断
     ;读键盘输入
     ;有输入则发送
     send:
        ; 检测线路寄存器是否有错误
        mov     dx,3fdh
        in      al,dx
        test    al,1EH
        jnz     error

        ; OE检测是否可以发送数据
        test    al,20h
        jz      receive 

        ; 发送键盘数据
        ; show the `send` string and get the character fromt he keyboard

	    mov	    dl,0ffh
	    mov	    ah,06h
	    int 	21h
	    jz	    receive
            
	    mov     dx,3f8h
        out     dx,al
     ;2==========================================

     ; 输入 * 退出
     cmp    al,'*'
     jz     stop

     ; 输出到屏幕
     call   back
     mov    dx,offset p4
     mov    ah,9
     int    21h

     mov    bx,7
     mov    ah,14
     int    10h

    ;下面是自己写的内容3=======================
    ;接收部分
    ;包括接收状态判断
    ;出错状态判断

    receive:
        mov     dx,3fdh
        in      al,dx
        test    al,01h
        jz      send

        test    al,04h
        jnz     error
        
        ; 接收数据
        mov     dx,3f8h
        in      al,dx
    ;3=======================================

    ; 接收到 * 号退出
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
