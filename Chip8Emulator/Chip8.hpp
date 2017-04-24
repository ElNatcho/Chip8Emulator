#ifndef CHIP8_HPP
#define CHIP8_HPP

// Includes
#include<SFML\Graphics.hpp>
#include<iostream>
#include<array>

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

	bool *_keyPushedFlag;
	BYTE *_lastKeyPushed;

};

#endif