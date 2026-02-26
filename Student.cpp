#include "pre.h"
#include "Classes.h"

Student::Student(string id, string name, string pwd)
{
	m_id = id;
	m_name = name;
	m_pwd = pwd;
}

inline void Student::operMenu()
{
    bool exit = true;
    while (exit) {
        UI::clearScreen();
        UI::printHeader("学生操作面板");
        UI::printOption(1, "申请预约");
        UI::printOption(2, "查看自身的预约");
        UI::printOption(3, "查看所有预约");
        UI::printOption(4, "取消预约");
        UI::printOption(5, "注销登录");

        UI::printInputPrompt();

        int select = 0;
        cin >> select;

        switch (select) {
        case 1:
            create_stu_order();
            break;
        case 2:
            check_stu_own_order();
            break;
        case 3:
            check_all_order();
            break;
        case 4:
            cancel_own_order();
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

void Student::init_add_res_in_sheet(std::weak_ptr<Reservation> wptr1)
{
	RES_SHEET.push_back(wptr1);
}

void Student::create_stu_order()
{
    UI::clearScreen();
    UI::printHeader("学生操作面板-申请预约");
    std::cout << "  请选择要申请的教室:\n\n";
    UI::printOption(1, "机房1");
    UI::printOption(2, "机房2");
    UI::printOption(3, "机房3");
    UI::printInputPrompt();

    int select1;
    cin >> select1;
    if (select1>3||select1<0)
    {
        UI::clearScreen();
        cout << UI::RED << "未知的输入\n" << UI::RESET << endl;
        system("pause");
        return;
    }

    UI::clearScreen();
    UI::printHeader("学生操作面板-申请预约");
    std::cout << "  请选择要申请的日期:\n\n";
    UI::printOption(1, "周一");
    UI::printOption(2, "周二");
    UI::printOption(3, "周三");
    UI::printOption(4, "周四");
    UI::printOption(5, "周五");
    UI::printInputPrompt();
    int select2;
    cin >> select2;
    if (select2> 5 || select2 < 0)
    {
        UI::clearScreen();
        cout << UI::RED << "未知的输入\n" << UI::RESET << endl;
        system("pause");
        return;
    }

    UI::clearScreen();
    UI::printHeader("学生操作面板-申请预约");
    std::cout << "  请选择要申请的时段:\n\n";
    UI::printOption(1, "上午");
    UI::printOption(2, "下午");
    UI::printInputPrompt();
    int select3;
    cin >> select3;
    if (select3 > 2 || select3 < 0)
    {
        UI::clearScreen();
        cout << UI::RED << "未知的输入\n" << UI::RESET << endl;
        system("pause");
        return;
    }
    UI::clearScreen();
    UI::printHeader("学生操作面板-申请预约");
    string out1="  您要申请:";
    string out2 = "";
    string out3 = "";
    string out4 = "";
    if (select1 == 1) out2 += " 机房1 "; if (select1 == 2) out2 += " 机房2 "; if (select1 == 3) out2 += " 机房3 ";
    if (select2 == 1) out3 += " 周一 "; if (select2 == 2) out3 += " 周二 "; if (select2 == 3) out3 += " 周三 "; if (select2 == 4) out3 += " 周四 "; if (select2 == 5) out3 += " 周五 "; 
    if (select3 == 1) out4 += " 上午 "; if (select3 == 2) out4 += " 下午 ";
    //查询当前时段的占用情况

	cout << out1 << UI::BLUE << out2 +out3+out4<< UI::RESET << "\n  该教室时段申请情况：" << UI::BLUE << provider->check_room_spare(select1,select2,select3) << UI::RESET << "\n  是否确认？(y/n):\n\n";

    UI::printTextInputPrompt();
    string select;
    cin >> select;
    if (select == "y")
    {
        this->RES_SHEET.push_back(provider->create_order(this->m_id,out2,out3,out4,select1,select2 - 1,select3 - 1));
        cout << UI::GREEN << " \n 提交成功！\n" << UI::RESET;
    }
    else if (select == "n");
    else cerr << UI::RED << "无效的输入"
        << UI::RESET << endl;
    system("pause");
}

void Student::check_stu_own_order()
{
    UI::clearScreen();
    UI::printHeader("学生操作面板-查看自身预约");
    std::cout << "  您共持有 " << UI::BLUE << RES_SHEET.size() << UI::RESET << " 个预约\n\n";
    UI::printDash("预约详细");
    cout << UI::BOLD<<UI::BLUE << "预约编号   申请人学号\t机房\t日期\t时段\t订单状态\n" << UI::RESET;
    for (auto it = RES_SHEET.begin();it!=RES_SHEET.end();it++)
    {
        if (it->lock()==nullptr) continue;
        it->lock()->show_details();
        cout << "\n";
    }
    cout << UI::GRAY<<"\n注: 订单状态解释： 0未通过 1通过 2待审核 3已取消 \n\n"<< UI::RESET;
    system("pause");
}

void Student::check_all_order()
{
    UI::clearScreen();
    UI::printHeader("学生操作面板-查看全部预约");
    std::cout << "  当前共有 " << UI::BLUE << provider->get_order_num() << UI::RESET << " 个预约\n\n";
    //获取总预约表指针
    auto ALL_RES_SHEET = provider->get_all_order();

    UI::printDash("预约详细");
    cout << UI::BOLD << UI::BLUE << "预约编号   申请人学号\t机房\t日期\t时段\t订单状态\n" << UI::RESET;
    for (auto it = ALL_RES_SHEET.begin(); it != ALL_RES_SHEET.end(); it++)
    {
        auto itt = *it;
        itt->show_details();
        cout << "\n";
    }
    cout << UI::GRAY << "\n注: 订单状态解释： 0未通过 1通过 2待审核 3已取消 \n\n" << UI::RESET;
    system("pause");
}

void Student::cancel_own_order()
{
    UI::clearScreen();
    UI::printHeader("学生操作面板-关闭预约");
    std::cout << "  您共持有 " << UI::BLUE << RES_SHEET.size() << UI::RESET << " 个预约\n\n";
    UI::printDash("预约详细");
    cout << UI::BOLD << UI::BLUE << "预约编号   申请人学号\t机房\t日期\t时段\t订单状态\n" << UI::RESET;
    for (auto it = RES_SHEET.begin(); it != RES_SHEET.end(); it++)
    {
        it->lock()->show_details();
        cout << "\n";
    }
    cout << UI::GRAY << "\n注: 订单状态解释： 0未通过 1通过 2待审核 3已取消 \n\n" << UI::RESET;
    cout << UI::BLUE << "  请输入你要关闭的订单的订单编号:\n" << UI::RESET;
    UI::printTextInputPrompt();
    string choice;
    cin >> choice;
    //检查输入是否合法,获取目标位置
    bool input_passed = false;
    auto wp = RES_SHEET.begin();
    for (auto it = RES_SHEET.begin(); it != RES_SHEET.end(); it++)
    {
        if (it->lock()->get_res_id()==choice)
        {
            input_passed = true;
            wp = it;
            break;
        }
    }
    UI::clearScreen();
    UI::printHeader("学生操作面板-关闭预约");
    if (input_passed)
    {
	    //通过，开始更改
       // wp->lock()->cancel_res();
        provider->cancel_order(wp->lock());
        cout << UI::GREEN << "  预约 " << wp->lock()->get_res_id() << " 现已取消。\n\n" << UI::RESET;

    }else
    {
        cout << UI::RED << "  错误的预约编号\n\n" << UI::RESET;

    }

    system("pause");
}
