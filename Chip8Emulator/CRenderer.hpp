#ifndef CRENERER_HPP
#define CRENERER_HPP

// Includes
#include<SFML\Graphics.hpp>
#include<iostream>
#include<array>
#include"Chip8.hpp"

#define SCALE_FAKTOR 10

// CRenderer
class CRenderer {
public:

	// -- Kon/Destruktor --
	CRenderer();
	~CRenderer();

	// -- Methoden --
	void update();
	void renderDisplay(std::array<BYTE, DISPLAY_SIZE> disp_mem);

private:

	// -- Member Vars --
	sf::RenderWindow *_window;
	sf::Event		 *_sfEvent;

	sf::Image   *_img;
	sf::Texture *_tex;
	sf::Sprite  *_spr;

};


#endif