; This file is a translation of the C program translate.c.
;
; The find_abs function covered in class is a reasonably accurate
; illustration of the code produced by a non-optimizing compiler.
; (note that all int32_t's are instead treated as int16_t's for LC-3,
; which is technically a liberty on my part).  Each C statement 
; translates to a set of instructions.  Explanatory comments are, of 
; course, not usually produced by a compiler.
;
; I did take liberties in translating the rest of the code.  In
; particular, I use PUTS in place of printf, and used a modified
; version of our READNUM subroutine (one that allows negative 
; numbers) in place of scanf.  Since that code already handles 
; errors, I ignored the scanf error-handling code in the C program.  
; Also, I use our printbinary code (changed into a subroutine) for 
; printing the absolute value in binary (rather than hex, since the 
; regular class is still using printing in hex as an MP).  Finally, 
; I use 16-bit integers rather than 32-bit integers.
;

	.ORIG	x3000

	; set up for C execution
	LEA	R4,GLOBAL_DATA
	LD	R6,STACK
	; R5 is bits, but that's ok--there is no frame on the stack yet

	; call main; there are no parameters for main
	JSR	MAIN
	LDR	R0,R6,#0	; R0 <- return value
	ADD	R6,R6,#1	; pop return value

	; check the return value--just for fun--normally, the shell
	; or whatever program started our program handles this part
	ADD	R0,R0,#0
	BRz	EXEC_DONE

	; code terminated with a non-zero exit status; print a message
	LEA	R0,FAIL
	PUTS

EXEC_DONE
	HALT

STACK	.FILL	xFE00	; stack for C code execution
FAIL	.STRINGZ "\nmain terminated abnormally.\n"

;--------------------------------------------------------------------------
;
; int find_abs (int num)
;
FIND_ABS
	
	; set up the stack frame
	ADD	R6,R6,#-4	; need 4 locations for linkage +
				;    local variable
	STR	R5,R6,#1	; save previous frame pointer
	ADD	R5,R6,#0	; set frame pointer
	STR	R7,R5,#2	; save return address

	; check the condition (0 <= num)
	LDR	R0,R5,#4	; R0 <- num
	BRn	ELSE_CONDITION

	; condition is true (0 <= num), so expression value is num
	LDR	R0,R5,#4	; R0 <- num
	BRnzp	DONE_CONDITIONAL

ELSE_CONDITION
	; condition is false (0 > num), so expression value is -num
	LDR	R0,R5,#4	; R0 <- -num
	NOT	R0,R0	
	ADD	R0,R0,#1	

DONE_CONDITIONAL		; write the result into abs_value
	STR	R0,R5,#0	; abs_value <- R0
	
	; return abs_value
	LDR	R0,R5,#0	; R0 <- abs_value
	STR	R0,R5,#3	; (return value) <- R0

	; tear down the stack frame
	LDR	R7,R5,#2	; restore return address
	LDR	R5,R5,#1	; restore frame pointer
	ADD	R6,R6,#3	; pop local variable and linkage
				;    (except for return value)

	; all done!
	RET

;--------------------------------------------------------------------------
;
; int main ()
;
MAIN
	
	; set up the stack frame
	ADD	R6,R6,#-3	; need 3 locations for linkage
	STR	R5,R6,#0	; save previous frame pointer
	ADD	R5,R6,#-1	; set frame pointer
	STR	R7,R5,#2	; save return address

	; compiler symbol table indicates that the prompt is 
	; stored at R4 + #1, so we copy that value into R0,
	; then use PUTS to print the string
	ADD	R0,R4,#1	; print prompt
	PUTS

	; read the user's number from the keyboard into R0
	JSR	READNUM		; fake scanf %d for our example
				;    (returns number in R0)
	STR	R0,R4,#0	; the_number <- R0

	; call find_abs (the_number)
	LDR	R0,R4,#0	; push a copy of the_number
	ADD	R6,R6,#-1
	STR	R0,R6,#0
	JSR	FIND_ABS	; call the function
	LDR	R0,R6,#0	; R0 <- return value
	ADD	R6,R6,#2	; pop return value and parameter
	; the_number = find_abs (the_number)
	STR	R0,R4,#0	; the_number <- return value

	; compiler symbol table indicates that the output message 
	; is stored at R4 + #33, so we copy that value into R0,
	; then use PUTS to print the string
	LD	R0,P2_OFF	; R0 <- #33
	ADD	R0,R0,R4	; print output message
	PUTS

	; PRINT_BINARY with the_number
	LDR	R0,R4,#0	; R0 <- the_number
	JSR	PRINT_BINARY

	; compiler symbol table indicates that the suffix of the
	; output message is stored at R4 + #66, so we copy that 
	; value into R0, then use PUTS to print the string
	LD	R0,P2_SUF	; R0 <- #66
	ADD	R0,R0,R4	; print output message
	PUTS

	; return 0
	AND	R0,R0,#0	; R0 <- 0
	STR	R0,R5,#3	; return value <- R0

	; tear down the stack frame
	LDR	R7,R5,#2	; restore return address
	LDR	R5,R5,#1	; restore frame pointer
	ADD	R6,R6,#2	; pop linkage (except for return value)

	; all done!
	RET

