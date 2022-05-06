; MP2 - Stack calculator
;
; Team:
; Alice Getmanchuk aliceg3
; Jacob Tentis jtentis2
; Jerry Balan agbalan2

; Problem statement is to create a calculator for integers 0-9 with functions +, -, *, /, and ^
; There is no need to manage overflow following the flow chart provided, 
; the program first matches the character input if space, ignored if 0-9 input, pushed to stack
; if one of the functions, uses JSR to access subroutine each subroutine saves the PC,
; completes the operation, then goes back to the same place in the code.
; When the program detects '=', then the final result in stack is pushed out and printed in hex
; using Lab1/MP1 code at PRINT_HEX. If the stack does not have only one value by the end,
; we know that there is an error with the expression provided, and we will alert the user
; and halt the program.

.ORIG x3000

PROG_LP	GETC			; Read one ascii character of user input and load into R0
	OUT			; Print the user input so the user sees what they inputted

	; Test if the user entered =
	LD R1, EQUAL_COMP	; Load the complement of '=' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '=' in R1
	BRz EQUAL		; If no difference, user entered '=', branch to EQUAL

	; Test if the user entered ' ' (space)
	LD R1, SPACE_COMP	; Load the complement of ' ' into R1
	ADD R1, R0, R1		; Find the difference between the user input and ' ' in R1
	BRz PROG_LP		; If no difference, user entered ' ', go back and get another char
	
	; Check if the input is a valid operation
	LD R1, PLUS_COMP	; Load the complement of '+' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '+' in R1
	BRz VALIDOP		; If no difference, user entered '+', branch to VALIDOP

	; Check if the input is a valid operation
	LD R1, MIN_COMP		; Load the complement of '-' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '-' in R1
	BRz VALIDOP		; If no difference, user entered '-', branch to VALIDOP

	; Check if the input is a valid operation
	LD R1, MUL_COMP		; Load the complement of '*' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '*' in R1
	BRz VALIDOP		; If no difference, user entered '*', branch to VALIDOP

	; Check if the input is a valid operation
	LD R1, DIV_COMP		; Load the complement of '/' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '/' in R1
	BRz VALIDOP		; If no difference, user entered '/', branch to VALIDOP

	; Check if the input is a valid operation
	LD R1, EXP_COMP		; Load the complement of '^' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '^' in R1
	BRz VALIDOP		; If no difference, user entered '^', branch to EQUAL

	; Check if the input is not within the number range
	LD R1, ZERO_COMP	; Load the complement of '0' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '0' in R1
	BRn INVALID		; If negative, user entered chat <'0', branch to INVALID

	LD R1, NINE_COMP	; Load the complement of '9' into R1
	ADD R1, R0, R1		; Find the difference between the user input and '9' in R1
	BRp INVALID		; If positive, user entered chat >'9', branch to INVALID


; valid number, not operation - push number onto stack
	LD R1, ZERO_COMP	; Loads the complement of '0' into R1
	ADD R0, R0, R1		; Subtracts the ascii number by ascii '0' to get hex number in R0
	JSR PUSH		; Push the hex number on the stack
	BRnzp PROG_LP		; Go back and get new input
	
; valid operation
VALIDOP	JSR EVALUATE		; Evaluate (pop) using the operation in R0, new value in R6
	AND R0, R0, #0		; Clear R0
	ADD R0, R6, #0		; Set R0 to R6 (new value after the operation)
	JSR PUSH		; Push the new result number back into the stack
	BRnzp PROG_LP		; Go back and get new input

; invalid condition here
INVALID	LEA R0, INVALID_EXPR	; Set R0 to memory location of error string
	PUTS			; Print the error string
	HALT			; Halts program

