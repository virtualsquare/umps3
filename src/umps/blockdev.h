/*
 * uMPS - A general purpose computer system simulator
 *
 * Copyright (C) 2004 Mauro Morsiani
 * Copyright (C) 2020 Mattia Biondi
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

// This class implements the block devices' 4096 byte sectors/flash devices blocks.
// Each object contains a single buffer; methods are provided to read/write
// these blocks from/to real files and to access to the word-sized contents.
// This class is provided primarily to make DMA transfer easier and to
// standardize block handling.

class Block
{
public:

// This method returns an empty (unitialized) 4096 byte Block
	Block();

// Object deletion is done by default handler

// This method fills a Block with file contents starting at "offset"
// bytes from file start, as computed by caller.
// Returns TRUE if read does not succeed, FALSE otherwise
	bool ReadBlock(FILE * blkFile, SWord offset);

// This method writes Block contents in a file, starting at "offset"
// bytes from file start, as computed by caller. Returns TRUE if
// write does not succeed, FALSE otherwise
	bool WriteBlock(FILE * blkFile, SWord offset);

// This method returns the Word contained in the Block at ofs (Word
// items) offset, range [0..BLOCKSIZE - 1]. Warning: in-bounds
// checking is leaved to caller
	Word getWord(unsigned int ofs);

// This method fills with "value" the Word contained in the Block at
// ofs (Word items) offset, range [0..BLOCKSIZE - 1]. Warning:
// in-bounds checking is leaved to caller
	void setWord(unsigned int ofs, Word value);

private:
// Block contents
	Word blkBuf[BLOCKSIZE];
};


/****************************************************************************/


// This class contains the simulated disk drive geometry and performance
// parameters. They are filled by mkdev utility and used by DiskDevice class
// for detailed disk performance simulation.
// Position, min, max and default values, where applicable, are defined in
// h/blockdev.h header file.
//
// Parameters are:
// number of cylinders;
// number of heads;
// number of sectors per track;
// disk rotation time in microseconds;
// average track-to-track seek time in microseconds;
// data % of sector (to compute inter-sector gap)

class DiskParams
{
public:

// This method reads disk parameters from file header, builds a
// DiskParams object, and returns the disk sectors start offset:
// this allows to modify the parameters' size without changing the
// caller.  If fileOfs returned is 0, something has gone wrong; file
// is rewound after use
	DiskParams(FILE * diskFile, SWord * fileOfs);

// Object deletion is done by default handler

// These methods return the corresponding geometry or performance
// figure
	unsigned int getCylNum(void);
	unsigned int getHeadNum(void);
	unsigned int getSectNum(void);
	unsigned int getRotTime(void);
	unsigned int getSeekTime(void);
	unsigned int getDataSect(void);

private:
// parameter buffer
	unsigned int parms[DISKPNUM];
};


// This class contains the simulated flash device geometry and performance
// parameters. They are filled by mkdev utility and used by FlashDevice class
// for detailed flash device performance simulation.
// Position, min, max and default values, where applicable, are defined in
// h/blockdev.h header file.
//
// Parameters are:
// number of blocks;
// average read/write time in microseconds;

class FlashParams
{
public:

// This method reads flash device parameters from file header, builds a
// FlashParams object, and returns the flash device blocks start offset:
// this allows to modify the parameters' size without changing the
// caller. If fileOfs returned is 0, something has gone wrong; file
// is rewound after use
	FlashParams(FILE * flashFile, SWord * fileOfs);

// Object deletion is done by default handler

// These methods return the corresponding geometry or performance
// figure

	unsigned int getBlocksNum(void);
	unsigned int getWTime(void);

private:
// parameter buffer
	unsigned int parms[FLASHPNUM];
};
