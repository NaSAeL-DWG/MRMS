#include "pre.h"
#include "Classes.h"


Teacher::Teacher(string id, string name, string pwd)
{
	m_id = id;
	m_name = name;
	m_pwd = pwd;
}

inline void Teacher::operMenu()
{
    bool exit = true;
    while (exit) {
        UI::clearScreen();
        UI::printHeader("教师操作面板");
        UI::printOption(1, "查看所有预约");
        UI::printOption(2, "审核预约");
        UI::printOption(3, "注销登录");

        UI::printInputPrompt();

        int select = 0;
        cin >> select;

        switch (select) {
        case 1:
            check_all_res();
            break;
        case 2:
            exam_res();
            break;
        case 3:
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

void Teacher::check_all_res()
{
    UI::clearScreen();
    UI::printHeader("教师操作面板-查看全部预约");
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

void Teacher::exam_res()
{
    UI::clearScreen();
    UI::printHeader("教师操作面板-查看全部预约");
    
    if (provider->get_applicant_queue_num() == 0)
    {
        cout << " 当前无预约待审核\n\n";
    }else
    {
	    //获取队列
	    
        bool exit = true;
        while(exit && provider->get_applicant_queue_num()>0)
        {
        	auto& APPLICANT_QUEUE = provider->get_applicant_queue();
            if (APPLICANT_QUEUE->m_pass == "3")
            {
                //已取消就跳过审核队列
                provider->skip_applicant_in_queue();
                continue;
            }
            UI::clearScreen();
            UI::printHeader("教师操作面板-审核预约");
            cout << " 当前共有 " << UI::BLUE << provider->get_applicant_queue_num() << UI::RESET << " 个预约待审核\n\n";
            cout << "  "; UI::printDash("当前预约");
            cout << "   申请id：" << UI::BLUE << APPLICANT_QUEUE->m_r_id << "\n" << UI::RESET;
            cout << "   申请人学号：" << UI::BLUE << APPLICANT_QUEUE->m_stu_id << "\n" << UI::RESET;
            cout << "   申请机房：" << UI::BLUE << APPLICANT_QUEUE->m_room_id+" "+ APPLICANT_QUEUE->m_day + " " + APPLICANT_QUEUE->m_time+ " " << "\n\n" << UI::RESET;
            cout << "  "; UI::printDash("--------");
            cout << UI::BLUE << "\n  请输入审核结果: \n" << UI::RESET;
            UI::printOption(1, "通过");
            UI::printOption(2, "拒绝");
            UI::printOption(9, "退出审核系统");
            UI::printInputPrompt();
            int select = 0;
            cin >> select;

            switch (select) {
            case 1:
                provider->pass_applicant_in_queue();
                break;
            case 2:
                provider->deny_applicant_in_queue();
                break;
            case 9:
                exit = !exit;
                break;

            default:
                cout << UI::RED << "输入有误，请重新选择！\n" << UI::RESET << endl;
                system("pause");
                UI::clearScreen();
                break;
            }

        }
        if (provider->get_applicant_queue_num() == 0)
        {
            UI::clearScreen();
            UI::printHeader("教师操作面板-查看全部预约");
            cout << " 当前无预约待审核\n\n";
        }
	    
		
    }
    system("pause");
}
