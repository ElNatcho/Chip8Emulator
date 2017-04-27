#include"CCompiler.hpp"

// -- Konstruktor --
CCompiler::CCompiler() {
	// Alloc Mem
	_jmpAddr = new std::map<std::string, short>();
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
}

// -- getJmpAddr --
// Methode sucht nach Jump-Adressen und speichert diese in der map bzw. löscht sie aus dem Code
//
void CCompiler::getJmpAddr() {
	std::regex  reg(":[\\w\\d]+((\t)|(\\s))");
	std::smatch match;
	for (int i = 0; i < _sourceCode->size(); i++) { // Durch den kompletten Sourc-Code iterieren
		if (std::regex_search(_sourceCode->at(i), match, reg)) {
			_jmpAddr->insert(std::make_pair(
				match.str().substr(1, match.str().size() - 2),
				i * 2 + 0x200
			));
			_sourceCode->at(i) = match.suffix().str();
			match.empty();
		}
	}
}

// -- Destruktor --
CCompiler::~CCompiler() {
	// Free Mem
	_jmpAddr->clear();
	SAFE_DELETE(_jmpAddr);
	SAFE_DELETE(_srcLoader);
	_sourceCode->clear();
	SAFE_DELETE(_sourceCode);
}