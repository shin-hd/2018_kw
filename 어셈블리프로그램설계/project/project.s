	AREA project, CODE, READONLY
		ENTRY
Main					;r10 = Matrix_data, r11 = n = 3, r12 = k, sp = memory address
	LDR r10, =Matrix_data
	LDR sp, Result_data
	
	LDMIA r10!, {r11-r12}	;get n, k
	
	;initMatrix
	MOV r6, #1
	LSL r6, r12			;r6 = 1*2^k
	MOV r5, r6, LSL #2	;r5 = 4*2^k
GetRowSize
	LDR r0, [r10], #4
	STR r0, [sp], r5
	ADD r3, #1;
	CMP r3, r11		;r3 == n ?
	BNE GetRowSize	;loop, if false
	
	ADD r4, #1		;col++
	LDR r1, Result_data
	SUB r1, sp, r1	;size of row
	LDR r2, temp
	STR r1, [r2]	;store one row's size
	
	MOV r3, sp		;copy sp
	SUB sp, sp, r5
	ADD sp, sp, #4
initPadding
	STR r0, [sp], #4
	CMP r3, sp		;sp is next row
	BNE initPadding
	
initLoop
	MOV r7, #1
	MOV r3, #0		;row = 0
initColLoop
	ADD sp, sp, r1
	ADD r7, #1
	CMP r7, r6		;2^k == r7 ?
	BNE initColLoop
initRowLoop
	LDR r0, [r10], #4
	STR r0, [sp], r5
	ADD r3, #1
	CMP r3, r11		;r3 == n ?
	BNE initRowLoop	;loop, if false
	;row padding
	MOV r3, sp		;copy sp
	SUB sp, sp, r5
	ADD sp, sp, #4
rowPadding
	STR r0, [sp], #4
	CMP r3, sp		;sp is next row
	BNE rowPadding
	;end
	ADD r4, #1		;col++
	CMP r4, r11		;r4 == n ?
	BNE initLoop	;loop, if false
	;continue, if end

