.ORIG x3000

LEA R6, R6START
JSR TREE_FIND
HALT

TREE_FIND
	ADD R6, R6, #-3
	STR R5, R6, #0
	ADD R5, R6, #-1
	STR R7, R5, #2

;  if (!root) return NULL;
	LDR R0, R5, #4
	BRz TREE_FIND_RETURN_R0

;  if (root->value == v) return root;
	LDR R0, R5, #4 ; R0 <- root
	LDR R2, R0, #0 ; R2 <- root->value
	LDR R3, R5, #5 ; R3 <- v
	NOT R1, R3
	ADD R1, R1, #1
	ADD R1, R2, R1 ; R1 = root->value - v
	BRz TREE_FIND_RETURN_R0

;   return tree_find((root->value < v) ? root->right : root->left, v);

	BRp SKIP_ONE_ADD
	ADD R0, R0, #1
SKIP_ONE_ADD
	LDR R0, R0, #1

	ADD R6, R6, #-2
	STR R0, R6, #0
	STR R3, R6, #1
	JSR TREE_FIND
	LDR R0, R6, #0
	ADD R6, R6, #3

TREE_FIND_RETURN_R0
	STR R0, R5, #3

	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #2
	RET

STACK   .BLKW #100
R6START .FILL TREE_A      
        .FILL #3

TREE_A .FILL #5
       .FILL TREE_B
       .FILL #0

TREE_B .FILL #2
       .FILL #0
       .FILL TREE_C

TREE_C .FILL #3
       .FILL #0
       .FILL #0

.END

;                  <- new r5
; (r5 save)        <- new r6
; (r7 save)
; (return value)
; root <- R6
; v