; equals sign is entered, check to see if we have one value to output and output it
EQUAL	LD R3, STACK_START	; Load STACK_START memory location to R3
	LD R4, STACK_TOP	; Load STACK_TOP memory location to R4
	ADD R4, R4, #1		; Increment R4 by one for START to match TOP
	JSR MIN			; Subtract R3 and R4, store result in R0
	ADD R0, R0, #0		; GetCC for R0
	BRnp INVALID		; If START is not equal to TOP, branch to invalid
	LDI R5, STACK_START	; Store the remaining value in the stack to R5
	LDI R3, STACK_START	; Store the remaining value in the stack to R3
	JSR PRINT_HEX		; Print the hex of the value in R3
	HALT			; Halt the program



INVALID_EXPR	.STRINGZ	"Invalid Expression"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

;using lab1/MP1 code
	ST R7, P_HexR7		; Save R7 to memory
	AND R2, R2, #0 		; Clear R2, the digit counter
	ADD R2, R2, #4 		; Set R2 to 4
OUT_LP	AND R0, R0, #0  	; Clear R0, the digit
	AND R1, R1, #0 		; Clear R1, the bitcounter 
	ADD R1, R1, #4 		; Set R1 to 4
IN_LP	BRnp SKIP 		; Checks if bitcounter is 0, if not goes to SKIP
	ADD R0, R0, #-9		; Subtracts to perform nessecary check if R0 > 9 or not
	BRp #1			; Differentiates between letters and numbers
	ADD R0, R0, #-7		; This assumes numbers, which are lower in the ascii list
	ADD R0, R0, #15		; Repeated addition to get to the desired ascii value
	ADD R0, R0, #15		; ^
	ADD R0, R0, #15		; ^
	ADD R0, R0, #15		; ^
	ADD R0, R0, #4		; ^
	OUT			; Prints the respective ascii value for one of the 4 digits of hex
	ADD R2, R2, #-1		; Decrement digit counter
	BR SKIPOUT		; skip to SKIPOUT, avoid other condition
SKIP	ADD R0, R0, R0		; Clear R0
	ADD R3, R3, #0 		; GetCC for R3, for the next BR
	BRzp #1			; Check if MSB is 1
	ADD R0, R0, #1		; Increment R0, (if MSB is 1)
	ADD R3, R3, R3		; Left shift R3 (to get future MSB)
	ADD R1, R1, #-1		; Decrement bitcounter R1
	BR IN_LP 		; Branches to inner loop (IN_LP), where it will be checked again
SKIPOUT	ADD R2, R2, #0		; GetCC for R2, for next BR
	BRnp OUT_LP		; If the digit counter R2 is 0, continue as printing if finished
	LD R7, P_HexR7		; Load R7 from memory
	RET

P_HexR7    .BLKW #1    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
; main part of program deals with valid inputs
; this will only be run if an operation is needed to run
; 
	ST R7, EVAL_SaveR7	; Save R7
	AND R1, R1, #0		; Clear R1
	ADD R1, R0, #0		; Set R1 to R0
	AND R3, R3, #0		; Clear R3
	AND R4, R4, #0		; Clear R4
	JSR POP			; POP an item out of the stack
	ADD R4, R0, #0		; put that item into R4
	JSR POP			; POP another item out of the stack
	ADD R3, R0, #0		; put that item into R3
	ADD R5, R5, #0		; check if the POP created underflow error (implemented in POP)
	BRp INVALID		; if underflow, go to invalid
	
	LD R2, PLUS_COMP	; Load complement of '+' into R2
	ADD R2, R2, R1		; Subtract '+' with the user input
	BRnp #2			; If the result is not 0 (user did not inputted '+') check other op
	JSR PLUS		; User inputted '+', use PLUS to evaluate
	BR EVAL_D		; Branch to EVAL_D

	LD R2, MIN_COMP		; Load complement of '-' into R2
	ADD R2, R2, R1		; Subtract '-' with the user input
	BRnp #2			; If the result is not 0 (user did not inputted '-') check other op
	JSR MIN			; User inputted '-', use MIN to evaluate
	BR EVAL_D		; Branch to EVAL_D

	LD R2, MUL_COMP		; Load complement of '*' into R2
	ADD R2, R2, R1		; Subtract '*' with the user input
	BRnp #2			; If the result is not 0 (user did not inputted '*') check other op
	JSR MUL			; User inputted '*', use MUL to evaluate
	BR EVAL_D		; Branch to EVAL_D

	LD R2, DIV_COMP		; Load complement of '/' into R2
	ADD R2, R2, R1		; Subtract '/' with the user input
	BRnp #2			; If the result is not 0 (user did not inputted '/') check other op
	JSR DIV			; User inputted '/', use DIV to evaluate
	BR EVAL_D		; Branch to EVAL_D

	LD R2, EXP_COMP		; Load complement of '^' into R2
	ADD R2, R2, R1		; Subtract '^' with the user input
	BRnp #2			; If the result is not 0 (user did not inputted '^') check other op
	JSR EXP			; User inputted '^', use EXP to evaluate
	BR EVAL_D		; Branch to EVAL_D
	
	BR INVALID		; Catch-all statement that ensures user typed invalid operation

	
