/**
 * msf.cpp  -  MSF parser core.
 * PDB parser uses this engine to parse a .pdb file.
 *
 * This is the part of the PDB parser.
 * (C) Great, 2010.
 * xgreatx@gmail.com
 */

#include <msf.h>
#include <err.h>

namespace symenglib {

    void MSF::Open(const std::string & file) {
        currentPdbFile.open(file, std::fstream::in | std::ios::binary);
        currentPdbFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        Open(currentPdbFile);
    }

    void MSF::Open(const std::fstream & filestream) {
        currentPdbFile.seekg(0, std::ios::end);
        u64 nSize = static_cast<u64> (currentPdbFile.tellg());
        if (nSize<sizeof (MSF_HDR)) {
            throw symenglib::SYMENGLIB_BAD_PDB_FILE();
        }
        MSF_HDR msf_hdr;
    }

    void MSF::Close() {
        currentPdbFile.close();
    }
}