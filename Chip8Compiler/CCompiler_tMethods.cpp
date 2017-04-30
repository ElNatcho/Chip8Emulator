#include"CCompiler.hpp"

// -- _setupTFMap --
// Methode setzt die Übersetzungsfunktionszeigermap auf
//
void CCompiler::_setupTFMap() {
	// Alloc Mem
	_tempStr = new std::string();
	_tempReg = new u_16;
	_tempAddr = new short;
	_tempParam = new u_16;
	_tFuncPtrs = new std::map<std::string, tFuncPtr>();

	// Map füllen
	_tFuncPtrs->insert(std::make_pair("CLS"  , &CCompiler::tCLS));
	_tFuncPtrs->insert(std::make_pair("RET"  , &CCompiler::tRET));
	_tFuncPtrs->insert(std::make_pair("JMP"  , &CCompiler::tJMP));
	_tFuncPtrs->insert(std::make_pair("IE"   , &CCompiler::tIE));
	_tFuncPtrs->insert(std::make_pair("INE"  , &CCompiler::tINE));
	_tFuncPtrs->insert(std::make_pair("MOV"  , &CCompiler::tMOV));
	_tFuncPtrs->insert(std::make_pair("ADD"  , &CCompiler::tADD));
	_tFuncPtrs->insert(std::make_pair("OR"   , &CCompiler::tOR));
	_tFuncPtrs->insert(std::make_pair("AND"  , &CCompiler::tAND));
	_tFuncPtrs->insert(std::make_pair("XOR"  , &CCompiler::tXOR));
	_tFuncPtrs->insert(std::make_pair("SUB"  , &CCompiler::tSUB));
	_tFuncPtrs->insert(std::make_pair("RSH"  , &CCompiler::tRSH));
	_tFuncPtrs->insert(std::make_pair("SUBC" , &CCompiler::tSUBC));
	_tFuncPtrs->insert(std::make_pair("LSH"  , &CCompiler::tLSH));
	_tFuncPtrs->insert(std::make_pair("JMP0" , &CCompiler::tJMP0));
	_tFuncPtrs->insert(std::make_pair("RND"  , &CCompiler::tRND));
	_tFuncPtrs->insert(std::make_pair("DRW"  , &CCompiler::tDRW));
	_tFuncPtrs->insert(std::make_pair("IKPR" , &CCompiler::tIKPR));
	_tFuncPtrs->insert(std::make_pair("IKNPR", &CCompiler::tIKNPR));
	_tFuncPtrs->insert(std::make_pair("GDT"  , &CCompiler::tGDT));
	_tFuncPtrs->insert(std::make_pair("WFKPR", &CCompiler::tWFKPR));
	_tFuncPtrs->insert(std::make_pair("SDT"  , &CCompiler::tSDT));
	_tFuncPtrs->insert(std::make_pair("SST"  , &CCompiler::tSST));
	_tFuncPtrs->insert(std::make_pair("SISP" , &CCompiler::tSISP));
	_tFuncPtrs->insert(std::make_pair("BCD"  , &CCompiler::tBCD));
	_tFuncPtrs->insert(std::make_pair("RDMP" , &CCompiler::tRDMP));
	_tFuncPtrs->insert(std::make_pair("RLOD" , &CCompiler::tRLOD));
}

// -- tCLS --
// Methode erstellt den CLS opcode
// @param args: Parameter der Funktion
//
short CCompiler::tCLS(std::string args) {
	return 0x00E0;
}

// -- tRET --
// Methode erstellt den RET opcode
// @param args: Parameter der Funktion
//
short CCompiler::tRET(std::string args) {
	return 0x00EE;
}

// -- tJMP --
// Methode erstellt den JMP opcode
// @param args: Parameter der Funktion
//
short CCompiler::tJMP(std::string args) {
	int addr = _searchForAddress(&args);
	if (addr >= 0) {
		return 0x1000 | (0x00000FFF & addr);
	} else {
		throw std::exception(("JMP: Unknown Paramter: " + args).c_str());
	}
}

// -- tIE --
// Methode erstellt den IE opcode
// @param args: Parameter der Funktion
//
short CCompiler::tIE(std::string args) {
	u_16 reg = _searchForRegister(&args); // Nach VX suchen
	if (reg > 0xF) {
		throw std::exception(("IE: No valid register in: " + args).c_str());
	}

	// Nach VY oder 0xNN oder NN suchen
	u_16 param = _searchForRegister(&args);
	if (param > 0xF) {
		param = _searchForNumber(&args);
		if (param < 0) {
			throw std::exception(("IE: No valid second parameter in: " + args).c_str());
		} else {
			return (0x3000 | (reg << 8) | (0x00FF & param));
		}
	} else {
		return (0x5000 | (reg << 8) | (param << 4));
	}
}

