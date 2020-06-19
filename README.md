<h1><img src="src/frontends/qmps/data/icons/64x64/umps3.svg" alt="uMPS" align="center"> µMPS</h1>

A complete virtual machine simulator based around the MIPS R2/3000 microprocessor.

Please report any bugs you find by [creating an issue ticket](https://github.com/virtualsquare/umps3/issues/new) here on GitHub.
Make sure you include steps on how to reproduce it.

## Table of Contents

* [Introduction](#introduction)
* [Getting started](#getting-started)
  * [Dependencies](#dependencies)
  * [Building from source](#building-from-source)
* [Uninstallation](#uninstallation)
* [License](#license)

## Introduction

µMPS is an educational computer system architecture and an accompanying emulator designed from the ground up to achieve the right trade-off between simplicity and elegance on one side, and realism on the other. This makes µMPS ideally suited for use in education, such as hands-on operating systems or computer architecture university courses.

The µMPS processor implements the MIPS I instruction set, and can therefore be supported out of the box by existing MIPS compilers. The architecture details a complete set of I/O devices (terminals, disks, flash devices, printers, and network adapters) that feature a clean, consistent, programming interface. The previous revision of the µMPS architecture (µMPS2) brings multiprocessor support.

The emulator comes with built-in debugging features and an easy to use graphical user interface. Apart from the emulator itself, several support utilities are provided that can get you quickly started in developing programs for µMPS.

[Learn more about µMPS](http://mps.sourceforge.net/about.html)

## Getting started

µMPS was already packaged for the distros listed below.
If you can't find your distro here, you will have to [build from source](#building-from-source).

If you create a package for any other distribution, please consider contributing the template.

If you are using **Arch Linux**, you can install the AUR package [umps3-git](https://aur.archlinux.org/packages/umps3-git/) to get the latest version, or [umps3](https://aur.archlinux.org/packages/umps3/) for the latest stable release.

### Dependencies

A compiler with C++11 support ([clang-3.3+](https://llvm.org/releases/download.html), [gcc-4.8+](https://gcc.gnu.org/releases.html)), [cmake 3.5+](https://cmake.org/download/), [git](https://git-scm.com/downloads)
- `Qt 5.5+`
- `libelf`
- `boost 1.34+` (headers)
- `libsigc++ 2.0`

Apart from the dependencies listed above, you will also need a MIPS cross toolchain in your PATH.
CMakelists.txt will do its best to detect one; if that fails, you can pass the toolchain tool prefix to `cmake` using `-DMIPS_TOOL_PREFIX=PREFIX`.
Known prefixes are:
- `mips-sde-elf-`
- `mips(el)-elf-`
- `mips(el)-linux-`
- `mips(el)-linux-gnu-`

### Building from source

Please [report any problems](https://github.com/virtualsquare/umps3/issues/new) you run into when building the project.

Get the source code, from the root of the source tree run:
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

By default, the software is installed locally in `/usr/local/`.
If you want to install it somewhere else (e.g. in `/usr/`) you can pass the path using `-DCMAKE_INSTALL_PREFIX:PATH=/usr`.

## Uninstallation

From the root of the binary tree run:
```sh
$ sudo make uninstall
```
N.B.: "install_manifest.txt" is generated during the installation process.

## License

µMPS is licensed under the GPLv3 license. [See LICENSE for more information](https://github.com/virtualsquare/umps3/blob/master/LICENSE).

- "[Papirus Icons](https://git.io/papirus-icon-theme)" by [Papirus Development Team](https://github.com/PapirusDevelopmentTeam) is licensed under [GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
- Logo and all other icons derived by [Mattia Biondi](https://github.com/mattiabiondi) from "[Papirus Icons](https://git.io/papirus-icon-theme)"
