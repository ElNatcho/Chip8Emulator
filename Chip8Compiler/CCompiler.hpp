#ifndef CCOMPILER_HPP
#define CCOMPILER_HPP

// Includes
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<regex>
#include<map>
#include"CStaticTools.hpp"
#include"CSrcLoader.hpp"

#define CODE_OFFSET 0x200

typedef unsigned char  BYTE;
typedef unsigned short u_16;

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

	// Funktionszeiger
	typedef short(CCompiler::*tFuncPtr)(std::string);

	// -- Kon/Destruktor --
	CCompiler();
	~CCompiler();

	// -- Methoden --
	void loadSrc(std::string path);
	void compile();

private:

	// -- Member Vars --
	CSrcLoader *_srcLoader;
	std::vector<std::string> *_sourceCode;

	std::map<std::string, short> *_jmpAddr; // Map speichert die Adressen der Jump-Adressen
	std::map<std::string, short>::iterator _jmpAddrIt;

	std::vector<short> *_opcodes;

	std::regex  *_regex;
	std::smatch *_match;

	// -- Member Methods --
	void getJmpAddr();
	void _compileInstr(std::string instr);

	// - Translate Methods -
	short tCLS   (std::string args);
	short tRET   (std::string args);
	short tJMP   (std::string args);
	short tIE    (std::string args);
	short tINE   (std::string args);
	short tMOV   (std::string args);
	short tADD   (std::string args);
	short tOR    (std::string args);
	short tADD   (std::string args);
	short tXOR   (std::string args);
	short tSUB   (std::string args);
	short tRSH   (std::string args);
	short tSUBC  (std::string args);
	short tLSH   (std::string args);
	short tJMP0  (std::string args);
	short tRND   (std::string args);
	short tDRW   (std::string args);
	short tIKPR  (std::string args);
	short tIKNPR (std::string args);
	short tGDT   (std::string args);
	short tWFKPR (std::string args);
	short tSDT   (std::string args);
	short tSST   (std::string args);
	short tSISP  (std::string args);
	short tBCD   (std::string args);
	short tRDMP  (std::string args);
	short tRLOD  (std::string args);

	BYTE  _searchForRegister(std::string *args);
	int _searchForNumber(std::string *args);
	int _searchForAddress(std::string *args);
	int _searchForHexNum(std::string *args);

	int _s_hexToInt(std::string hex);
	std::stringstream *_strs;

};

#endif