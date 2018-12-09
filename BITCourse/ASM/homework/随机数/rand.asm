; 使用线性迭代的思路实现随机数的生成,随机数范围 [0, 29],种子[0, 10)
; X_{n+1} = (a * X_n + b) mod c
; a, b, c 均为质数，c的目的是为了将结果更好的散射
; a = 17, b = 23, c = 97

; Author : GMFTBY
; Time   : 2017.12.1

; 数据段定义
DATA    SEGMENT
DATA    ENDS

; 代码段定义
CODE    SEGMENT
MAIN    PROC    FAR
    ASSUME  CS:CODE,DS:DATA,ES:NOTHING
    PUSH    DS
    XOR     AX,AX
    PUSH    AX
    MOV     AX,DATA
    MOV     DS,AX

    ; 输入的种子在AL中
    MOV     AH,0
    INT     16H
    SUB     AL,48   ; 转换得到数字
    XOR     AH,AH

    MOV     CX,1000
    LOOP_FOR:
            MOV     BL,17
            MUL     BL      ; AL * 17
            XOR     AH,AH
            ADD     AL,23
            XOR     AH,AH
            MOV     BL,29
            DIV     BL
            MOV     AL,AH
            LOOP    LOOP_FOR
    XOR     AH,AH
    CALL    PRINTAX
    RET    
MAIN    ENDP

; 输出AX的数值
PRINTAX     PROC
        MOV     BX,10
        OR      AX,AX    ; ax won't be changed , but if the ax's content is 0, jump to _0_
        JZ      _0_
LOOP_P:
        XOR     DX,DX
        DIV     BX
        MOV     CX,AX
        OR      CX,DX
        JZ      _E_
        PUSH    DX      ; push the remaining number nto the stack
        CALL    LOOP_P
        POP     DX
        ADD     DL,'0'  ; change the ASCII into the number
        JMP     _1_
_0_:
        MOV     DL,'0'
_1_:   
        MOV     AH,2    ; print one character to the terminal
        INT     21H
_E_:
        RET
PRINTAX     ENDP

CODE    ENDS
        END     MAIN

