CODE    SEGMENT
        ORG     100H
        ASSUME  CS:CODE,DS:CODE
MAIN    PROC    NEAR
        MOV     AX,A
        ADD     AX,B
        MOV     SUM,AX
        A       DW      123
        B       DW      456
        SUM     DW      ?
        RET
MAIN    ENDP
CODE    ENDS
        END     MAIN
