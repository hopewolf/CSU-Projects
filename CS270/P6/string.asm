; Begin reserved section: do not change ANYTHING in reserved section!
; The ONLY exception to this is that you MAY change the .FILL values for
; Option, Value1 and Value2. This makes it easy to initialize the values in the
; program, so that you do not need to continually re-enter them. This
; makes debugging easier as you need only change your code and re-assemble.
; Your test value(s) will already be set.
;------------------------------------------------------------------------------
; Author: Fritz Sieker
;
; Description: Tests the implementation of a simple string library and I/O
;

            .ORIG x3000
            BR Main
Functions
            .FILL Test_pack         ; (option 0)
            .FILL Test_unpack       ; (option 1)
            .FILL Test_printCC      ; (option 2)
            .FILL Test_strlen       ; (option 3)
            .FILL Test_strcpy       ; (option 4)
            .FILL Test_strcat       ; (option 5)
            .FILL Test_strcmp       ; (option 6)

; Parameters and return values for all functions
Option      .FILL 0                 ; which function to call
String1     .FILL x4000             ; default location of 1st string
String2     .FILL x4100             ; default location of 2nd string
Result      .BLKW 1                 ; space to store result
Value1      .FILL 0                 ; used for testing pack/unpack
Value2      .FILL 0                 ; used for testing pack/unpack
lowerMask   .FILL 0x00FF            ; mask for lower 8 bits
upperMask   .FILL 0xFF00            ; mask for upper 8 bits

Main        LEA R0,Functions        ; get base of jump table
            LD  R1,Option           ; get option to use, no error checking
            ADD R0,R0,R1            ; add index of array
            LDR R0,R0,#0            ; get address to test
            JMP R0                  ; execute test

Test_pack   
            LD R0,Value1            ; load first character
            LD R1,Value2            ; load second character
            JSR pack                ; pack characters
            ST R0,Result            ; save packed result
End_pack    HALT                    ; done - examine Result

Test_unpack 
            LD R0,Value1            ; value to unpack
            JSR unpack              ; test unpack
            ST R0,Value1            ; save upper 8 bits
            ST R1,Value2            ; save lower 8 bits
End_unpack  HALT                    ; done - examine Value1 and Value2

Test_printCC    
            LD R0,Value1            ; get the test value
            .ZERO R1                ; reset condition codes
            JSR printCC             ; print condition code
End_printCC HALT                    ; done - examine output

Test_strlen 
            LD R0,String1           ; load string pointer
            GETS                    ; get string
            LD R0,String1           ; load string pointer
            JSR strlen              ; calculate length
            ST R0,Result            ; save result
End_strlen  HALT                    ; done - examine memory[Result]

Test_strcpy 
            LD R0,String1           ; load string pointer
            GETS                    ; get string
            LD R0,String2           ; R0 is dest
            LD R1,String1           ; R1 is src
            JSR strcpy              ; copy string
            PUTS                    ; print result of strcpy
            NEWLN                   ; add newline
End_strcpy  HALT                    ; done - examine output

Test_strcat 
            LD R0,String1           ; load first pointer
            GETS                    ; get first string
            LD R0,String2           ; load second pointer
            GETS                    ; get second string
            LD R0,String1           ; dest is first string
            LD R1,String2           ; src is second string
            JSR strcat              ; concatenate string
            PUTS                    ; print result of strcat
            NEWLN                   ; add newline
End_strcat  HALT                    ; done - examine output

Test_strcmp 
            LD R0,String1           ; load first pointer
            GETS                    ; get first string
            LD R0,String2           ; load second pointer
            GETS                    ; get second string
            LD R0,String1           ; dest is first string
            LD R1,String2           ; src is second string
            JSR strcmp              ; compare strings
            JSR printCC             ; print result of strcmp
End_strcmp  HALT                    ; done - examine output

;------------------------------------------------------------------------------
; End of reserved section
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; on entry R0 contains first value, R1 contains second value
; on exit  R0 = (R0 << 8) | (R1 & 0xFF)

pack        ; fill in your code, ~11 lines of code
            LD R2, lowerMask        ; R2 = 0x00FF
            AND R1,R1,R2            ; get the lower bits (R1 & 0xFF)
            AND R2,R2,#8            ; R2 = 8 shift counter
MASK
            ADD R0,R0,R0            ; left shift R0 by eight (R0 << 8)
            ADD R2,R2,#-1           ; decrement shift counter
            BRp MASK
            
            NOT R0,R0               ; not R0 to be OR'd
            NOT R1,R1               ; not R1 to be OR'd
            AND R0,R0,R1            ; ADD ~R0,~R1
            NOT R0,R0               ; not the result (R0 << 8) | (R1 & 0xFF)
            
            RET

;------------------------------------------------------------------------------
; on entry R0 contains a value
; on exit  R0 = upper 2 hex values(shifted 8 right), R1 = lower 2 hex values

unpack      ; fill in your code, ~14 lines of code
            LD R2, lowerMask        ; R2 = 0x00FF
            AND R1,R0,R2            ; R1 = lower half of R0
            ST R1, Value2           ; Store Value1 W/ R1 so you can use R1 later
            AND R1,R1,#0            ; set R0 to 0
            LD R2, upperMask        ; R2 = 0xFF00
            AND R0,R0,R2            ; clears the bottom 2 bits
            AND R2,R2,#0
            ADD R2,R2,#8            ; R2 = shift counter
            ADD R3,R3,#1            ; R3 = source mask
            ADD R4,R4,#1            ; R4 = destination mask
