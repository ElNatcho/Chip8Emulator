#include"Chip8.hpp"

int main() {
	Chip8 *chip8 = new Chip8();

	chip8->init();
	chip8->loadProg("prog1");

	while (!*chip8->progDone) {
		// N�chsten Opcode ausf�hren
		chip8->execute();

		if (*chip8->drawFlag)
			; // Screen zeichnen

		// Key-States aktualisieren
		chip8->handleKeys();
	}

	SAFE_DELETE(chip8);

	return 0;
}