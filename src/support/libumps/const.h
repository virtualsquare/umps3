/*
 * uMPS - A general purpose computer system simulator
 *
 * Copyright (C) 2020 Mikey Goldweber
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

/****************************************************************************
 *
 * This header file contains utility constants & macro definitions.
 *
 ****************************************************************************/

#ifndef UMPS_CONSTS_H
#define UMPS_CONSTS_H

/* Hardware & software constants */
#define PAGESIZE        4096    /* page size in bytes */
#define WORDLEN         4       /* word size in bytes */


/* timer, timescale, TOD-LO and other bus regs */
#define RAMBASEADDR     0x10000000
#define TODLOADDR       0x1000001C
#define INTERVALTMR     0x10000020
#define TIMESCALEADDR   0x10000024

/* utility constants */
#define TRUE            1
#define FALSE           0
#define HIDDEN          static
#define EOS             '\0'

#define NULL            ((void *)0)

/* device interrupts */
#define DISKINT         3
#define FLASHINT        4
#define NETWINT         5
#define PRNTINT         6
#define TERMINT         7

#define DEVINTNUM       5       /* interrupt lines used by devices */
#define DEVPERINT       8       /* devices per interrupt line */
#define DEVREGLEN       4       /* device register field length in bytes, and regs per dev */
#define DEVREGSIZE      16      /* device register size in bytes */

/* device register field number for non-terminal devices */
#define STATUS          0
#define COMMAND         1
#define DATA0           2
#define DATA1           3

/* device register field number for terminal devices */
#define RECVSTATUS      0
#define RECVCOMMAND     1
#define TRANSTATUS      2
#define TRANCOMMAND     3

/* device common STATUS codes */
#define UNINSTALLED     0
#define READY           1
#define BUSY            3

/* device common COMMAND codes */
#define RESET           0
#define ACK             1

/* Memory related constants */
#define KSEG0           0x00000000
#define KSEG1           0x20000000
#define KSEG2           0x40000000
#define KUSEG           0x80000000
#define RAMSTART        0x20000000
#define BIOSDATAPAGE    0x0FFFF000

/* Useful Operations */
#define MIN(A,B)        ((A) < (B) ? A : B)
#define MAX(A,B)        ((A) < (B) ? B : A)
#define ALIGNED(A)      (((unsigned)A & 0x3) == 0)

/* Macro to load the Interval Timer */
#define LDIT(T)         ((*((cpu_t *) INTERVALTMR)) = (T) *(*((cpu_t *) TIMESCALEADDR)))

/* Macro to read the TOD clock */
#define STCK(T)         ((T) = ((*((cpu_t *) TODLOADDR)) / (*((cpu_t *) TIMESCALEADDR))))

#endif /* !defined(UMPS_CONST_H) */
