#pragma once

#include "GameChild.h"
#include "GameMainNS\GameMain.h"

namespace StateNS {

class Parent;

namespace GameNS {


//SateNS::GameNS‚Å‚ÌParent‚Ì–ð–Ú
class Play : public Child
{
public:
	enum NextSequence
	{
		SEQ_TITLE,
		SEQ_PAUSE,
		SEQ_CONVERSE,
		SEQ_LOAD,
		SEQ_SAVE,
		SEQ_CLEAR,
		SEQ_OVER,

		SEQ_NONE
	};


	Play();
	~Play();
	void initialize();
	Child* update(Parent*);
	void draw() const;
	void moveTo(NextSequence);

private:
	GameMainNS::GameMain* gameMain;
	NextSequence mNextSeq;
};




}
}

