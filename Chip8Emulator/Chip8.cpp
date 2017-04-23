#include"Chip8.hpp"

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

}

// -- loadProg --
// Methode lädt ein Program in den Speicher
// @prog_path: Pfad zum/Name des Programms, dass geladen werden soll
//
void Chip8::loadProg(std::string prog_path) {

}

// -- execute --
// Methode führt einen Emulationszyklus aus
//
void Chip8::execute() {
	// Fetch opcode
	*_opcode = _memory->at(*_reg_pc) << 8 | _memory->at(*_reg_pc + 1);

	// Decode opcode
	switch (*_opcode & 0xF000) {
	case 0x0000: {

		}
		break;

	case 0x1000: // 0x1NNN: Springt zu Stelle NNN
		*_reg_pc = 0x0FFF & *_opcode;
		break;

	case 0x2000: // 0x2NNN: Ruft Subroutine an der Position NNN auf
		_stack->at(*_reg_sp) = *_reg_pc;
		*_reg_sp += 1;
		*_reg_pc = 0x0FFF & *_opcode;
		break;

	case 0x3000: // 0x3XNN: Nächste Instruktion wird übersprungen wenn VX == NN
		if (_reg_v->at((*_opcode & 0x0F00) >> 2) == *_opcode & 0x00FF)
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0x4000: // 0x4XNN: Nächste Instruktion wird übersprungen wenn VX != NN
		if (_reg_v->at((*_opcode & 0x0F00) >> 2) != *_opcode & 0x00FF)
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0x5000: // 0x5XY0: Nächste Instruktion wird übersprungen wenn VX == VY
		if (_reg_v->at((*_opcode & 0x0F00) >> 2) == _reg_v->at((*_opcode & 0x00F0) >> 1))
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0x6000: // 0x6XNN: Setzt VX = NN
		_reg_v->at((*_opcode & 0x0F00) >> 2) = *_opcode & 0x00FF;
		*_reg_pc += 2;
		break;

	case 0x7000: // 0x7XNN: Addiert VX mit NN und speichert es in VX (VX += NN)
		_reg_v->at((*_opcode & 0x0F00) >> 2) += *_opcode & 0x00FF;
		*_reg_pc += 2;
		break;

	case 0x8000: {
	
		}
		break;

	case 0x9000: // 0x9XY0: Nächste Instruktion wird übersprungen wenn VX != VY
		if (_reg_v->at((*_opcode & 0x0F00) >> 2) != _reg_v->at((*_opcode & 0x00F0) >> 1))
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0xA000: // 0xANNN: Setzt I = NNN
		*_reg_i = *_opcode & 0x0FFF;
		*_reg_pc += 2;
		break;

	case 0xB000: // 0xBNNN: Springt an die Adresse NNN + V0
		*_reg_pc = (*_opcode & 0x0FFF) + _reg_v->at(0);
		break;

	case 0xC000: // 0xCXNN: Setzt VX = rand() & NN
		_reg_v->at((*_opcode & 0x0F00) >> 2) = (rand() % 255) & (*_opcode & 0x00FF);
		*_reg_pc += 2;
		break;

	case 0xD000: // 0xDXYN: Zeichnet ein Sprite an Pos VX, VY mit einer Breite von 8 Pixel und der Höhe N. Daten für die Zeile werden ab der Speicheradresse I gelesen
		unsigned short x_pos = _reg_v->at((*_opcode & 0x0F00) >> 2);
		unsigned short y_pos = _reg_v->at((*_opcode & 0x00F0) >> 1);
		unsigned short h = *_opcode & 0x000F;
		unsigned short pixel;

		_reg_v->at(0xF) = 0;
		for (int y = y_pos; y < h; y++) {
			pixel = _memory->at(*_reg_i + y);
			for (int x = 0; x < 8; x++) {
				if ((pixel & (0x80 >> x)) != 0) {
					if (_displayMem->at(x + x_pos + (y * 64)) == 1)
						_reg_v->at(0xF) = 1;
					_displayMem->at(x + x_pos + (y * 64)) ^= 1;
				}
			}
		}
		
		*drawFlag = true;
		*_reg_pc += 2;

		break;

	case 0xE000: {

		}
		break;

	case 0xF000: {

		}
		break;
	}
}

// -- handleKeys --
// Methode speichert die aktuellen Key-States
//
void Chip8::handleKeys() {

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
}