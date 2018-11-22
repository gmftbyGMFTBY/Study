; Author : GMFTBY
; Time   : 2017.11.26

; Defination for the data segment
DATA SEGMENT
; IDDA    DB      10          ; Student ID (GMFTBY)
;         DB      ?           ; The count for the input character
;         DB      10 DUP(?)   ; The buffer for the array
IDDA    DB      30 DUP(?)
DATA ENDS

; Defination for the code segment
CODE SEGMENT
MAIN    PROC    FAR
        ASSUME  CS:CODE,DS:DATA,ES:NOTHING
        ; The content for the homework
        ; Get the input string from the termial

        ; The next 3 lines is for the RET to exit the SEGMENT Successfully
        PUSH    DS
        XOR     AX,AX
        PUSH    AX

        ; The next 2 lines load the DATA into DS
        MOV     AX,DATA
        MOV     DS,AX
        ; Input the ID
        ; MOV     AH,0AH
        ; LEA     DX,IDDA     ; Save the ID into the IDDA
        ; INT     21H
        MOV     CX,12        ; Input 12 character
        MOV     BX,0        ; Count
LOOP_INPUT:
        MOV     AH,1
        INT     21H
        MOV     [IDDA+BX],AL
        INC     BX
        LOOP    LOOP_INPUT
       
        ; Output the Back and Enter
        MOV     AH,0EH
        MOV     AL,0DH
        INT     10H
        MOV     AH,0EH
        MOV     AL,0AH
        INT     10H

        ; Output the ID
        MOV     CX,12
        MOV     BX,0
LOOP_OUTPUT:
        MOV     AH,2
        MOV     DL,[IDDA+BX]
        INT     21H
        INC     BX
        LOOP    LOOP_OUTPUT

        ; Changee the IDDA
        MOV     AL,[IDDA+11]     ; Get the LAST number 
        MOV     AH,[IDDA+10]
        MOV     CX,11
        ; Right Remove
LOOP_CHANGE:
        MOV     SI,CX
        MOV     DH,IDDA[SI-1]
        MOV     IDDA[SI],DH
        LOOP    LOOP_CHANGE
        MOV     CX,11
LOOP_CHANGE2:
        MOV     SI,CX
        MOV     DH,IDDA[SI-1]
        MOV     IDDA[SI],DH
        LOOP    LOOP_CHANGE2
        MOV     IDDA,AH         ; The last number place at the [IDDA]
        MOV     [IDDA+1],AL
       
        ; Output the Back and Enter
        MOV     AH,0EH
        MOV     AL,0DH
        INT     10H
        MOV     AH,0EH
        MOV     AL,0AH
        INT     10H

        ; Output the ID
        MOV     CX,12
        MOV     BX,0
LOOP_OUTPUT2:
        MOV     AH,2
        MOV     DL,[IDDA+BX]
        INT     21H
        INC     BX
        LOOP    LOOP_OUTPUT2

        RET
MAIN    ENDP
CODE    ENDS
        END     MAIN

; Under coding is a sub processure for print the number in the ax
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

CODE ENDS
        END MAIN
