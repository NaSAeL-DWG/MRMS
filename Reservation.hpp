#pragma once
#include "pre.h"

class Reservation
{
public:
	string m_r_id;
	string m_stu_id;
	string m_room_id;
	string m_day;
	string m_time;
	string m_pass; //0未通过 1通过 2待审核 //3已取消
	int m_room_sys_id;//123 roomid
	int m_day_sys_id;//01234 周一-周五
	int m_time_sys_id;//01 上午下下午

	Reservation(string id, string stu_id, string room_id, string day, string time,string pass,int rm_id,int day_id,int time_id);
	void show_details();
	void change_status(string new_status);
	void pass_res();
	void denied_res();
	void cancel_res();
	string get_res_id();
};