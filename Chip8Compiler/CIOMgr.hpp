#ifndef CIOMGR_HPP
#define CIOMGR_HPP

// Includes
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"CStaticTools.hpp"

// CIOMgr
class CIOMgr {
public:

	// -- Kon/Destruktor --
	CIOMgr();
	~CIOMgr();

	// -- Methoden --
	std::vector<std::string> loadSrc(std::string path);
	void writeOpcodes(std::string path, std::vector<short> &opcodes);

	// -- Public Vars --
	int writeFlags;
	int readFlags;

private:

	// -- Member Vars --
	std::ifstream *_ifstream;
	std::ofstream *_ofstream;

	std::string *_tempStr;
	std::vector<std::string> *_src;

};

#endif