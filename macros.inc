;
; Macro Definitions
;
; ==========================================================================
;
;  Copyright 2006 Thorsten Klose (tk@midibox.org)
;  Licensed for personal non-commercial use only.
;  All other rights reserved.
; 
; ==========================================================================

IFSET	MACRO	reg, bit, instr
	btfsc	reg, bit
	instr
	ENDM


IFCLR	MACRO	reg, bit, instr
	btfss	reg, bit
	instr
	ENDM

BIFSET	MACRO	reg, bit, reg_a, instr
	btfsc	reg, bit, reg_a
	instr
	ENDM


BIFCLR	MACRO	reg, bit, reg_a, instr
	btfss	reg, bit, reg_a
	instr
	ENDM

;; ==========================================================================

IFNEQ   MACRO   reg, reg_a, instr
        cpfseq  reg, reg_a
        instr
        ENDM

IFLEQ   MACRO   reg, reg_a, instr
        cpfsgt  reg, reg_a
        instr
        ENDM

IFGEQ   MACRO   reg, reg_a, instr
        cpfslt  reg, reg_a
        instr
        ENDM

	
;; ==========================================================================

IRQ_DISABLE MACRO
        bcf     INTCON, GIE
        ENDM

IRQ_ENABLE MACRO
        bsf     INTCON, GIE
        ENDM

;; ==========================================================================

TABLE_ADDR_FULL MACRO addr
        movlw   LOW(addr)
        movwf   TBLPTRL
        movlw   HIGH(addr)
        movwf   TBLPTRH
        movlw   (((addr) >> 16) & 0xff) ; store upper Byte
        movwf   TBLPTRU
        ENDM
        
TABLE_ADDR MACRO addr
        movlw   LOW(addr)
        movwf   TBLPTRL
        movlw   HIGH(addr)
        movwf   TBLPTRH
        ENDM

TABLE_ADD_W MACRO
	addwf	TBLPTRL, F
	movlw	0x00
	addwfc	TBLPTRH, F
        ENDM

;; ==========================================================================

JUMPTABLE_2BYTES MACRO max_value
	addlw	-max_value	; ensure that jump index is not greater than (max_value-1)
	skpnc
	movlw	-max_value
	addlw	max_value
	call	MIOS_HLP_GetIndex_2bytes
	ENDM

JUMPTABLE_2BYTES_UNSECURE MACRO
	call	MIOS_HLP_GetIndex_2bytes
	ENDM

JUMPTABLE_4BYTES MACRO max_value
	addlw	-max_value	; ensure that jump index is not greater than (max_value-1)
	skpnc
	return
	addlw	max_value
	call	MIOS_HLP_GetIndex_4bytes
	ENDM

JUMPTABLE_4BYTES_UNSECURE MACRO
	call	MIOS_HLP_GetIndex_4bytes
	ENDM

;; ==========================================================================

TWOBYTE_ENTRY MACRO low_byte, high_byte
        dw      (high_byte << 8) | (low_byte)
        ENDM

;; ==========================================================================

#define skpnz	btfsc	STATUS, Z 
#define skpz	btfss	STATUS, Z 
#define skpndc	btfsc	STATUS, DC 
#define skpdc	btfss	STATUS, DC
#define skpnc	btfsc	STATUS, C
#define skpc	btfss	STATUS, C
#define clrc	bcf	STATUS, C
#define setc	bsf	STATUS, C
#define clrz	bcf	STATUS, Z
#define setz	bsf	STATUS, Z
#define rrf	rrcf	
#define rlf	rlcf

rgoto   MACRO   label
        bra     label
        ENDM

SET_BSR MACRO   reg
        movlb   HIGH(reg)
        ENDM

;; ==========================================================================

FONT_ENTRY MACRO width, height, x0, char_offset
	dw	((height) << 8) | (width), ((char_offset) << 8) | (x0)
	ENDM

;; ==========================================================================

STRING MACRO length, pos, str
	da	((length) << 8) | (pos), str
	ENDM

;; ==========================================================================
