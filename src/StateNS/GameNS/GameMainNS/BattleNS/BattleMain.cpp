#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleStringController.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {


Main::Main()
{
	initialize();
}

Main::~Main()
{

}

void Main::initialize()
{
	stage = new Stage();
	aController = new ActionController();
	sController = new StringController();

	mNext = GameScene::SCENE_NONE;
	mTime = 0;

	//メッセージ追加
	sController->addMessage("ゆうしゃはどうする？");
	sController->addMessage("魔物が現れた！");
	sController->addMessage("line two");
	sController->addMessage("line one");


	//バトルに参加するキャラクターの配列を作成
	addActor();

	//素早さ順にソート
	sort(actors.begin(), actors.end());

	//はじめは行動決定の場面
	mChild = new Decide(actors);


}

void Main::update(GameParent* _parent)
{
	mTime++;

	//背景の処理
	stage->update();

	//if (mTime % 60 == 1)newTurn();

	//バトルの処理(Stateパターン)
	BattleChild* next = mChild->update(this);

	//シーケンス更新
	if (mChild != next)
	{
		SAFE_DELETE(mChild);
		mChild = next;
	}

	//Sキーでフィールドへ
	if (Input_S())
		mNext = GameScene::SCENE_FIELD;

}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "BattleMain");
	stage->draw();
	mChild->draw();
	sController->draw();
}

//次の場面を返す
GameScene Main::changeScene()
{
	return mNext;
}

//ActionControllerにActionを追加する
void Main::addAction(Action* a) { aController->addAction(a); }

//========================================================================
// 内部private関数
//========================================================================
void Main::addActor()
{
	Actor::Status s = { 0, "me", false, 100, 10, 10, 10, 10, 5 };
	actors.push_back(new Player(s));

}

//========================================================================
// Decideクラス
//========================================================================
Decide::Decide(vector<Actor*>& vec_act)
{
	initialize(vec_act);
}

Decide::~Decide() 
{
	while (!act_que.empty())act_que.pop();
}

//各ターンの初めに行われる処理
void Decide::initialize(vector<Actor*> vec_act)
{
	//行動順のキューを作成
	for (auto &act : vec_act)
	{
		act_que.push(act);
	}
}

BattleChild* Decide::update(Main* _main)
{
	BattleChild* next = this;

	//攻撃を決定, 返り値は決まったかどうか
	bool doneAction = (act_que.front())->attack();

	//攻撃が決まったら
	if (doneAction)
	{
		//ActionControllerに追加
		_main->addAction((act_que.front())->getAction());

		//先頭をpop
		act_que.pop();

		//バトル場面へ移行
		if (act_que.empty())
		{
			next = new Battle();
		}
	}
	return next;
}

void Decide::draw() const
{

}


//========================================================================
// Battleクラス
//========================================================================
Battle::Battle()
{
	initialize();
}

Battle::~Battle()
{

}

void Battle::initialize()
{

}

BattleChild* Battle::update(Main* _main)
{
	BattleChild* next = this;

	return next;
}

void Battle::draw() const
{

}



}
}
}
}