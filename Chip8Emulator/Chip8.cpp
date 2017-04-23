#include"Chip8.hpp"

// -- Konstruktor --
Chip8::Chip8() {
	// Alloc Memory
	_reg_v = new std::array<BYTE, REG_SIZE>();
	_stack = new std::array<unsigned short, STACK_SIZE>();
	_memory = new std::array<BYTE, MEM_SIZE>();
	_displayMem = new std::array<unsigned long, DISPLAY_SIZE>();
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