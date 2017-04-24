#include"Chip8.hpp"

// -- clear_screen_0x00E0 --
// Methode cleared das Display
//
void Chip8::clear_screen_0x00E0() {

}

// -- return_subr_0x00EE --
// Methode "returned" von einer Subroutine
//
void Chip8::return_subr_0x00EE() {

}

// -- jump_0x1NNN --
// PC springt zu einer bestimmten Stelle
//
void Chip8::jump_0x1NNN() {

}

// -- call_subr_0x2NNN --
// Methode führt eine Subroutine aus
//
void Chip8::call_subr_0x2NNN() {

}

// -- comp_0x3XNN --
// Methode vergleicht ein Register und eine Zahl (==)
//
void Chip8::comp_0x3XNN() {

}

// -- compn_0x4XNN --
// Methode vergleicht ein Register mit einer Zahl (!=)
// 
void Chip8::compn_0x4XNN() {

}

// -- compr_0x5XY0 --
// Methode vergleicht zwei Register (==)
//
void Chip8::compr_0x5XY0() {

}

// -- setr_0x6XNN --
// Methode ändert den Wert eines Registers (VX = NN)
//
void Chip8::setr_0x6XNN() {

}

// -- add_0x7XNN --
// Methode addiert ein Register und eine Zahl
//
void Chip8::add_0x7XNN() {

}

// -- setr_0x8XY0 --
// Methode ändert den Wert eines Registers zu dem Wert eines anderen Registers (VX = VY)
//
void Chip8::setr_0x8XY0() {

}

// -- bitOR_0x8XY1 --
// Methode berechnet das binäre ODER zweier Register (VX |= VY)
//
void Chip8::bitOR_0x8XY1() {

}

// -- bitAND_0x8XY2 --
// Methode berechnet das binäre UND zweier Register (VX &= VY)
//
void Chip8::bitAND_0x8XY2() {

}

// -- bitXOR_0x8XY3 --
// Methode berechnet das binäre exklusive ODER zweier Register (VX ^= VY)
//
void Chip8::bitXOR_0x8XY3() {

}

// -- addr_0x8XY4 --
// Methode addiert zwei Register (VX += VY)
//
void Chip8::addr_0x8XY4() {

}

// -- subr_0x8XY5 --
// Methode subtrahiert zwei Register (VX -= VY)
//
void Chip8::subr_0x8XY5() {

}

// -- bitShR_0x8XY6 --
//  Bitshift eines Registers nach rechts
//
void Chip8::bitShR_0x8XY6() {

}

// -- subr_0x8XY7 -- 
// Methode subtrahiert zwei Register (VX = VY - VX)
//
void Chip8::subr_0x8XY7() {

}

// -- bitShL_0x8XYE --
// Bitshift eines Register nach links
//
void Chip8::bitShL_0x8XYE() {

}

// -- compnr_0x9XY0 --
// Methode vergleicht zwei Register (VX != VY)
//
void Chip8::compnr_0x9XY0() {

}

// -- setI_0xANNN --
// Methode setzt den Instruktionszeiger
//
void Chip8::setI_0xANNN() {

}

// -- jumpR_0xBNNN --
// Methode springt zur Adresse NNN + VX
//
void Chip8::jumpR_0xBNNN() {

}

// -- setR_rand_0xCXNN --
// Methode setzt den Wert eines Register zu einer zufälligen Zahl
//
void Chip8::setR_rand_0xCXNN() {

}

// -- drawSpr_0xDXYN --
// Methode zeichnet ein Sprite auf das Display
//
void Chip8::drawSpr_0xDXYN() {

}

// -- chkKeyR_0xEX9E --
// Methode prüft ob der Knopf (VX) gedrückt ist (KEY_PRESSED)
//
void Chip8::chkKeyR_0xEX9E() {

}

// -- chkNKeyR_0xEXA1 -- 
// Methode prüft ob der Knopf (VX) gedrückt ist (KEY_NOT_PRESSED)
//
void Chip8::chkNKeyR_0xEXA1() {

}

// -- setRTimer_0xFX07 --
// VX = delay_timer
//
void Chip8::setRTimer_0xFX07() {

}

// -- waitFKey_0xFX0A --
// Methode unterbricht das Programm solange bis ein Knopf gedrückt wird
//
void Chip8::waitFKey_0xFX0A() {

}

// -- setDTimer_0xFX15 --
// delay_timer = VX
//
void Chip8::setDTimer_0xFX15() {

}

// -- setSTimer_0xFX18 --
// sound_timer = VX
//
void Chip8::setSTimer_0xFX18() {

}

// -- addI_0xFX1E --
// Methode addiert einen Wert zum Instruktionspointer
//
void Chip8::addI_0xFX1E() {

}

// -- setItoSpr_0xFX29 -- 
// Methode setzt den Instruktionspointer zur Anfangsadresse eines Sprites
//
void Chip8::setItoSpr_0xFX29() {

}

// -- set_BCD_0xFX33 --
// 
void Chip8::set_BCD_0xFX33() {

}

// -- reg_dump_0xFX55 --
// Methode speichert die aktuellen Register(V0-VX) an der Adresse des Instruktionspointers
//
void Chip8::reg_dump_0xFX55() {

}

// -- reg_load_0xFX65 --
// Methode lädt Daten ab der Adresse des Instruktionspointers in die aktuellen Register (V0-VX)
//
void Chip8::reg_load_0xFX65() {

}