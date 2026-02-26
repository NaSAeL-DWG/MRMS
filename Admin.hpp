#pragma once
#include "pre.h"
#include "Identity.h"

class Admin : public Identity {
public:
    Admin(string id, string pwd, Provide* a);

  //~Admin();

public:
    void operMenu() override;

  // 添加账号
  void add_account_enter();
  void add_student_account();
  void add_teacher_account();

  // 查看账号
    void get_account_info();
	void get_stu_account_info();
	void get_tec_account_info();


  // 查看机房
  void get_room_status();

  // 清空预约
  void clear_reser();

 // void sign_out();
};
