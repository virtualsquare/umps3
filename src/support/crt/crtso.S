/*
 * uMPS - A general purpose computer system simulator
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
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

#include <umps/regdef.h>
#include <umps/arch.h>
#include <umps/aout.h>
#include <umps/bios_defs.h>

#define CORE_TEXT_VADDR 0x20001000
#define KERNELSTACKSIZE 0x00001000


	.text
	.align	2

	.globl	__start
	.type	__start, @function
	.ent	__start
	.extern	main
__start:
	.frame	$sp, 16, $ra
	.mask	0x00000000, 0
	.fmask	0x00000000, 0

	/* computes stack bottom (end of first page of RAM)
	   using $k0 and $k1 (k0 and k1) */
	lw	$k0, BUS_REG_RAM_BASE
	li	$k1, KERNELSTACKSIZE
	addu	$k0, $k0, $k1
	addiu	$sp, $k0, -8

	/* Initialize $gp */
	lw	$gp, CORE_TEXT_VADDR + (AOUT_HE_GP_VALUE << 2)

	addiu	$sp, $sp, -16
	jal	main
	addiu	$sp, $sp, 16

	.set	noreorder
	.set	nomacro
	li 	$a0, BIOS_SRV_HALT
	nop
	break
	nop
	.set	reorder
	.set	macro

	.end	__start
	.size	__start, .-__start
