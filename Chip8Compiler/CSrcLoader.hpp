#ifndef CSRCLOADER_HPP
#define CSRCLOADER_HPP

// Includes
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"CStaticTools.hpp"

// CSrcLoader
class CSrcLoader {
public:

	// -- Kon/Destruktor --
	CSrcLoader();
	~CSrcLoader();

	// -- Methoden --
	void loadSrc(std::string path);
	std::vector<std::string> getSrcCode();

private:

	// -- Member Vars --
	std::ifstream *_ifstream;
	std::string *_tempStr;

	std::vector<std::string> *_src;

};

#endif