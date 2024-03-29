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

`umps3-objdump` -- The umps3-objdump object file analysis utility

# SYNOPSIS

`umps3-objdump` [*OPTIONS*] *FILE*

# DESCRIPTION

The command-line `umps3-objdump` utility is used to analyze object files created by the `umps3-elf2umps` utility.

This utility performs the same functions as `mipsel-linux-gnu-objdump` (or `mips-linux-gnu-objdump`) which is included in the cross-platform development tool set.

`umps3-objdump` is used to analyze `.core`, `.rom`, and `.aout` object files while `mipsel-linux-gnu-objdump` is used to analyze ELF-formatted object files.

The output from `umps3-objdump` is directed to stdout.

# OPTIONS

  `-h`
:  Optional flag to show the `.aout` program header, if present.

  `-d`
:  Optional flag to "disassemble" and display the `.text` area in *FILE*.\

  ` `
:  This is an "assembly" dump of the code, thus it will contain load and branch delay slots; differing from the machine language version of the same code.

  `-x`
:  Optional flag to produce a complete little-endian format hexadecimal word dump of *FILE*.\

  ` `
:  Zero-filled blocks will be skipped and marked with \*asterisks\*.\

  ` `
:  The output will appear identical regardless of whether *FILE* is little-endian or big-endian.

  `-b`
:  Optional flag to produce a complete byte dump of *FILE*.\

  ` `
:  Zero-filled blocks will be skipped and marked with \*asterisks\*.\

  ` `
:  Unlike with the *-x* flag, the endian-format of the output will depend on the endianness of *FILE*; i.e. if *FILE* is big-endian than the output will be big-endian.

  `-a`
:  Flag to perform all of the above optional operations.

# FILES

*FILE* is the `.core`, `.rom`, or `.aout` object file to be analyzed.

# AUTHOR

Mauro Morsiani\
Contributors can be listed on GitHub.

# BUGS

Report issues on GitHub: *https://github.com/virtualsquare/umps3*

# SEE ALSO

**umps3**(1), **umps3-elf2umps**(1), **umps3-mkdev**(1)

Full documentation at: *https://github.com/virtualsquare/umps3*\
Project wiki: *https://wiki.virtualsquare.org/#!umps/umps.md*

# COPYRIGHT

2004, Mauro Morsiani\
