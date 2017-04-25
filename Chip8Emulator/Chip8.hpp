#ifndef CHIP8_HPP
#define CHIP8_HPP

// Includes
#include<SFML\Graphics.hpp>
#include<iterator>
#include<iostream>
#include<array>
#include<map>

// Vorwärtsdekleration
class CProgLoader;

#define SAFE_DELETE(X) {if(X!=nullptr){delete(X); X=nullptr;}}

#define MEM_SIZE   4096
#define REG_SIZE   16
#define STACK_SIZE 16

#define DISPLAY_SIZE  64 * 32
#define KEYBOARD_SIZE 16

#define KEY_NOT_PRESSED 0
#define KEY_PRESSED     1

typedef unsigned char BYTE;

const std::array<sf::Keyboard::Key, 16> _keys = { 
	sf::Keyboard::Key::X,
	sf::Keyboard::Key::Num1,
	sf::Keyboard::Key::Num2,
	sf::Keyboard::Key::Num3,
	sf::Keyboard::Key::Q,
	sf::Keyboard::Key::W,
	sf::Keyboard::Key::E,
	sf::Keyboard::Key::A,
	sf::Keyboard::Key::S,
	sf::Keyboard::Key::D,
	sf::Keyboard::Key::Z,
	sf::Keyboard::Key::C,
	sf::Keyboard::Key::Num4,
	sf::Keyboard::Key::R,
	sf::Keyboard::Key::F,
	sf::Keyboard::Key::V
};

const unsigned char chip8_fontset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

// Chip8
class Chip8 {
public:

	// Funktionszeiger
	typedef void(Chip8::*funcPtr)();

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
	bool *progDone;

private:

	// -- Member Vars --
	std::array<BYTE, MEM_SIZE> *_memory;
	std::array<BYTE, REG_SIZE> *_reg_v;
	std::array<BYTE, KEYBOARD_SIZE> *_keyboardMem;
	std::array<unsigned short, STACK_SIZE> *_stack;
	std::array<BYTE, DISPLAY_SIZE> *_displayMem;

	unsigned short *_reg_i;
	unsigned short *_reg_sp;
	unsigned short *_reg_pc;

	BYTE *_delay_timer;
	BYTE *_sound_timer;

	unsigned short *_opcode;

	bool *_keyPushedFlag;
	BYTE *_lastKeyPushed;

	CProgLoader *_progLoader;

	std::map<short, funcPtr> *_opcodeTable;
	std::map<short, funcPtr>::iterator _it;

	// -- Member Methods --

	void _setup_opcodes();

	// - OPCODES -
	void clear_screen_0x00E0();
	void return_subr_0x00EE();
	void jump_0x1NNN();
	void call_subr_0x2NNN();
	void comp_0x3XNN();
	void compn_0x4XNN();
	void compr_0x5XY0();
	void setr_0x6XNN();
	void add_0x7XNN();
	void setr_0x8XY0();
	void bitOR_0x8XY1();
	void bitAND_0x8XY2();
	void bitXOR_0x8XY3();
	void addr_0x8XY4();
	void subr_0x8XY5();
	void bitShR_0x8XY6();
	void subr_0x8XY7();
	void bitShL_0x8XYE();
	void compnr_0x9XY0();
	void setI_0xANNN();
	void jumpR_0xBNNN();
	void setR_rand_0xCXNN();
	void drawSpr_0xDXYN();
	void chkKeyR_0xEX9E();
	void chkNKeyR_0xEXA1();
	void setRTimer_0xFX07();
	void waitFKey_0xFX0A();
	void setDTimer_0xFX15();
	void setSTimer_0xFX18();
	void addI_0xFX1E();
	void setItoSpr_0xFX29();
	void set_BCD_0xFX33();
	void reg_dump_0xFX55();
	void reg_load_0xFX65();

};

#endif