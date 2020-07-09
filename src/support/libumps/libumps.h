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

/*
 * External declarations for uMPS library module.
 */

#ifndef UMPS_LIBUMPS_H
#define UMPS_LIBUMPS_H

/*
 * "Forward declaration" hack!!
 * Many functions in this module accept a pointer to a cpu state
 * (STATE_PTR) structure. We cannot just forward declare that because
 * state_t was commonly defined by clients as an anonymous struct
 * typedef.
 */
#define STATE_PTR void*

/* Functions valid in user mode
 */


/* This function cause a system call trap
 */

extern unsigned int SYSCALL(unsigned int number, unsigned int arg1, unsigned int arg2, unsigned int arg3);


/* All these functions access CP0 registers.
 * Access to CP0 registers is always possible in kernel mode, or in user
 * mode with CPU 0 bit _set_ in STATUS register
 */

extern unsigned int getINDEX(void);

extern unsigned int getRANDOM(void);

extern unsigned int getENTRYLO(void);

extern unsigned int getBADVADDR(void);

extern unsigned int getENTRYHI(void);

extern unsigned int getSTATUS(void);

extern unsigned int getCAUSE(void);

extern unsigned int getEPC(void);

extern unsigned int getPRID(void);

extern unsigned int getTIMER(void);


/* Only some of CP0 register are R/W: handling requires care.
 * All functions return the value in register after write
 */

extern unsigned int setINDEX(unsigned int index);

extern unsigned int setENTRYLO(unsigned int entry);

extern unsigned int setENTRYHI(unsigned int entry);

extern unsigned int setSTATUS(unsigned int entry);

extern unsigned int setCAUSE(unsigned int cause);

extern unsigned int setTIMER(unsigned int timer);


/* these functions produce a program trap if executed in user mode
 * without CPU0 bit _set_
 */

extern void TLBWR(void);

extern void TLBWI(void);

extern void TLBP(void);

extern void TLBR(void);

extern void TLBCLR(void);

extern void WAIT(void);


/* This function allows a current process to change its operating mode,
 * turning on/off interrupt masks, turning on user mode, and at the same time
 * changing the location of execution.
 * It is available only in kernel mode, thru a BIOS routine
 * (otherwise it causes a break).
 * It updates processor status, PC and stack pointer _completely_,
 * in one atomic operation.
 * It has no meaningful return value.
 */

extern unsigned int LDCXT (unsigned int stackPtr, unsigned int status, unsigned int pc);


/* This function may be called from kernel or from user mode with CPU 0
 * STATUS bit _on_: otherwise, it will cause a trap
 */

/* This function stores processor state to memory. It intentionally leaves
 * the PC field set to 0; putting a meaningful value there is programmer's
 * task.
 * Return value is PC value for the instruction immediately following
 * the call.
 * This too is NOT an atomic operation: the processor state is saved
 * register by register to memory. So, this call is interruptible (in a
 * clean way) or cause a trap (for example, an memory access error if
 * pointer is not correctly set).
 * If called from user state, it will trap ONLY if CPU 0 bit of STATUS CP0
 * register is NOT set, and only when access to CP0 register (STATUS, ENTRYHI,
 * CAUSE) is requested (if no other errors intervene).
 * However, trying it does not harm system security a bit.
 */

extern unsigned int STST(STATE_PTR statep);


/* This function may be used to restart an interrupted/blocked process,
 * reloading it from a physical address passed as argument.
 * It is available only in kernel mode, thru a BIOS routine
 * (otherwise it causes a break).
 * It updates processor status _completely_, in one atomic operation.
 * It has no meaningful return value: $2 (v0) register is used for
 * BIOS call, but it is reloaded too.
 * Remember that it is programmer's task to increment PC where
 * needed (e.g. syscall handling)
 */

extern unsigned int LDST(STATE_PTR statep);


/* This function stops the system printing a warning message on terminal 0
 */

extern void PANIC(void);


/* This function halts the system printing a regular shutdown message on
 * terminal 0
 */

extern void HALT(void);

extern void INITCPU(unsigned int cpuid, STATE_PTR start_state);

extern int CAS(volatile unsigned int *atomic, unsigned int oldval, unsigned int newval);

#endif /* !defined(UMPS_LIBUMPS_H) */
