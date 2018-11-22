; C库函数的实现 : strcmp
; Author : GMFTBY
; Time   : 2017.12.2

; 数据段定义
DATA    SEGMENT
BUFFER1 DB      205
        DB      ?
        DB      205 DUP(0)
BUFFER2 DB      205
        DB      ?
        DB      205 DUP(0)
MESSAGE_NO      DB      'NOT MATCH','$'
MESSAGE_YES     DB      'MATCH','$'
CRLF    DB      0DH,0AH,'$'
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
        ; 输入字符串
        LEA     DX,BUFFER1
        CALL    MY_SCANF
        LEA     DX,BUFFER2
        CALL    MY_SCANF
        CALL    MY_STRCPY
        RET
MAIN    ENDP

; 输入函数
MY_SCANF        PROC
        MOV     AH,0AH
        INT     21H
        ; 输出换行和回车
        MOV     AH,9
        LEA     DX,CRLF
        INT     21H
        RET
MY_SCANF        ENDP

; 实现的C库函数 : strcmp
MY_STRCPY       PROC
        MOV     AL,[BUFFER1+1]
        MOV     AH,[BUFFER2+1]
        CMP     AL,AH
        JNE     END_OF_CALL
        MOV     DL,[BUFFER1+1]
        XOR     DH,DH
        MOV     BX,0
        LOOP_FOR:
                MOV     AL,[BUFFER1+2+BX]
                MOV     AH,[BUFFER2+2+BX]
                CMP     AL,AH
                JNE     END_OF_CALL
                INC     BX
                CMP     BX,DX
                JNE     LOOP_FOR
        JMP     END_OF_YES
END_OF_CALL:
        MOV     AH,9
        LEA     DX,MESSAGE_NO
        INT     21H
        RET
END_OF_YES:
        MOV     AH,9
        LEA     DX,MESSAGE_YES
        INT     21H
        RET
MY_STRCPY       ENDP

PRINTAX     PROC
        MOV     BX,100
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
