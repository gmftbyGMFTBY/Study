; 第三章测试代码

DATA    SEGMENT
VAR     DW      100,200,300,400
TESTP   DW      ?
DATA    ENDS

CODE    SEGMENT
MAIN    PROC    FAR
        ASSUME  CS:CODE,DS:DATA,ES:NOTHING
        PUSH    DS
        XOR     AX,AX
        PUSH    AX
        MOV     AX,DATA
        MOV     DS,AX
        ; 立即数寻址9,寄存器寻址方式BL
        ; MOV     BL,9
        ; MOV     AL,BL
        ; XOR     AH,AH

        ; 直接寻址方式
        ; MOV     AX,WORD PTR [100H]
        ; MOV     AX,VAR

        ; 寄存器间接寻址
        ; MOV     BP,100
        ; MOV     AX,[BP]

        ; 寄存器相对寻址方式,VAR    100,200,300,400
        ; MOV     BX,2
        ; MOV     AX,8[BX]
        ; CALL    PRINTAX
        ; MOV     AX,[BX+8]
        ; MOV     AX,[BX+VAR]

        ; 基址变址寻址方式
        ; LEA     BX,VAR
        ; MOV     SI,6
        ; MOV     AX,[BX][SI]     ; MOV   AL,[BX+SI]

        ; 相对基址变址寻址方式
        ; MOV     BX,0
        ; MOV     SI,2
        ; MOV     AX,VAR[BX+SI]     ; MOV   AX,ARY[0,1] -> 200

        ; 段内直接寻址转移
        ; MOV     AX,100
        ; JMP     NEAR    PTR   FOR_1
        ; CALL    PRINTAX
        ; FOR_1:
        ;     MOV     AX,1
        ; CALL    PRINTAX

        ; 段内间接寻址
        ; MOV     BX,0
        ; JMP     WORD    PTR     [BX]

        ; MOV
        ; MOV     AX,SEG VAR
        ; CALL    PRINTAX
        ; MOV     AX,OFFSET VAR
        ; CALL    PRINTAX

        ; PUSH & POP
        MOV     AX,1
        PUSH    AX
        POP     TESTP
        MOV     AX,TESTP
        CALL    PRINTAX
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
PRINTAX     ENDP

CODE    ENDS
        END     MAIN

