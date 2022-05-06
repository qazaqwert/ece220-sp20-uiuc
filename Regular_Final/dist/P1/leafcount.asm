.ORIG x3000

;;R5 - frame pointer
;;R6 - stack pointer
;;MAIN
LD R6, STACK
LD R5, STACK
LD R1, ND_VAL
STR R1, R6, #0    ; push root (x6000) to stack
JSR LEAF_COUNT
LDR R0, R6, #0
LD R1, ASCII_ZERO
ADD R0, R0, R1
OUT
HALT

            ;;LEAF_COUNT 
            LEAF_COUNT
            ;;Part 1 - callee set-up
            ;allocate space for return value
            ADD R6, R6, #-1
            ;Push return address to stack
            ADD R6, R6, #-1
            STR R7, R6, #0
            ;Store old frame pointer
            ADD R6, R6, #-1
            STR R5, R6, #0
            ;Set up new frame pointer
            ADD R5, R6, #-1
            ; Reserve two local variables (left_count, right_count)
            ADD R6, R6, #-2


;;Part 2 - implement function logic
;YOUR CODE STARTS HERE
PART2INIT   ADD R0, R0, #0
            ADD R2, R2, #0  
            ADD R3, R3, #0
            ADD R4, R4, #0
            ADD R5, R5, #0

PART2       LDR R2, R1, #0 
            BRz PART3
            LDR R2, R1, #1
            ADD R3, R2, #0
            LDR R2, R1, #1
            ADD R3, R2, #0
            BRnp SKIP
            ADD R0, R0 #1
SKIP        ADD R1, R1, #2     





;;Part 3 - callee tear-down (prepare to return)
;YOUR CODE STARTS HERE

PART3       




RET

STACK .FILL x7000
ND_VAL .FILL x6000
ASCII_ZERO .FILL x0030
.END
