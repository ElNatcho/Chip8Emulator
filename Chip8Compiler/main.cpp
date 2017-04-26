#include"CSrcLoader.hpp"

int main() {
	CSrcLoader *ldr = new CSrcLoader();

	ldr->loadSrc("test.txt");
	
	SAFE_DELETE(ldr);

	return 0;
}