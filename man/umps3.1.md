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

`umps3` -- Virtual machine simulator based around the MIPS R2/3000 microprocessor

# SYNOPSIS

`umps3` [*CONFIGURATION*]

# DESCRIPTION

`uMPS` is an educational computer system architecture and an accompanying emulator designed from the ground up to achieve the right trade-off between simplicity and elegance on one side, and realism on the other. This makes `uMPS` ideally suited for use in education, such as hands-on operating systems or computer architecture university courses.

The uMPS processor implements the MIPS I instruction set, and can therefore be supported out of the box by existing MIPS compilers. The architecture details a complete set of I/O devices (terminals, disks, flash devices, printers, and network adapters) that feature a clean, consistent, programming interface. The previous revision of the uMPS architecture (uMPS2) brings multiprocessor support.

The emulator comes with built-in debugging features and an easy to use graphical user interface. Apart from the emulator itself, several support utilities are provided that can get you quickly started in developing programs for `uMPS`.

# AUTHOR

Mauro Morsiani,\
Tomislav Jonjic *tjonjic@gmail.com*,\
Mattia Biondi *mattiabiondi1@gmail.com*,\
Contributors can be listed on GitHub.

# BUGS

Report issues on GitHub: *https://github.com/virtualsquare/umps3*

# SEE ALSO

**umps3-elf2umps**(1), **umps3-mkdev**(1), **umps3-objdump**(1)

Full documentation at: *https://github.com/virtualsquare/umps3**br/*
Project wiki: *https://wiki.virtualsquare.org/#!umps/umps.md*

# COPYRIGHT

2004, Mauro Morsiani,\
2010-2011, Tomislav Jonjic *tjonjic@gmail.com*,\
2020, Mattia Biondi *mattiabiondi1@gmail.com*
