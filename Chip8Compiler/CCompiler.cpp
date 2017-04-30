#include"CCompiler.hpp"

// -- Konstruktor --
CCompiler::CCompiler() {
	// Alloc Mem
	_strs = new std::stringstream();
	_regex = new std::regex();
	_match = new std::smatch();
	_ioMgr = new CIOMgr();
	_jmpAddr = new std::map<std::string, short>();
	_opcodes = new std::vector<short>();
	_sourceCode = new std::vector<std::string>();

	_setupTFMap();
}

// -- loadSrc --
// Methode lädt den Source-Code aus einer Datei
// @param path: Pfad zur/Name der Src-Datei
//
void CCompiler::loadSrc(std::string path) {
	*_sourceCode = _ioMgr->loadSrc(path);
}

// -- compile --
// Methode compilet den Source-Code
//
void CCompiler::compile() {
	try {
		_getJmpAddr();
		for (int i = 0; i < _sourceCode->size(); i++) {
			_compileInstr(_sourceCode->at(i));
		}
	} catch (std::exception &e) {
		std::cout << "ERR: " << e.what() << std::endl;
	}
}

// -- writeOpc --
// Methode exportiert die erzeugten Opcodes in eine Datei
// @param path: Pfad zur/Name der Datei
//
void CCompiler::writeOpc(std::string path) {
	_ioMgr->writeOpcodes(path, *_opcodes);
}

// -- getJmpAddr --
// Methode sucht nach Jump-Adressen und speichert diese in der map bzw. löscht sie aus dem Code
//
void CCompiler::_getJmpAddr() {
	*_regex = ":[\\w\\d]+((\t)|(\\s))";
	for (int i = 0; i < _sourceCode->size(); i++) { // Durch den kompletten Sourc-Code iterieren
		if (std::regex_search(_sourceCode->at(i), *_match, *_regex)) {
			_jmpAddr->insert(std::make_pair(
				_match->str().substr(1, _match->str().size() - 2),
				i * 2 + 0x200
			));
			_sourceCode->at(i) = _match->suffix().str();
			_match->empty();
		}
	}
}

// -- compileInstr --
// Methode compilet eine Instruktion
// @path instr: Instruktion die compiliert werden soll
//
void CCompiler::_compileInstr(std::string instr) {
	*_regex = "[\\w]+(0?)";
	if (std::regex_search(instr, *_match, *_regex)) {
		_tFPtrIt = _tFuncPtrs->find(_match->str());
		if (_tFPtrIt != _tFuncPtrs->end()) {
			try {
				_opcodes->push_back((this->*(_tFPtrIt->second))(_match->suffix().str()));
			} catch (std::exception &e) {
				std::cout << "ERROR: " << e.what() << std::endl;
			}
		} else {
			*_tempParam = _searchForNumber(&_match->str());
			if (*_tempParam < 0) {
				throw std::exception(("ERR: No valid instr. in: " + instr).c_str());
			} else {
				_opcodes->push_back(*_tempParam);
			}
		}
	} else {
		*_tempParam = _searchForNumber(&instr);
		if (*_tempParam < 0) {
			throw std::exception(("ERR: No valid instr. in: " + instr).c_str());
		} else {
			_opcodes->push_back(*_tempParam);
		}
	}
	
}

// -- Destruktor --
CCompiler::~CCompiler() {
	// Free Mem
	SAFE_DELETE(_strs);
	SAFE_DELETE(_regex);
	SAFE_DELETE(_match);
	_jmpAddr->clear();
	SAFE_DELETE(_jmpAddr);
	_opcodes->clear();
	SAFE_DELETE(_opcodes);
	SAFE_DELETE(_ioMgr);
	_sourceCode->clear();
	SAFE_DELETE(_sourceCode);
}