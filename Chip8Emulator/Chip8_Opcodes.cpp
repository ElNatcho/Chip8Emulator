#include"Chip8.hpp"

// -- _setup_opcodes --
// Methode füllt das Opcodemethodenzeigerarray mit den Methoden
//
void Chip8::_setup_opcodes() {
	// Alloc Mem
	_opcodeTable = new std::map<short, funcPtr>();

	// Methoden in den table einfügen
	_opcodeTable->insert(std::make_pair(0x0000, &Chip8::clear_screen_0x00E0));
	_opcodeTable->insert(std::make_pair(0x000E, &Chip8::return_subr_0x00EE));
	_opcodeTable->insert(std::make_pair(0x1000, &Chip8::jump_0x1NNN));
	_opcodeTable->insert(std::make_pair(0x2000, &Chip8::call_subr_0x2NNN));
	_opcodeTable->insert(std::make_pair(0x3000, &Chip8::comp_0x3XNN));
	_opcodeTable->insert(std::make_pair(0x4000, &Chip8::compn_0x4XNN));
	_opcodeTable->insert(std::make_pair(0x5000, &Chip8::compr_0x5XY0));
	_opcodeTable->insert(std::make_pair(0x6000, &Chip8::setr_0x6XNN));
	_opcodeTable->insert(std::make_pair(0x7000, &Chip8::add_0x7XNN));
	_opcodeTable->insert(std::make_pair(0x8000, &Chip8::setr_0x8XY0));
	_opcodeTable->insert(std::make_pair(0x8001, &Chip8::bitOR_0x8XY1));
	_opcodeTable->insert(std::make_pair(0x8002, &Chip8::bitAND_0x8XY2));
	_opcodeTable->insert(std::make_pair(0x8003, &Chip8::bitXOR_0x8XY3));
	_opcodeTable->insert(std::make_pair(0x8004, &Chip8::addr_0x8XY4));
	_opcodeTable->insert(std::make_pair(0x8005, &Chip8::subr_0x8XY5));
	_opcodeTable->insert(std::make_pair(0x8006, &Chip8::bitShR_0x8XY6));
	_opcodeTable->insert(std::make_pair(0x8007, &Chip8::subr_0x8XY7));
	_opcodeTable->insert(std::make_pair(0x800E, &Chip8::bitShL_0x8XYE));
	_opcodeTable->insert(std::make_pair(0x9000, &Chip8::compnr_0x9XY0));
	_opcodeTable->insert(std::make_pair(0xA000, &Chip8::setI_0xANNN));
	_opcodeTable->insert(std::make_pair(0xB000, &Chip8::jumpR_0xBNNN));
	_opcodeTable->insert(std::make_pair(0xC000, &Chip8::setR_rand_0xCXNN));
	_opcodeTable->insert(std::make_pair(0xD000, &Chip8::drawSpr_0xDXYN));
	_opcodeTable->insert(std::make_pair(0xE00E, &Chip8::chkKeyR_0xEX9E));
	_opcodeTable->insert(std::make_pair(0xE001, &Chip8::chkNKeyR_0xEXA1));
	_opcodeTable->insert(std::make_pair(0xF007, &Chip8::setRTimer_0xFX07));
	_opcodeTable->insert(std::make_pair(0xF00A, &Chip8::waitFKey_0xFX0A));
	_opcodeTable->insert(std::make_pair(0xF015, &Chip8::setDTimer_0xFX15));
	_opcodeTable->insert(std::make_pair(0xF018, &Chip8::setSTimer_0xFX18));
	_opcodeTable->insert(std::make_pair(0xF01E, &Chip8::addI_0xFX1E));
	_opcodeTable->insert(std::make_pair(0xF029, &Chip8::setItoSpr_0xFX29));
	_opcodeTable->insert(std::make_pair(0xF033, &Chip8::set_BCD_0xFX33));
	_opcodeTable->insert(std::make_pair(0xF055, &Chip8::reg_dump_0xFX55));
	_opcodeTable->insert(std::make_pair(0xF065, &Chip8::reg_load_0xFX65));
}

