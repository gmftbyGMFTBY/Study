; 大数相乘
; Author : GMFTBY
; Time   : 2017.12.1

; 数据段定义
DATA    SEGMENT
IDDA1   DB      100
        DB      ?
        DB      100 DUP(0)
IDDA2   DB      100
        DB      ?
        DB      100 DUP(0)
RESULT  DB      205
        DB      ?
        DB      205 DUP(0)
MULTIFLAG       DW      ?
ADDFLAG         DW      ?
; IDDA1 / IDDA2 / RESULT 的符号位
IDDA1FLAG       DB      ?
IDDA2FLAG       DB      ?
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

        ; 主逻辑
        CALL    MYIN1
        CALL    MYIN2
        CALL    INIT
        CALL    REVERSE1
        CALL    REVERSE2
        CALL    CALCULATE
        CALL    REVERSE3
        ; CALL    PRINT1
        ; CALL    PRINT2
        CALL    PRINT3

        RET
MAIN    ENDP

; 主逻辑
CALCULATE   PROC
        ; 外层循环使用BX计数调节，内层循环使用BP计数调节
        MOV     BX,0
        LOOP_OUT:
                MOV     MULTIFLAG,0
                MOV     ADDFLAG,0
                MOV     BP,0
                LOOP_IN:
                        MOV     AL,[IDDA1+2+BP]
                        MUL     [IDDA2+2+BX]
                        ADD     AX,MULTIFLAG    ; 计算结果在AX
                        MOV     DL,10
                        DIV     DL
                        PUSH    AX
                        XOR     AH,AH
                        MOV     MULTIFLAG,AX    ; 求取新的乘法进位
                        POP     AX
                        MOV     AL,AH
                        XOR     AH,AH           ; temp1是余数(AX)
                        MOV     SI,BX
                        ADD     SI,BP
                        ADD     AL,[RESULT+2+SI]
                        ADD     AX,ADDFLAG
			            MOV	    DL,10
                        DIV     DL
                        PUSH 	AX
                        XOR     AH,AH
                        MOV     ADDFLAG,AX
                        POP     AX
                        MOV     AL,AH
                        XOR     AH,AH           ; temp2是余数(AX)
                        MOV     SI,BX
                        ADD     SI,BP
                        MOV     [RESULT+2+SI],AL
                        INC     BP
                        MOV     DL,[IDDA1+1]
                        XOR     DH,DH
                        CMP     BP,DX
                        JNE     LOOP_IN
                MOV     AX,MULTIFLAG
                ADD     AX,ADDFLAG
                XOR     AH,AH
                MOV     SI,BX
                ADD     SI,BP
                MOV     [RESULT+2+SI],AL
                INC     BX
                MOV     DL,[IDDA2+1]
                XOR     DH,DH
                CMP     BX,DX
                JNE     LOOP_OUT
        ; 计算新串的长度
        MOV     AL,[IDDA1+1]
        ADD     AL,[IDDA2+1]
        MOV     [RESULT+1],AL
        RET
CALCULATE   ENDP

; 输出回车换行
SPACE   PROC
        MOV     AH,0EH
        MOV     AL,0DH
        INT     10H
        MOV     AH,0EH
        MOV     AL,0AH
        INT     10H
        RET
SPACE   ENDP

; 初始化数据串,ASCII -> 数据,统一减30H
INIT    PROC
        MOV     BX,0
        LOOP_DEC1:
                SUB     [IDDA1+2+BX],30H
                INC     BX
                CMP     BL,[IDDA1+1]
                JNE     LOOP_DEC1
        MOV     BX,0
        LOOP_DEC2:
                SUB     [IDDA2+2+BX],30H
                INC     BX
                CMP     BL,[IDDA2+1]
                JNE     LOOP_DEC2
        ; 清空RESULT
        MOV     BX,0
        LOOP_CLEAR:
                MOV     [RESULT+2+BX],0
                INC     BX
                CMP     BX,204
                JNE     LOOP_CLEAR
        RET
INIT    ENDP

; 输出数据串1
PRINT1  PROC
        PUSH    BX
        MOV     BX,0
        LOOP_PRINT1:
                MOV     AH,2
		        MOV	    DH,[IDDA1+2+BX]
		        ADD	    DH,30H
                MOV     DL,DH
                INT     21H
                INC     BX
                CMP     BL,[IDDA1+1]
                JNE     LOOP_PRINT1
        CALL    SPACE
        POP     BX
        RET
PRINT1  ENDP

; 输出数据串2
PRINT2  PROC
        PUSH    BX
        MOV     BX,0
        LOOP_PRINT2:
                MOV     AH,2
		        MOV	    DH,[IDDA2+2+BX]
		        ADD	    DH,30H
                MOV     DL,DH
                INT     21H
                INC     BX
                CMP     BL,[IDDA2+1]
                JNE     LOOP_PRINT2
        CALL    SPACE
        POP     BX
        RET
