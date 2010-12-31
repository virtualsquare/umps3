/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * uMPS - A general purpose computer system simulator
 *
 * Copyright (C) 2010 Tomislav Jonjic
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

#ifndef UMPS_MACHINE_CONFIG_H
#define UMPS_MACHINE_CONFIG_H

#include <string>

#include "umps/arch.h"
#include "umps/types.h"

enum ROMType {
    ROM_TYPE_BOOT,
    ROM_TYPE_BIOS,
    ROM_TYPE_CORE,
    ROM_TYPE_STAB,
    N_ROM_TYPES
};

class MachineConfig {
public:
    static const Word MIN_RAM = 8;
    static const Word MAX_RAM = 512;
    static const Word DEFAUlT_RAM_SIZE = 64;

    static const unsigned int MIN_CPUS = 1;
    static const unsigned int MAX_CPUS = 8;
    static const unsigned int DEFAULT_NUM_CPUS = 1;

    static const unsigned int MIN_CLOCK_RATE = 1;
    static const unsigned int MAX_CLOCK_RATE = 99;
    static const unsigned int DEFAULT_CLOCK_RATE = 1;

    static const Word MIN_TLB = 4;
    static const Word MAX_TLB = 64;
    static const Word DEFAULT_TLB_SIZE = 16;

    static const Word MIN_ASID = 0;
    static const Word MAX_ASID = 64;

    static MachineConfig* LoadFromFile(const std::string& fileName, std::string& error);
    static MachineConfig* Create(const std::string& fileName);

    const std::string& getFileName() const { return fileName; }

    void Save();

    bool Validate(std::string* error) const;

    void setLoadCoreEnabled(bool setting) { loadCoreFile = setting; }
    bool isLoadCoreEnabled() const { return loadCoreFile; }

    void setRamSize(Word size);
    Word getRamSize() const { return ramSize; }

    void setNumProcessors(unsigned int value);
    unsigned int getNumProcessors() const { return cpus; }

    void setClockRate(unsigned int value);
    unsigned int getClockRate() const { return clockRate; }

    void setTLBSize(Word size);
    Word getTLBSize() const { return tlbSize; }

    void setROM(ROMType type, const std::string& fileName);
    const std::string& getROM(ROMType type) const;

    void setSymbolTableASID(Word asid);
    Word getSymbolTableASID() const { return symbolTableASID; }

    unsigned int getDeviceType(unsigned int il, unsigned int devNo) const;
    bool getDeviceEnabled(unsigned int il, unsigned int devNo) const;
    void setDeviceEnabled(unsigned int il, unsigned int devNo, bool setting);
    void setDeviceFile(unsigned int il, unsigned int devNo, const std::string& fileName);
    const std::string& getDeviceFile(unsigned int il, unsigned int devNo) const;

private:
    MachineConfig(const std::string& fileName);

    void resetToFactorySettings();
    bool validFileMagic(Word tag, const char* fName);

    std::string fileName;

    bool loadCoreFile;

    Word ramSize;
    unsigned int cpus;
    unsigned int clockRate;
    Word tlbSize;

    std::string romFiles[N_ROM_TYPES];
    Word symbolTableASID;

    std::string devFiles[N_EXT_IL][N_DEV_PER_IL];
    bool devEnabled[N_EXT_IL][N_DEV_PER_IL];

    static const char* const deviceKeyPrefix[N_EXT_IL];
};

#endif // UMPS_MACHINE_CONFIG_H