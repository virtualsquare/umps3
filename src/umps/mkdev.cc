/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
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
 * This is a stand-alone program which produces "empty" disk image files
 * with specified performance figures and geometry, or assembles existing
 * data files into a single flash device image file.  Disk image files are
 * used to emulate disk devices; flash device image files are used to emulate
 * flash drive devices.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#include <umps/const.h>
#include "umps/types.h"
#include "umps/blockdev_params.h"

/****************************************************************************/
/* Declarations strictly local to the module.                               */
/****************************************************************************/

// default disk image file name
HIDDEN char diskDflFName[] = "disk0";
HIDDEN char flashDflFName[] = "flash0";

// default disk header parameters (see h/blockdev.h)
HIDDEN unsigned int diskDfl[DISKPNUM] =         {       DFLCYL,
	                                                    DFLHEAD,
	                                                    DFLSECT,
	                                                    DFLROTTIME,
	                                                    DFLSEEKTIME,
	                                                    DFLDATAS
};

// default flash device header parameters (see h/blockdev.h)
HIDDEN unsigned int flashDfl[FLASHPNUM] =       {       DFLBLOCKS,
	                                                    DFLWTIME,
};

//
// Program functions
//

HIDDEN void showHelp(const char * prgName);
HIDDEN int mkDisk(int argc, char * argv[]);
HIDDEN int mkFlash(int argc, char * argv[]);
HIDDEN bool decodeDiskP(int idx, unsigned int * par, const char * str);
HIDDEN bool decodeFlashP(int idx, unsigned int * par, const char * str);
HIDDEN int writeDisk(const char * prg, const char * fname);
HIDDEN int writeFlash(const char * prg, const char * fname, const char * file);
HIDDEN void testForCore(FILE * rfile);

// StrToWord is duplicated here from utility.cc to avoid full utility.o linking
HIDDEN bool StrToWord(const char * str, Word * value);


/****************************************************************************/
/* Definitions to be exported.                                              */
/****************************************************************************/

// This function scans the line arguments; if no error is found, the
// required file is produced, or a warning/help message is printed.
// See showHelp() for argument format.
// Returns an EXIT_SUCCESS/FAILURE code
int main(int argc, char* argv[])
{
	int ret = EXIT_SUCCESS;

	if (argc == 1)
		showHelp(argv[0]);
	else if (SAMESTRING("-d", argv[1]))
		ret = mkDisk(argc, argv);
	else if (SAMESTRING("-f", argv[1]))
		ret = mkFlash(argc, argv);
	else {
		fprintf(stderr, "%s : Unknown argument(s)\n", argv[0]);
		showHelp(argv[0]);
		ret = EXIT_FAILURE;
	}

	return ret;
}

/****************************************************************************/
/* Definitions strictly local to the module.                                */
/****************************************************************************/

// This function prints a warning/help message on standard error
HIDDEN void showHelp(const char * prgName)
{
	fprintf(stderr, "%s syntax : %s {-d | -f} [parameters..]\n\n", prgName, prgName);
	fprintf(stderr, "%s -d <diskfile>%s [cyl [head [sect [rpm [seekt [datas]]]]]]\n",prgName, MPSFILETYPE);
	fprintf(stderr, "where:\n\tcyl = no. of cylinders\t\t\t[1..%u]\t(default = %u)\n", MAXCYL, diskDfl[CYLNUM]);
	fprintf(stderr, "\thead = no. of heads\t\t\t[1..%u]\t(default = %u)\n", MAXHEAD, diskDfl[HEADNUM]);
	fprintf(stderr, "\tsect = no. of sectors\t\t\t[1..%u]\t(default = %u)\n", MAXSECT, diskDfl[SECTNUM]);
	fprintf(stderr, "\trpm = disk rotations per min.\t\t[%u..%u]\t(default = %.0f)\n", MINRPM, MAXRPM, 6E7F / diskDfl[ROTTIME]);
	fprintf(stderr, "\tseekt = avg. cyl2cyl time (microsecs.)\t[1..%u]\t(default = %u)\n", MAXSEEKTIME, diskDfl[SEEKTIME]);
	fprintf(stderr, "\tdatas = sector data occupation %%\t[%u%%..%u%%]\t(default = %u%%)\n", MINDATAS, MAXDATAS, diskDfl[DATASECT]);
	fprintf(stderr, "\t<diskfile> = disk image file name\t\t\t(example = %s%s)\n", diskDflFName, MPSFILETYPE);
	fprintf(stderr, "\n%s -f <flashfile>%s <file> [blocks [wt]]\n", prgName, MPSFILETYPE);
	fprintf(stderr, "where:\n\tblocks = no. of blocks\t\t\t[1..0x%.6X]\t(default = %u)\n", MAXBLOCKS, flashDfl[BLOCKSNUM]);
	fprintf(stderr, "\twt = avg. write time (microsecs.)\t[1..%u]\t(default = %u)\n", MAXWTIME, flashDfl[WTIME]);
	fprintf(stderr, "\t<flashfile> = flash dev. image file name\t\t(example = %s%s)\n", flashDflFName, MPSFILETYPE);
	fprintf(stderr, "\t<file> = file to be written\n");
	fprintf(stderr, "\tnote: use /dev/null as <file> to create an empty image file\n\n");
}


