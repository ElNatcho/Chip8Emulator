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
	case 0x0000:
		switch (*_opcode & 0x000F) {
		case 0x0000: // 0x00E0: Methode cleart den Screen
			for (int i = 0; i < _displayMem->size(); i++)
				_displayMem->at(i) = 0;
			*_reg_pc += 2;
			break;

		case 0x000E: // 0x00EE: Springt aus einer Subroutine
			*_reg_sp -= 1;
			*_reg_pc = _stack->at(*_reg_sp);
			break;
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
		if (_reg_v->at((*_opcode & 0x0F00) >> 8) == *_opcode & 0x00FF)
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0x4000: // 0x4XNN: Nächste Instruktion wird übersprungen wenn VX != NN
		if (_reg_v->at((*_opcode & 0x0F00) >> 8) != *_opcode & 0x00FF)
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0x5000: // 0x5XY0: Nächste Instruktion wird übersprungen wenn VX == VY
		if (_reg_v->at((*_opcode & 0x0F00) >> 8) == _reg_v->at((*_opcode & 0x00F0) >> 4))
			*_reg_pc += 4;
		else
			*_reg_pc += 2;
		break;

	case 0x6000: // 0x6XNN: Setzt VX = NN
		_reg_v->at((*_opcode & 0x0F00) >> 8) = *_opcode & 0x00FF;
		*_reg_pc += 2;
		break;

	case 0x7000: // 0x7XNN: Addiert VX mit NN und speichert es in VX (VX += NN)
		_reg_v->at((*_opcode & 0x0F00) >> 8) += *_opcode & 0x00FF;
		*_reg_pc += 2;
		break;

	case 0x8000: 
		switch (*_opcode & 0x000F) {
		case 0x0000: // 0x8XY0: VX = VY
			_reg_v->at((*_opcode & 0x0F00) >> 8) = _reg_v->at((*_opcode & 0x00F0) >> 4);
			*_reg_pc += 2;
			break;

		case 0x0001: // 0x8XY1: VX = VX | VY
			_reg_v->at((*_opcode & 0x0F00) >> 8) |= _reg_v->at((*_opcode & 0x00F0) >> 4);
			_reg_v->at(0xF) = 0;
			*_reg_pc += 2;
			break;

		case 0x0002: // 0x8XY2: VX = VX & VY
			_reg_v->at((*_opcode & 0x0F00) >> 8) &= _reg_v->at((*_opcode & 0x00F0) >> 4);
			_reg_v->at(0xF) = 0;
			*_reg_pc += 2;
			break;

		case 0x0003: // 0x8XY3: VX = VX ^ VY
			_reg_v->at((*_opcode & 0x0F00) >> 8) ^= _reg_v->at((*_opcode & 0x00F0) >> 4);
			_reg_v->at(0xF) = 0;
			*_reg_pc += 2;
			break;

		case 0x0004: {// 0x8XY4: VX = VX + VY
				unsigned short e = _reg_v->at((*_opcode & 0x0F00) >> 8) + _reg_v->at((*_opcode & 0x00F0) >> 4);
				if (e > 0xFF)
					_reg_v->at(0xF) = 1;
				else
					_reg_v->at(0xF) = 0;
				_reg_v->at((*_opcode & 0x0F00) >> 8) = e & 0x0000FFFF;
			}
			*_reg_pc += 2;
			break;

		case 0x0005: { // 0x8XY5: VX = VX - VY
				short e = _reg_v->at((*_opcode & 0x0F00) >> 8) - _reg_v->at((*_opcode & 0x00F0) >> 4);
				if (e >= 0)
					_reg_v->at(0xF) = 1;
				else
					_reg_v->at(0xF) = 0;
				_reg_v->at((*_opcode & 0x0F00) >> 8) = e & 0x0000FFFF;
			}
			*_reg_pc += 2;
			break;

		case 0x0006: // 0x8XY6: VX = VX >> 1
			_reg_v->at(0xF) = _reg_v->at((*_opcode & 0x0F00) >> 8) & 0x01;
			_reg_v->at((*_opcode & 0x0F00) >> 8) >>= 1;
			*_reg_pc += 2;
			break;

		case 0x0007: { // 0x8XY7: VX = VY - VX
				short e = _reg_v->at((*_opcode & 0x00F0) >> 4) - _reg_v->at((*_opcode & 0x0F00) >> 2);
				if (e >= 0)
					_reg_v->at(0xF) = 1;
				else
					_reg_v->at(0xF) = 0;
				_reg_v->at((*_opcode & 0x0F00) >> 8) = e & 0x0000FFFF;
			}
			*_reg_pc += 2;
			break;

		case 0x000E: // 0x8XYE: VX = VX << 1
			_reg_v->at(0xF) = (_reg_v->at((*_opcode & 0x0F00) >> 8) & 0xF000) >> 3;
			_reg_v->at((*_opcode & 0x0F00) >> 8) <<= 1;
			*_reg_pc += 2;
			break;

		}	
		break;

	case 0x9000: // 0x9XY0: Nächste Instruktion wird übersprungen wenn VX != VY
		if (_reg_v->at((*_opcode & 0x0F00) >> 8) != _reg_v->at((*_opcode & 0x00F0) >> 4))
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
		_reg_v->at((*_opcode & 0x0F00) >> 8) = (rand() % 255) & (*_opcode & 0x00FF);
		*_reg_pc += 2;
		break;

	case 0xD000: { // 0xDXYN: Zeichnet ein Sprite an Pos VX, VY mit einer Breite von 8 Pixel und der Höhe N. Daten für die Zeile werden ab der Speicheradresse I gelesen
			unsigned short x_pos = _reg_v->at((*_opcode & 0x0F00) >> 8);
			unsigned short y_pos = _reg_v->at((*_opcode & 0x00F0) >> 4);
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
		}
		
		*drawFlag = true;
		*_reg_pc += 2;

		break;

	case 0xE000:
		switch (*_opcode & 0x000F) {
		case 0x000E: // 0xEX9E: Wenn der Schalter VX gedrückt wurde wird die nächste Instrukton übersprungen
			if (_keyboardMem->at(_reg_v->at((*_opcode & 0x0F00) >> 8) & 0x000F) == KEY_PRESSED)
				*_reg_pc += 4;
			else
				*_reg_pc += 2;
			break;

		case 0x0001: // 0xEXA1: Wenn der Schalter VX nicht gedrückt wurde wird die nächste Instrukton übersprungen
			if (_keyboardMem->at(_reg_v->at((*_opcode & 0x0F00) >> 8) & 0x000F) != KEY_PRESSED)
				*_reg_pc += 4;
			else
				*_reg_pc += 2;
			break;
		}
		break;

	case 0xF000:
		switch (*_opcode & 0x00FF) {
		case 0x0007: // 0xFX07: VX = delay_timer
			_reg_v->at((*_opcode & 0x0F00) >> 8) = *_delay_timer;
			*_reg_pc += 2;
			break;

		case 0x000A: // 0xFX0A: Wartet bis ein Knopf gedrückt wurde und Speichert ihn in VX

			break;

		case 0x0015: // 0xFX15: delay_timer = VX
			*_delay_timer = _reg_v->at((*_opcode & 0x0F00) >> 8);
			*_reg_pc += 2;
			break;

		case 0x0018: // 0xFX18: sound_timer = VX
			*_sound_timer = _reg_v->at((*_opcode & 0x0F00) >> 8);
			break;

		case 0x001E: // 0xFX1E: I += VX
			*_reg_i += _reg_v->at((*_opcode & 0x0F00) >> 8);
			*_reg_pc += 2;
			break;

		case 0x0029: // 0xFX29: Setzt I zur Adresse des Sprites das den Buchstaben in VX repräsentiert
			*_reg_i = _reg_v->at((*_opcode & 0x0F00) >> 8) * 40;
			break;

		case 0x0033: { // 0xFX33
				unsigned short v = _reg_v->at((*_opcode & 0x0F00) >> 8);
				unsigned short h = v / 100;
				v -= 100 * h;
				unsigned short z = v / 10;
				v -= 10 * z;
				unsigned short e = v / 1;
				v -= 1 * e;
				if (e != 0)
					throw std::exception("BCD_ERR");

				_memory->at(*_reg_i) = h;
				_memory->at(*_reg_i + 1) = z;
				_memory->at(*_reg_i + 2) = e;

				*_reg_pc += 2;
			}
			break;

		case 0x0055: // 0xFX55: Speichert V0 - VX in Memory an der Adresse I
			for (int i = 0; i < ((*_opcode & 0x0F00) >> 8); i++) {
				_memory->at(*_reg_i + i) = _reg_v->at(i);
			}
			break;
			
		case 0x0065: // 0xFX65: Lädt Register V0 - VX aus der Memory ab der Adresse I
			for (int i = 0; i < ((*_opcode & 0x0F00) >> 8); i++) {
				_reg_v->at(i) = _memory->at(*_reg_i + i);
			}
			break;
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