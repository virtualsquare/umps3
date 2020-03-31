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

#ifndef UMPS_MP_CONTROLLER_H
#define UMPS_MP_CONTROLLER_H

#include "umps/types.h"

class MachineConfig;
class Machine;
class SystemBus;
class Processor;

class MPController {
public:
MPController(const MachineConfig* config, Machine* machine);

Word Read(Word addr, const Processor* cpu) const;
void Write(Word addr, Word data, const Processor* cpu);

private:
static const unsigned int kCpuResetDelay = 50;
static const unsigned int kCpuHaltDelay = 50;
static const unsigned int kPoweroffDelay = 1000;

const MachineConfig* const config;
Machine* const machine;

Word bootPC;
Word bootSP;
};

#endif // UMPS_MP_CONTROLLER_H