// -- tIE --
// Methode erstellt den IE opcode
// @param args: Parameter der Funktion
//
short CCompiler::tINE(std::string args) {
	u_16 reg = _searchForRegister(&args); // Nach VX suchen
	if (reg > 0xF) {
		throw std::exception(("INE: No valid register in: " + args).c_str());
	}

	// Nach VY oder 0xNN oder NN suchen
	u_16 param = _searchForRegister(&args);
	if (param > 0xF) {
		param = _searchForNumber(&args);
		if (param < 0) {
			throw std::exception(("IE: No valid second parameter in: " + args).c_str());
		} else {
			return (0x4000 | (reg << 8) | (0x00FF & param));
		}
	} else {
		return (0x9000 | (reg << 8) | (param << 4));
	}
}

// -- tMOV -- 
// Methode erstellt den MOV opcode
// @param args: Parameter der Funktion
//
short CCompiler::tMOV(std::string args) {
	*_regex = "(i|I)|((v|V)\\d)";
	if (std::regex_search(args, *_match, *_regex)) {
		if (_match->str()[0] == 'v' || _match->str()[0] == 'V') { // MOV VX
			BYTE reg = _s_hexToInt(_match->str().substr(1));
			args = _match->suffix();
			u_16 param = _searchForRegister(&args); // Nach VY suchen
			if (param > 0xF) { // VY wurde nicht gefunden
				param = _searchForNumber(&args); // Nach absoluten Zahlen suchen
				if (param < 0) { // Keine Zahl gefunden
					throw std::exception(("MOV VX: No valid number or register in: " + args).c_str());
				} else { // Zahl gefunden
					return (0x6000 | (reg << 8) | (0x00FF & param));
				}
			} else { // VY wurde gefunden
				return (0x8000 | (reg << 8) | (param << 4));
			}
		} else if(_match->str()[0] == 'i' || _match->str()[0] == 'I') { // MOV I
			args = _match->suffix();
			u_16 addr = _searchForAddress(&args); // Nach Adresse prüfen
			if (addr > 0) { // Adresse prüfen
				return (0xA000 | (addr & 0x0FFF));
			} else {
				throw std::exception(("MOV I: No valid address in: " + args).c_str());
			}
		} else {
			throw std::exception(("MOV: No valid param in: " + args).c_str());
		}
	} else {
		throw std::exception(("MOV: No valid parameter in: " + args).c_str());
	}
}

// -- tADD --
// Methode erstellt den ADD opcode
// @param args: Parameter der Funktion
//
short CCompiler::tADD(std::string args) {
	*_regex = "(i|I)|((v|V)\\d)";
	if (std::regex_search(args, *_match, *_regex)) {
		if (_match->str()[0] == 'v' || _match->str()[0] == 'V') { // ADD to VX
			*_tempReg = _s_hexToInt(_match->str().substr(1));
			args = _match->suffix().str();
			*_tempParam = _searchForRegister(&args);
			if (*_tempParam > 0xF) {
				*_tempParam = _searchForNumber(&args); // Nach absoluten Zahlen suchen
				if (*_tempParam < 0) { // Keine Zahl gefunden
					throw std::exception(("ADD VX: No valid number or register in: " + args).c_str());
				} else { // Zahl gefunden
					return (0x7000 | (*_tempReg << 8) | (0x00FF & *_tempParam));
				}
			} else {
				return (0x8004 | (*_tempReg << 8) | (*_tempParam << 4));
			}
		} else if (_match->str()[0] == 'i' || _match->str()[0] == 'I') { // ADD to I
			args = _match->suffix();
			*_tempReg = _searchForRegister(&args);
			if (*_tempReg > 0xF) {
				throw std::exception(("ADD: No valid register in: " + args).c_str());
			} else {
				return (0xF01E | (*_tempReg << 8));
			}
		} else {
			throw std::exception(("ADD: No valid param in: " + args).c_str());
		}
	} else {
		throw std::exception(("ADD: No valid parameter in: " + args).c_str());
	}
}

// -- tOR --
// Methode erstellt den OR opcode
// @param args: Parameter der Funktion
//
short CCompiler::tOR(std::string args) {
	return t2Regs(&args, 0x8001, "OR");
}

