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

	//�g�ɕ\�����镶���̃N���X
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

	//FrameMessage�̐擪
	FrameMessage* beginMessage;

	//frameMessage�̍Ō��
	FrameMessage* endMessage;

	//legacy
	vector<string> frameMessage{};


	//�����������ʒu, BattleFrame.png�Ɉˑ�
	//array<const int, 5> frameLine{ 345, 370, 395, 420, 445 };

};
















}
}
}
}