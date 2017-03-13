#pragma once

#include "StateChild.h"


namespace StateNS {


class Title : public Child{
public:
	Title();
	~Title();
	void initialize();
	Child* update(const GrandParent*);
	void draw() const;

private:
	int mBackImg;
};




}