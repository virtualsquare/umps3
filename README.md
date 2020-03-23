# uMPS
Welcome to uMPS!
uMPS is a complete virtual machine simulator based around the MIPS R2/3000 microprocessor.

## Prerequisites

- Qt 4.6.x or later
- libelf
- Boost (headers) 1.34+
- libsigc++ 2.0

Apart from the dependencies listed above, you will also need a MIPS cross toolchain in your PATH.
CMakelists.txt will do its best to detect one; if that fails, you can pass the toolchain tool prefix to `cmake` using `-DMIPS_TOOL_PREFIX=PREFIX`.
Known prefixes are:
- `mips-sde-elf-`
- `mips(el)-elf-`
- `mips(el)-linux-`
- `mips(el)-linux-gnu-`

## Installation

Get the source code, from the root of the source tree run:
```
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
```
$ sudo make uninstall
```
N.B.: "install_manifest.txt" is generated during the installation process.
