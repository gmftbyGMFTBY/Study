; 课本习题6.4
; 老师，我是那个使用dosbox的同学，386环境的扩展寄存器我无法使用，我这里的ESP使用SP代替
; 对掌握知识没有影响
; 老师寄存器间接寻址，16位下无法使用ESP制定，只能使用BP

; Author : GMFTBY
; Time   : 2017.11.29

; 数据段定义
DATA    SEGMENT
DATA    ENDS

; 代码段定义
CODE    SEGMENT
MAIN    PROC    FAR
        ASSUME  CS:CODE,DS:DATA,ES:NOTHING
        ; 诸多必要的定义
        PUSH    DS
        XOR     AX,AX
        PUSH    AX
        MOV     AX,DATA
        MOV     DS,AX
        ; 调用子程序1
        MOV     AX,10
        PUSH    AX
        MOV     AX,20
        PUSH    AX
        CALL    SUBPROC1
        ADD     SP,4
        ; 子程序1输出结果,结果在AX中
        CALL    PRINTAX
        MOV     AH,0EH
        MOV     AL,0DH
        INT     10H
        MOV     AH,0EH
        MOV     AL,0AH
        INT     10H
        ; 调用子程序2
        MOV     AX,100
        PUSH    AX
        MOV     AX,200
        PUSH    AX
        CALL    SUBPROC2
        ; 子程序2输出结果，结果在AX中
        CALL    PRINTAX
        RET
MAIN    ENDP

; 子程序1,不跳过堆栈
; ??? 删掉FAR PTR就可以成功，莫名其妙 ???,存在FAR PTR会出现计算出错的情况
SUBPROC1    PROC
        PUSH    BP
        MOV     BP,SP
        MOV     AX,[BP+4]
        SUB     AX,[BP+6]
        POP     BP
        RET
SUBPROC1    ENDP

; 子程序2,跳过堆栈
SUBPROC2    PROC
        PUSH    BP
        MOV     BP,SP
        MOV     AX,[BP+4]
        SUB     AX,[BP+6]
        POP     BP
        RET     4
SUBPROC2    ENDP

PRINTAX     PROC
        MOV     BX,10
        OR      AX,AX
        JZ      _0_
LOOP_P:
        XOR     DX,DX
        DIV     BX
        MOV     CX,AX
        OR      CX,DX
        JZ      _E_
        PUSH    DX
        CALL    LOOP_P
        POP     DX
        ADD     DL,'0'
        JMP     _1_
_0_:
        MOV     DL,'0'
_1_:
        MOV     AH,2
        INT     21H
_E_:
        RET
PRINTAX  ENDP

CODE    ENDS
        END     MAIN

