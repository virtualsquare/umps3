<p align=center>
  <a href="https://wiki.virtualsquare.org/#!education/umps.md">
    <img alt="µMPS3" src="https://raw.githubusercontent.com/virtualsquare/umps3/master/src/frontends/qmps/data/icons/64x64/umps3.svg">
  </a>
</p>

---

<p align=center>
  <a href="https://repology.org/project/umps3/versions">
    <img src="https://repology.org/badge/latest-versions/umps3.svg" alt="latest packaged version(s)">
  </a>
  <a href="https://github.com/virtualsquare/umps3/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/virtualsquare/umps3" alt="License">
  </a>
</p>

# µMPS3

A complete virtual machine simulator based around the MIPS R2/3000 microprocessor.

Please report any bugs you find by [creating an issue ticket](https://github.com/virtualsquare/umps3/issues/new) here on GitHub.
Make sure you include steps on how to reproduce it.

## Table of Contents

* [Introduction](#introduction)
* [Screenshots](#screenshots)
* [How to install](#how-to-install)
  * [Ubuntu](#ubuntu)
  * [Debian](#debian)
  * [Arch Linux](#arch-linux)
  * [Building from source](#building-from-source)
* [Getting started](#getting-started)
* [License](#license)

## Introduction

µMPS is an educational computer system architecture and an accompanying emulator designed from the ground up to achieve the right trade-off between simplicity and elegance on one side, and realism on the other.
This makes µMPS ideally suited for use in education, such as hands-on operating systems or computer architecture university courses.

The µMPS processor implements the MIPS I instruction set, and can therefore be supported out of the box by existing MIPS compilers.
The architecture details a complete set of I/O devices (terminals, disks, flash devices, printers, and network adapters) that feature a clean, consistent, programming interface.

The emulator comes with built-in debugging features and an easy to use graphical user interface.
Apart from the emulator itself, several support utilities are provided that can get you quickly started in developing programs for µMPS.

µMPS is now in its third iteration: µMPS3.
Due to the pedagogically driven changes implemented in µMPS3, this latest version is **NOT** backward compatible with either µMPS2 or µMPS(1).

[Learn more about µMPS](https://wiki.virtualsquare.org/#!education/umps.md)

## Screenshots

<img src="https://wiki.virtualsquare.org/education/pictures/umps3-1.png" alt="screenshot 1" width="32%"/> <img src="https://wiki.virtualsquare.org/education/pictures/umps3-2.png" alt="screenshot 2" width="32%"/> <img src="https://wiki.virtualsquare.org/education/pictures/umps3-3.png" alt="screenshot 3" width="32%"/>

## How to install

<a href="https://repology.org/project/umps3/versions">
    <img src="https://repology.org/badge/vertical-allrepos/umps3.svg" alt="Packaging status" align="right">
</a>

µMPS3 was already packaged for the distros listed below.
If you can't find your distro here, you will have to [build from source](#building-from-source).

If you create a package for any other distribution, please consider contributing the template.

### Ubuntu

If you are using **Ubuntu 20.04 Focal Fossa**, **18.04 Bionic Beaver** or **16.04 Xenial Xerus** ([Checking your Ubuntu Version](https://help.ubuntu.com/community/CheckingYourUbuntuVersion)) or [derivatives](https://wiki.ubuntu.com/DerivativeTeam/Derivatives) (e.g. **Linux Mint**), you need to:

1. enable [Universe](https://help.ubuntu.com/community/Repositories/Ubuntu)
```bash
$ sudo add-apt-repository universe
$ sudo apt update
```
2. add the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps)
```bash
$ sudo add-apt-repository ppa:virtualsquare/umps
$ sudo apt update
```
3. install 
```bash
$ sudo apt install umps3
```

### Debian

#### Debian Unstable ("sid")

If you are using **Debian Unstable ("sid")**, you can install the [official µMPS3 package](https://packages.debian.org/sid/umps3) using:
```bash
$ sudo apt install umps3
```

#### Debian 11 Testing ("bullseye")

If you are using **Debian 11 Testing ("bullseye")**, you need to:

1. add the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps) for the [Ubuntu 20.04 (Focal Fossa)](https://releases.ubuntu.com/focal/) version to your [Apt sources configuration file](https://wiki.debian.org/SourcesList):
```bash
$ echo 'deb http://ppa.launchpad.net/virtualsquare/umps/ubuntu focal main' | sudo tee /etc/apt/sources.list.d/virtualsquare-ubuntu-umps-focal.list 
```
2. import the [signing key](https://keyserver.ubuntu.com/pks/lookup?fingerprint=on&op=index&search=0xBB8957296BD01F6CA96B5C88046AB1F65C49333A):
```bash
$ sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 046AB1F65C49333A
```
3. re-synchronize the package index files:
```bash
$ sudo apt update
```
4. install 
```bash
$ sudo apt install umps3
```

#### Debian 10 Stable ("buster")

If you are using **Debian 10 ("buster")**, you need to:

1. add the [virtualsquare/umps PPA](https://launchpad.net/~virtualsquare/+archive/ubuntu/umps) for the [Ubuntu 18.04 (Bionic Beaver)](https://releases.ubuntu.com/18.04/) version to your [Apt sources configuration file](https://wiki.debian.org/SourcesList):
```bash
$ echo 'deb http://ppa.launchpad.net/virtualsquare/umps/ubuntu bionic main' | sudo tee /etc/apt/sources.list.d/virtualsquare-ubuntu-umps-bionic.list 
```
2. import the [signing key](https://keyserver.ubuntu.com/pks/lookup?fingerprint=on&op=index&search=0xBB8957296BD01F6CA96B5C88046AB1F65C49333A):
```bash
$ sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 046AB1F65C49333A
```
3. re-synchronize the package index files:
```bash
$ sudo apt update
```
4. install 
```bash
$ sudo apt install umps3
```

### Arch Linux

If you are using **Arch Linux** or [derivatives](https://wiki.archlinux.org/index.php/Arch-based_distributions) (e.g. **Manjaro**), you can install the AUR package [umps3-git](https://aur.archlinux.org/packages/umps3-git/) to get the latest version, or [umps3](https://aur.archlinux.org/packages/umps3/) for the latest stable release.

- [AUR - Installing and upgrading packages](https://wiki.archlinux.org/index.php/Arch_User_Repository#Installing_and_upgrading_packages)
- [AUR helpers](https://wiki.archlinux.org/index.php/AUR_helpers)

### Building from source

Please [report any problems](https://github.com/virtualsquare/umps3/issues/new) you run into when building the project.

#### Dependencies

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

For example, on **Debian** and [derivatives](https://www.debian.org/derivatives/) (e.g. **Ubuntu**, **Pop!_OS**):
```sh
$ sudo apt install git build-essential cmake qtbase5-dev libelf-dev libboost-dev libsigc++-2.0-dev gcc-mipsel-linux-gnu
```

#### Get the source code

```sh
$ git clone https://github.com/virtualsquare/umps3
```

#### Build and Install

```sh
$ cd umps3
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

#### Launch

You should now be able to launch µMPS3 via the application menu of your desktop environment, or by typing `umps3` at the command line.

#### Uninstallation

From the root of the binary tree run:
```sh
$ sudo make uninstall
```
N.B.: "install_manifest.txt" is generated during the installation process.

## Getting started

[How to get started using µMPS3](https://wiki.virtualsquare.org/#!education/tutorials/umps/getting_started.md)

## License

µMPS3 is licensed under the [GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html) license. [See LICENSE for more information](https://github.com/virtualsquare/umps3/blob/master/LICENSE).

[Papirus Icons](https://git.io/papirus-icon-theme) by [Papirus Development Team](https://github.com/PapirusDevelopmentTeam) is licensed under [GPL-3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)

Logo and all other icons derived by [Mattia Biondi](https://github.com/mattiabiondi) from [Papirus Icons](https://git.io/papirus-icon-theme)