// -- clear_screen_0x00E0 --
// Methode cleared das Display
//
void Chip8::clear_screen_0x00E0() {
	for (int i = 0; i < _displayMem->size(); i++)
		_displayMem->at(i) = 0;
	*_reg_pc += 2;
}

// -- return_subr_0x00EE --
// Methode "returned" von einer Subroutine
//
void Chip8::return_subr_0x00EE() {
	*_reg_sp -= 1;
	*_reg_pc = _stack->at(*_reg_sp);
}

// -- jump_0x1NNN --
// PC springt zu einer bestimmten Stelle
//
void Chip8::jump_0x1NNN() {
	*_reg_pc = 0x0FFF & *_opcode;
}

// -- call_subr_0x2NNN --
// Methode führt eine Subroutine aus
//
void Chip8::call_subr_0x2NNN() {
	_stack->at(*_reg_sp) = *_reg_pc;
	*_reg_sp += 1;
	*_reg_pc = 0x0FFF & *_opcode;
}

// -- comp_0x3XNN --
// Methode vergleicht ein Register und eine Zahl (==)
//
void Chip8::comp_0x3XNN() {
	if (_reg_v->at((*_opcode & 0x0F00) >> 8) == (*_opcode & 0x00FF))
		*_reg_pc += 4;
	else
		*_reg_pc += 2;
}

// -- compn_0x4XNN --
// Methode vergleicht ein Register mit einer Zahl (!=)
// 
void Chip8::compn_0x4XNN() {
	std::cout << (int)_reg_v->at((*_opcode & 0x0F00) >> 8) << " " << ((*_opcode) & 0x00FF) << std::endl;
	if ((int)_reg_v->at((*_opcode & 0x0F00) >> 8) != (*_opcode & 0x00FF)) {
		*_reg_pc += 4;
	}
	else {
		*_reg_pc += 2;
	}
}

// -- compr_0x5XY0 --
// Methode vergleicht zwei Register (==)
//
void Chip8::compr_0x5XY0() {
	if (_reg_v->at((*_opcode & 0x0F00) >> 8) == _reg_v->at((*_opcode & 0x00F0) >> 4))
		*_reg_pc += 4;
	else
		*_reg_pc += 2;
}

// -- setr_0x6XNN --
// Methode ändert den Wert eines Registers (VX = NN)
//
void Chip8::setr_0x6XNN() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) = *_opcode & 0x00FF;
	//*_reg_pc += 2;
}

// -- add_0x7XNN --
// Methode addiert ein Register und eine Zahl
//
void Chip8::add_0x7XNN() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) += *_opcode & 0x00FF;
	//*_reg_pc += 2;
}

// -- setr_0x8XY0 --
// Methode ändert den Wert eines Registers zu dem Wert eines anderen Registers (VX = VY)
//
void Chip8::setr_0x8XY0() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) = _reg_v->at((*_opcode & 0x00F0) >> 4);
	//*_reg_pc += 2;
}

// -- bitOR_0x8XY1 --
// Methode berechnet das binäre ODER zweier Register (VX |= VY)
//
void Chip8::bitOR_0x8XY1() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) |= _reg_v->at((*_opcode & 0x00F0) >> 4);
	_reg_v->at(0xF) = 0;
	//*_reg_pc += 2;
}

// -- bitAND_0x8XY2 --
// Methode berechnet das binäre UND zweier Register (VX &= VY)
//
void Chip8::bitAND_0x8XY2() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) &= _reg_v->at((*_opcode & 0x00F0) >> 4);
	_reg_v->at(0xF) = 0;
	//*_reg_pc += 2;
}

// -- bitXOR_0x8XY3 --
// Methode berechnet das binäre exklusive ODER zweier Register (VX ^= VY)
//
void Chip8::bitXOR_0x8XY3() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) ^= _reg_v->at((*_opcode & 0x00F0) >> 4);
	_reg_v->at(0xF) = 0;
	//*_reg_pc += 2;
}

