;功能:演示保护方式下的中断处理过程
.386P
;----------------------------------------------------------------------------
;存储段描述符结构类型定义
;----------------------------------------------------------------------------
Desc            STRUC
LimitL          DW      0 ;段界限(BIT0-15)
BaseL           DW      0 ;段基地址(BIT0-15)
BaseM           DB      0 ;段基地址(BIT16-23)
Attributes      DB      0 ;段属性
LimitH          DB      0 ;段界限(BIT16-19)(含段属性的高4位)
BaseH           DB      0 ;段基地址(BIT24-31)
Desc            ENDS
;----------------------------------------------------------------------------
;伪描述符结构类型定义(用于装入全局或中断描述符表寄存器)
;----------------------------------------------------------------------------
PDesc           STRUC
Limit           DW      0 ;16位界限
Base            DD      0 ;32位基地址
PDesc           ENDS
;----------------------------------------------------------------------------
;门描述符结构类型定义
;----------------------------------------------------------------------------
Gate            STRUC
OffsetL         DW      0 ;32位偏移的低16位
Selector        DW      0 ;选择子
DCount          DB      0 ;双字计数
GType           DB      0 ;类型
OffsetH         DW      0 ;32位偏移的高16位
Gate            ENDS
;----------------------------------------------------------------------------
;存储段描述符类型值说明
;----------------------------------------------------------------------------
ATDR            EQU     90h ;存在的只读数据段类型值
ATDW            EQU     92h ;存在的可读写数据段属性值
ATDWA           EQU     93h ;存在的已访问可读写数据段类型值
ATCE            EQU     98h ;存在的只执行代码段属性值
ATCER           EQU     9ah ;存在的可执行可读代码段属性值
ATCCO           EQU     9ch ;存在的只执行一致代码段属性值
ATCCOR          EQU     9eh ;存在的可执行可读一致代码段属性值
DA_386IGate	    EQU	    8Eh ;386 中断门类型值
;----------------------------------------------------------------------------
DSEG            SEGMENT USE16                 ;16位数据段
;----------------------------------------------------------------------------
_SavedIMREG_M   db      0       ; 中断屏蔽寄存器值
_SavedIMREG_S   db      0       ; 
                DB      512 dup (0)
TopOfStack      LABEL   BYTE

GDT             LABEL   BYTE                  ;全局描述符表
DUMMY           Desc    <>                    ;空描述符
Code            Desc    <0ffffh,,,ATCER,,>    ;代码段描述符
DataV           Desc    <0ffffh,,,ATDW,,>     ;源数据段描述符
DataP           Desc    <0ffffh,,,ATDWA,,>    ;目标数据段描述符
Code32          Desc    <0ffffh,,,ATCER,40h,> ;代码段描述符
;----------------------------------------------------------------------------
GDTLen          =       $-GDT                 ;全局描述符表长度
VGDTR           PDesc   <GDTLen-1,>           ;伪描述符
;----------------------------------------------------------------------------
Code_Sel        =       Code-GDT              ;代码段选择子
DataV_Sel       =       DataV-GDT             ;源数据段选择子
DataP_Sel       =       DataP-GDT             ;目标数据段选择子
Code32_Sel      =       Code32-GDT            ;目标数据段选择子
;----------------------------------------------------------------------------
; IDT
ALIGN 32
IDT		LABEL		BYTE
IDT_00_1F       Gate    32 dup (<offset SpuriousHandler, Code32_Sel, 0, DA_386IGate, 0>)
IDT_20          Gate    1  dup (<offset ClockHandler, Code32_Sel, 0, DA_386IGate, 0>)
IDT_21_7F       Gate    95 dup (<offset SpuriousHandler, Code32_Sel, 0, DA_386IGate, 0>)
IDT_80          Gate    1  dup (<offset UserIntHandler, Code32_Sel, 0, DA_386IGate, 0>)

IDTLen          =       $-IDT                 ;中断描述符表长度
VIDTR           PDesc   <IDTLen-1,>           ;伪描述符

_wSSValueInRealMode     dw      0
_wSPValueInRealMode	dw	0
_SavedIDTR		dd	0	; 用于保存 IDTR
			dd	0
;----------------------------------------------------------------------------
DSEG            ENDS                          ;数据段定义结束
;----------------------------------------------------------------------------
;打开A20地址线
;----------------------------------------------------------------------------
EnableA20       MACRO
                push    ax
                in      al,92h
                or      al,00000010b
                out     92h,al
                pop     ax
                ENDM
;----------------------------------------------------------------------------
;关闭A20地址线
;----------------------------------------------------------------------------
DisableA20      MACRO
                push    ax
                in      al,92h
                and     al,11111101b
                out     92h,al
                pop     ax
                ENDM

