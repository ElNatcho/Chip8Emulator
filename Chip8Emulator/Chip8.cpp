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
	_old_pc = new unsigned short;

	_delay_timer = new BYTE;
	_sound_timer = new BYTE;

	_opcode = new unsigned short;

	drawFlag = new bool;
	progDone = new bool;

	_keyPushedFlag = new bool;
	_lastKeyPushed = new BYTE;

	_progLoader = new CProgLoader();

	_setup_opcodes();
}

// -- init --
// Methode initialisiert den Emulator (Register/Memory)
//
void Chip8::init() {
	// Memory clearen
	for (int i = 0; i < _memory->size(); i++)
		_memory->at(i) = 0;

	// Fontset in den Speicher laden
	for (int i = 0; i < FONTSET_SIZE; i++)
		_memory->at(i) = chip8_fontset[i];

	// Register clearen
	for (int i = 0; i < _reg_v->size(); i++) // V-Register clearen
		_reg_v->at(i) = 0;
	*_reg_i  = 0; // Addr-Reg zurücksetzen
	*_reg_sp = 0; // Stack-Ptr zurücksetzen
	*_reg_pc = 0; // Prog-Counter zurücksetzen
	*_old_pc = 0; // Prog-Counter (Prüfvariable) zurücksetzen

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
	*drawFlag = false;

}

// -- loadProg --
// Methode lädt ein Program in den Speicher
// @prog_path: Pfad zum/Name des Programms, dass geladen werden soll
//
void Chip8::loadProg(std::string prog_path) {
	_progLoader->loadProg(prog_path, _memory);

	*_reg_pc = 0x200;
	*_old_pc = 0x200;
}

// -- execute --
// Methode führt einen Emulationszyklus aus
//
void Chip8::execute() {
	// DrawFlag zurücksetzen
	*drawFlag = false;

	// Testen ob der PC noch im Speicherbereich liegt
	if (*_reg_pc > 4094) {
		std::cout << "PC out of Range: " << *_reg_pc << std::endl;
		*progDone = true;
		return;
	}

	// Fetch opcode
	*_opcode = _memory->at(*_reg_pc) << 8 | _memory->at(*_reg_pc + 1);

	std::cout << "AktuellerOpcode: " << std::hex << *_opcode << std::dec << std::endl;

	// Decode opcode

	// Instruktion ausführen
	if ((*_opcode & 0xF000) == 0x0000 || (*_opcode & 0xF000) == 0x8000 ||
		(*_opcode & 0xF000) == 0xE000)
		_it = _opcodeTable->find(*_opcode & 0xF00F);
	else if ((*_opcode & 0xF000) == 0xF000)
		_it = _opcodeTable->find(*_opcode & 0xF0FF);
	else
		_it = _opcodeTable->find(*_opcode & 0xF000);

	if (_it != _opcodeTable->end())
		(this->*(_it->second))();

	// PC erhöhen
	if (*_reg_pc == *_old_pc)
		*_reg_pc += 2;

	*_old_pc = *_reg_pc;

	// Timer updaten
	if (*_delay_timer > 0)
		*_delay_timer -= 1;
	if (*_sound_timer > 0) {
		*_sound_timer -= 1;
		if(*_sound_timer == 0)
			std::cout << "BUZZ" << std::endl;
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

// -- getDisplayMem --
// Methode gibt den Speicher des Displays zurück
//
std::array<BYTE, DISPLAY_SIZE> Chip8::getDisplayMem() {
	return *_displayMem;
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
	SAFE_DELETE(_old_pc);

	SAFE_DELETE(_delay_timer);
	SAFE_DELETE(_sound_timer);

	SAFE_DELETE(_opcode);

	SAFE_DELETE(drawFlag);
	SAFE_DELETE(progDone);

	SAFE_DELETE(_keyPushedFlag);
	SAFE_DELETE(_lastKeyPushed);

	SAFE_DELETE(_progLoader);
}