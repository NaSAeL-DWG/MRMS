#include "pre.h"
#include "Classes.h"

Reservation::Reservation(string id,string stu_id,string room_id,string day,string time, string pass, int rm_id, int day_id, int time_id)
{
	m_pass = pass;
	m_r_id = id;
	m_stu_id = stu_id;
	m_room_id = room_id;
	m_day = day;
	m_time = time;
	m_day_sys_id = day_id;
	m_room_sys_id = rm_id;
	m_time_sys_id = time_id;
}

void Reservation::show_details()
{
	cout << m_r_id + "\t   " + m_stu_id + "\t\t" + m_room_id + "\t" + m_day + "\t" + m_time + "\t" + m_pass ;
	//对齐按照中文后一个\t对齐
}

void Reservation::change_status(string new_status)
{
	m_pass = new_status;
}

void Reservation::cancel_res()
{
	m_pass = "3";
}

void Reservation::denied_res()
{
	m_pass = "0";
}

void Reservation::pass_res()
{
	m_pass = "1";
}

string Reservation::get_res_id()
{
	return m_r_id;
}