P2_OFF	.FILL	#33
P2_SUF	.FILL	#66

;--------------------------------------------------------------------------
;
; readnumsub.asm (an earlier example) modified to allow the user to
; enter a negative number and also to remove test code and directives; 
; on return, R0 holds the number entered using the keyboard; R0 through R3 
; and R7 are caller-saved; R4, R5, and R6 are callee-saved (necessary for 
; this subroutine to be called from C)
;

; subroutine developed as an extension of the
; earlier binary code

; read a decimal number from the keyboard,
; convert it from ASCII to 2's complement, and
; return it in R0.  If any non-numeric character 
; is pressed, or the number overflows, print an 
; error message and start over.

; R0 holds the value of the last key pressed
; R1 holds the current value of the number being input
; R2 holds the additive inverse of ASCII '0' (0xFFD0)
; R3 is used as a temporary register

READNUM				; the subroutine to read a number

	ST R7,SAVE_R7		; TRAP overwrites R7, so must save
	ST R3,SAVE_R3		; callee saves register values
	ST R2,SAVE_R2
	ST R1,SAVE_R1

; MODIFICATION TO HANDLE NEGATIVE NUMBERS
	ST R4,SAVE_R4
	AND R4,R4,#0		; number is initially positive (R4=0)
; END OF MODIFICATION

	LD R2,NEG_0		; put the value -x30 in R2
	AND R1,R1,#0		; clear the current value

READ_LOOP
	GETC			; read a character
	OUT			; echo it back to monitor
	ADD R3,R0,#-10		; compare with ENTER
	BRz DONE		; if ENTER pressed, done

; MODIFICATION TO HANDLE NEGATIVE NUMBERS
	; note that one CAN type 00-001 (for example) ... trying to
	; limit modifications, so I'm going to ignore it
	LD R3,NMINUS		; compare with minus sign
	ADD R3,R0,R3
	BRnp NOT_MINUS
	ADD R1,R1,#0		; number so far must be 0
	BRnp BAD_KEY
	ADD R4,R4,#0		; can't type two negative signs
	BRnp BAD_KEY
	ADD R4,R4,#1		; mark as negative
	BRnzp READ_LOOP
NOT_MINUS
; END OF MODIFICATION

	ADD R0,R0,R2		; subtract x30 from R0
	BRn BAD_KEY		; smaller than '0' means error
	ADD R3,R0,#-10		; check if > '9'
	BRzp BAD_KEY		; greater than '9' means error
	ADD R3,R1,R1		; sequence of adds multiplies R1 by 10
	BRn OVERFLOW		; overflow, but not really necessary here
	ADD R3,R3,R3
	BRn OVERFLOW		; overflow, but not really necessary here
	ADD R1,R1,R3
	BRn OVERFLOW		; overflow
	ADD R1,R1,R1
	BRn OVERFLOW		; overflow
	ADD R1,R1,R0		; finally, add in new digit
	BRn OVERFLOW		; overflow
	BRnzp READ_LOOP		; get another digit

DONE
	ADD R0,R1,#0		; move R1 into R0	
; MODIFICATION TO HANDLE NEGATIVE NUMBERS
	ADD R4,R4,#0		; check whether '-' was pressed
	BRz IS_POS
	NOT R0,R0		; negate R0
	ADD R0,R0,#1
