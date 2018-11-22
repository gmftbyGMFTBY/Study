; 编写多重循环(2)

; Author : GMFTBY
; Time   : 2017.12.1

; 数据段
DATA    SEGMENT
DATA    ENDS

; 代码段
CODE    SEGMENT
MAIN    PROC    FAR 
        ASSUME  CS:CODE,DS:DATA,ES:NOTHING
        PUSH    DS
        XOR     AX,AX
        PUSH    AX
        MOV     AX,DATA
        MOV     DS,AX

        ; 5多重循环
        MOV     AX,0
        LOOP_OUT:
                ADD     AX,1
                MOV     BX,0
                LOOP_IN:
                        ADD     BX,1
                        CMP     BX,10
                        JNE     LOOP_IN
                CMP     AX,10
                JNE     LOOP_OUT
RET
MAIN    ENDP

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
