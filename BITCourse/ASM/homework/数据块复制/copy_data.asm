; 数据块复制(内存->内存)
; Author : GMFTBY
; Time   : 2017.12.6

DATA    SEGMENT
BUFFER1     DB  100
            DB  ?
            DB  100 DUP(?)

BUFFER2     DB  100
            DB  ?
            DB  100 DUP(?)
CRLF        DB  0DH,0AH,'$'
DATA    ENDS

CODE    SEGMENT
MAIN    PROC    FAR
        ASSUME  CS:CODE,DS:DATA,ES:NOTHING
        PUSH    DS
        XOR     AX,AX
        PUSH    AX
        MOV     AX,DATA
        MOV     DS,AX

        ; 输入数据段
        LEA     DX,BUFFER1
        CALL    INPUT_BUFFER

        ; 数据块赋值
        CALL    COPY
        
        ; 输出换行
        MOV     AH,9
        LEA     DX,CRLF
        INT     21H

        ; 数据块输出
        CALL    OUTPUT_STRING
        RET
MAIN    ENDP

; 输入数据段
INPUT_BUFFER    PROC
        MOV     AH,0AH
        INT     21H
        RET
INPUT_BUFFER    ENDP

; 数据块赋值
COPY    PROC
        MOV     AL,[BUFFER1+1]
        MOV     [BUFFER2+1],AL
        MOV     CL,AL
        XOR     CH,CH
        MOV     BX,0
        LOOP_COPY:
                MOV     AL,[BUFFER1+2+BX]
                MOV     [BUFFER2+2+BX],AL
                INC     BX
                CMP     BX,CX
                JNE     LOOP_COPY
        RET
COPY    ENDP    

; 数据块输出
OUTPUT_STRING   PROC
        MOV     CL,[BUFFER2+1]
        XOR     CH,CH
        MOV     BX,0
        LOOP_OUT:
                MOV     AH,2
                MOV     DL,[BUFFER2+2+BX]
                INT     21H
                INC     BX
                CMP     BX,CX
                JNE     LOOP_OUT
        RET
OUTPUT_STRING   ENDP

CODE    ENDS
        END     MAIN