IS_POS
	LD R4,SAVE_R4		; restore R4
; END OF MODIFICATION

	LD R1,SAVE_R1		; restore register values for caller
	LD R2,SAVE_R2
	LD R3,SAVE_R3
	LD R7,SAVE_R7

	RET			; return

; print error message: "non-digit pressed"
BAD_KEY
	LEA R0,BK_MSG		; point R0 to the start of the string
PRINT_ERR
	PUTS			; the trap that you're not allowed to use in MP2
	AND R1,R1,#0		; reset current value
; MODIFICATION TO HANDLE NEGATIVE NUMBERS
	AND R4,R4,#0		; number is initially positive (R4=0)
; END OF MODIFICATION
	BRnzp READ_LOOP		; try reading again

; print error message: "overflow"
OVERFLOW
	LEA R0,OF_MSG		; point R0 to the start of the string
	BRnzp PRINT_ERR

SAVE_R1	.BLKW 1		; storage for saved register values
SAVE_R2	.BLKW 1
SAVE_R3	.BLKW 1
; MODIFICATION TO HANDLE NEGATIVE NUMBERS
SAVE_R4 .BLKW 1
NMINUS	.FILL xFFD3	; the additive inverse of ASCII '-'
; END OF MODIFICATION
SAVE_R7	.BLKW 1
NEG_0	.FILL xFFD0	; the additive inverse of ASCII '0'
NUM1	.BLKW 1		; storage for the results
NUM2	.BLKW 1

; error messages.  The sequence \n means newline and is replaced
; with a single ASCII linefeed character (#10).  Similar sequences
; include \r for #13 (carriage return), \t for #9 (TAB), \\ for 
; backslash, etc.
BK_MSG	.STRINGZ "\nnon-digit pressed\n"
OF_MSG	.STRINGZ "\noverflow\n"

;--------------------------------------------------------------------------
;
; printbinary.asm (an earlier example) unmodified except to turn it into
; a subroutine; R0 holds the value to be printed; R0 through R3 and R7 are
; caller-saved; R4, R5, and R6 are callee-saved (necessary for this
; subroutine to be called from C); note that since the routine uses I/O
; registers directly, we need not save R7
;

; MODIFICATION: label the subroutine and save R4
PRINT_BINARY
	ST	R4,PB_R4	; save R4
	; removed code to set the value of R0
; END OF MODIFICATION

	; print the value in R0 as a 16-bit binary number

	; R0 holds the number (shifted left to find bits)
	; R1 holds the bit number being printed (15 down to 0)
	; R2 holds the ASCII character for that bit
	; R3 holds x30 (ASCII '0') for convenience

	AND	R1,R1,#0	; start with bit 15
	ADD	R1,R1,#15
	LD	R3,ZERO		; initialize R3
BITLOOP ADD	R2,R3,#0	; copy R3 to R2 ('0')
	ADD	R0,R0,#0	; check bit value
	BRzp	ZEROBIT		; skip next instruction for 0 bit
	ADD	R2,R2,#1	; print a 1 bit
ZEROBIT	LDI	R4,DSR		; wait for display to be ready
	BRzp	ZEROBIT
	STI	R2,DDR		; write ASCII character to display
	ADD	R0,R0,R0	; shift R0 left to find next bit
	ADD	R1,R1,#-1	; count down in bit index
	BRzp	BITLOOP		; print another until index < 0

; MODIFICATION: HALT in the original code replaced with this sequence
	LD	R4,PB_R4	; restore R4
	RET
PB_R4	.BLKW	#1	
; data below are part of the subroutine, so we won't move to the global 
;    data area; removed number printed as an example
; END OF MODIFICATION

ZERO	.FILL	x30		; ASCII digit '0'
DSR	.FILL	xFE04		; DSR address in LC-3
DDR	.FILL	xFE06		; DDR address in LC-3

;--------------------------------------------------------------------------

GLOBAL_DATA	; data starts here
	.FILL	#0	; the_number -- accessed as [R4 + #0]
	.STRINGZ "Please enter a decimal number: "
	.STRINGZ "The absolute value in binary is "
	.STRINGZ ".\n"

	.END

