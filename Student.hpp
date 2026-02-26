#pragma once
#include "pre.h"
#include "Identity.h"
#include "Reservation.hpp"

class Student : public Identity {
public:
	Student(string id, string name, string pwd);

	std::vector<std::weak_ptr<Reservation>> RES_SHEET; //学生自己的申请表
	void operMenu() override;

	//初始化表函数
	void init_add_res_in_sheet(std::weak_ptr<Reservation> wptr1);

	//功能
	void create_stu_order();
	void check_stu_own_order();
	void check_all_order();
	void cancel_own_order();
	//void sign_out();
};