EVAL_D	LD R7, EVAL_SaveR7	; Loads the previously saved value of R7
	AND R6, R6, #0		; Clear R6
	ADD R6, R0, #0		; Takes output from R0 (from any operation), puts it in R6
	RET			; Return to memory location of R7

EVAL_SaveR7    .BLKW #1    ;

ZERO_COMP    	.FILL   xFFD0   ; Complement of ascii of 0
NINE_COMP    	.FILL   xFFC7   ; Complement of ascii of 9
PLUS_COMP    	.FILL   xFFD5   ; Complement of ascii of plus sign
MIN_COMP    	.FILL   xFFD3   ; Complement of ascii of minus sign
MUL_COMP    	.FILL   xFFD6   ; Complement of ascii of multiplication (*) sign
DIV_COMP    	.FILL   xFFD1   ; Complement of ascii of division (/) sign
EXP_COMP    	.FILL   xFFA2   ; Complement of ascii of exponent (^) sign
EQUAL_COMP    	.FILL   xFFC3   ; Complement of ascii of equal sign
SPACE_COMP	.FILL	xFFE0	; Complement of ascii of space

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;input R3, R4
;out R0
PLUS    
;your code goes here
	AND R0, R0, #0		;clear R0
	ADD R0, R3, R4        	; add R3 and R4 -> R0
	RET
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN    
;your code goes here
	AND R0, R0, #0		; clear R0
    	ST R4, MIN_SAVER4	; save R4
    	NOT R4, R4        	;
    	ADD R4, R4, #1        	; make R4 negative
    	ADD R0, R3, R4        	; add R3 and negative R4 -> R0
	LD R4, MIN_SAVER4	; Load the R4 saved
    	RET

MIN_SAVER4	.BLKW #1  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL    
;your code goes here
	ST R7, MUL_SAVER7 	; Store R7
	ST R1, MUL_SAVER1	; Store R1
	AND R1, R1, #0 		; clear R1
	ADD R1, R4, #0 		; R1 <= R4
	AND R4, R4, #0 		; clear R4
	ADD R1, R1, #0 		; read nzp from R1
MUL_L	BRz FINI		; Check if counter R1 is zero
	JSR PLUS		; Go to PLUS, add R3 and R4, output to R0
	ADD R4, R0, #0		; Get output of R0 and place in R4
	ADD R1, R1, #-1		; Decrease counter R1 by 1
	BRnzp MUL_L		; Loop back to MUL_L

FINI	AND R0, R0, #0		; Clear R0
	ADD R0, R4, #0		; Put R4 in R0
	LD R7, MUL_SAVER7	; Load R7 from saved memory
	LD R1, MUL_SAVER1	; Load R1 from saved memory
	RET

MUL_SAVER1	.BLKW #1  ;
MUL_SAVER7	.BLKW #1  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV    
;your code goes here
	ST R1, DIV_SAVER1	; Save R1 to memory
    	AND R0, R0, #0		; Clear R0
    	AND R1, R1, #0		; Clear R1
    	NOT R4, R4		; Make R4 negative
    	ADD R4, R4, #1		; ^
