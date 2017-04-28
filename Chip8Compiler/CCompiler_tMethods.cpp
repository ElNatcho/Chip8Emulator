#include"CCompiler.hpp"

// -- setupTMap --

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
			return (0x3000 | (reg << 2) | (0x00FF & param));
		}
	} else {
		return (0x5000 | (reg << 2) | (param << 1));
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
			return (0x4000 | (reg << 2) | (0x00FF & param));
		}
	} else {
		return (0x9000 | (reg << 2) | (param << 1));
	}
}

// -- tMOV -- 
// Methode erstellt den MOV opcode
// @param args: Parameter der Funktion
//
short CCompiler::tMOV(std::string args) {
	*_regex = "(i|I)|((v|V)\\d{1})";
	if (std::regex_search(args, *_match, *_regex)) {
		args = _match->suffix();
		if (_match->str().at(0) == 'V' || _match->str().at(0) == 'v') { // MOV VX
			BYTE reg = _s_hexToInt(_match->str().substr(1));
			u_16 param = _searchForRegister(&args); // Nach VY suchen
			if (param > 0xF) { // VY wurde nicht gefunden
				param = _searchForNumber(&args); // Nach absoluten Zahlen suchen
				if (param < 0) { // Keine Zahl gefunden
					throw std::exception(("MOV VX: No valid number or register in: " + args).c_str());
				} else { // Zahl gefunden
					return (0x6000 | (reg << 2) | (0x00FF & param));
				}
			} else { // VY wurde gefunden
				return (0x8000 | (reg << 2) | (param << 1));
			}
		} else { // MOV I
			u_16 addr = _searchForAddress(&args); // Nach Adresse prüfen
			if (addr > 0) { // Adresse prüfen
				return (0xA000 | (addr & 0x0FFF));
			} else {
				throw std::exception(("MOV I: No valid address in: " + args).c_str());
			}
		}
	} else {
		throw std::exception(("MOV: No valid parameter in: " + args).c_str());
	}
}

// -- _searchForRegister --
// Methode sucht im einem String nach einem Register
// @param args: String der durchsucht werden soll
//
BYTE CCompiler::_searchForRegister(std::string *args) {
	*_regex = "(v|V)\\d{1}";
	if (std::regex_search(*args, *_match, *_regex)) {
		*args = _match->suffix().str();
		return _s_hexToInt(_match->str().substr(1));
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
			*args = _match->suffix().str();
			return std::stoi(_match->str());
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
	*_regex = "0x[0-1A-Fa-f]+";
	if (std::regex_search(*args, *_match, *_regex)) {
		*args = _match->suffix().str();
		return _s_hexToInt(_match->str().substr(2));
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
	int tmpNum;
	*_strs << hex;
	*_strs >> tmpNum;
	return tmpNum;
}