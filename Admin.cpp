#include "pre.h"
#include "Classes.h"

Admin::Admin(string id, string pwd, Provide* a) {
    provider = a;
    m_id = id;
    m_pwd = pwd;
}

void Admin::get_account_info()
{
    UI::clearScreen();
    UI::printHeader("管理员面板-查看账号");
    std::cout << "  请选择要查看的账号身份:\n\n";
    UI::printOption(1, "学生");
    UI::printOption(2, "教师");
    UI::printInputPrompt();

    int select = 0;
    cin >> select;
    if (select == 1) get_stu_account_info();
    else if (select == 2) get_tec_account_info();
    else cerr << UI::RED << "无效的输入"
        << UI::RESET << endl;
    system("pause");
}

void Admin::get_stu_account_info()
{
	//要查表学生对象，要看其预约吗？似乎不用
    UI::clearScreen();
    UI::printHeader("管理员面板-查看学生账号");

    std::cout << "  当前共 "<<UI::BLUE <<provider->get_stu_num() <<UI::RESET<<" 名学生\n\n";

    UI::printDash("学生名单");
    cout << UI::BLUE << UI::BOLD << "\t学号\t姓名\n" << UI::RESET;
    for (const auto& stu : provider->STUDENT_SHEET)
    {
        cout << "\t" + stu.second->m_id << "\t" + stu.second->m_name << "\n";
    }
    cout << endl;
    UI::printDash("--------");
    std::cout << "\n  请输入要查询的学生的学号:\n\n";
    UI::printTextInputPrompt();
    string fid;
    cin >> fid;
    //开始查找
    std::weak_ptr<Student> wptrt = provider->get_stu_account(fid);
    if (wptrt.lock() != nullptr) {
        string stu_id = wptrt.lock()->m_id;
        string stu_name = wptrt.lock()->m_name;
        string stu_pwd = wptrt.lock()->m_pwd;
        int stu_order_num = wptrt.lock()->RES_SHEET.size();
        //UI
        UI::clearScreen();
        UI::printHeader("管理员面板-查看学生账号");

        std::cout << UI::GREEN << "  查询成功！\n\n" << UI::RESET;
        std::cout << "  学号: " + stu_id + "\n  姓名: " + stu_name + "\n  密码: " + stu_pwd + "\n  已申请订单: " << stu_order_num<<endl;

    }
    else
    {
        UI::clearScreen();
        UI::printHeader("管理员面板-查看学生账号");

        std::cout << UI::RED << "  查询失败，学生不存在！\n\n" << UI::RESET;

    }


}

void Admin::get_tec_account_info()
{
    UI::clearScreen();
    UI::printHeader("管理员面板-查看教师账号");

    std::cout << "  当前共 " << UI::BLUE << provider->get_tea_num() << UI::RESET << " 名教师\n\n";

    UI::printDash("教师名单");
    cout << UI::BLUE << UI::BOLD << "\t职工号\t姓名\n" << UI::RESET;
    for (const auto& tea : provider->TEACHER_SHEET)
    {
        cout << "\t" + tea.second->m_id << "\t" + tea.second->m_name << "\n";
    }
    cout << endl;
    UI::printDash("--------");
    std::cout << "\n  请输入要查询的教师的职工号:\n\n";
    UI::printTextInputPrompt();
    string fid;
    cin >> fid;
    //开始查找
    std::weak_ptr<Teacher> wptrt = provider->get_tea_account(fid);
    if (wptrt.lock() != nullptr) {
        string tea_id = wptrt.lock()->m_id;
        string tea_name = wptrt.lock()->m_name;
        string tea_pwd = wptrt.lock()->m_pwd;
        //UI
        UI::clearScreen();
        UI::printHeader("管理员面板-查看教师账号");

        std::cout << UI::GREEN << "  查询成功！\n\n" << UI::RESET;
        std::cout << "  职工号: " + tea_id + "\n  姓名: " + tea_name + "\n  密码: " + tea_pwd << endl;

    }
    else
    {
        UI::clearScreen();
        UI::printHeader("管理员面板-查看教师账号");

        std::cout << UI::RED << "  查询失败，教师不存在！\n\n" << UI::RESET;

    }
}

inline void Admin::add_account_enter()
{
    UI::clearScreen();
    UI::printHeader("管理员面板-添加账号");
    std::cout << "  请选择添加的账号身份:\n\n";
    UI::printOption(1, "学生");
    UI::printOption(2, "教师");
    UI::printInputPrompt();

    int select = 0;
    cin >> select;
    if (select == 1) add_student_account();
    else if (select == 2) add_teacher_account();
    else cerr << UI::RED << "无效的输入"
        << UI::RESET << endl;
    system("pause");
}

inline void Admin::add_student_account()
{
    string id, name, pwd;
    //获取输入
    UI::clearScreen();
    while (true) {
        UI::printHeader("管理员面板-添加学生账号");
        std::cout << "  请输入学号: \n";
        UI::printTextInputPrompt();
        cin >> id;

        //查重
        if (!provider->check_account_available(0, id))
        {
            UI::clearScreen();
            cerr << UI::RED << "该id已存在"<< UI::RESET << endl;
            continue;
        }
        break;
    }

    UI::clearScreen();
    UI::printHeader("管理员面板-添加学生账号");
    std::cout << "  请输入姓名: \n";
    UI::printTextInputPrompt();
    cin >> name;
    UI::clearScreen();
    UI::printHeader("管理员面板-添加学生账号");
    std::cout << "  请输入密码: \n";
    UI::printTextInputPrompt();
    cin >> pwd;
    //添加到sheet中，使用provide逻辑
    provider->add_student_account(id, name, pwd);
    cout << UI::GREEN << "学生账号添加成功！[id] " << UI::GRAY << id << UI::GREEN
        << " [name] " << UI::GRAY << name << UI::GREEN
        << " [pwd] " << UI::GRAY << pwd << endl;

}

