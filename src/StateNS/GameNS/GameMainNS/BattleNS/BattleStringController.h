#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


class StringController
{
public:
	StringController();
	~StringController();
	void initialize();
	void update();
	void draw() const;
	void addMessage(string _message);
	void resetMessage();

private:
	int mFrameImg;
	int mUpperImg;
	int mTime;
	int mTimeFromLastAdd;
	int message_dy;

	//枠に表示する文字のクラス
	class FrameMessage
	{
	public:
		FrameMessage(string);
		~FrameMessage();
		void update();
		void draw(int x, int y) const;
		void addNext(FrameMessage*);
		void setEnd(bool);
		FrameMessage* get(int);

	private:
		bool isEnd;
		string message;
		//FrameMessage* prev;
		FrameMessage* next;
	};

	//FrameMessageの先頭
	FrameMessage* beginMessage;

	//frameMessageの最後尾
	FrameMessage* endMessage;

	//legacy
	vector<string> frameMessage{};


	//文字を書く位置, BattleFrame.pngに依存
	//array<const int, 5> frameLine{ 345, 370, 395, 420, 445 };

};
















}
}
}
}