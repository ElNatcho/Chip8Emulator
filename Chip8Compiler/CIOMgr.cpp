#include"CIOMgr.hpp"

// -- Konstruktor --
CIOMgr::CIOMgr() {
	// Alloc Mem
	_src = new std::vector<std::string>();
	_tempStr = new std::string();
	_ifstream = new std::ifstream();
	_ofstream = new std::ofstream();

	// Werte setzen
	writeFlags = std::ios::out;
	readFlags  = std::ios::in;

}

// -- loadSrc --
// Methode lädt Code aus einer Source-Datei
// @param path: Pfad zur/Name der Source-Datei
//
std::vector<std::string> CIOMgr::loadSrc(std::string path) {
	// Datei öffnen
	if (_ifstream->is_open())
		_ifstream->close();
	_ifstream->open(path, readFlags);

	// Inhalt auslesen
	while (!_ifstream->eof() && _ifstream->good()) {
		std::getline(*_ifstream, *_tempStr);
		_src->push_back(*_tempStr);
	}

	// Datei schliessen
	_ifstream->close();

	return *_src;
}

// -- writeOpcodes --
// Methode schreibt die erzeugten Opcodes in eine Datei
// @param path   : Pfad zur/Name der Datei
// @param opcodes: Opcodes die exportiert werden sollen
void CIOMgr::writeOpcodes(std::string path, std::vector<short> &opcodes) {
	// Datei öffnen
	if (_ofstream->is_open())
		_ofstream->close();
	_ofstream->open(path, writeFlags);

	// Inhalt schreiben
	for (int i = 0; i < opcodes.size(); i++) {
		*_ofstream << static_cast<unsigned short>(opcodes.at(i)) << "\n";
	}

	// Datei schliessen
	_ofstream->close();
}

// -- Destruktor --
CIOMgr::~CIOMgr() {
	// Free Mem
	SAFE_DELETE(_src);
	SAFE_DELETE(_tempStr);
	SAFE_DELETE(_ifstream);
	SAFE_DELETE(_ofstream);
}