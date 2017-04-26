#ifndef CCOMPILER_HPP
#define CCOMPILER_HPP

// Includes
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include"CStaticTools.hpp"
#include"CSrcLoader.hpp"

#define CODE_OFFSET 0x200

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
	void loadSrc(std::string path);
	void compile();

private:

	// -- Member Vars --
	std::vector<std::string> *_sourceCode;

	std::map<std::string, short> *_jmpAddr; // Map speichert die Adressen der Jump-Adressen

	CSrcLoader *_srcLoader;

	// -- Member Methods --
	void getJmpAddr();

};

#endif