;----------------------------------------------------------------------------
;16位偏移的段间直接转移指令的宏定义(在16位代码段中使用)
;----------------------------------------------------------------------------
JUMP16          MACRO   Selector,Offset
                DB      0eah     ;操作码
                DW      Offset   ;16位偏移量
                DW      Selector ;段值或段选择子
                ENDM
;----------------------------------------------------------------------------
CSEG            SEGMENT USE16                 ;16位代码段
                ASSUME  CS:CSEG,DS:DSEG
;----------------------------------------------------------------------------
Start           PROC
                mov     ax,DSEG
                mov     ds,ax
                mov     _wSSValueInRealMode,ss
                mov     _wSPValueInRealMode,sp

                ;准备要加载到GDTR的伪描述符
                mov     bx,16
                mul     bx
                add     ax,OFFSET GDT          ;计算并设置基地址
                adc     dx,0                   ;界限已在定义时设置好
                mov     WORD PTR VGDTR.Base,ax
                mov     WORD PTR VGDTR.Base+2,dx
                ;准备要加载到IDTR的伪描述符

                mov     ax,SEG IDT
                mov     bx,16
                mul     bx
                add     ax,OFFSET IDT          ;计算并设置基地址
                adc     dx,0                   ;界限已在定义时设置好
                mov     WORD PTR VIDTR.Base,ax
                mov     WORD PTR VIDTR.Base+2,dx
                ;设置代码段描述符

                mov     ax,cs
                mul     bx
                mov     WORD PTR Code.BaseL,ax ;代码段开始偏移为0
                mov     BYTE PTR Code.BaseM,dl ;代码段界限已在定义时设置好
                mov     BYTE PTR Code.BaseH,dh

                mov     ax,seg SpuriousHandler
                mul     bx
                mov     WORD PTR Code32.BaseL,ax ;代码段开始偏移为0
                mov     BYTE PTR Code32.BaseM,dl ;代码段界限已在定义时设置好
                mov     BYTE PTR Code32.BaseH,dh

                mov     ax,8000h
                mov     dx,000BH
                mov     WORD PTR DataV.BaseL,ax
                mov     BYTE PTR DataV.BaseM,dl
                mov     BYTE PTR DataV.BaseH,dh
                ;设置目标数据段描述符

                mov     ax,ds
                mul     bx                     ;计算并设置目标数据段基址
                mov     WORD PTR DataP.BaseL,ax
                mov     BYTE PTR DataP.BaseM,dl
                mov     BYTE PTR DataP.BaseH,dh

        	; 保存中断屏蔽寄存器(IMREG)值
        	in	al, 21h
                mov     _SavedIMREG_M, al
        
                in      al, 0A1h
                mov     _SavedIMREG_S, al
        
        	; 保存 IDTR
        	sidt	QWORD PTR _SavedIDTR

                ;加载GDTR
                lgdt    QWORD PTR VGDTR
                cli                            ;关中断
                EnableA20                      ;打开地址线A20

                lidt    QWORD PTR VIDTR
                
                ;切换到保护方式
                mov     eax,cr0
                or      eax,1
                mov     cr0,eax
                ;清指令预取队列,并真正进入保护方式
                JUMP16  Code_Sel,<OFFSET Virtual>
ALIGN 32
Virtual:        ;现在开始在保护方式下运行
                mov     ax,DataV_Sel
                mov     gs,ax                  ;加载源数据段描述符
                mov     ax,DataP_Sel
                mov     ds,ax                  ;加载源数据段描述符
        	mov	ss,ax			; 堆栈段选择子
                mov     sp,offset TopOfStack
                
                call    Init8259A

		mov	ah, 0Ch				; 0000 黑底    1100 红字
		mov	al, '!'
		mov	gs:[((80 * 0 + 72) * 2)], ax	; 屏幕第 0 行, 第 72 列。
		
		;        x:      jmp     x
		int     080h
		
		sti
		mov     ebx,0
WaitLoop:	
		cmp     ebx, 100
		jb      WaitLoop
		
		cli

                call    SetRealmode8259A

                ;切换回实模式
                mov     eax,cr0
                and     al,11111110b
                mov     cr0,eax
                ;清指令预取队列,进入实方式
                JUMP16  <SEG Real>,<OFFSET Real>

