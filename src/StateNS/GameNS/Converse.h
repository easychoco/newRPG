#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {


class Converse : public Child
{
public:
	Converse();
	~Converse();
	void initialize();
	Child* update(StateNS::Parent*);
	void draw() const;

};




}
}