inline void Admin::add_teacher_account()
{
    string id, name, pwd;
    //获取输入
    UI::clearScreen();
    while (true) {
        UI::printHeader("管理员面板-添加教师账号");
        std::cout << "  请输入职工号: \n";
        UI::printTextInputPrompt();
        cin >> id;

        //查重
        if (!provider->check_account_available(1, id))
        {
            UI::clearScreen();
            cerr << UI::RED << "该id已存在" << UI::RESET << endl;
            continue;
        }
        break;
    }

    UI::clearScreen();
    UI::printHeader("管理员面板-添加教师账号");
    std::cout << "  请输入姓名: \n";
    UI::printTextInputPrompt();
    cin >> name;
    UI::clearScreen();
    UI::printHeader("管理员面板-添加教师账号");
    std::cout << "  请输入密码: \n";
    UI::printTextInputPrompt();
    cin >> pwd;
    //添加到sheet中，使用provide逻辑
    provider->add_teacher_account(id, name, pwd);
    cout << UI::GREEN << "教师账号添加成功！[id] " << UI::GRAY << id << UI::GREEN
        << " [name] " << UI::GRAY << name << UI::GREEN
        << " [pwd] " << UI::GRAY << pwd << endl;

}

void Admin::clear_reser()
{
    UI::clearScreen();
    UI::printHeader("管理员面板-清空预约");
    std::cout << "  当前共有 "<<UI::BLUE << provider->get_order_num() << UI::RESET <<" 个预约\n";
    std::cout << "  请确认是否要清空预约？(y/n):\n\n";

    UI::printTextInputPrompt();

    string select;
    cin >> select;
    if (select == "y")
    {
	    provider->clear_all_res();
        std::cout << "  清理成功！当前共有 " << UI::BLUE << provider->get_order_num() << UI::RESET << "个预约\n";
    }
    else if (select == "n") add_teacher_account();
    else cerr << UI::RED << "无效的输入"
        << UI::RESET << endl;
    system("pause");
}

void Admin::get_room_status()
{
    auto& r1 = provider->get_room1_sheet();
    auto& r2 = provider->get_room2_sheet();
    auto& r3 = provider->get_room3_sheet();
    
    UI::clearScreen();
    UI::printHeader("管理员面板-查看机房");
    cout << "\n";
    cout << "\t\t"; UI::printDash("机房1");
    cout << UI::BLUE << UI::BOLD << "\t \\"<<"\t周一 " << "\t周二 " << "\t周三 " << "\t周四 " << "\t周五\n ";
    cout << UI::BLUE << UI::BOLD << "\t上午" << UI::RESET << "\t" << r1[0][0] << "\t" << r1[1][0] << "\t" << r1[2][0] << "\t" << r1[3][0] << "\t" << r1[4][0] << "\n";
    cout << UI::BLUE << UI::BOLD << "\t下午" << UI::RESET << "\t" << r1[0][1] << "\t" << r1[1][1] << "\t" << r1[2][1] << "\t" << r1[3][1] << "\t" << r1[4][1] << "\n";
    cout << "\n";
    cout << "\t\t"; UI::printDash("机房2");
    cout << UI::BLUE << UI::BOLD << "\t \\" << "\t周一 " << "\t周二 " << "\t周三 " << "\t周四 " << "\t周五\n ";
    cout << UI::BLUE << UI::BOLD << "\t上午" << UI::RESET << "\t" << r2[0][0] << "\t" << r2[1][0] << "\t" << r2[2][0] << "\t" << r2[3][0] << "\t" << r2[4][0] << "\n";
    cout << UI::BLUE << UI::BOLD << "\t下午" << UI::RESET << "\t" << r2[0][1] << "\t" << r2[1][1] << "\t" << r2[2][1] << "\t" << r2[3][1] << "\t" << r2[4][1] << "\n";
    cout << "\n";
    cout << "\t\t"; UI::printDash("机房3");
    cout << UI::BLUE << UI::BOLD << "\t \\" << "\t周一 " << "\t周二 " << "\t周三 " << "\t周四 " << "\t周五\n ";
    cout << UI::BLUE << UI::BOLD << "\t上午" << UI::RESET << "\t" << r3[0][0] << "\t" << r3[1][0] << "\t" << r3[2][0] << "\t" << r3[3][0] << "\t" << r3[4][0] << "\n";
    cout << UI::BLUE << UI::BOLD << "\t下午" << UI::RESET << "\t" << r3[0][1] << "\t" << r3[1][1] << "\t" << r3[2][1] << "\t" << r3[3][1] << "\t" << r3[4][1] << "\n";
    cout << "\n";
    system("pause");

}


inline void Admin::operMenu() { //操作菜单
    bool exit = true;
    while (exit) {
        UI::clearScreen();
        UI::printHeader("ADMIN DASHBOARD");
        UI::printOption(1, "添加账号");
        UI::printOption(2, "查看账号");
        UI::printOption(3, "查看机房");
        UI::printOption(4, "清空预约");
        UI::printOption(5, "注销登录");

        UI::printInputPrompt();

        int select = 0;
        cin >> select;

        switch (select) {
        case 1:
            add_account_enter();
            break;
        case 2:
            get_account_info();
            break;
        case 3:
            get_room_status();
            break;
        case 4:
            clear_reser();
            break;
        case 5:
            exit = !exit;
            break;

        default:
            cout << UI::RED << "输入有误，请重新选择！\n" << UI::RESET << endl;
            system("pause");
            UI::clearScreen();
            break;
        }
    }
}