; init 8259A 
Init8259A:
    ; ICW operations
	MOV	        AL, 011H    ; ICW1: 00010001
	OUT	        020H, AL	; 主8259, ICW1
	CALL    	io_delay

	OUT     	0A0H, AL	; 从8259, ICW1
	CALL    	io_delay

	MOV 	    AL, 020H	; 00100000
	OUT     	021H, AL	; 主8259, ICW2.
	CALL    	io_delay

	MOV     	AL, 028H	; IRQ8 对应中断向量 00101000
	OUT 	    0A1H, AL	; 从8259, ICW2.
	CALL    	io_delay

	MOV     	AL, 004H	; IR2 对应从8259    00000100
	OUT 	    021H, AL	; 主8259, ICW3.
	CALL    	io_delay

	MOV     	AL, 002H	; 对应主8259的 IR2  00000010
	OUT 	    0A1H, AL	; 从8259, ICW3.
	CALL    	io_delay

	MOV     	AL, 001h    ; 00000001, 普通全嵌套，非自动结束EOI结束,8位CPU
	OUT     	021H, AL	; 主8259, ICW4.
	CALL    	io_delay
    
    OUT         0A1H, AL	; 从8259, ICW4, 普通全嵌套，非自动结束EOI结束，8位CPU
	CALL    	io_delay

    ; OCW operations
	MOV     	AL, 11111110B	; 主片只开启0号中断,只开启定时器中断
	OUT     	021H, AL	; 主8259, OCW1.
	CALL    	io_delay

	MOV     	AL, 11111111B	; 屏蔽从8259所有中断
	OUT     	0A1H, AL    	; 从8259, OCW1.
	CALL    	io_delay

	RET


; SetRealmode 8259A 
SetRealmode8259A:
    ; ICW operations
	MOV 	    AL, 011H    ; 00010001
	OUT     	020H, AL	; 主8259, ICW1.
	CALL    	io_delay

	OUT 	    0A0H, AL	; 从8259, ICW1.
	CALL    	io_delay

    MOV         AL,  08H    ; IRQ0 对应中断向量 0x20, 00001000
	OUT     	021H, AL	; 主8259, ICW2.
	CALL    	io_delay

    MOV         AL,  70H    ; IRQ8 对应中断向量 0x28, 01110000
	OUT 	    0A1H, AL	; 从8259, ICW2.
	CALL    	io_delay

	MOV     	AL, 004H	; IR2 对应从8259, 00000100, 2 号
	OUT     	021H, AL	; 主8259, ICW3
	CALL    	io_delay

	MOV     	AL, 002H	; 对应主8259的 IR2, 00000010, 2
	OUT 	    0A1H, AL	; 从8259, ICW3.
	CALL    	io_delay

	MOV     	AL, 001H    ; 00000001, 主片普通全嵌套，非自动结束,16-32位CPU，进入保护模式
	OUT     	021H, AL	; 主8259, ICW4.
	CALL    	io_delay

	OUT     	0A1H, AL	; 从8259, ICW4.,从片相同设置
	CALL    	io_delay

    ; OCW operations
	MOV     	AL, 11111111B	; 屏蔽从8259所有中断
	OUT     	0A1H, AL	; 从8259, OCW1.
	CALL    	io_delay

    MOV         AL, _SavedIMREG_M       ; 恢复中断屏蔽寄存器(IMREG)的原值
	OUT     	021H, AL		        ;    
	CALL    	io_delay

	RET

; just nop without any operations
io_delay:
	NOP
	NOP
	NOP
    NOP
	RET
    

; 8259 back to the real mode
Real:
    ; close the position of the A20
    DisableA20
    lidt    QWORD PTR _SavedIDTR

    mov     ax,DSEG
    mov     ds,ax
    mov     ss,_wSSValueInRealMode
    mov     sp,_wSPValueInRealMode

    sti

    mov     ax,4c00h
    int     21h

Start           ENDP
;----------------------------------------------------------------------------
CSEG            ENDS                           ;代码段定义结束
;----------------------------------------------------------------------------
CSEG32          SEGMENT USE32
; interrupt handler ---------------------------------------------------------------
                ASSUME CS:CSEG32,DS:DSEG
ClockHandler:
        inc     ebx
	inc	byte ptr gs:[((80 * 0 + 70) * 2)] ; 屏幕第 0 行, 第 70 列。
	mov	al, 20h
	out	20h, al				; 发送 EOI
	iretd


UserIntHandler:
	mov	ah, 0Ch				; 0000 黑底    1100 红字
	mov	al, 'I'
	mov	gs:[((80 * 0 + 71) * 2)], ax	; 屏幕第 0 行, 第 71 列。
	iretd


SpuriousHandler:
	mov	ah, 0Ch				; 0000 黑底    1100 红字
	mov	al, '!'
	mov	gs:[((80 * 0 + 72) * 2)], ax	; 屏幕第 0 行, 第 72 列。
	iretd
; ---------------------------------------------------------------------------
CSEG32          ENDS
                END     Start