// -- addr_0x8XY4 --
// Methode addiert zwei Register (VX += VY)
//
void Chip8::addr_0x8XY4() {
	unsigned short e = _reg_v->at((*_opcode & 0x0F00) >> 8) + _reg_v->at((*_opcode & 0x00F0) >> 4);
	if (e > 0xFF)
		_reg_v->at(0xF) = 1;
	else
		_reg_v->at(0xF) = 0;
	_reg_v->at((*_opcode & 0x0F00) >> 8) = e & 0x0000FFFF;
	//*_reg_pc += 2;
}

// -- subr_0x8XY5 --
// Methode subtrahiert zwei Register (VX -= VY)
//
void Chip8::subr_0x8XY5() {
	short e = _reg_v->at((*_opcode & 0x0F00) >> 8) - _reg_v->at((*_opcode & 0x00F0) >> 4);
	if (e >= 0)
		_reg_v->at(0xF) = 1;
	else
		_reg_v->at(0xF) = 0;
	_reg_v->at((*_opcode & 0x0F00) >> 8) = e & 0x0000FFFF;
	//*_reg_pc += 2;
}

// -- bitShR_0x8XY6 --
//  Bitshift eines Registers nach rechts
//
void Chip8::bitShR_0x8XY6() {
	_reg_v->at(0xF) = _reg_v->at((*_opcode & 0x0F00) >> 8) & 0x01;
	_reg_v->at((*_opcode & 0x0F00) >> 8) >>= 1;
	//*_reg_pc += 2;
}

// -- subr_0x8XY7 -- 
// Methode subtrahiert zwei Register (VX = VY - VX)
//
void Chip8::subr_0x8XY7() {
	short e = _reg_v->at((*_opcode & 0x00F0) >> 4) - _reg_v->at((*_opcode & 0x0F00) >> 2);
	if (e >= 0)
		_reg_v->at(0xF) = 1;
	else
		_reg_v->at(0xF) = 0;
	_reg_v->at((*_opcode & 0x0F00) >> 8) = e & 0x0000FFFF;
	//*_reg_pc += 2;
}

// -- bitShL_0x8XYE --
// Bitshift eines Register nach links
//
void Chip8::bitShL_0x8XYE() {
	_reg_v->at(0xF) = (_reg_v->at((*_opcode & 0x0F00) >> 8) & 0xF000) >> 3;
	_reg_v->at((*_opcode & 0x0F00) >> 8) <<= 1;
	//*_reg_pc += 2;
}

// -- compnr_0x9XY0 --
// Methode vergleicht zwei Register (VX != VY)
//
void Chip8::compnr_0x9XY0() {
	if (_reg_v->at((*_opcode & 0x0F00) >> 8) != _reg_v->at((*_opcode & 0x00F0) >> 4))
		*_reg_pc += 4;
	else
		*_reg_pc += 2;
}

// -- setI_0xANNN --
// Methode setzt den Instruktionszeiger
//
void Chip8::setI_0xANNN() {
	*_reg_i = *_opcode & 0x0FFF;
	//*_reg_pc += 2;
}

// -- jumpR_0xBNNN --
// Methode springt zur Adresse NNN + VX
//
void Chip8::jumpR_0xBNNN() {
	*_reg_pc = (*_opcode & 0x0FFF) + _reg_v->at(0);
}

// -- setR_rand_0xCXNN --
// Methode setzt den Wert eines Register zu einer zufälligen Zahl
//
void Chip8::setR_rand_0xCXNN() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) = (rand() % 255) & (*_opcode & 0x00FF);
	//*_reg_pc += 2;
}

// -- drawSpr_0xDXYN --
// Methode zeichnet ein Sprite auf das Display
//
void Chip8::drawSpr_0xDXYN() {
	unsigned short x_pos = _reg_v->at((*_opcode & 0x0F00) >> 8);
	unsigned short y_pos = _reg_v->at((*_opcode & 0x00F0) >> 4);
	unsigned short h = *_opcode & 0x000F;
	unsigned short pixel;

	_reg_v->at(0xF) = 0;
	for (int y = 0; y < h; y++) {
		pixel = _memory->at(*_reg_i + y);
		for (int x = 0; x < 8; x++) {
			if ((pixel & (0x80 >> x)) != 0) {
				if (_displayMem->at(x + x_pos + ((y + y_pos) * 64)) == 1)
					_reg_v->at(0xF) = 1;
				_displayMem->at(x + x_pos + ((y + y_pos) * 64)) ^= 1;
			}
		}
	}
	*drawFlag = true;
	//*_reg_pc += 2;
}

