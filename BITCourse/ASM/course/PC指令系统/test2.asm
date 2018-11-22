DATA    SEGMENT
ARY     DB      '0123456789ABCDEF'
DATA    ENDS

CODE    SEGMENT
MAIN    PROC    FAR
        ASSUME  CS:CODE,DS:CODE,ES:NOTHING
        PUSH    DS
        XOR     AX,AX
        PUSH    AX
        MOV     AX,DATA
        MOV     DS,AX

        ; XLAT
        ; MOV     BX,OFFSET   ARY
        ; MOV     AL,9
        ; XLAT
        ; XOR     AH,AH
        ; CALL    PRINTAX

        ; 基本移位指令
        MOV     AL,2
        MOV     CL,2
        SHL     AL,CL
        XOR     AH,AH
        CALL    PRINTAX

        RET
MAIN    ENDP

PRINTAX PROC
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
PRINTAX ENDP

CODE    ENDS
        END     MAIN