PRINT2  ENDP

; 输出结果串
PRINT3  PROC
        ; 输出符号
        MOV     AL,IDDA1FLAG
        MOV     BL,IDDA2FLAG
        XOR     AL,BL
        CMP     AL,0
        JE      NEXT
        MOV     AH,2
        MOV     DL,'-'
        INT     21H
        NEXT:
        ; 结果是0
        CMP     [RESULT+3],0
        JE      EN
        MOV     BX,1
        LOOP_PRINT3:
                MOV     AH,2
		        MOV	    DH,[RESULT+2+BX]
		        ADD	    DH,30H
                CMP     DH,30H
                MOV     DL,DH
                INT     21H
                INC     BX
                CMP     BL,[RESULT+1]
                JNE     LOOP_PRINT3
        CALL    SPACE
        JMP     EE
        EN:
                MOV     AH,2
                MOV     DL,30H
                INT     21H
        EE:
                RET
PRINT3  ENDP

; 翻转子函数1
REVERSE1    PROC
        MOV     CL,[IDDA1+1]
        MOV     CH,CH
        MOV     BX,0
        LOOP_PUSH1:
                MOV     AL,[IDDA1+2+BX]
                XOR     AH,AH
                PUSH    AX
                INC     BX
                LOOP    LOOP_PUSH1
        MOV     CL,[IDDA1+1]
        XOR     CH,CH
        MOV     BX,0
        LOOP_POP1:
                POP     AX
                MOV     [IDDA1+2+BX],AL
                INC     BX
                LOOP    LOOP_POP1
        RET
REVERSE1    ENDP

; 翻转子函数2
REVERSE2    PROC
        MOV     CL,[IDDA2+1]
        XOR     CH,CH
        MOV     BX,0
        LOOP_PUSH2:
                MOV     AL,[IDDA2+2+BX]
                XOR     AH,AH
                PUSH    AX
                INC     BX
                LOOP    LOOP_PUSH2
        MOV     CL,[IDDA2+1]
        XOR     CH,CH
        MOV     BX,0
        LOOP_POP2:
                POP     AX
                MOV     [IDDA2+2+BX],AL
                INC     BX
                LOOP    LOOP_POP2
        RET
REVERSE2    ENDP

; 翻转子函数3
REVERSE3    PROC
        MOV     CL,[RESULT+1]
        XOR     CH,CH
        MOV     BX,0
        LOOP_PUSH3:
                MOV     AL,[RESULT+2+BX]
                XOR     AH,AH
                PUSH    AX
                INC     BX
                LOOP    LOOP_PUSH3
        MOV     CL,[RESULT+1]
        XOR     CH,CH
        MOV     BX,0
        LOOP_POP3:
                POP     AX
                MOV     [RESULT+2+BX],AL
                INC     BX
                LOOP    LOOP_POP3
        RET
REVERSE3    ENDP

; 前移消去IDDA1符号位
FORWARD1     PROC
        MOV     AL,[IDDA1+2]
        CMP     AL,45
        JNE     ENFORWARD1
        ; 前移消去符号位
        MOV     IDDA1FLAG,45
        MOV     BX,1
        LOOP_FORWARD1:
                MOV     AL,[IDDA1+2+BX]
                MOV     [IDDA1+1+BX],AL
                INC     BX
                CMP     BL,[IDDA1+1]
                JNE     LOOP_FORWARD1
        SUB     [IDDA1+1],1
        ENFORWARD1:
        RET
FORWARD1     ENDP

; 前移消去IDDA2符号位
FORWARD2    PROC
        MOV     AL,[IDDA2+2]
        CMP     AL,45
        JNE     ENFORWARD2
        MOV     IDDA2FLAG,45
        MOV     BX,1
        LOOP_FORWARD2:
                MOV     AL,[IDDA2+2+BX]
                MOV     [IDDA2+1+BX],AL
                INC     BX
                CMP     BL,[IDDA2+1]
                JNE     LOOP_FORWARD2
        SUB     [IDDA2+1],1
        ENFORWARD2:
        RET
FORWARD2    ENDP

; 输入数据串1
MYIN1   PROC
        MOV     AH,0AH
        LEA     DX,IDDA1
        INT     21H
        CALL    SPACE
        CALL    FORWARD1
        RET
MYIN1   ENDP

; 输入数据串2
MYIN2   PROC
        MOV     AH,0AH
        LEA     DX,IDDA2
        INT     21H
        CALL    SPACE
        CALL    FORWARD2
        RET
MYIN2   ENDP

; 测试REVERSE3, PRINT3, 以及必要的检验
TESTRESULT  PROC
        ; 先保证之前调用过INIT,清空了RESULT
        MOV     [RESULT+1],20
        CALL    PRINT3
        CALL    REVERSE3
        CALL    PRINT3
        RET
TESTRESULT  ENDP

CODE    ENDS
        END     MAIN
