#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleStringController.h"
#include "..\MiddleMain.h"

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

	//メッセージ初期化
	sController->addMessage("");
	sController->addMessage("");
	sController->addMessage("");
	sController->addMessage("");

	sController->addMessage("まものがあらわれた！");
	
	//バトルに参加するキャラクターの配列を作成
	addActor();

	//はじめは行動決定の場面
	mChild = new Decide(actors);
}

Child* Main::update(GameParent* _parent)
{
	Child* next = this;

	mTime++;

	//背景の処理
	stage->update();

	BattleChild* nextChild = 0;

	//バトルの処理(Stateパターン)
	if(!finBattle())
		nextChild = mChild->update(aController, sController, actors);

	//シーケンス更新
	if (mChild != nextChild)
	{
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	if (finBattle())mFinTime++;
	
	//Sキーでフィールドへ
	if (mFinTime > 60 || Input_S())
		next = new MiddleMain(GameScene::SCENE_FIELD, 0);

	return next;
}

void Main::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "BattleMain");
	stage->draw();
	drawStatus(  0, 330 - players.size() * 40, players);//330はメッセージ枠の上端
	drawStatus(440, 330 - enemies.size() * 40, enemies);//330は(ry
	sController->draw();
	if(!finBattle())mChild->draw(aController);
	aController->draw();
}


//========================================================================
// 内部private関数
//========================================================================
void Main::addActor()
{
	//Actor配列の作成
	Actor::Status p1{ 0, "ゆうしゃ", false, 50, 8, 5, 8, 5, 5 };
	actors.push_back(new Player(p1));

	Actor::Status p2{ 1, "まほうつかい", false, 30, 1, 2, 10, 8, 10 };
	actors.push_back(new Player(p2));

	Actor::Status p3{ 2, "そうりょ", false, 60, 3, 10, 3, 10, 5 };
	actors.push_back(new Player(p3));

	Actor::Status p4{ 3, "ぶとうか", false, 40, 10, 10, 2, 2, 6 };
	actors.push_back(new Player(p4));

	Actor::Status e1{ 4, "てきだぞ", true, 100, 100, 100, 100, 100, 100 };
	actors.push_back(new Enemy(e1, 5));

	Actor::Status e2{ 5, "てきです", true, 100, 100, 100, 100, 100, 100 };
	actors.push_back(new Enemy(e2, 5));


	//playersとenemies配列の作成
	//参照によりactorsと同じインスタンスを使う
	for (auto &actor : actors)
	{
		if (actor->status.isEnemy)enemies.push_back(actor);
		else players.push_back(actor);
	}
}

void Main::drawStatus(int _x, int _y, const vector<Actor*>& _actor) const
{
	//描画する範囲の下端
	int bottom = _y + _actor.size() * 40;

	//てきとうに200
	int right = _x + 200;

	//枠を描画
	DrawBox(_x, _y, right, bottom, MyData::GLAY, true);

	//名前と体力を描画
	short i = 0;
	for (auto &actor : _actor)
	{
		//5とか7とかは要・微調整
		DrawFormatString(_x + 10, _y + 3 + 40 * i, MyData::BLACK, "%s %d / %d", actor->status.name, actor->getHP(), actor->status.maxHP);
		DrawBox(_x + 5, _y + 40 * i + 20, _x + right - 5, _y + 40 * i + 30, MyData::WHITE, false);
		DrawBox(_x + 7, _y + 40 * i + 22, _x + 7 + (right - 14) * actor->getHP() / actor->status.maxHP, _y + 40 * i + 28, MyData::GREEN, true);
		i++;
	}
}

bool Main::finBattle() const
{
	bool eFin = false;
	for (auto& ene : enemies)
	{
		eFin |= ene->isAlive();
	}

	bool pFin = false;
	{
		for (auto& player : players)
		{
			pFin |= player->isAlive();
		}
	}
	return !(eFin & pFin);
}



//========================================================================
// Decideクラス
//========================================================================
Decide::Decide(vector<Actor*> vec_act)
{
	initialize(vec_act);
}

Decide::~Decide() 
{
	while (!act_que.empty())act_que.pop();

	enemies.clear();
	enemies.shrink_to_fit();

	players.clear();
	players.shrink_to_fit();
}

//各ターンの初めに行われる処理
void Decide::initialize(vector<Actor*>& vec_act)
{
	//各actを初期化
	for (auto &act : vec_act)
	{
		act->initialize();
	}

	//enemyとplayerの配列を作成
	for (auto &actor : vec_act)
	{
		if (actor->isAlive())
		{
			if (actor->status.isEnemy)enemies.push_back(actor);
			else players.push_back(actor);
		}
	}

	//素早さ順にソート
	std::sort(vec_act.begin(), vec_act.end(), &Actor::cmp);

	//行動順のキューを作成
	for (auto &act : vec_act)
	{
		act_que.push(act);
	}
}

BattleChild* Decide::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	BattleChild* next = this;

	//攻撃を決定, 返り値は決まったかどうか(boolean)
	doneNum += (players[doneNum])->attack(_sController, enemies);		

	//全てのplayerの行動が決まったら
	if(doneNum >= (int)players.size())
	{
		//敵の行動を決める
		for (auto& ene : enemies)
		{
			ene->attack(_sController, players);
		}

		while (!act_que.empty())
		{
			//ActionControllerに追加
			_aController->addAction((act_que.front())->getAction());

			//先頭をpop
			act_que.pop();
		}

		//バトル場面へ移行
		next = new Battle();
		
	}
	return next;
}

void Decide::draw(ActionController* gomi) const
{
	(players[doneNum])->draw(enemies);
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

BattleChild* Battle::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	BattleChild* next = this;

	bool battleDone = _aController->update(_sController, _actors);

	if (battleDone)
	{
		next = new Decide(_actors);
	}

	//バトルが終わっていればFinishへ


	return next;
}

void Battle::draw(ActionController* _aController) const
{
	_aController->draw();
}





}
}
}
}