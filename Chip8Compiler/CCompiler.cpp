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
	int dp_pos;
	for (int i = 0; i < _sourceCode->size(); i++) { // Durch den kompletten Sourc-Code iterieren
		dp_pos = -1;
		dp_pos = _sourceCode->at(i).find(":");
		if (dp_pos >= 0 && dp_pos < _sourceCode->at(i).length()) {
			_jmpAddr->insert(std::make_pair( // Jmp-Adr einfügen
				_sourceCode->at(i).substr(dp_pos, _sourceCode->at(i).find(" ", dp_pos)),
				CODE_OFFSET + i * 2
			));
			for (int j = dp_pos; j < _sourceCode->at(i).size(); j++) {
				if (_sourceCode->at(i).at(j) == ' ' || _sourceCode->at(i).at(j) == '\t') {
					_sourceCode->at(i) = _sourceCode->at(i).substr(j);
				}
			}
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