MAIN    ADD R3, R3, R4		; Subtract R3 by R4 and store in R3
    	BRn DONE		; If negative result, we are done
    	ADD R0, R0, #1		; Increment counter
    	BR MAIN			; Go back to main and try again
DONE    ADD R4, R4, #-1		; Negate R4 again (restoring original value)
    	NOT R4, R4		; ^
    	ADD R3, R3, R4		; R3 <- R3 + R4
    	ADD R1, R3, #0		; R1 <- R3
	LD R1, DIV_SAVER1	; Load R1 from memory
    	RET

DIV_SAVER1	.BLKW #1  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
    	ST R7, EXPSAVE_R7	; Save R7 to memory
    	ST R5, EXPSAVE_R5	; Save R5 to memory
    	ST R3, EXPSAVE_R3	; Save R3 to memory
    	AND R5, R5, #0		; Clear R5
        ADD R5, R4, #0		; Set R5 to R4
    	BRz ONE			; case for which exponent is 0 (so result is 1)
    	ADD R5, R5, #-1    	; in order to get loop count correctly
        AND R4, R4, #0		; Clear R4
        ADD R4, R3, #0		; Set R4 to R3
    
    
SA    	LD R4, EXPSAVE_R3    	; placing R3 into R4 so that muliplication

MULT    AND R0, R0, #0    	; beginning of multiplying loop to do base_exp times base_exp
    	ADD R4, R4, #0    	; loop counter for multiplying
    	BRz FINI    		; case for if thing being multiplied by is 0
    
STAR    ADD R0, R3, R0    	; multiplying loop R0<-R3+R0
    	ADD R4, R4, #-1    	; decrement mult counter
    	BRp STAR    		; if mult counter still positive, go back to STAR
    

    	ADD R3, R0, #0    	; store result of multiplying (R0) into R3
    	ADD R5, R5, #-1    	; decrement exponent
    	BRp SA        		; if positive exponent, return to SA and repeat mult loop
    	BRz FIN        		; if exp = 0, then go to FIN

ONE   	ADD R0, R0, #1    	; making result = 1 if exp =0
    
FIN    	LD R5, EXPSAVE_R5	; Load R5 from memory
    	LD R7, EXPSAVE_R7    	; Load R7 from memory
	LD R3, EXPSAVE_R3	; Load R3 from memory
    	RET

EXPSAVE_R3 .BLKW #1		;
EXPSAVE_R5 .BLKW #1		;
EXPSAVE_R7 .BLKW #1		;
    
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH    
    ST R3, PUSH_SaveR3    ;save R3
    ST R4, PUSH_SaveR4    ;save R4
    AND R5, R5, #0        ;
    LD R3, STACK_END    ;
    LD R4, STACk_TOP    ;
    ADD R3, R3, #-1        ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0        ;no overflow, store value in the stack
    ADD R4, R4, #-1        ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH        ;
OVERFLOW
    ADD R5, R5, #1        ;
DONE_PUSH
    LD R3, PUSH_SaveR3    ;
    LD R4, PUSH_SaveR4    ;
    RET


PUSH_SaveR3    .BLKW #1    ;
PUSH_SaveR4    .BLKW #1    ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP    
    ST R3, POP_SaveR3    ;save R3
    ST R4, POP_SaveR4    ;save R3
    AND R5, R5, #0        ;clear R5
    LD R3, STACK_START    ;
    LD R4, STACK_TOP    ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz UNDERFLOW        ;
    ADD R4, R4, #1        ;
    LDR R0, R4, #0        ;
    ST R4, STACK_TOP    ;
    BRnzp DONE_POP        ;
UNDERFLOW
    ADD R5, R5, #1        ;
DONE_POP
    LD R3, POP_SaveR3    ;
    LD R4, POP_SaveR4    ;
    RET


POP_SaveR3    .BLKW #1    ;
POP_SaveR4    .BLKW #1    ;
STACK_END    .FILL x3FF0    ;
STACK_START    .FILL x4000    ;
STACK_TOP    .FILL x4000    ;


.END

