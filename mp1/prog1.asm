;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **
;	Partners: aliceg3, agbalan2

	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;	Partners: aliceg3, agbalan2

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
	
; you will need to insert your code to print the histogram here
; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments
	

;      This prints the histogram needed by keeping track of the address of the
;      memory location that stores the histogram and uses the predefined order
;      to iterate through the list of letters and non letters. It prints the
;      number of each letter and all of the cumulative non letters.
;      By incrementing the address and ascii value of the historgram in two
;      seperate registers, we are able to more easily print the respective ascii
;      and letter frequency values for each bin.
;      Partners: aliceg3, agbalan2
	
;      R0 is things addresses or ascii values to output (for OUT and PUTS)
;      R1 is the bit counter for printing the value of each bin (inner counter)
;      R2 is the digit counter for printing each digit for every bin (outer counter)
;       R3 holds the value for each bin, the thing that you want to print
;       R4 holds counter for the number of loop iterations needed (#27)
;       R5 holds the value of the hist (starting with ascii @ to Z)
;       R6 holds the memory address of the hist
	

       LD R4, NUM_BINS              ; Load the number of bins into R4 (#27)
       LD R5, NEG_AT         ; Load the negative representation of ascii @ into R5
       NOT R5, R5            ; Not R5, then adding one in the next line
       ADD R5, R5, #1        ; R5 ends up being the ascii value of @
       LD R6, HIST_ADDR      ; Load the starting place for the hist address in R6
	
LOOPY  AND R0, R0, #0        ; Reset R0 to #0
       ADD R0, R0, R5        ; Put the R5 into R0
       OUT                   ; Print the ascii value in R0, will be @ through Z
       LD R0, STR_SPACE      ; Load ascii space into R0
       OUT                   ; Print the space
       LDR R3, R6, #0        ; Load the frequency of letters used into R3

; --------------  LAB 1 ---------------- (Prints the data in the current bin.)
	
       AND R2, R2, #0               ; Clear R2, the digit counter
       ADD R2, R2, #4               ; Set R2 to 4
OUT_LP AND R0, R0, #0               ; Clear R0, the digit
       AND R1, R1, #0               ; Clear R1, the bitcounter
       ADD R1, R1, #4               ; Set R1 to 4
IN_LP  BRnp SKIP             ; Checks if bitcounter is 0, if not goes to SKIP
       ADD R0, R0, #-9              ; Subtracts to perform nessecary check if R0 > 9 or not
       BRp #1                ; Differentiates between letters and numbers
       ADD R0, R0, #-7              ; This assumes numbers, which are lower in the ascii list
       ADD R0, R0, #15              ; Repeated addition to get to the desired ascii value
       ADD R0, R0, #15              ; ^
       ADD R0, R0, #15              ; ^
       ADD R0, R0, #15              ; ^
       ADD R0, R0, #4        ; ^
       OUT                   ; Prints the respective ascii value for one of the 4 digits of hex
       ADD R2, R2, #-1              ; Decrement digit counter
       BR SKIPOUT            ; skip to SKIPOUT, avoid other condition
	

SKIP   ADD R0, R0, R0        ; Clear R0
       ADD R3, R3, #0               ; GetCC for R3, for the next BR
       BRzp #1               ; Check if MSB is 1
       ADD R0, R0, #1        ; Increment R0, (if MSB is 1)
       ADD R3, R3, R3        ; Left shift R3 (to get future MSB)
       ADD R1, R1, #-1              ; Decrement bitcounter R1
       BR IN_LP              ; Branches to inner loop (IN_LP), where it will be checked again
SKIPOUT ADD R2, R2, #0        ; GetCC for R2, for next BR
       BRnp OUT_LP           ; If the digit counter R2 is 0, continue as printing if finished

; ------------ END LAB 1 -------------
	
       LD R0, NEW_LN         ; Load ascii line break into R0
       OUT                   ; Prints line break
       ADD R5, R5, #1        ; Increment R5 (ascii representation)
       ADD R6, R6, #1        ; Increment R6 (memory bin location)
       ADD R4, R4, #-1       ; Decrement R4 (bin counter)
       BRp LOOPY             ; If the bin counter (R4) is not finished iterating (=0), go again
	
DONE   HALT                  ; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
STR_SPACE	.FILL x0020	;Ascii space
NEW_LN		.FILL x000A	;Ascii new line

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
