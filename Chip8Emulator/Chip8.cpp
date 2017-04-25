#include"Chip8.hpp"
#include"CProgLoader.hpp"

// -- Konstruktor --
Chip8::Chip8() {
	// Alloc Memory
	_reg_v = new std::array<BYTE, REG_SIZE>();
	_stack = new std::array<unsigned short, STACK_SIZE>();
	_memory = new std::array<BYTE, MEM_SIZE>();
	_displayMem = new std::array<BYTE, DISPLAY_SIZE>();
	_keyboardMem = new std::array<BYTE, KEYBOARD_SIZE>();
	
	_reg_i  = new unsigned short;
	_reg_sp = new unsigned short;
	_reg_pc = new unsigned short;

	_delay_timer = new BYTE;
	_sound_timer = new BYTE;

	_opcode = new unsigned short;

	drawFlag = new bool;
	progDone = new bool;

	_keyPushedFlag = new bool;
	_lastKeyPushed = new BYTE;

	_progLoader = new CProgLoader();
}

// -- init --
// Methode initialisiert den Emulator (Register/Memory)
//
void Chip8::init() {
	// Memory clearen
	for (int i = 0; i < _memory->size(); i++)
		_memory->at(i) = 0;

	// Register clearen
	for (int i = 0; i < _reg_v->size(); i++) // V-Register clearen
		_reg_v->at(i) = 0;
	*_reg_i  = 0; // Addr-Reg zurücksetzen
	*_reg_sp = 0; // Stack-Ptr zurücksetzen
	*_reg_pc = 0; // Prog-Counter zurücksetzen

	// Stack clearen
	for (int i = 0; i < _stack->size(); i++)
		_stack->at(i) = 0;

	// Timer clearen
	*_delay_timer = 0;
	*_sound_timer = 0;

	// Display/Keyboard-Mem clearen
	for (int i = 0; i < _displayMem->size(); i++) // Clear Display-Mem
		_displayMem->at(i) = 0;
	for (int i = 0; i < _keyboardMem->size(); i++) // Clear Keyboard-Mem
		_keyboardMem->at(i) = 0;

	// Programm-Flags setzen
	*progDone = false;
	*drawFlag = true;

}

// -- loadProg --
// Methode lädt ein Program in den Speicher
// @prog_path: Pfad zum/Name des Programms, dass geladen werden soll
//
void Chip8::loadProg(std::string prog_path) {
	_progLoader->loadProg(prog_path, _memory);

	*_reg_pc = 0x200;
}

