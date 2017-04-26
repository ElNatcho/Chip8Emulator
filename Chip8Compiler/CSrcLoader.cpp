#include"CSrcLoader.hpp"

// -- Konstruktor --
CSrcLoader::CSrcLoader() {
	// Alloc Mem
	_ifstream = new std::ifstream();
	_tempStr  = new std::string();
	_src      = new std::vector<std::string>();
}

// -- loadSrc --
// Methode lädt Code aus einer Source-Datei
// @param path: Pfad zur/Name der Source-Datei
//
void CSrcLoader::loadSrc(std::string path) {
	// Datei schliessen
	if (_ifstream->is_open())
		_ifstream->close();
	_ifstream->open(path);

	// Inhalt auslesen
	while (!_ifstream->eof() && _ifstream->good()) {
		std::getline(*_ifstream, *_tempStr);
		_src->push_back(*_tempStr);
	}

	// Datei schliessen
	_ifstream->close();
}

// -- getSrcCode --
// Methode gibt den ausgelesenen Source-Code zurück
//
std::vector<std::string> CSrcLoader::getSrcCode() {
	return *_src;
}

// -- Destruktor --
CSrcLoader::~CSrcLoader() {
	// Free Mem
	SAFE_DELETE(_ifstream);
	SAFE_DELETE(_tempStr);
	SAFE_DELETE(_src);
}