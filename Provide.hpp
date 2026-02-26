#pragma once
#include "pre.h"
#include "Admin.hpp"
#include "Student.hpp"
#include "Teacher.hpp"
#include "Reservation.hpp"
class Provide
{
public:
	std::vector<std::vector<int>> ROOM1_PEONUM_INFO; //房间1人数占用情况 x:周1-5 y:上午下午的学生id
	std::vector<std::vector<int>> ROOM2_PEONUM_INFO; //房间2人数占用情况 
	std::vector<std::vector<int>> ROOM3_PEONUM_INFO; //房间3人数占用情况 
	std::vector<int> ROOMS_STU_NUM; //目前订单数量
	std::queue<std::shared_ptr<Reservation>> APPLICANT_QUEUE; //申请队列，1.id 2.房间(123) 3.时段 可能换成query类
	std::unordered_map<std::string, std::shared_ptr<Student>> STUDENT_SHEET; //学生表 存取学生对象的智能指针用于管理生命周期 id,name,pwd
	std::unordered_map<std::string, std::shared_ptr<Teacher>> TEACHER_SHEET; //教师表
	std::vector<std::shared_ptr<Reservation>> RES_SHEET; //预约表 1.订单id（排列=id-1 )2.stu id 3.room id 4.申请day 5时段
    std::vector<int> ROOM_LIMIT; //房间限制人数
	std::vector<string> ADMIN_ACCOUNT;// 管理员 0 id 1 pwd
	std::shared_ptr<Admin> ADMIN;//ptr
public:
	Provide();
	//~Provide();

	void load_room_info();
	void load_room1_info();
	void load_room2_info();
	void load_room3_info();
	void load_stu_res_sheet();//这里加载订单
    void load_stu_sheet(); 
    void load_tec_sheet();
	void load_admin_account();
	

	void save_all();
	void save_room_info();
	void save_room1_info();
	void save_room2_info();
	void save_room3_info();
	void save_stu_res_sheet();
	void save_stu_sheet();
	void save_tec_sheet();
	void save_admin_account();

    void add_student_account(const string& id, const string& name, const string& pwd);
    void add_teacher_account(const string& id, const string& name, const string& pwd);
    bool check_account_available(const bool &mode, const string &id);

	
	std::weak_ptr<Student> get_stu_account(string id);
	std::weak_ptr<Teacher> get_tea_account(string id);
	int get_stu_num();
	int get_tea_num();
	int get_order_num();

	void clear_all_res();

	std::weak_ptr<Reservation> create_order(string stu_id, string room_id, string day, string time, int rm_id, int day_id, int time_id);
	std::vector<std::shared_ptr<Reservation>>& get_all_order();

	std::vector<std::vector<int>>& get_room1_sheet();
	std::vector<std::vector<int>>& get_room2_sheet();
	std::vector<std::vector<int>>& get_room3_sheet();
	string check_room_spare(int room, int day, int time);

	
	std::shared_ptr<Reservation>& get_applicant_queue();
	int get_applicant_queue_num();

	void pass_applicant_in_queue();
	void deny_applicant_in_queue();
	void skip_applicant_in_queue();
	
	std::shared_ptr<Student> stu_login(string id, string pwd);
	std::shared_ptr<Teacher> tea_login(string id, string pwd);
	std::shared_ptr<Admin> admin_login(string id, string pwd);
	void cancel_order(std::shared_ptr<Reservation>);

};
