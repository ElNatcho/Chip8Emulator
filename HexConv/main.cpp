#include"Converter.hpp"

int main() {
	std::string file;
	std::string hex_val;

	std::cout << "Datei in die die Daten geschrieben werden sollen: ";
	std::cin >> file;

	Converter *_converter = new Converter(file);

	while (true) {
		std::cout << "0x";
		std::cin >> hex_val;

		if (hex_val == "exit")
			break;

		_converter->convert(hex_val);
	}

	delete(_converter);
	
	return 0;
}