#ifndef CONVERTER_HPP
#define CONVERTER_HPP

// Includes
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

#define SAFE_DELETE(X) {if(X!=nullptr){delete(X);X=nullptr;}}

// Converter
class Converter {
public:

	// -- Kon/Destruktor --
	Converter(std::string dmp_file);
	~Converter();

	// -- Methoden --
	void convert(std::string hex);

private:

	// -- Member Vars --
	std::ofstream *_ofstream;

	std::stringstream *_strs;

	int *_tmpNum;

};

#endif