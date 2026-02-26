#pragma once
#include "pre.h"
#include "Identity.h"

class Teacher : public Identity {
public:
	Teacher(string id, string name, string pwd);

	void operMenu() override;

	//功能
	void check_all_res();
	void exam_res();
};