// -- execute --
// Methode führt einen Emulationszyklus aus
//
void Chip8::execute() {
	// Testen ob der PC noch im Speicherbereich liegt
	if (*_reg_pc > 4096) {
		std::cout << "PC out of Range: " << *_reg_pc << std::endl;
		return;
	}

	// Fetch opcode
	*_opcode = _memory->at(*_reg_pc) << 8 | _memory->at(*_reg_pc + 1);

	// Decode opcode

	// Testen ob die Anwendung zu Ende ist
	if (*_opcode == 0xFFFF) {
		*progDone = true;
		return;
	}

	// Instruktion ausführen
	switch (*_opcode & 0xF000) {
	case 0x0000:
		switch (*_opcode & 0x000F) {
		case 0x0000: // 0x00E0: Methode cleart den Screen

			break;

		case 0x000E: // 0x00EE: Springt aus einer Subroutine

			break;
		}
		break;

	case 0x1000: // 0x1NNN: Springt zu Stelle NNN

		break;

	case 0x2000: // 0x2NNN: Ruft Subroutine an der Position NNN auf

		break;

	case 0x3000: // 0x3XNN: Nächste Instruktion wird übersprungen wenn VX == NN

		break;

	case 0x4000: // 0x4XNN: Nächste Instruktion wird übersprungen wenn VX != NN

		break;

	case 0x5000: // 0x5XY0: Nächste Instruktion wird übersprungen wenn VX == VY

		break;

	case 0x6000: // 0x6XNN: Setzt VX = NN

		break;

	case 0x7000: // 0x7XNN: Addiert VX mit NN und speichert es in VX (VX += NN)

		break;

	case 0x8000:
		switch (*_opcode & 0x000F) {
		case 0x0000: // 0x8XY0: VX = VY

			break;

		case 0x0001: // 0x8XY1: VX = VX | VY

			break;

		case 0x0002: // 0x8XY2: VX = VX & VY

			break;

		case 0x0003: // 0x8XY3: VX = VX ^ VY

			break;

		case 0x0004: // 0x8XY4: VX = VX + VY

			break;

		case 0x0005: // 0x8XY5: VX = VX - VY

			break;

		case 0x0006: // 0x8XY6: VX = VX >> 1

			break;

		case 0x0007: { // 0x8XY7: VX = VY - VX

			break;

		case 0x000E: // 0x8XYE: VX = VX << 1

			break;

		}
					 break;

		case 0x9000: // 0x9XY0: Nächste Instruktion wird übersprungen wenn VX != VY

			break;

		case 0xA000: // 0xANNN: Setzt I = NNN

			break;

		case 0xB000: // 0xBNNN: Springt an die Adresse NNN + V0

			break;

		case 0xC000: // 0xCXNN: Setzt VX = rand() & NN

			break;

		case 0xD000: // 0xDXYN: Zeichnet ein Sprite an Pos VX, VY mit einer Breite von 8 Pixel und der Höhe N. Daten für die Zeile werden ab der Speicheradresse I gelesen

			break;

		case 0xE000:
			switch (*_opcode & 0x000F) {
			case 0x000E: // 0xEX9E: Wenn der Schalter VX gedrückt wurde wird die nächste Instrukton übersprungen

				break;

			case 0x0001: // 0xEXA1: Wenn der Schalter VX nicht gedrückt wurde wird die nächste Instrukton übersprungen

				break;
			}
			break;

		case 0xF000:
			switch (*_opcode & 0x00FF) {
			case 0x0007: // 0xFX07: VX = delay_timer

				break;

			case 0x000A: // 0xFX0A: Wartet bis ein Knopf gedrückt wurde und Speichert ihn in VX

				break;

			case 0x0015: // 0xFX15: delay_timer = VX

				break;

			case 0x0018: // 0xFX18: sound_timer = VX

				break;

			case 0x001E: // 0xFX1E: I += VX

				break;

			case 0x0029: // 0xFX29: Setzt I zur Adresse des Sprites das den Buchstaben in VX repräsentiert

				break;

			case 0x0033: // 0xFX33

				break;

			case 0x0055: // 0xFX55: Speichert V0 - VX in Memory an der Adresse I

				break;

			case 0x0065: // 0xFX65: Lädt Register V0 - VX aus der Memory ab der Adresse I

				break;
			}
			break;
		}
	}
}

// -- handleKeys --
// Methode speichert die aktuellen Key-States
//
void Chip8::handleKeys() {
	*_keyPushedFlag = false;
	for (int i = 0; i < _keys.size(); i++) {
		if (sf::Keyboard::isKeyPressed(_keys.at(i))) {
			if (_keyboardMem->at(i) != KEY_PRESSED) {
				_keyboardMem->at(i) = KEY_PRESSED;
				*_lastKeyPushed = i;
				*_keyPushedFlag = true;
			}
		} else {
			_keyboardMem->at(i) = KEY_NOT_PRESSED;
		}
	}
}

// -- Destruktor --
Chip8::~Chip8() {
	// Free Memory
	SAFE_DELETE(_reg_v);
	SAFE_DELETE(_stack);
	SAFE_DELETE(_memory);
	SAFE_DELETE(_displayMem);
	SAFE_DELETE(_keyboardMem);

	SAFE_DELETE(_reg_i);
	SAFE_DELETE(_reg_sp);
	SAFE_DELETE(_reg_pc);

	SAFE_DELETE(_delay_timer);
	SAFE_DELETE(_sound_timer);

	SAFE_DELETE(_opcode);

	SAFE_DELETE(drawFlag);
	SAFE_DELETE(progDone);

	SAFE_DELETE(_keyPushedFlag);
	SAFE_DELETE(_lastKeyPushed);

	SAFE_DELETE(_progLoader);
}