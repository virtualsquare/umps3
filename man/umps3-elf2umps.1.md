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

`umps3-elf2umps` -- The umps3-elf2umps object file conversion utility

# SYNOPSIS

`umps3-elf2umps` [*OPTIONS*] -k *FILE*\
`umps3-elf2umps` [*OPTIONS*] -b *FILE*\
`umps3-elf2umps` [*OPTIONS*] -a *FILE*

# DESCRIPTION

The command-line `umps3-elf2umps` utility is used to convert the ELF formatted executable and object files produced by the gcc cross-platform development tools into the `.aout`, `.core`, and `.rom` formatted files required by `uMPS3`.

A successful conversion will produce a file by the name of `file.core.umps`, `file.rom.umps`, or `file.aout.umps` accordingly.

A `.stab` file is a text file containing a one-line uMPS3-specific header and the contents of the symbol table from the ELF-formatted input file.
It is used by the uMPS3 simulator to map `.text` and `.data` locations to their symbolic, i.e. kernel/OS source code, names.
Hence the automatic generation of the `.stab` file whenever a `.core` file is produced.
Since `.stab` files are text files one can also examine/modify them using traditional text-processing tools.

In addition to its utility in tracking down errors in the `umps3-elf2umps` program (which hopefully no longer exist), the *-v* flag is of general interest since it illustrates which ELF sections were found and produced and the resulting header data for `.core` and `.aout` files.
For `.rom` files, the *-v* flag also displays the BIOS code size obtained during file conversion.

# OPTIONS

  `-v`
:  Optional flag to produce verbose output during the conversion process.

  `-m`
:  Optional flag to generate the `.stab` symbol table map file associated with *FILE*.

  `-k`
:  Flag to produce a `.core` formatted file.
:  This flag can only be used with an executable file.
:  A `.stab` file is automatically produced with this option.

  `-b`
:  Flag to produce a `.rom` formatted file.
:  This flag can only be used with an object file that does not contain relocations.

  `-a`
:  Flag to produce a `.aout` formatted file.\
:  This flag can only be used with an executable file.

# FILES

*FILE* is the executable or object file to be converted.

# AUTHOR

Mauro Morsiani\
Tomislav Jonjic *tjonjic@gmail.com*\
Contributors can be listed on GitHub.

# BUGS

Report issues on GitHub: *https://github.com/virtualsquare/umps3*

# SEE ALSO

**umps3**(1), **umps3-mkdev**(1), **umps3-objdump**(1)

Full documentation at: *https://github.com/virtualsquare/umps3*\
Project wiki: *https://wiki.virtualsquare.org/#!umps/umps.md*

# COPYRIGHT

2004, Mauro Morsiani\
2010-2011, Tomislav Jonjic *tjonjic@gmail.com*\
