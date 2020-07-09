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

#ifndef BIOS_DEFS_H
#define BIOS_DEFS_H

/*
 * BIOS services, invoked via break traps
 * FIXME: Are all of these safe to use (abuse?) as break codes?
 */
#define BIOS_SRV_LDCXT	    0
#define BIOS_SRV_LDST	    1
#define BIOS_SRV_PANIC	    2
#define BIOS_SRV_HALT	    3

/*
 * We use the BIOS-reserved registers as pointers to BIOS related data
 * structures (the exception vector and the PC/SP exception handlers)
 */
#define BIOS_EXCPT_VECT_BASE	CPUCTL_BIOS_RES_0
#define BIOS_PC_AREA_BASE	CPUCTL_BIOS_RES_1

/* BIOS Data Page base address */
#define BIOS_DATA_PAGE_BASE	    0x0FFFF000
#define BIOS_EXEC_HANDLERS_ADDRS    0x0FFFF900


#endif /* BIOS_DEFS_H */
