/*
 * uMPS - A general purpose computer system simulator
 *
 * Copyright (C) 2004 Mauro Morsiani
 * Copyright (C) 2011 Tomislav Jonjic
 * Copyright (C) 2020 Mattia Biondi, Mikey Goldweber
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "umps/regdef.h"
#include "umps/arch.h"
#include "umps/cp0.h"
#include "umps/bios_defs.h"

/* Constants */

#define ASIDSTEP    0x00000040
#define VPNMASK     0xFFFFF000
#define VECTSIZE    140

/* NOP padding: 30 nops - string length (32 bytes) */
#define GENEXC_PADDING    (30 * 4) - 32
#define ENDSTRADDR        0x00000008
#define PANICSTRADDR      (ENDSTRADDR + 16)

/* Terminal device related stuff */
#define TERM0COMMAND      DEV_REG_ADDR(IL_TERMINAL, 0) + 0xC
#define BUSYCODE          3
#define BYTELEN           8
#define PRINTCHR          2

#define CAUSENEGMASK      0xFFFFFF83
#define KUPSTATUSMASK     0x00000008
#define SAFESTATUSMASK    0xFFFFFFFC

	/*
	 * Code start
	 */

	.text
	.align	2
	.globl	bios
	.type	bios,@function
	.ent	bios
bios:
	.frame	$fp,0,$k1
	.mask	0x00000000,0
	.fmask	0x00000000,0

	/*
	 * Tell gas not to use $at in pseudoop expansions
	 */
	.set noat

	/*
	 * 0x00000000 address
	 * This is the entry point for UTLB type exceptions.
	 */
	.set noreorder
	.set nomacro
	b	LUTLBHandler
	nop

EndStr:
	.asciiz	"System halted \n"
PanicStr:
	.asciiz "kernel panic()\n"

	.space	GENEXC_PADDING

	/*
	 * 0x00000080 address
	 * This is the entry point for general ("other", non-TLB) exceptions.
	 */
	b	LEXCHandler
	nop

	.space	0x80 - 0x8
	/*
	 * 0x00000100 address
	 * Secondary processor startup routine
	 */
	b	LInitSecondaryProcessor
	nop

	/*
	 * 0x00000108: panic()
	 * Print a message on terminal 0 and loop forever
	 */

	.set	reorder
	.set	macro

LPanic:
	li	$a0, PANICSTRADDR - 1

LTermOp:
	li 	$a3, TERM0COMMAND
	li 	$t0, BUSYCODE

LWaitForReady:
	lw 	$a2, -4($a3)
	beq	$a2, $t0, LWaitForReady

LPrintLoop:
	addiu	$a0, 1
	lbu	$a1, 0($a0)

	# char 0 ends the string
	beq	$0, $a1, LInfinite

	#prepares PRINTCHAR command
	sll 	$a1, BYTELEN
	addi	$a1, PRINTCHR
	sw	$a1, 0($a3)

	b	LWaitForReady

LInfinite:
	b	LInfinite

LHalt:
	# this call prints a message on terminal 0 and loops forever
	li	$a0, ENDSTRADDR - 1
	b 	LTermOp

/*
 * Get a cpu up and runing: initialize BIOS related structures and
 * load the supplied processor state.
 */
LInitSecondaryProcessor:
	/* Set up a convenient pointer to some scratch RAM space */
	li	$t0, BIOS_CPU_SCRATCH_RAM_SIZE
	mfc0	$t1, $CP0_PRID
	mult	$t0, $t1
	mflo	$t0
	li	$t1, BIOS_LEGACY_SCRATCH_BASE
	subu	$t0, $t1, $t0

	li	$t1, BIOS_SCRATCH_BASE
	sw	$t0, 0($t1)

	/* Initialize ptr to new/old areas */
	lw	$t1, 8($t0)
	li	$t2, BIOS_EXCVEC_BASE
	sw	$t1, 0($t2)

	/* Load a new state */
	lw	$k0, 4($t0)
	b	LLoadStart

/*
 * Handle TLBL/TLBS refill misses
 * $k1 is address of kernel branch address
 */
LUTLBHandler:
	li  $k1, KERNEL_UTLB_ADDR
	b   LSOldLNewArea

