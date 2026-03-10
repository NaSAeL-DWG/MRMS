#include "pre.h"
#include "Classes.h"

int main() {
  // menu 
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Provide provider;
    Login ler(provider);
    bool exit = true;
    ler.login_enter();
	system("pause");
	return 0;
}
