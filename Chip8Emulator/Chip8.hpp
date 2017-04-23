#ifndef CHIP8_HPP
#define CHIP8_HPP

// Includes
#include<iostream>
#include<array>

#define SAFE_DELETE(X) {if(X!=nullptr){delete(X); X=nullptr;}}

#define MEM_SIZE   4096
#define REG_SIZE   16
#define STACK_SIZE 16

#define DISPLAY_SIZE 64 * 32
#define KEYBOARD_SIZE 16

typedef unsigned char BYTE;

// Chip8
class Chip8 {
public:

	// -- Kon/Destruktor --
	Chip8();
	~Chip8();

	// -- Methoden --
	void init();
	void loadProg(std::string prog_path);

	void execute();
	void handleKeys();

	// -- Vars -- 
	bool *drawFlag;

private:

	// -- Member Vars --
	std::array<BYTE, MEM_SIZE> *_memory;
	std::array<BYTE, REG_SIZE> *_reg_v;
	std::array<BYTE, KEYBOARD_SIZE> *_keyboardMem;
	std::array<unsigned short, STACK_SIZE> *_stack;
	std::array<BYTE , DISPLAY_SIZE> *_displayMem;

	unsigned short *_reg_i;
	unsigned short *_reg_sp;
	unsigned short *_reg_pc;

	BYTE *_delay_timer;
	BYTE *_sound_timer;

	unsigned short *_opcode;

};

#endif