/*
 * General exception handler
 *
 * k0 and k1 registers are always available (never have live
 * values outside BIOS)
 */
LEXCHandler:
	/* Copy Cause.ExcCode to k0 and dispatch accordingly */
	mfc0	$k0, $CP0_Cause
	andi	$k0, $k0, CAUSE_EXCCODE_MASK
	srl	$k0, CAUSE_EXCCODE_BIT

	/* cause 9 is BREAK */
	addi  $k0, -9
	beq   $k0, $0, LBreakHandler

	/* Handle all other exception types the same */

	/* If EPC address is in BIOS area, something in kernel has
	 * gone horribly wrong: eg. BIOS running with int unmasked (a big
	 * bug for BIOS).
	 */
	mfc0	$k0, $CP0_EPC
	li	$k1, BIOS_LEGACY_EXCVEC_BASE
	subu	$k0, $k0, $k1
	bltz	$k0, LPanic

	/* Else: save processor state into BIOS data RAM space and pass
	 * along handling to the kernel
	 */
	li  $k1, KERNEL_EXCPT_ADDR
	b	LSOldLNewArea

LBreakHandler:
	/* If EPC address is in BIOS area, something in kernel or in BIOS
	 * has gone horribly wrong (a BIOS bug probably). */
	mfc0	$k0, $CP0_EPC
	li	$k1, BIOS_LEGACY_EXCVEC_BASE
	subu	$k0, $k0, $k1
	bltz	$k0, LPanic

	/*
	 * A BIOS service routine is requested:
	 * look into $a0 register for identification.
	 */

	move	$k1, $a0

	/* any BREAK may be executed only in kernel mode
	 * kernel mode of caller is set when KUP bit in STATUS mask is 0
	 */
	mfc0	$k0, $CP0_Status
	andi	$k0, $k0, KUPSTATUSMASK
	beq	  $k0, $0, LisKernel

	/* If in user mode, pass along to kernel */
	li  $k1, KERNEL_EXCPT_ADDR
	b	LSOldLNewArea

LisKernel:
	/* 0  is FORK(STATUS, EntryHI, PC, CAUSE) */
	beq 	$0, $k1, LFORK

	addi    $k1, -1

	/* 1 is LDST */
	beq 	$0, $k1, LLDST

	addi    $k1, -1

	/* 2 is PANIC routine */
	beq	$0, $k1, LPanic

	addi	$k1, -1

	/* 3 is HALT routine */
	beq     $0, $k1, LHalt

	/* any other break is passed up to SYS handler */
	li  $k1, KERNEL_EXCPT_ADDR
	b	LSOldLNewArea

LFORK:
	# $v0 is ENTRYHI, $a1 is STATUS, $a2 is new PC, $a3 is CAUSE

	# EntryHI loading
	mtc0	$v0, $CP0_EntryHi

	# STATUS preparation
	move 	$k1, $a1
	# this for BIOS safety: no KU or IE bits on
	li	$k0, SAFESTATUSMASK
	and	$k1, $k1, $k0

	# STATUS loading
	mtc0	$k1, $CP0_Status

	# CAUSE loading
	mtc0 	$a3, $CP0_Cause

	# get new PC and jump
	move 	$k1, $a2

	.set noreorder
	.set nomacro
	jr	$k1
	rfe
	.set reorder
	.set macro


LLDST:
	# this means load from physical address in $a1
	move	$k0, $a1
	b	LLoadStart


/*
 * Save cpu (exception) state into BIOS data RAM space, load PC and SP
 *  and pass along handling to the kernel (address in $k1)
 */
LSOldLNewArea:
	li  $k0, BIOS_DATA_BASE