// This function builds an empty disk image file, putting geometry and
// performance figures (by default or passed as command line arguments)
// in file header.
// Returns an EXIT_SUCCESS/FAILURE code
HIDDEN int mkDisk(int argc, char * argv[])
{
	int i;
	bool error = false;
	int ret = EXIT_SUCCESS;

	if (argc < 3 || argc > 9 || strstr(argv[2], MPSFILETYPE) == NULL)
	{
		// too many or too few args
		fprintf(stderr, "%s : disk image file parameters wrong/missing\n", argv[0]);
		ret = EXIT_FAILURE;
	}
	else
	{
		// start argument decoding
		if (argc == 3)
			// all by default: build file image
			ret = writeDisk(argv[0], argv[2]);
		else
		{
			// scan args and places them in diskDfl[]
			for (i = 0; i < argc - 3 && !error; i++)
				error = decodeDiskP(i, &(diskDfl[i]), argv[i + 3]);
			if (!error)
				// build file images
				ret = writeDisk(argv[0], argv[2]);
			else
			{
				fprintf(stderr, "%s : disk image file parameters wrong/missing\n", argv[0]);
				ret = EXIT_FAILURE;
			}
		}
	}
	return(ret);
}


// This function builds a flash device image file from a data file passed as
// command line argument, putting geometry and performance figures (by default
// or passed as command line arguments) in file header. The data file is split
// into BLOCKSIZE blocks.
// Returns an EXIT_SUCCESS/FAILURE code
HIDDEN int mkFlash(int argc, char * argv[])
{
	int i;
	bool error = false;
	int ret = EXIT_SUCCESS;

	if (argc < 4 || argc > 6 || strstr(argv[2], MPSFILETYPE) == NULL)
	{
		// too many or too few args
		fprintf(stderr, "%s : flash device image file parameters wrong/missing\n", argv[0]);
		ret = EXIT_FAILURE;
	}
	else
	{
		// start argument decoding
		if (argc == 4)
			// all by default: build file image
			ret = writeFlash(argv[0], argv[2], argv[3]);
		else
		{
			// scan args and places them in flashDfl[]
			for (i = 0; i < argc - 4 && !error; i++)
				error = decodeFlashP(i, &(flashDfl[i]), argv[i + 4]);
			if (!error)
				// build file images
				ret = writeFlash(argv[0], argv[2], argv[3]);
			else
			{
				fprintf(stderr, "%s : flash device image file parameters wrong/missing\n", argv[0]);
				ret = EXIT_FAILURE;
			}
		}
	}
	return(ret);
}


// This function decodes disk parameters contained in string str by
// argument position idx on the command line.
// The decoded parameter returns thru par pointer, while decoding success
// is signaled returning TRUE if an error occurred, and FALSE otherwise

