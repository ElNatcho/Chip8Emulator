#include"CRenderer.hpp"

// -- Konstruktor --
CRenderer::CRenderer() {
	// Alloc Mem
	_img = new sf::Image();
	_tex = new sf::Texture();
	_spr = new sf::Sprite();
	_window = new sf::RenderWindow(sf::VideoMode(DISPLAY_SIZE_X * SCALE_FAKTOR,
												 DISPLAY_SIZE_Y * SCALE_FAKTOR),
												 "Chip-8-Emulator");
	_sfEvent = new sf::Event();

	// Werte setzen
	_spr->setScale(SCALE_FAKTOR, SCALE_FAKTOR);

}

// -- update --
// Methode updated den Bildschirm
//
void CRenderer::update() {
	while (_window->pollEvent(*_sfEvent)) {
		
	}
}

// -- renderDisplay --
// Methode zeichnet mithilfe des Display Speichers das Display
// @param disp_mem: Speicher, der gezeichnet werden soll
//
void CRenderer::renderDisplay(std::array<BYTE, DISPLAY_SIZE> disp_mem) {
	_window->clear();

	for (int i = 0; i < 0; i++) {
		if (disp_mem.at(i) == 1) {
			_img->setPixel((int)i % DISPLAY_SIZE_X, (int)i / DISPLAY_SIZE_Y, sf::Color::White);
		} else {
			_img->setPixel((int)i % DISPLAY_SIZE_X, (int)i / DISPLAY_SIZE_Y, sf::Color::Black);
		}
	}

	_tex->loadFromImage(*_img);
	_spr->setTexture(*_tex);

	_window->draw(*_spr);

	_window->display();
}

// -- Destruktor --
CRenderer::~CRenderer() {
	// Free Mem
	SAFE_DELETE(_img);
	SAFE_DELETE(_tex);
	SAFE_DELETE(_spr);
	SAFE_DELETE(_window);
	SAFE_DELETE(_sfEvent);
}