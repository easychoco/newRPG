#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {


class Pause : public Child
{
public:
	Pause();
	~Pause();
	void initialize();
	Child* update(StateNS::Parent*);
	void draw() const;

};




}
}