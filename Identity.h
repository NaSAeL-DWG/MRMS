#pragma once
#include "pre.h"
//#include "Provide.hpp"

class Provide;

class Identity {
public:
	virtual void operMenu() = 0;

	Provide* provider;
	std::string m_name;	
	std::string m_id;
	std::string m_pwd;
};
