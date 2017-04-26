#ifndef CCOMPILER_HPP
#define CCOMPILER_HPP

// Includes
#include<iostream>
#include<string>
#include<regex>

// Gültige Befehle
const std::string valid_instr[] = {
	"CLS",
	"RET",
	"JMP",
	"CALL",
	"IE",
	"INE",
	"MOV",
	"ADD",
	"AND",
	"OR",
	"XOR",
	"SUB",
	"RSH",
	"SUBC",
	"LSH",
	"JMP0",
	"RND",
	"DRW",
	"IKPR",
	"IKNPR",
	"GDT",
	"WFKPR",
	"SDT",
	"SST",
	"SISP",
	"BCD",
	"RDMP",
	"RLOD"
};

// CCompiler
class CCompiler {
public:

	// -- Kon/Destruktor --
	CCompiler();
	~CCompiler();

	// -- Methoden --


private:

};

#endif