// -- tAND --
// Methode erstellt den AND opcode
// @param args: Parameter der Funktion
//
short CCompiler::tAND(std::string args) {
	return t2Regs(&args, 0x8002, "AND");
}

// -- tXOR --
// Methode erstellt den XOR opcode
// @param args: Parameter der Funktion
//
short CCompiler::tXOR(std::string args) {
	return t2Regs(&args, 0x8003, "XOR");
}

// -- tSUB --
// Methode erstellt den SUB opcode
// @param args: Parameter der Funktion
//
short CCompiler::tSUB(std::string args) {
	return t2Regs(&args, 0x8005, "SUB");
}

// -- tRSH --
// Methode erstellt den RSH opcode 
// @param args: Parameter der Funktion
//
short CCompiler::tRSH(std::string args) {
	return t1Reg(args, 0x8006, "RSH");
}

// -- tSUBC --
// Methode erstellt den SUBC opcode
// @param args: Parameter der Funktion
//
short CCompiler::tSUBC(std::string args) {
	return t2Regs(&args, 0x8007, "SUBC");
}

// -- tLSH --
// Methode erstellt den LSH opcode
// @param args: Parameter der Funktion
//
short CCompiler::tLSH(std::string args) {
	return t1Reg(args, 0x800E, "LSH");
}

// -- tJMP0 --
// Methode erstellt den JMP0 opcode
// @param args: Parameter der Funktion
//
short CCompiler::tJMP0(std::string args) {
	*_tempParam = _searchForNumber(&args);
	if (*_tempParam < -1) {
		throw std::exception(("JMP0: No valid number in: " + args).c_str());
	} else {
		return (0xB000 | (0x0FFF & *_tempParam));
	}
}

// -- tRND --
// Methode erstellt den RND opcode 
// @param args: Parameter der Funktion
//
short CCompiler::tRND(std::string args) {
	*_tempReg = _searchForRegister(&args);
	if (*_tempReg > 0xF) {
		throw std::exception(("RND: No valid register in: " + args).c_str());
	} else {
		*_tempParam = _searchForNumber(&args);
		if (*_tempParam < -1) {
			throw std::exception(("JMP0: No valid number in: " + args).c_str());
		} else {
			return (0xC000 | (*_tempReg << 8) | (0x00FF & *_tempParam));
		}
	}
}

// -- tDRW --
// Methode erstellt den DRW opcode
// @param args: Parameter der Funktion
//
short CCompiler::tDRW(std::string args) {
	*_tempAddr = t2Regs(&args, 0xD000, "DRW");
	*_tempParam = _searchForNumber(&args);
	if (*_tempParam < -1) {
		throw std::exception(("JMP0: No valid number in: " + args).c_str());
	} else {
		return (*_tempAddr | (0x00FF & *_tempParam));
	}
}

// -- tIKPR --
// Methode erstellt den IKPR opcode
// @param args: Parameter der Funktion
//
short CCompiler::tIKPR(std::string args){
	return t1Reg(args, 0xE09E, "IKPR");
}

// -- tIKNPR --
// Methode erstellt den IKNPR opcode
// @param args: Parameter der Funktion
//
short CCompiler::tIKNPR(std::string args) {
	return t1Reg(args, 0xE0A1, "IKNPR");
}

// -- tGDT --
// Methode erstellt den GDT opcode
// @param args: Parameter der Funktion
// 
short CCompiler::tGDT(std::string args) {
	return t1Reg(args, 0xF007, "GDT");
}

// -- tWFKPR --
// Methode erstellt den WFKPR opcode
// @param args: Parameter der Funktion
//
short CCompiler::tWFKPR(std::string args) {
	return t1Reg(args, 0xF00A, "WFKPR");
}

// -- tSDT --
// Methode erstellt den SDT opcode
// @param args: Parameter der Funktion
//
short CCompiler::tSDT(std::string args) {
	return t1Reg(args, 0xF015, "SDT");
}

// -- tSST --
// Methode erstellt den SST opcode
// @param args: Parameter der Funktion
//
short CCompiler::tSST(std::string args) {
	return t1Reg(args, 0xF018, "SST");
}

// -- tSISP --
// Methode erstellt den SISP opcode
// @param args: Parameter der Funktion
//
short CCompiler::tSISP(std::string args) {
	return t1Reg(args, 0xF029, "SISP");
}

