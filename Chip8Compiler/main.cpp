#include"CCompiler.hpp"

int main() {
	CCompiler *compiler = new CCompiler();

	compiler->loadSrc("test.txt");
	compiler->compile();

	delete(compiler);

	return 0;
}