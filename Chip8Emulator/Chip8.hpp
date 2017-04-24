#ifndef CHIP8_HPP
#define CHIP8_HPP

// Includes
#include<SFML\Graphics.hpp>
#include<iostream>
#include<array>

// Vorwärtsdekleration
class CProgLoader;

#define SAFE_DELETE(X) {if(X!=nullptr){delete(X); X=nullptr;}}

#define MEM_SIZE   4096
#define REG_SIZE   16
#define STACK_SIZE 16

#define DISPLAY_SIZE 64 * 32
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
	std::array<BYTE , DISPLAY_SIZE> *_displayMem;

	unsigned short *_reg_i;
	unsigned short *_reg_sp;
	unsigned short *_reg_pc;

	BYTE *_delay_timer;
	BYTE *_sound_timer;

	unsigned short *_opcode;

	bool *_keyPushedFlag;
	BYTE *_lastKeyPushed;

	CProgLoader *_progLoader;

};

#endif