HIDDEN bool decodeDiskP(int idx, unsigned int * par, const char * str)
{
	Word temp;
	bool error = false;

	if (!StrToWord(str, &temp))
		// error decoding parameter
		error = true;
	else
		switch (idx)
		{
		// argument decoded by position on command line
		// min and max values are checked if needed

		case CYLNUM:
			if (INBOUNDS(temp, 1, MAXCYL + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		case HEADNUM:
			if (INBOUNDS(temp, 1, MAXHEAD + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		case SECTNUM:
			if (INBOUNDS(temp, 1, MAXSECT + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		case ROTTIME:
			if (INBOUNDS(temp, MINRPM, MAXRPM + 1))
				*par = (unsigned int) (6E7F / temp);
			else
				error = true;
			break;

		case SEEKTIME:
			if (INBOUNDS(temp, 1, MAXSEEKTIME + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		case DATASECT:
			if (INBOUNDS(temp, MINDATAS, MAXDATAS + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		default:
			// unknown parameter
			error = true;
		}
	return(error);
}


// This function decodes flash device parameters contained in string str by
// argument position idx on the command line.
// The decoded parameter returns thru par pointer, while decoding success
// is signaled returning TRUE if an error occurred, and FALSE otherwise

HIDDEN bool decodeFlashP(int idx, unsigned int * par, const char * str)
{
	Word temp;
	bool error = false;

	if (!StrToWord(str, &temp))
		// error decoding parameter
		error = true;
	else
		switch (idx)
		{
		// argument decoded by position on command line
		// min and max values are checked if needed

		case BLOCKSNUM:
			if (INBOUNDS(temp, 1, MAXBLOCKS + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		case WTIME:
			if (INBOUNDS(temp, 1, MAXWTIME + 1))
				*par = (unsigned int) temp;
			else
				error = true;
			break;

		default:
			// unknown parameter
			error = true;
		}
	return(error);
}


// This function creates the disk image file on the disk, prepending it with
// a header containing geometry and performance figures.
// A number of 4096-byte empty blocks is created, depending on disk geometry.
// Returns an EXIT_SUCCESS/FAILURE code
HIDDEN int writeDisk(const char * prg, const char * fname)
{
	FILE * dfile = NULL;
	int ret = EXIT_SUCCESS;

	unsigned int i;
	unsigned int dfsize = diskDfl[CYLNUM] * diskDfl[HEADNUM] * diskDfl[SECTNUM];
	Word blk[BLOCKSIZE];
	Word diskid = DISKFILEID;

	// clear block
	for (i = 0; i < BLOCKSIZE; i++)
		blk[i] = 0;

	// try to open image file and write header
	if ((dfile = fopen(fname, "w")) == NULL || \
	    fwrite((void *) &diskid, WORDLEN, 1, dfile) != 1 || \
	    fwrite((void *) diskDfl, sizeof(unsigned int), DISKPNUM, dfile) != DISKPNUM)
		ret = EXIT_FAILURE;
	else
	{
		// write empty blocks
		for (i = 0; i < dfsize && ret != EXIT_FAILURE; i++)
			if (fwrite((void *) blk, WORDLEN, BLOCKSIZE, dfile) != BLOCKSIZE)
				ret = EXIT_FAILURE;
		if (fclose(dfile) != 0)
			ret = EXIT_FAILURE;
	}

	if (ret == EXIT_FAILURE)
		fprintf(stderr, "%s : error writing disk file image %s : %s\n", prg, fname, strerror(errno));

	return(ret);
}


// This function creates the flash device image file on the disk, prepending it with
// a header containing geometry and performance figures.
// Returns an EXIT_SUCCESS/FAILURE code
HIDDEN int writeFlash(const char * prg, const char * fname, const char * file)
{
	FILE * ffile = NULL;
	FILE * rfile = NULL;
	int ret = EXIT_SUCCESS;

	unsigned int i, j;
	unsigned int ffsize = flashDfl[BLOCKSNUM];
	Word blk[BLOCKSIZE];
	Word flashid = FLASHFILEID;

	// clear block
	for (i = 0; i < BLOCKSIZE; i++)
		blk[i] = 0UL;

	// tries to open image file and write header
	if ((ffile = fopen(fname, "w")) == NULL || \
	    fwrite((void *) &flashid, WORDLEN, 1, ffile) != 1 || \
	    fwrite((void *) flashDfl, sizeof(unsigned int), FLASHPNUM, ffile) != FLASHPNUM)
		ret = EXIT_FAILURE;
	else
	{
		// tries to process data file
		if((rfile = fopen(file, "r")) == NULL)
			ret = EXIT_FAILURE;
		else {
			// file exists and is readable: process it

			// .core files should be stripped of magic file tag for
			// .alignment reasons
			testForCore(rfile);

			for (j = 0; j < ffsize && ret != EXIT_FAILURE; j++) {
				// split file into blocks inside the flash device image
				if (!feof(rfile)) {
					// read block from input file
					if (fread((void *) blk, WORDLEN, BLOCKSIZE, rfile) != BLOCKSIZE)
						if (ferror(rfile))
							ret = EXIT_FAILURE;

					// write block to output file
					if (fwrite((void *) blk, WORDLEN, BLOCKSIZE, ffile) != BLOCKSIZE)
						ret = EXIT_FAILURE;

					// clear block
					for (i = 0; i < BLOCKSIZE; i++)
						blk[i] = 0UL;
				} else {
					// write empty block
					if (fwrite((void *) blk, WORDLEN, BLOCKSIZE, ffile) != BLOCKSIZE)
						ret = EXIT_FAILURE;
				}
			}
			if (!feof(rfile))
				fprintf(stderr, "%s : error writing flash device file image %s : file %s truncated\n", prg, fname, file);
			fclose(rfile);
		}
		// try to close flash device image file
		if (fclose(ffile) != 0)
			ret = EXIT_FAILURE;
	}

	if (ret == EXIT_FAILURE)
		fprintf(stderr, "%s : error writing flash device file image %s : %s\n", prg, fname, strerror(errno));

	return(ret);
}


// This function tests if file to be inserted is a .core file; if so the
// magic file tag should be skipped for alignment reasons, else file should
// be inserted as-is
HIDDEN void testForCore(FILE * rfile)
{
	Word tag;

	// file existence have been tested by caller
	if (fread((void *) &tag, WORDLEN, 1, rfile) == 0 || tag != COREFILEID)
		// file is empty or not .core
		rewind(rfile);
	// else file is .core: leave file position as it is to skip tag
}


// This function converts a string to a Word (typically, an address) value.
// Returns TRUE if conversion was successful, FALSE otherwise
HIDDEN bool StrToWord(const char * str, Word * value)
{
	char * endp;
	bool valid = true;

	// try to convert the string into a unsigned long
	*value = strtoul(str, &endp, 0);

	if (endp != NULL)
	{
		// there may be some garbage
		while (*endp != EOS && valid)
		{
			if (!isspace(*endp))
				valid = false;
			endp++;
		}
	}
	return(valid);
}
