#include "pre.h"
#include "Classes.h"

void admin_create(fstream &file);
Admin *admin_login(Provide* ppp);


int main() {
  // menu 
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::shared_ptr<Provide> provider = std::make_shared<Provide>();
    Provide* prov = &(*provider);
    Login ler(prov);
    bool exit = true;
    ler.login_enter();
	system("pause");
	return 0;
}
