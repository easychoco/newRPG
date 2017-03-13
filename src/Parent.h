#pragma once

#include "StateNS\StateChild.h"

typedef StateNS::Child Child;


class Parent {
public:

	Parent();
	~Parent();
	void update();
	void draw() const;
	void initialize();

private:
	Child* mChild;
};