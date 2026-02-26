#include "Login.hpp"

void Login::login_enter()
{
    bool exit = true;
    while (exit) {
        // UI::clearScreen();
        UI::printBanner();
        std::cout << "  请选择你的身份:\n\n";
        UI::printOption(1, "学生");
        UI::printOption(2, "教师");
        UI::printOption(3, "管理员");
        UI::printOption(0, "退出系统");

        UI::printInputPrompt();

        int select = 0;
        cin >> select;

        switch (select) {
        case 1: // 学生身份
        	stu_login();
            break;
        case 2: // 老师身份
        	tea_login();
            break;
        case 3: // 管理员身份
            admin_login();
            break;
        case 0: // 退出系统
            provider->save_all();
            exit = !exit;
            break;
        default:
            cout << "输入有误，请重新选择！\n" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
}

void Login::admin_login()
{
    string id = "", pwd = "";
    bool exit = true;
    UI::clearScreen();
    UI::printHeader("管理员账号登录");
    cout << UI::BLUE << "  请输入id:\n" << UI::RESET;
    UI::printTextInputPrompt();
    cin >> id;
    cout << UI::BLUE << "  请输入密码:\n" << UI::RESET;
    UI::printTextInputPrompt();
    cin >> pwd;
    //查找登录对象
    auto s = provider->admin_login(id, pwd);
    if (s == nullptr)
    {
        cerr << UI::RED << "  登录失败：错误的id或密码" << UI::RESET;
        return;
    }
    s->operMenu();
}

void Login::stu_login()
{
	string id = "", pwd = "";
	bool exit = true;
    UI::clearScreen();
    UI::printHeader("学生账号登录");
    cout << UI::BLUE << "  请输入学号:\n" << UI::RESET;
    UI::printTextInputPrompt();
    cin >> id;
    cout << UI::BLUE << "  请输入密码:\n" << UI::RESET;
    UI::printTextInputPrompt();
    cin >> pwd;
    //查找登录对象
    auto s =provider->stu_login(id, pwd);
    if (s == nullptr)
    {
        cerr << UI::RED << "  登录失败：错误的id或密码" << UI::RESET;
        return;
    }
    s->operMenu();
}

void Login::tea_login()
{
    string id = "", pwd = "";
    bool exit = true;
    UI::clearScreen();
    UI::printHeader("教师账号登录");
    cout << UI::BLUE << "  请输入职工号:\n" << UI::RESET;
    UI::printTextInputPrompt();
    cin >> id;
    cout << UI::BLUE << "  请输入密码:\n" << UI::RESET;
    UI::printTextInputPrompt();
    cin >> pwd;
    //查找登录对象
    auto s = provider->tea_login(id, pwd);
    if (s == nullptr)
    {
        cerr << UI::RED << "  登录失败：错误的id或密码" << UI::RESET;
        return;
    }
    s->operMenu();
}

