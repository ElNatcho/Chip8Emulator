#include"CProgLoader.hpp"

// -- Konstruktor --
CProgLoader::CProgLoader() {
	// Alloc Mem
	_curPos = new int;
	_tempStr = new std::string();
	_ifstream = new std::ifstream();
	_curOpcode = new short;
}

// -- loadProg --
// Methode lädt ein Programm aus einer Datei
// @param path: Pfad zum/Name des Programms
// @param mem : Ptr zum Mem-Array in welches das Programm geschrieben werden soll
//
void CProgLoader::loadProg(std::string path, std::array<BYTE, MEM_SIZE> *mem) {
	*_curPos = 0x200;
	*_curOpcode = 0;
	*_tempStr = "";

	// Datei öffnen
	if (_ifstream->is_open())
		_ifstream->close();
	_ifstream->open(path);

	// Daten lesen
	while (!_ifstream->eof() && *_curPos < MEM_SIZE){
		try {
			std::getline(*_ifstream, *_tempStr);
			*_curOpcode = std::stoi(*_tempStr);
			mem->at(*_curPos)	  = (*_curOpcode & 0xFF00) >> 8;
			mem->at(*_curPos + 1) = (*_curOpcode & 0x00FF);
		} catch (std::exception &e) {
			std::cout << "Datei " << path << " konnte nicht geladen werden: " << e.what() << std::endl;
			mem->at(*_curPos) = 0;
			mem->at(*_curPos + 1) = 0;
		}
		*_curPos += 2;
	}

}

// -- Destruktor --
CProgLoader::~CProgLoader() {
	// Free Mem
	SAFE_DELETE(_curPos);
	SAFE_DELETE(_tempStr);
	SAFE_DELETE(_ifstream);
	SAFE_DELETE(_curOpcode);
}