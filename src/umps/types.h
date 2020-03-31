/*
 * uMPS - A general purpose computer system simulator
 *
 * Copyright (C) 2004 Mauro Morsiani
 * Copyright (C) 2011 Tomislav Jonjic
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
 * This header file contains some type definitions needed.
 *
 * "Word" (unsigned word) and "SWord" (signed word) represent MIPS
 * registers, and were introduced to allow a better debugging; by using them
 * appropriately, it was possible to detect where possibly incorrect
 * manipulation of register values and format were done.
 *
 ****************************************************************************/

#ifndef UMPS_TYPES_H
#define UMPS_TYPES_H

#include "base/basic_types.h"

typedef uint32_t Word;

typedef int32_t SWord;

#endif // UMPS_TYPES_H
