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

/****************************************************************************
 *
 * This module provides some utility classes for block devices handling.
 * They are: Block for block devices sectors/flash device blocks representation;
 * DiskParams for simulated disk devices performance parameters;
 * FlashParams for simulated flash devices performance parameters.
 *
 ****************************************************************************/

#include <stdio.h>

#include <umps/const.h>

#include "umps/types.h"
#include "umps/blockdev_params.h"
#include "umps/utility.h"
#include "umps/blockdev.h"


// This method returns an empty (unitialized) 4096 byte Block
Block::Block()
{
}


// This method fills a Block with file contents starting at "offset"
// bytes from file start, as computed by caller.
// Returns TRUE if read does not succeed, FALSE otherwise
bool Block::ReadBlock(FILE * blkFile, SWord offset)
{
	if (fseek(blkFile, offset, SEEK_SET) == EOF)
		// already at EOF
		return(true);
	else
	if (fread((void *)blkBuf, WORDLEN, BLOCKSIZE, blkFile) != BLOCKSIZE)
		// file too short
		return(true);
	else
		// all OK
		return(false);
}


// This method writes Block contents in a file, starting at "offset" bytes
// from file start, as computed by caller. Returns TRUE if write does not
// succeed, FALSE otherwise
bool Block::WriteBlock(FILE * blkFile, SWord offset)
{
	if (fseek(blkFile, offset, SEEK_SET) == EOF)
		// already at EOF
		return(true);
	else
	if (fwrite((void *)blkBuf, WORDLEN, BLOCKSIZE, blkFile) != BLOCKSIZE)
		// some error occurred
		return(true);
	else
		// all OK
		fflush(blkFile);
	return(false);
}


// This method returns the Word contained in the Block at ofs (Word items)
// offset, range [0..BLOCKSIZE - 1]. Warning: in-bounds checking is leaved
// to caller
Word Block::getWord(unsigned int ofs)
{
	if (ofs < BLOCKSIZE)
		return(blkBuf[ofs]);
	else
		return(MAXWORDVAL);
}


// This method fills with "value" the Word contained in the Block at ofs
// (Word items) offset, range [0..BLOCKSIZE - 1]. Warning: in-bounds
// checking is leaved to caller
void Block::setWord(unsigned int ofs, Word value)
{
	if (ofs < BLOCKSIZE)
		blkBuf[ofs] = value;
}


/****************************************************************************/


// This method reads disk parameters from file header, builds a
// DiskParams object, and returns the disk sectors start offset: this
// allows to modify the parameters' size without changing the caller.
// If fileOfs returned is 0, something has gone wrong; file is rewound after
// use
DiskParams::DiskParams(FILE * diskFile, SWord * fileOfs)
{
	SWord ret;
	unsigned int i;
	Block * blk = new Block();

	rewind(diskFile);
	if (blk->ReadBlock(diskFile, 0) || blk->getWord(0) != DISKFILEID)
		// errors in file reading or disk file magic number missing
		ret = 0;
	else
	{
		// if DISKFILEID is present all parameters should be correct;
		// fills the object
		for (i = 0; i < DISKPNUM; i++)
			parms[i] = (unsigned int) blk->getWord(i + 1);

		rewind(diskFile);
		// sets the disk contents start position
		ret = DISKPNUM + 1;
	}
	delete blk;

	*fileOfs = ret;
}

// All the following methods return the corresponding geometry or
// performance figure

unsigned int DiskParams::getCylNum(void)
{
	return(parms[CYLNUM]);
}

unsigned int DiskParams::getHeadNum(void)
{
	return(parms[HEADNUM]);
}

unsigned int DiskParams::getSectNum(void)
{
	return(parms[SECTNUM]);
}

unsigned int DiskParams::getRotTime(void)
{
	return(parms[ROTTIME]);
}

unsigned int DiskParams::getSeekTime(void)
{
	return(parms[SEEKTIME]);
}

unsigned int DiskParams::getDataSect(void)
{
	return(parms[DATASECT]);
}


// This method reads flash device parameters from file header, builds a
// FlashParams object, and returns the flash device blocks start offset: this
// allows to modify the parameters' size without changing the caller.
// If fileOfs returned is 0, something has gone wrong; file is rewound after
// use
FlashParams::FlashParams(FILE * flashFile, SWord * fileOfs)
{
	SWord ret;
	unsigned int i;
	Block * blk = new Block();

	rewind(flashFile);
	if (blk->ReadBlock(flashFile, 0) || blk->getWord(0) != FLASHFILEID)
		// errors in file reading or flash device file magic number missing
		ret = 0;
	else
	{
		// if FLASHFILEID is present all parameters should be correct;
		// fills the object
		for (i = 0; i < FLASHPNUM; i++)
			parms[i] = (unsigned int) blk->getWord(i + 1);

		rewind(flashFile);
		// sets the flash device contents start position
		ret = FLASHPNUM + 1;
	}
	delete blk;

	*fileOfs = ret;
}

// All the following methods return the corresponding geometry or
// performance figure

unsigned int FlashParams::getBlocksNum(void)
{
	return(parms[BLOCKSNUM]);
}

unsigned int FlashParams::getWTime(void)
{
	return(parms[WTIME]);
}
