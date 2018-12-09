.386
.model flat, stdcall
option casemap :none

include kernel32.inc
include fpu.inc

includelib msvcrt.lib
includelib kernel32.lib
includelib fpu.lib

scanf	PROTO C :ptr sbyte, :vararg
printf	PROTO C :ptr sbyte, :vararg

.data

inputString	byte	"请输入算式：", 0
string		byte    50 dup(?)   ; 原始输入字符串
num1		tbyte   ?           ; 第一个操作数
num2		tbyte   ?           ; 第二个操作数
result		byte    50 dup(0)   ; 存放结果

inFmt   byte    "%s", 0
outFmt  byte    "%s", 0ah, 0

.code

start:
	invoke	printf, offset inputString
    invoke	scanf, offset inFmt, offset string

    mov esi, offset string  ; 寻找操作符的位置
    inc esi
l1:
    mov al, [esi]
    cmp al, '+'
    je  l2
    cmp al, '-'
    je  l2
    cmp al, '*'
    je  l2
    cmp al, '/'
    je  l2
    inc esi
    jmp l1
l2:
    mov bl, [esi]       ; 将运算符存在bl中
    xor al, al
    mov [esi], al
    inc esi
    
    invoke FpuAtoFL, offset string, offset num1, DEST_MEM
    invoke FpuAtoFL, esi, offset num2, DEST_MEM

    cmp bl, '+'             ; 判断bl中的运算符
    je  Addition
    cmp bl, '-'
    je Subtraction
    cmp bl, '*'
    je Multiplication
    cmp bl, '/'
    je Division

Addition:
    invoke FpuAdd, offset num1, offset num2, 0, SRC1_REAL or SRC2_REAL or DEST_FPU
    jmp output
Subtraction:
    invoke FpuSub, offset num1, offset num2, 0, SRC1_REAL or SRC2_REAL or DEST_FPU
    jmp output
Multiplication:
    invoke FpuMul, offset num1, offset num2, 0, SRC1_REAL or SRC2_REAL or DEST_FPU
    jmp output
Division:
    invoke FpuDiv, offset num1, offset num2, 0, SRC1_REAL or SRC2_REAL or DEST_FPU

output:
    invoke FpuFLtoA, 0, 7h, offset result, SRC1_FPU or SRC2_DIMM
    invoke printf, offset outFmt, offset result
    invoke ExitProcess, 0
end start