setCalcBlock	;r11 = n, r12 = k
	LDR sp, Result_data
	LDR r9, temp
	LDR r10, [r9]	;r10 = rowSize
	MOV r9, #1		;r9 = row
	LDR r7, =Matrix_data
	LDR r6, [r7, #4]
	SUB r6, r6, r12
	MOV r8, #1
	LSL r8, r6		;r8 = (2^0~2)
	MOV r7, #4
	LSL r7, r7, r12	;r7 = 4 * 2^k
	
	;firstCalc
	ADD r9, #1		;row++
	B calcFirstPointBlock
returnFPB
	CMP r9, r11		;n == 2 ?
	BEQ firstPaddingStart	;do only calcFirstPointBlock, if n == 2
loopCalcFirstRow
	B calcFirstRowBlock
returnFRB
	ADD r9, #1		;row++
	CMP r9, r11		;row == n
	BNE calcFirstRowBlock	;loop, if false
firstPaddingStart
	MOV r3, #1		;0 ~ 2^k-1
	SUB r2, r12, #1	;k-1
	MOV r2, r10, LSL r2
	MOV r4, #1
	LSL r4, r12		;2^k
	LDR r0, [sp, r2]
	ADD sp, sp, #4
blockFirstPadding
	STR r0, [sp, r2]
	ADD sp, sp, #4
	ADD r3, #1
	CMP r3, r4		;sp is next row
	BNE blockFirstPadding
	;padding end
	MOV r6, r10
	LSL r6, r12
	SUB r6, r6, r10	;r6 = rowSize*(2^k-1)
	ADD sp, sp, r6	;get next row
	ADD r8, r8, #1	;col++
	CMP r8, r11		;n == 2 ?
	MOVNE r9, #1	;row = 0, if false
	BEQ chechSetLoop;check k to loop, if true
	
loopCalcRow
	ADD r9, #1		;row++
	B calcFirstColBlock
returnFCB
	CMP r9, r11		;n == 2 ?
	BEQ blockPaddingStart	;do only calcFirstColBlock, if n == 2
loopCalcBlock
	B calcMainBlock
return
	ADD r9, #1		;row++
	CMP r9, r11		;row == n
	BNE calcMainBlock	;loop, if false
blockPaddingStart
	MOV r3, #1		;0 ~ 2^k-1
	SUB r2, r12, #1	;k-1
	MOV r2, r10, LSL r2
	MOV r4, #1
	LSL r4, r12		;2^k
	LDR r0, [sp, r2]
	ADD sp, sp, #4
blockPadding
	STR r0, [sp, r2]
	ADD sp, sp, #4
	ADD r3, #1
	CMP r3, r4		;sp is next row
	BNE blockPadding
	;padding end
	MOV r6, r10
	LSL r6, r12
	SUB r6, r6, r10	;r6 = rowSize*(2^k-1)
	ADD sp, sp, r6	;get next row
	ADD r8, r8, #1	;col++
	CMP r8, r11		;col == n
	MOVNE r9, #1	;row = 0, if false
	BNE	loopCalcRow	;loop, if false
chechSetLoop	
	SUB r12, r12, #1
	LSL r11, #1
	CMP r12, #0		;k == 0 ?
	BNE setCalcBlock
	
colPaddingStart			;r11 = n * 2^k
	LDR r3, =Matrix_data
	LDR r12, [r3, #4]	;get k
	MOV r4, #1
	LSL r4, r12			;r4 = 2^k
	MOV r5, #0			;0~n*2^k
	ADD sp, r6
	SUB sp, r10		;get prev padding point address
colPadding
	LDR r0, [sp]
	MOV r3, #1
	MOV r2, r10
loopCol
	STR r0, [sp, r2]
	ADD r2, r2, r10	;r2 += r10
	ADD r3, #1		;col++
	CMP r3, r4		;r3 == 2^k ?
	BNE loopCol		;loop, if false
	ADD sp, sp, #4
	ADD r5, r5, #1	;row++
	CMP r5, r11		;r5 == n*2^k ?
	BNE colPadding	;loop, if false
	
	MOV pc, #0		;Program end
	
calcFirstPointBlock	;sp is left/top point address
	LDR r0, [sp]				;a
	MOV r2, r10, LSL r12
	LDR r1, [sp, r2]			;c
	BL calcMedian
	SUB r2, r12, #1	;k-1r
	MOV r2, r10, LSL r2
	STR r0, [sp, r2]	;ac/2
	
	MOV r2, r10, LSL r12
	LDR r0, [sp, r2]! 			;c
	LDR r1, [sp, r7]			;d
	BL calcMedian
	STR r0, [sp, r7, LSR #1]	;cd/2
	
	LDR r1, [sp, r7]!			;d
	SUB sp, sp, r10, LSL r12
	LDR r0, [sp]				;b
	BL calcMedian
	SUB r2, r12, #1	;k-1
	MOV r2, r10, LSL r2
	STR r0, [sp, r2]		;bd/2
	
	LDR r1, [sp, r2]		;bd
	SUB sp, sp, r7
	LDR r0, [sp, r2]		;ac
	BL calcMedian
	SUB r2, r12, #1 ;k-1
	MOV r2, r10, LSL r2
	ADD sp, sp, r7, LSR #1
	STR r0, [sp, r2]	;center
	
	SUB sp, sp, r7, LSR #1
	LDR r0, [sp]				;a
	LDR r1, [sp, r7]			;b
	BL calcMedian
	STR r0, [sp, r7, LSR #1]	;ab/2
	ADD sp, sp, r7				;sp is pointing next a(=b) address
	
	B returnFPB

calcFirstRowBlock	;sp is left/top point address
	MOV r2, r10, LSL r12
	LDR r0, [sp, r2]! 			;c
	LDR r1, [sp, r7]			;d
	BL calcMedian
	STR r0, [sp, r7, LSR #1]	;cd/2
	
	LDR r1, [sp, r7]!			;d
	SUB sp, sp, r10, LSL r12
	LDR r0, [sp]				;b
	BL calcMedian
	SUB r2, r12, #1	;k-1
	MOV r2, r10, LSL r2
	STR r0, [sp, r2]		;bd/2
	
	LDR r1, [sp, r2]		;bd
	SUB sp, sp, r7
	LDR r0, [sp, r2]		;ac
	BL calcMedian
	SUB r2, r12, #1 ;k-1
	MOV r2, r10, LSL r2
	ADD sp, sp, r7, LSR #1
	STR r0, [sp, r2]	;center
	
	SUB sp, sp, r7, LSR #1
	LDR r0, [sp]				;a
	LDR r1, [sp, r7]			;b
	BL calcMedian
	STR r0, [sp, r7, LSR #1]	;ab/2
	ADD sp, sp, r7				;sp is pointing next a(=b) address
	
	B returnFRB

calcFirstColBlock	;sp is left/top point address
	LDR r0, [sp]				;a
	MOV r2, r10, LSL r12
	LDR r1, [sp, r2]			;c
	BL calcMedian
	SUB r2, r12, #1	;k-1r
	MOV r2, r10, LSL r2
	STR r0, [sp, r2]	;ac/2
	
	MOV r2, r10, LSL r12
	LDR r0, [sp, r2]! 			;c
	LDR r1, [sp, r7]			;d
	BL calcMedian
	STR r0, [sp, r7, LSR #1]	;cd/2
	
	LDR r1, [sp, r7]!			;d
	SUB sp, sp, r10, LSL r12
	LDR r0, [sp]				;b
	BL calcMedian
	SUB r2, r12, #1	;k-1
	MOV r2, r10, LSL r2
	STR r0, [sp, r2]		;bd/2
	
	LDR r1, [sp, r2]		;bd
	SUB sp, sp, r7
	LDR r0, [sp, r2]		;ac
	BL calcMedian
	SUB r2, r12, #1 ;k-1
	MOV r2, r10, LSL r2
	ADD sp, sp, r7, LSR #1
	STR r0, [sp, r2]	;center
	
	ADD sp, sp, r7, LSR #1	;sp is pointing next a(=b) address
	B returnFCB

calcMainBlock	;sp is left/top point address
	MOV r2, r10, LSL r12
	LDR r0, [sp, r2]! 			;c
	LDR r1, [sp, r7]			;d
	BL calcMedian
	STR r0, [sp, r7, LSR #1]	;cd/2
	
	LDR r1, [sp, r7]!			;d
	SUB sp, sp, r10, LSL r12
	LDR r0, [sp]				;b
	BL calcMedian
	SUB r2, r12, #1	;k-1
	MOV r2, r10, LSL r2
	STR r0, [sp, r2]		;bd/2
	
	LDR r1, [sp, r2]		;bd
	SUB sp, sp, r7
	LDR r0, [sp, r2]		;ac
	BL calcMedian
	SUB r2, r12, #1 ;k-1
	MOV r2, r10, LSL r2
	ADD sp, sp, r7, LSR #1
	STR r0, [sp, r2]	;center
	
	ADD sp, sp, r7, LSR #1	;sp is pointing next a(=b) address
	B return

calcMedian				;use r0~r6
	MOV r2, r0, LSL #1
	LSR r2, #24
	MOV r3, r1, LSL #1
	LSR r3, #24			;get E using Shift

	MOV r4, r0, LSL #9
	LSR r4, #9
	MOV r5, r1, LSL #9
	LSR r5, #9			;get M using Shift
	
	LSR r0, #31
	LSR r1, #31			;get S using Shift
	
	MOV r6, #1
	ORR r4, r4, r6, LSL #23
	ORR r5, r5, r6, LSL #23 ;set integer number 1
	
	CMP r2, r3			;get exponent difference
	
	SUBGT r6, r2, r3	;r2 - r3, if r2 > r3
	LSRGT r5, r6		;shift
	
	SUBLT r6, r3, r2	;r3 - r2, if r2 < r3
	MOVLT r2, r3		;r2 = r3
	LSRLT r4, r6		;shift

	CMP r0, r1			;add/sub
	BNE Msub			;not equal
	
Madd
	ADD r4, r4, r5	;r4 + r5
	MOV r6, #1;
	ANDS r6, r4, r6, LSL #24	;check carry out
	ADDNE r2, r2, #1	;E++, if carry out is exist
	LSRNE r4, #1		;M >> 1
	B GetFullFloat
	
Msub
	CMP r4, r5
	MOVEQ r0, #0
	MOVEQ pc, lr		;zero result
	SUBGT r4, r4, r5	;r4 - r5
	SUBLT r4, r5, r4	;r5 - r4
	MOVLT r0, r1		;sign bit is greater's
	MOV r3, #0			;count loop
	MOV r6, #1
	LSL r6, #23
Loop					;find integer 1
	ANDS r5, r6, r4, LSL r3		;1 & (r4 << r3)
	ADDEQ r3, #1		;count++
	BEQ Loop			;r4 << r3 bit is 0. Loop must do 'break' because r4 is not zero (zero result)
	LSL r4, r3			;shift r4
	SUB r2, r2, r3		;E - r3
	
GetFullFloat
	LSL r4, #9
	SUB r2, #1		;/2
	LSL r2, #24
	LSR r2, #1
	ORR r0, r2, r0, LSL #31
	ORR r0, r0, r4, LSR #9
	MOV pc, lr			;back to the function
	
Matrix_data	
	DCD 3
	DCD 2
	DCD 2_01000010011010000000000000000000
	DCD 2_10111111111101000000000000000000
	DCD 2_11000000110000000000000000000000
	DCD 2_11000010111000000000000000000000
	DCD 2_01000011000000000000000000000000
	DCD 2_01000010001011000000000000000000
	DCD 2_01000011110001000000000000000000
	DCD 2_01000011011100000000000000000000
	DCD 2_01000001101000000000000000000000
	
Result_data
	DCD 0x60000000
		
temp
	DCD 0x40000000

	END