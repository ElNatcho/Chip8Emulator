#include"Chip8.hpp"
#include"CRenderer.hpp"

#define OPS 120;

void delayCycle(sf::Clock &c, sf::Time *t);

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Chip8Emulator.exe <ROM>" << std::endl;
		return 0;
	}

	// Alloc Mem
	sf::Clock *clock = new sf::Clock();
	sf::Time  *time  = new sf::Time;

	Chip8 *chip8 = new Chip8();
	CRenderer *renderer = new CRenderer();

	// Chip8 initialisieren und Programm laden
	chip8->init();
	chip8->loadProg(argv[1]);

	// Display clearen
	renderer->renderDisplay(chip8->getDisplayMem());

	while (!*chip8->progDone) {
		// Zeit zurücksetzen
		*time = time->Zero;

		// Nächsten Opcode ausführen
		chip8->execute();

		renderer->update(); // Sreen updaten
		if (*chip8->drawFlag)
			renderer->renderDisplay(chip8->getDisplayMem()); // Screen zeichnen

		// Key-States aktualisieren
		chip8->handleKeys();

		// Warten bis der Zyklus vorbei ist
		delayCycle(*clock, time);
	}

	SAFE_DELETE(chip8);
	SAFE_DELETE(renderer);

	return 0;
}

void delayCycle(sf::Clock &c, sf::Time *t) {
	do {
		*t += c.restart();
	} while (t->asMilliseconds() < 1000/60);
}