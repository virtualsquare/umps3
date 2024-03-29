<!--
.\" Copyright (C) 2020 Mattia Biondi, Mikey Goldweber, Renzo Davoli
.\"
.\" This is free documentation; you can redistribute it and/or
.\" modify it under the terms of the GNU General Public License,
.\" as published by the Free Software Foundation, either version 3
.\" of the License, or (at your option) any later version.
.\"
.\" The GNU General Public License's references to "object code"
.\" and "executables" are to be interpreted as the output of any
.\" document formatting or typesetting system, including
.\" intermediate and printed output.
.\"
.\" This manual is distributed in the hope that it will be useful,
.\" but WITHOUT ANY WARRANTY; without even the implied warranty of
.\" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
.\" GNU General Public License for more details.
.\"
.\" You should have received a copy of the GNU General Public
.\" License along with this manual; if not, write to the Free
.\" Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
.\" MA 02110-1301 USA.
.\"
-->
# NAME

`umps3-mkdev` -- The umps3-mkdev device creation utility

# SYNOPSIS

`umps3-mkdev` -d *DISKFILE* [*DISKOPTIONS*]\
`umps3-mkdev` -f *FLASHFILE* *FILE* [*FLASHOPTIONS*]

# DESCRIPTION

The command-line `umps3-mkdev` utility is used to create the files that represent disk and flash devices.

 `DISKS`:
: Disks in uMPS3 are "direct access" nonvolatile read/write devices.
: The `umps3-mkdev` utility allows one to create an empty disk only; this way an OS developer may elect any desired disk data organization.

 ` `
: The created *DISKFILE* represents the entire disk contents, even when empty.
: Hence this file may be very large.
: It is recommended to create small disks which can be used to represent a little portion of an otherwise very large disk unit.

  ` `
: As with real disks, differing performance statistics result in differing simulated drive performance.
: E.g. a faster rotation speed results in less latency delay and a smaller sector data occupancy percentage results in shorter read/write times.

  ` `
: The default values for all these parameters are shown when entering the `umps3-mkdev` alone without any parameters.

 `FLASH DEVICES`:
: Flash devices in uMPS3 are "random access" nonvolatile read/write devices.
: A uMPS3 flash device is essentially equivalent to a seek-free one-dimensional disk drive.
: The `umps3-mkdev` utility allows one to create both slow flash devices (e.g. USB stick) or fast flash devices (e.g. SSDs).
: Furthermore, the utility allows one to create both empty flash devices as well as ones preloaded with a specific file.

  ` `
: The created *FLASHFILE* represents the entire device contents, even when empty.
: Hence this file may be very large.
: It is recommended to create small flash devices which can be used to represent a little portion of an otherwise very large device.

  ` `
: uMPS3 caps the maximum block size for flash devices at 2\^24.
: This translates to a maximum device size of 64GB.

  ` `
: As with real flash devices, read operations are faster than write operations.
: The read speed for uMPS3 flash devices is fixed at 75% of the device write time in microseconds.

  ` `
: The default values for all these parameters are shown when entering the `umps3-mkdev` alone without any parameters.

# OPTIONS

  `-d`
: instructs the utility to build a disk file image.

  `-f`
: instructs the utility to build a flash device file image.

# FILES

  `DISKFILE`
: is the name of the disk file image to be created.

  `FLASHFILE`
: is the name of the flash device file image to be created.

  `FILE`
: is the name of the file to be preloaded onto the device beginning with block 0.
: If one wishes to create an empty flash device but still specify some of the additional parameters, use `/dev/null` as the *FILE* argument.
: To load a flash device with a collection of files, it is recommended to initially create a single `.tar` file from the collection and then use this single `.tar` file for this parameter.
: We recommend the `.tar` file format due to its simple structure.

# DISKOPTIONS

[*CYL* [*HEAD* [*SECT* [*RPM* [*SEEKT* [*DATAS*]]]]]]

 `CYL`:
: Number of cylinders: [1..65535], default = 32

 `HEAD`:
: Number of heads/surfaces: [1..255], default = 2

 `SECT`:
: Number of 4KB sectors/tracks: [1..255], default = 8

 `RPM`:
: Disk rotations per minute: [360..10800], default = 3600

 `SEEKT`:
: Average cylinder to cylinder seek time in microseconds: [1..10000], default = 100

 `DATAS`:
: Sector data occupation %: [10%..90%], default = 80%

# FLASHOPTIONS

[*BLOCKS* [*WT*]]

 `BLOCKS`:
: Number of blocks: [1..0xFFFFFF], default = 512

  `WT`:
: Average write time in microseconds: [1..10000], default = 1000

# AUTHOR

Mauro Morsiani\
Mattia Biondi *mattiabiondi1@gmail.com*\
Contributors can be listed on GitHub.

# BUGS

Report issues on GitHub: *https://github.com/virtualsquare/umps3*

# SEE ALSO

`umps3`(1), `umps3-elf2umps`(1), `umps3-objdump`(1)

Full documentation at: *https://github.com/virtualsquare/umps3*\
Project wiki: *https://wiki.virtualsquare.org/#!umps/umps.md*

# COPYRIGHT

2004, Mauro Morsiani\
2020, Mattia Biondi *mattiabiondi1@gmail.com*
