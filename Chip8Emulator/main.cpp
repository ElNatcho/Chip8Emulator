#include"Chip8.hpp"
#include"CRenderer.hpp"

int main() {
	Chip8 *chip8 = new Chip8();
	CRenderer *renderer = new CRenderer();

	chip8->init();
	chip8->loadProg("test_disp.txt");

	renderer->renderDisplay(chip8->getDisplayMem());

	while (!*chip8->progDone) {
		// Nächsten Opcode ausführen
		chip8->execute();

		renderer->update(); // Sreen updaten
		if (*chip8->drawFlag)
			renderer->renderDisplay(chip8->getDisplayMem()); // Screen zeichnen

		// Key-States aktualisieren
		chip8->handleKeys();
	}

	SAFE_DELETE(chip8);
	SAFE_DELETE(renderer);

	return 0;
}