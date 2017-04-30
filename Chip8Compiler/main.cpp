#include"CCompiler.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Chip8Compiler <SRC_FILE> <ROM_NAME>" << std::endl;
		return 0;
	}


	CCompiler *compiler = new CCompiler();

	compiler->loadSrc(argv[1]);
	compiler->compile();
	compiler->writeOpc(argv[2]);

	delete(compiler);

	return 0;
}