// -- chkKeyR_0xEX9E --
// Methode prüft ob der Knopf (VX) gedrückt ist (KEY_PRESSED)
//
void Chip8::chkKeyR_0xEX9E() {
	if (_keyboardMem->at(_reg_v->at((*_opcode & 0x0F00) >> 8) & 0x000F) == KEY_PRESSED)
		*_reg_pc += 4;
	else
		*_reg_pc += 2;
}

// -- chkNKeyR_0xEXA1 -- 
// Methode prüft ob der Knopf (VX) gedrückt ist (KEY_NOT_PRESSED)
//
void Chip8::chkNKeyR_0xEXA1() {
	if (_keyboardMem->at(_reg_v->at((*_opcode & 0x0F00) >> 8) & 0x000F) != KEY_PRESSED)
		*_reg_pc += 4;
	else
		*_reg_pc += 2;
}

// -- setRTimer_0xFX07 --
// VX = delay_timer
//
void Chip8::setRTimer_0xFX07() {
	_reg_v->at((*_opcode & 0x0F00) >> 8) = *_delay_timer;
	//*_reg_pc += 2;
}

// -- waitFKey_0xFX0A --
// Methode unterbricht das Programm solange bis ein Knopf gedrückt wird
//
void Chip8::waitFKey_0xFX0A() {
	do {
		handleKeys();
	} while (*_keyPushedFlag);
	_reg_v->at((*_opcode & 0x0F00) >> 8) = *_lastKeyPushed;
	//*_reg_pc += 2;
}

// -- setDTimer_0xFX15 --
// delay_timer = VX
//
void Chip8::setDTimer_0xFX15() {
	*_delay_timer = _reg_v->at((*_opcode & 0x0F00) >> 8);
	//*_reg_pc += 2;
}

// -- setSTimer_0xFX18 --
// sound_timer = VX
//
void Chip8::setSTimer_0xFX18() {
	*_sound_timer = _reg_v->at((*_opcode & 0x0F00) >> 8);
	//*_reg_pc += 2;
}

// -- addI_0xFX1E --
// Methode addiert einen Wert zum Instruktionspointer
//
void Chip8::addI_0xFX1E() {
	*_reg_i += _reg_v->at((*_opcode & 0x0F00) >> 8);
	//*_reg_pc += 2;
}

// -- setItoSpr_0xFX29 -- 
// Methode setzt den Instruktionspointer zur Anfangsadresse eines Sprites
//
void Chip8::setItoSpr_0xFX29() {
	*_reg_i = _reg_v->at((*_opcode & 0x0F00) >> 8) * 40;
	//*_reg_pc += 2;
}

// -- set_BCD_0xFX33 --
// 
void Chip8::set_BCD_0xFX33() {
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

	//*_reg_pc += 2;
}

// -- reg_dump_0xFX55 --
// Methode speichert die aktuellen Register(V0-VX) an der Adresse des Instruktionspointers
//
void Chip8::reg_dump_0xFX55() {
	for (int i = 0; i < ((*_opcode & 0x0F00) >> 8); i++) {
		_memory->at(*_reg_i + i) = _reg_v->at(i);
	}
	//*_reg_pc += 2;
}

// -- reg_load_0xFX65 --
// Methode lädt Daten ab der Adresse des Instruktionspointers in die aktuellen Register (V0-VX)
//
void Chip8::reg_load_0xFX65() {
	for (int i = 0; i < ((*_opcode & 0x0F00) >> 8); i++) {
		_reg_v->at(i) = _memory->at(*_reg_i + i);
	}
	//*_reg_pc += 2;
}