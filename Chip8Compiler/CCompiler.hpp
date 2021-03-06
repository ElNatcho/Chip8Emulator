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
#include"CIOMgr.hpp"

#define CODE_OFFSET 0x200

typedef unsigned char  BYTE;
typedef unsigned short u_16;

// G�ltige Befehle
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
	void writeOpc(std::string path);

private:

	// -- Member Vars --
	CIOMgr *_ioMgr;
	std::vector<std::string> *_sourceCode;

	std::map<std::string, short> *_jmpAddr; // Map speichert die Adressen der Jump-Adressen
	std::map<std::string, short>::iterator _jmpAddrIt;

	std::vector<short> *_opcodes;

	std::regex  *_regex;
	std::smatch *_match;

	// -- Member Methods --
	void _getJmpAddr();
	void _compileInstr(std::string instr);

	// - Translate Methods -
	void _setupTFMap();

	short tCLS   (std::string args);
	short tRET   (std::string args);
	short tJMP   (std::string args);
	short tIE    (std::string args);
	short tINE   (std::string args);
	short tMOV   (std::string args);
	short tADD   (std::string args);
	short tOR    (std::string args);
	short tAND   (std::string args);
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

	short t1Reg (std::string  args, short opcode_raw, std::string operation);
	short t2Regs(std::string *args, short opcode_raw, std::string operation);

	BYTE  _searchForRegister(std::string *args);
	int _searchForNumber(std::string *args);
	int _searchForAddress(std::string *args);
	int _searchForHexNum(std::string *args);

	int _s_hexToInt(std::string hex);

	// - Translate Vars -
	std::stringstream *_strs;

	std::map<std::string, tFuncPtr> *_tFuncPtrs;
	std::map<std::string, tFuncPtr>::iterator _tFPtrIt;

	std::string *_tempStr;

	u_16 *_tempReg;
	u_16 *_tempParam;
	short *_tempAddr;

};

#endif