#ifndef CPROGLOADER_HPP
#define CPROGLOADER_HPP

// Includes
#include<exception>
#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include"Chip8.hpp"

// CProgLoader
class CProgLoader {
public:

	// -- Kon/Destruktor --
	CProgLoader();
	~CProgLoader();

	// -- Methoden --
	void loadProg(std::string path, std::array<BYTE, MEM_SIZE> *mem);

private:

	// -- Member Vars --
	int *_curPos;

	std::ifstream *_ifstream;

	short *_curOpcode;

};

#endif