// -- tBCD --
// Methode erstellt den BCD opcode
// @param args: Parameter der Funktion
//
short CCompiler::tBCD(std::string args) {
	return t1Reg(args, 0xF033, "BCD");
}

// -- tRDMP --
// Methode erstellt den RDMP opcode
// @param args: Parameter der Funktion
//
short CCompiler::tRDMP(std::string args) {
	return t1Reg(args, 0xF055, "RDMP");
}

// -- tRLOD --
// Methode erstellt den RLOD opcode
// @param args: Parameter der Funktion
//
short CCompiler::tRLOD(std::string args) {
	return t1Reg(args, 0xF065, "RLOD");
}

// -- _searchForRegister --
// Methode sucht im einem String nach einem Register
// @param args: String der durchsucht werden soll
//
BYTE CCompiler::_searchForRegister(std::string *args) {
	*_regex = "(v|V)[0-9A-Fa-f]{1}";
	if (std::regex_search(*args, *_match, *_regex)) {
		*_tempStr = _match->str().substr(1);
		*args = _match->suffix().str();
		return _s_hexToInt(*_tempStr);
	} else {
		return 0x10;
	}
}

// -- _searchForNumber --
// Methode sucht nach einer Hex oder Normalen Zahl
// @param args: String der durchsucht werden soll
//
int CCompiler::_searchForNumber(std::string *args) {
	int e = _searchForHexNum(args);
	if (e == -1) {
		*_regex = "\\d+";
		if (std::regex_search(*args, *_match, *_regex)) {
			*_tempStr = _match->str();
			*args = _match->suffix().str();
			return std::stoi(*_tempStr);
		} else {
			return -1;
		}
	} else {
		return 0x0000FFFF & e;
	}
}

// -- _searchForHexNum --
// Methode sucht nach einer Hex-Zahl
// @param args: String der durchsucht werden soll
//
int CCompiler::_searchForHexNum(std::string *args) {
	*_regex = "0x[0-9A-Fa-f]+";
	if (std::regex_search(*args, *_match, *_regex)) {
		*_tempStr = _match->str().substr(2);
		*args = _match->suffix().str();
		return _s_hexToInt(*_tempStr);
	} else {
		return -1;
	}
}

// -- _searchForAddress -- 
// Methode sucht nach einer Sprung-Adresse
// @param args: String der durchsucht werden soll
//
int CCompiler::_searchForAddress(std::string *args) {
	*_regex = "\\$[\\w\\d]+";
	if (std::regex_search(*args, *_match, *_regex)) {
		_jmpAddrIt = _jmpAddr->find(_match->str().substr(1));
		if (_jmpAddrIt != _jmpAddr->end()) {
			return _jmpAddrIt->second;
		}
	}
	return -1;
}

// -- s_hexToInt --
// Methode konvertiert eine als String gespeicherte Hex Nummer zu einem Integer
// @param hex: String der konvertiert werden soll
//
int CCompiler::_s_hexToInt(std::string hex) {
	int tmpNum = 0;
	*_strs << std::hex << hex;
	*_strs >> std::hex >> tmpNum;
	_strs->clear();
	return tmpNum;
}

// -- t1Reg --
// Methode dient als template für die RSH, LSH, ... Instruktionen
// @param args      : Parameter der Funktion
// @param opcode_raw: Späterer Opcode
// @param operation : Name der Instruktion
//
short CCompiler::t1Reg(std::string args, short opcode_raw, std::string operation) {
	*_tempReg = _searchForRegister(&args);
	if (*_tempReg > 0xF) {
		throw std::exception((operation + ": No valid register in: " + args).c_str());
	} else {
		return (opcode_raw | (*_tempReg << 8));
	}
}

// -- t2Regs --
// Methode dient als template für die OR, AND, XOR, SUB... Instruktionen
// @param args      : Parameter der Funktion
// @param opcode_raw: Späterer Opcode
// @param operation : Name der Instruktion
//
short CCompiler::t2Regs(std::string *args, short opcode_raw, std::string operation) {
	*_tempReg = _searchForRegister(args);
	if (*_tempReg > 0xF) {
		throw std::exception((operation + ": No valid register in: " + *args).c_str());
	} else {
		*_tempParam = _searchForRegister(args);
		if (*_tempParam > 0xF) {
			throw std::exception((operation + ": No valid register in: " + *args).c_str());
		} else {
			return (opcode_raw | (*_tempReg << 8) | (*_tempParam << 4));
		}
	}
}