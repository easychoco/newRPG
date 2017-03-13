#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {


class Over : public Child
{
public:
	Over();
	~Over();
	void initialize();
	Child* update(StateNS::Parent*);
	void draw() const;

};




}
}