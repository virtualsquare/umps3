/*
 * uMPS - A general purpose computer system simulator
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

#ifndef UMPS_ERROR_H
#define UMPS_ERROR_H

#include <stdexcept>
#include <string>

class Error : public std::runtime_error {
public:
explicit Error(const std::string& what) throw()
	: std::runtime_error(what) {
}
virtual ~Error() throw() {
}
};

class FileError : public Error {
public:
explicit FileError(const std::string& fileName) throw()
	: Error("Error accessing `" + fileName + "'"),
	fileName(fileName)
{
}
virtual ~FileError() throw() {
}

const std::string fileName;
};

class InvalidFileFormatError : public Error {
public:
InvalidFileFormatError(const std::string& fileName, const std::string& what) throw()
	: Error(what),
	fileName(fileName)
{
}
virtual ~InvalidFileFormatError() throw() {
}

const std::string fileName;
};

class InvalidCoreFileError : public InvalidFileFormatError {
public:
InvalidCoreFileError(const std::string& fileName, const std::string& what) throw()
	: InvalidFileFormatError(fileName, what)
{
}
virtual ~InvalidCoreFileError() throw() {
}
};

class ReadingError : public Error {
public:
explicit ReadingError() throw()
	: Error("Reading error") {
}

virtual ~ReadingError() throw() {
}
};

class CoreFileOverflow : public Error {
public:
explicit CoreFileOverflow() throw()
	: Error("Core file too large") {
}

virtual ~CoreFileOverflow() throw() {
}
};

class EthError : public Error {
public:
EthError(unsigned int devNo) throw()
	: Error("Ethernet device error"), devNo(devNo) {
}
virtual ~EthError() throw() {
}

const unsigned int devNo;
};

// Error hook
void Panic(const char* message);

#endif // UMPS_ERROR_H
