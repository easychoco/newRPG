#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {


class Load : public Child
{
public:
	Load();
	~Load();
	void initialize();
	Child* update(StateNS::Parent*);
	void draw() const;

};




}
}