; 文件读写比较
; Author : GMFTBY
; Time   : 2017.12.6

DATA SEGMENT
PATHNM1     DB  'C:/TEST1.TXT'
BUFFER1     DB  100 DUP (0)
BAK1        DB  100 DUP (0)

PATHNM2     DB  'C:/TEST2.TXT'
BUFFER2     DB  100 DUP (0)
BAK2        DB  100 DUP (0)

MESSAGE_NO  DB  'NO MATCH ','$'
MESSAGE_YES DB  'MATCH','$'

LINENUMBER  DB  ?
DATA ENDS

CODE SEGMENT
MAIN    PROC    FAR
    ASSUME  CS:CODE,DS:DATA,ES:NOTHING
    PUSH    DS
    XOR     AX,AX
    PUSH    AX
    MOV     AX,DATA
    MOV     DS,AX

    ; 打开文件1TEST.TXT
    LEA     DX,PATHNM1
    CALL    OPEN_FILE

    ; 读取文件内容，存入BUFFER1
    LEA     DX,BUFFER1
    CALL    READ_FILE

    CALL    COPY_STRING1
    ; CALL    CLOSE_FILE

    LEA     SI,BAK1
    CALL    PRINT_STRING
    CALL    CLOSE_FILE

    LEA     DX,PATHNM2
    CALL    OPEN_FILE

    LEA     DX,BUFFER2
    CALL    READ_FILE

    CALL    COPY_STRING2
    CALL    CLOSE_FILE

    LEA     SI,BAK2
    CALL    PRINT_STRING

    ; 文件内容比对
    CALL    LOOK
    RET
MAIN   ENDP

LOOK    PROC
    MOV     LINENUMBER,1
    MOV     BX,0
    LOOP_LOOK:
            MOV     AL,[BAK1+BX]
            MOV     AH,[BAK2+BX]
            CMP     AL,AH
            JNE     END_OF_NO
            INC     BX
            CMP     AL,0AH
            JE      ADD_LINE
            FOR_NEXT:
                    CMP     BX,100
                    JNE     LOOP_LOOK
    JMP     END_OF_YES
    END_OF_NO:
            MOV     AH,9
            LEA     DX,MESSAGE_NO
            INT     21H
            MOV     AL,LINENUMBER
            XOR     AH,AH
            CALL    PRINTAX
            RET
    ADD_LINE:
            INC     LINENUMBER
            JMP     FOR_NEXT
    END_OF_YES:
            MOV     AH,9
            LEA     DX,MESSAGE_YES
            INT     21H
            RET
LOOK    ENDP

; 拷贝字符串1
COPY_STRING1    PROC
    PUSH    BX
    PUSH    AX
    PUSH    CX      ; CX必须保护好
    MOV     BX,0
    LOOP_COPY:
            MOV     AL,[BUFFER1+BX]
            MOV     [BAK1+BX],AL
            INC     BX
            CMP     BX,100
            JNE     LOOP_COPY
    POP     CX
    POP     AX
    POP     BX
    RET
COPY_STRING1    ENDP


COPY_STRING2    PROC
    PUSH    BX
    PUSH    AX
    PUSH    CX
    MOV     BX,0
    LOOP_COPY2:
            MOV     AL,[BUFFER2+BX]
            MOV     [BAK2+BX],AL
            INC     BX
            CMP     BX,100
            JNE     LOOP_COPY2
    POP     CX
    POP     AX
    POP     BX
    RET
COPY_STRING2    ENDP

; 打开文件
OPEN_FILE   PROC
    MOV     AH,3DH
    MOV     AL,2
    INT     21H
    RET
OPEN_FILE   ENDP

; 读取文件
READ_FILE   PROC
    MOV     BX,AX
    MOV     CX,100
    MOV     AH,3FH
    INT     21H
    RET
READ_FILE   ENDP

; 关闭文件
CLOSE_FILE  PROC
    MOV     AH,3EH
    INT     21H
    RET
CLOSE_FILE  ENDP

; 输出字符串检验
PRINT_STRING    PROC
    PUSH    CX
    PUSH    AX
    PUSH    BX
    PUSH    DX
    MOV     CX,100
    MOV     BX,0
    NEXT:
            MOV     DL,[SI+BX]
            MOV     AH,2
            INT     21H
            INC     BX
            CMP     BX,CX
            JNE     NEXT
    POP     DX
    POP     BX
    POP     AX
    POP     CX
    RET
PRINT_STRING    ENDP

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

CODE ENDS
        END MAIN
