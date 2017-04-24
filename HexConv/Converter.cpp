#include"Converter.hpp"

// -- Konstruktor --
// @param dmp_file: Datei in die die Konvertierten Werte geschrieben werden
//
Converter::Converter(std::string dmp_file) {
	// Alloc Mem
	_ofstream = new std::ofstream();
	_tmpNum = new int;
	_strs = new std::stringstream();

	// Datei öffnen
	_ofstream->open(dmp_file, std::ios::out | std::ios::trunc);
}

// -- convert --
// Methode convertiert einen Hex-Wert zu einem Int Wert und schreibt ihn in eine Datei
// @param hex: Hex-Wert der konvertiert werden soll
//
void Converter::convert(std::string hex) {
	// Wert konvertieren
	*_strs << std::hex << hex;
	*_strs >> *_tmpNum;

	_strs->clear();

	// Wert in Datei schreiben
	if (!_ofstream->is_open()) {
		std::cout << "FILE_ISNOT_OPEN_EXCEPTION" << std::endl;
		return;
	}

	*_ofstream << *_tmpNum;
	*_ofstream << "\n";
}

// -- Destruktor --
Converter::~Converter() {
	// Datei schliessen
	if (_ofstream->is_open())
		_ofstream->close();

	// Free Mem
	SAFE_DELETE(_ofstream);
	SAFE_DELETE(_tmpNum);
	SAFE_DELETE(_strs);
}