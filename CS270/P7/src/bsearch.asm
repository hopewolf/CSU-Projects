;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Start of reserved section - DO NOT CHANGE ANYTHING HERE!!!
; The only exception is that you can modify the .FILL value of Needle to make
; it easy to test.

                .ORIG x3000
                BR Main

; Stack base
Stack           .FILL x4000

; Parameter and result
Needle          .FILL #7
Result          .FILL xFFFF

; Entry point
Main            LD    R6, Stack           ; Stack initialization
                LD    R5, Stack           ;
                
                LD    R0, Count           ; Load the number of elements
                LEA   R1, Haystack        ; Load loAddress
                LD    R2, Needle          ; Load the element to search for
                
                AND   R3, R3, #0          ; Calculate hiAddress
                ADD   R3, R3, #-1         ;
                ADD   R3, R0, R3          ;
                ADD   R3, R1, R3          ;
                PUSH  R3                  ; Push parameters in reverse order
                PUSH  R1                  ;
                PUSH  R2                  ;
                JSR   BinarySearch        ; Call BinarySearch
                POP   R0                  ; Retrieve the return value
                ADD   R6, R6, #3          ; Clean up
                
                ST    R0, Result          ; Store the result in global variable
Finish          HALT
                
; End of reserved section
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; DO NOT ADD ANYTHING IN BETWEEN THESE SECTIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Start of the array definition - DO NOT CHANGE THE LABEL NAMES OR POSITIONS!!!
; In this section, you're only allowed to change the .FILL value for Count
; (number of elements in the array) and the .FILL values of the array but DO NOT
; delete or add any lines in this section (otherwise, you risk getting no
; credit). If you want fewer elements in the array, simply change Count. Note 
; that the maximum number of elements in the array is 20.

Count           .FILL #7

Haystack        .FILL #14
                .FILL #12
                .FILL #10
                .FILL #8
                .FILL #6
                .FILL #4
                .FILL #2
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0
                .FILL #0

; End of the array definition
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Start of the function definition
; This is where you will implement your BinarySearch function. DO NOT implement
; any other functions (not even helper functions).

; int *BinarySearch(int x, int *loAddress, int *hiAddress);
BinarySearch    ; Start here
                ; My solution was 75 lines (including empty lines and comments)
                ; be able to calculate mid address and offset
                ; if mid is less than value (R2) 
                ADD R6, R6, #-1         ; make space for ret value
                PUSH R7                 ; return address
                PUSH R5                 ; previous frame pointer
                ADD R5, R6, #-1         ; setup new frame pointer (unsure about constant)
                ADD R6, R6, #-2         ; allocate spacce for local vars (there are 2)
                
                ;;;;;;;;;;;;;;;;;;;;;;;;; body of function
                
                LDR R1, R5, #5          ; load loAddress from stack
                LDR R3, R5, #6          ; load hiAddress from stack
                
                NOT R1, R1              ; get 2's comp of loAddress
                ADD R1, R1, #1          ;
                ADD R4, R1, R3          ; check if loAddress > hiAddress (failed to find?)
                BRn BaseCase            ; branch to base case
                BRp MultElement         ; if its only one element left, skip DivideBy2, theres only one element
                .ZERO R3                ; theres only one element, offset is 0
                BRnzp WholeNum          ;
MultElement
                ADD R4, R1, R3          ; calculate midOffset
                .ZERO R3                ; use register 3 to store count of Division (the answer)
DivideBy2       ADD R3, R3, #1          ; increment count
                ADD R4, R4, #-2         ; perform Division using subtraction and iteration
                BRp DivideBy2           ; once R4 is nz, we have an answer(if not whole number, round up)
                BRz WholeNum            ; check if the number has a remainder if not(zero) do nothing, else(neg) round 1
                ADD R3, R3, #1          ; round up by one (if not whole number)
WholeNum        STR R3, R5, #0          ; store midOffset to stack
                
                LDR R1, R5, #5          ; re-load loAddress into R1
                ADD R4, R1, R3          ; calculate midAddress (loAddress + midOffset)
                STR R4, R5, #-1         ; store midAddress to stack
                
                ;;;;;;;;;;;;;;;;;;;;;;;;; recursive case
                
                LDR R4, R4, #0          ; load value at midAddress
                NOT R4, R4              ; 2's comp of R4
                ADD R4, R4, #1          ;
                ADD R4, R4, R2          ; subtract needle by value in midAddress to find if its equal, greater, or less
                
                BRz ValEqual
                BRn ValLess
                BRp ValGreat                
ValEqual        
                LDR R0, R5, #-1         ; load midAddress into R0
                STR R0, R5, #3          ; found the element in the list, store in return value on stack and return
                BRnzp End
ValLess
                LDR R3, R5, #6          ; load hiAddress from stack
                LDR R1, R5, #-1         ; load midAddress from stack
                ADD R1, R1, #1          ; ADD 1 to midAddress
                BRnzp Recurse           ; Push hiAddress, midAddress+1, element respectivly
ValGreat
                LDR R3, R5, #0          ; load midAddress from stack
                LDR R1, R5, #5          ; load loAddress from stack
                ADD R3, R3, #-1         ; subtract one from midAddress
                BRnzp Recurse           ; Push midAddress-1, loAddress, element respectivly
Recurse
                PUSH R3                 ; push param for hiAddress, loAddress, and the element 
                PUSH R1                 ;
                PUSH R2                 ;
                JSR BinarySearch        ; Recurse using the new pushed parameters on the stack
                POP R0
                ADD R6,R6,#3
                BRnzp End
                
                ;;;;;;;;;;;;;;;;;;;;;;;;; base case
BaseCase        
                .ZERO R0
End
                ADD R6, R6, #2          ; remove 2 local variables from stack
                STR R0, R5, #3          ; store answer in return value
                POP R5                  ; restore previous frame pointer
                POP R7                  ; restore return address
                RET

; End of the function definition
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                .END
