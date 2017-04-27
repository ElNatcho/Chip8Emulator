#include"CCompiler.hpp"

// -- Konstruktor --
CCompiler::CCompiler() {
	// Alloc Mem
	_regex = new std::regex();
	_match = new std::smatch();
	_jmpAddr = new std::map<std::string, short>();
	_opcodes = new std::vector<short>();
	_srcLoader = new CSrcLoader();
	_sourceCode = new std::vector<std::string>();
}

// -- loadSrc --
// Methode lädt den Source-Code aus einer Datei
// @param path: Pfad zur/Name der Src-Datei
//
void CCompiler::loadSrc(std::string path) {
	_srcLoader->loadSrc(path);
	*_sourceCode = _srcLoader->getSrcCode();
}

// -- compile --
// Methode compilet den Source-Code
//
void CCompiler::compile() {
	getJmpAddr();
	for (int i = 0; i < _sourceCode->size(); i++) {
		_compileInstr(_sourceCode->at(i));
	}
}

// -- getJmpAddr --
// Methode sucht nach Jump-Adressen und speichert diese in der map bzw. löscht sie aus dem Code
//
void CCompiler::getJmpAddr() {
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
	*_regex = "((\\s*)|(\t*))[\\w]+(0?)((\\s*)|(\t*))";
	std::regex_search(instr, *_match, *_regex);
	std::cout << _match->str() << std::endl << std::endl;
}

// -- Destruktor --
CCompiler::~CCompiler() {
	// Free Mem
	SAFE_DELETE(_regex);
	SAFE_DELETE(_match);
	_jmpAddr->clear();
	SAFE_DELETE(_jmpAddr);
	_opcodes->clear();
	SAFE_DELETE(_opcodes);
	SAFE_DELETE(_srcLoader);
	_sourceCode->clear();
	SAFE_DELETE(_sourceCode);
}