LSave:
	sw	$1, 16($k0)
	sw	$v0, 20($k0)
	sw	$v1, 24($k0)
	sw 	$a0, 28($k0)
	sw	$a1, 32($k0)
	sw	$a2, 36($k0)
	sw	$a3, 40($k0)
	sw	$t0, 44($k0)
	sw	$t1, 48($k0)
	sw	$t2, 52($k0)
	sw	$t3, 56($k0)
	sw	$t4, 60($k0)
	sw	$t5, 64($k0)
	sw	$t6, 68($k0)
	sw	$t7, 72($k0)
	sw	$s0, 76($k0)
	sw	$s1, 80($k0)
	sw	$s2, 84($k0)
	sw	$s3, 88($k0)
	sw	$s4, 92($k0)
	sw	$s5, 96($k0)
	sw	$s6, 100($k0)
	sw	$s7, 104($k0)
	sw	$t8, 108($k0)
	sw	$t9, 112($k0)

	/* $k0 and $k1 are not saved */

	sw	$gp, 116($k0)
	sw	$sp, 120($k0)
	sw	$fp, 124($k0)
	sw	$ra, 128($k0)

	/* move kernel branch-to address to $a0 */
	add   $a0, $0, $k1

	mfhi	$k1
	sw	$k1, 132($k0)
	mflo	$k1
	sw	$k1, 136($k0)
	/* all processor registers saved */

	/* gets EntryHI and stores it */
	mfc0	$k1, $CP0_EntryHi
	sw	$k1, 0($k0)

	/* gets CAUSE register and stores it */
	mfc0    $k1, $CP0_Cause
	sw      $k1, 4($k0)

	/* and now save STATUS and EPC registers */
	mfc0	$k1, $CP0_Status
	sw	$k1, 8($k0)
	mfc0    $k1, $CP0_EPC
	sw      $k1, 12($k0)

    /* All registers saved. Load SP with RAMTOP */
	/* get RAMTOP */
	li 	$k0, BUS_REG_RAM_BASE
	lw 	$k0, 0($k0)
	li 	$k1, BUS_REG_RAM_SIZE
	lw 	$k1, 0($k1)
	add	$sp, $k0, $k1

	/* Restore $a0 and Pass Control along to kernel */
	add $k1, $0, $a0
	li  $k0, BIOS_DATA_BASE
	lw  $a0, 28($k0)
	lw  $k0, 0($k1)
	jr  $k0
	nop

/*
 * Load CPU/CP0 registers from (state_t*) $k0
 */
LLoadStart:
	lw	$1, 16($k0)
	lw	$v0, 20($k0)
	lw	$v1, 24($k0)
	lw 	$a0, 28($k0)
	lw	$a1, 32($k0)
	lw	$a2, 36($k0)
	lw	$a3, 40($k0)
	lw	$t0, 44($k0)
	lw	$t1, 48($k0)
	lw	$t2, 52($k0)
	lw	$t3, 56($k0)
	lw	$t4, 60($k0)
	lw	$t5, 64($k0)
	lw	$t6, 68($k0)
	lw	$t7, 72($k0)
	lw	$s0, 76($k0)
	lw	$s1, 80($k0)
	lw	$s2, 84($k0)
	lw	$s3, 88($k0)
	lw	$s4, 92($k0)
	lw	$s5, 96($k0)
	lw	$s6, 100($k0)
	lw	$s7, 104($k0)
	lw	$t8, 108($k0)
	lw	$t9, 112($k0)

	/* $k0 and $k1 are not saved so they are not loaded too */

	lw	$gp, 116($k0)
	lw	$sp, 120($k0)
	lw	$fp, 124($k0)
	lw	$ra, 128($k0)

	lw	$k1, 132($k0)
	mthi	$k1
	lw	$k1, 136($k0)
	mtlo	$k1

	/* all processor registers loaded (almost) */

	/* storing new EntryHI into CP0 register */
	lw	$k1, 0($k0)
	mtc0	$k1, $CP0_EntryHi

	/* storing new CAUSE into CP0 register */
	lw	$k1, 4($k0)
	mtc0	$k1, $CP0_Cause

	/* now load STATUS register */
	lw	$k1, 8($k0)
	/* This is for avoiding trouble if STATUS has (erroneously)
	 * set bit 0/1. It would cause an immediate EXC trap or expose
	 * BIOS to interrupts. */
	srl 	$k1, 2
	sll	$k1, 2
	mtc0	$k1, $CP0_Status

	lw	$k1, 12($k0)

	/* load new PC and jump */
	.set noreorder
	.set nomacro
	jr	$k1
	rfe
	.set reorder
	.set macro

	.end	bios
	.size	bios, . - bios