ShiftLoop
            ADD R3,R3,R3            ; left shift R3 by eight
            ADD R2,R2,#-1           ; decrement R2 count
            BRp ShiftLoop
            
            ADD R2,R2,#8            ; reset counter to 8
            
MaskShift
            AND R1,R0,R3            ; test bit with destination mask
            BRz Iterate
            ADD R0,R0,R4
Iterate
            ADD R3,R3,R3
            ADD R4,R4,R4
            ADD R2,R2,#-1
            BRz DONE
            BRnzp MaskShift
            
DONE        LD R2, lowerMask
            AND R0, R0, R2
            LD R1,Value2    
            RET

;------------------------------------------------------------------------------
; on entry R0 contains value
; on exit  (see instructions)

StringNEG   .STRINGZ "NEGATIVE\n"   ; output strings
StringZERO  .STRINGZ "ZERO\n"
StringPOS   .STRINGZ "POSITIVE\n"
TempVal     .BLKW 1

printCC     ; fill in your code, ~11 lines of code
            ST R0, TempVal
            ST R7, Result
            ADD R0, R0, #0
            BRn NEG
            BRz ZER
            BRp POS
NEG
            LEA R0, StringNEG
            PUTS
            BRnzp Fin
ZER
            LEA R0, StringZero
            PUTS
            BRnzp Fin
POS
            LEA R0, StringPOS
            PUTS
            BRnzp Fin
            
Fin         LD R0, TempVal
            LD R7, Result
            RET

;------------------------------------------------------------------------------
; size_t strlen(char *s)
; on entry R0 points to string
; on exit  (see instructions)

strlen      ; fill in your code, ~7 lines of code
            .ZERO R1
LenLoop
            LDR R2, R0, #0
            BRz EXIT_strlen         ; if R2=0,then we have found end of string
            ADD R1,R1,#1            ; if not,increase the lenght by 1.
            ADD R0,R0,#1            ; increase the adress by one
            BRnzp LenLoop
EXIT_strlen
            .ZERO R0                
            ADD R0,R0,R1            ; store R1, which contains length and put it in R0
            RET

;------------------------------------------------------------------------------
; char *strcpy(char *dest, char *src)
; on entry R0 points to destination string, R1 points to source string
; on exit  (see instructions)

strcpy      ; fill in your code, ~8 lines of code
                 
            LDR R2,R1,#0            ; load character from R1 into R2
            STR R2,R0,#0            ; store R2 into its propper address in R0
            BRz EXIT_strcpy         ; check if it stored a zero (null terminator)
            ADD R0,R0,#1            ; increment R0 (destination) address by 1
            ADD R1,R1,#1            ; increment R1 (source) address by 1
            BRnzp strcpy
EXIT_strcpy
            LD R0,String2
            RET

;------------------------------------------------------------------------------
; char *strcat(char *dest, char *src)
; on entry R0 points to destination string, R1 points to source string
; on exit  (see instructions)

strcat_RA   .BLKW 1                 ; space for return address
strcat_dest .BLKW 1                 ; space for dest
strcat_src  .BLKW 1                 ; space for src

strcat      ST R7,strcat_RA         ; save return address
            ST R0,strcat_dest       ; save dest
            ST R1,strcat_src        ; save src

            ; fill in your code, ~5 lines of code
            ; HINT: call strlen and strcpy
            
            JSR strlen              ; get the lenght of R0
            ADD R2,R2,R0            ; R2 = R0
            LD R0, strcat_dest      ; R0 = st1
            LD R1, strcat_src       ; R1 = st2
            ADD R0,R0,R2            ; move R0 (st1 pointer) to the end of the string
            JSR strcpy              ; copy R1(st2) into the end of R0(st1)

            LD R0,strcat_dest       ; restore dest
            LD R7,strcat_RA         ; restore return address
            RET

;------------------------------------------------------------------------------
; int strcmp(char *s1, char *s2)
; on entry R0 points to first string, R1 points to second string
; on exit  (see instructions)

strcmp      ; fill in your code, ~12 lines of code
            
            LDR R2,R0,#0            ; R2 = char from R0 (st1)
            LDR R3,R1,#0            ; R3 = char from R1 (st2)
            ADD R4,R3,R2            ; check if both chars are null (both strings at end)
            BRz EXIT_strcmp
            NOT R3, R3
            ADD R3, R3, #1          ; get 2's comp of R3 for subtraction
            ADD R4,R3,R2            ; "subtract" the chars to get the difference
            BRnp EXIT_strcmp        ; if there is a difference, break loop
            ADD R0,R0,#1            ; incriment R0 (st1 pointer) by 1
            ADD R1,R1,#1            ; incriment R1 (st2 pointer) by 1
            BRnzp strcmp            ; unconditional loop
EXIT_strcmp
            .ZERO R0                ; prepare R0
            ADD R0,R0,R4            ; R0 = R4 (R4 is either NEG,POS,ZER)
            
            RET

;------------------------------------------------------------------------------
            .END
