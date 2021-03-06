#include "BattleMain.h"
#include "BattleStage.h"
#include "BattleActor.h"
#include "BattleAction.h"
#include "BattlePlayer.h"
#include "BattleEnemy.h"
#include "BattleStringController.h"
#include "..\FieldNS\FieldMain.h"
#include "..\CharacterData.h"
#include "..\MonsterData.h"

#include "..\..\..\..\KeyInput.h"

#include<fstream>


namespace StateNS {
namespace GameNS {
namespace GameMainNS {
namespace BattleNS {

//戦闘BGM
int BattleChild::mBGM;


Main::Main(Vector2 _player, array<int, 4> _party, int _eneLevel, int _monsterID) : 
	mPlayerPos(_player),
	party(_party)
{
	initialize(_eneLevel, _monsterID);
}

Main::~Main()
{
	actors.clear();
	actors.shrink_to_fit();

	players.clear();
	players.shrink_to_fit();

	enemies.clear();
	enemies.shrink_to_fit();

	SAFE_DELETE(stage);
	SAFE_DELETE(aController);
	SAFE_DELETE(sController);
	SAFE_DELETE(mChild);

}

void Main::initialize(int _eneLevel, int _monsterID)
{
	stage = new Stage(_eneLevel);
	aController = new ActionController();
	sController = new StringController();

	mTime = 0;
	mIsEscape = false;

	sController->addMessage("まものがあらわれた！");
	
	//バトルに参加するキャラクターの配列を作成
	addActor(_eneLevel, _monsterID);

	//はじめは行動決定の場面
	mChild = new FirstAnimation(actors);
	mChild->mBGM = LoadSoundMem("Data/Sound/battle.mp3");
	PlaySoundMem(mChild->mBGM, DX_PLAYTYPE_LOOP);

}

Child* Main::update(GameMain* _parent)
{

	Child* next = this;

	mTime++;

	//背景の処理
	stage->update();

	//メッセージの処理
	sController->update();

	//バトルの処理(Stateパターン)
	BattleChild*  nextChild = mChild->update(aController, sController, actors);
	mIsEscape |= aController->escapeBattle();

	//バトルのシーケンス更新
	if (mChild != nextChild)
	{
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	if (Input_S() || mChild->goField())
	{
		//負けていたらこれがfalseになる
		bool f_player{ false };
		//f_playerとf_enemyにそれぞれisAlive()を足す(論理和)
		for (auto* act : actors)
		{
			if (!act->status.isEnemy) f_player |= act->isAlive();
		}

		next = new FieldNS::Main(mPlayerPos, mIsEscape || !f_player);
	}


	return next;
}

void Main::draw() const
{
	stage->draw();

	drawStatus(0, 330 - players.size() * 40, players);//330はメッセージ枠の上端
	sController->draw();
	aController->draw();
	for (auto e : enemies)
	{
		e->draw(enemies, players);
	}

	mChild->draw(aController);
}


//========================================================================
// 内部private関数
//========================================================================
void Main::addActor(int _eneLevel, int _monsterID)
{
	//Actor配列の作成

	//playerとenemy通しで使うID
	int battleID{ 0 };

	//ファイル読み込み
	std::ifstream player_in("Data/Text/PlayerData.txt");

	//ファイルがなかったら
	if (!player_in)
	{
		using std::endl;
		std::ofstream out("Data/Text/PlayerData.txt");
		out << "0 ゆうしゃ 0" << endl;
		out << "1 まほうつかい 0" << endl;
		out << "2 かくとうか 0" << endl;
		out << "3 けんじゃ 0" << endl;
		out.close();
		player_in.open("Data/Text/PlayerData.txt");
	}

	int p_lv{ 0 };//プレイヤ−のレベル

	//一人ずつ読み込んでvectorに追加
	while (player_in)
	{
		int _ID{ -10 };
		string name{ "dummy" };
		int exp{ 0 };

		player_in >> _ID >> name >> exp;

		//読み込みすぎていたらbreak
		if (player_in.eof())break;

		//IDが一致するキャラを探索
		auto player = std::find_if(toCharacter.begin(), toCharacter.end(),
			[_ID](auto &spec) { return (spec.ID == _ID); });

		if (player == toCharacter.end())
		{
			//対象のキャラクターがいなかったら終了
			assert(!"ファイルが不正です");
			exit(0);
		}

		//100は次のレベルまでの必要経験値
		p_lv = 1 + exp / CharacterData::nextExp;

		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//能力値を計算
		h = calcHP(player->s.h, p_lv);
		a = calcStatus(player->s.a, p_lv);
		b = calcStatus(player->s.b, p_lv);
		c = calcStatus(player->s.c, p_lv);
		d = calcStatus(player->s.d, p_lv);
		s = calcStatus(player->s.s, p_lv);

		//回復量を計算
		int r = h - abs(a - c);
		r = max(r / 3, min(a, c));

		Actor::Status status{ battleID, _ID, name, false, p_lv, h, a, b, c, d, r, s };
		actors.push_back(new Player(status, exp));

		battleID++;
	}

	assert(actors.size() != 0 && "ファイルが不正です");
	player_in.close();



	//ここから敵

	//通常エンカウント
	if (_monsterID == -10)
	{
		normalEncount(p_lv, _eneLevel, battleID);
	}
	//シンボルエンカウント
	else
	{
		symbolEncount(_monsterID, battleID);
	}


	//playersとenemies配列の作成
	//参照によりactorsと同じインスタンスを使う
	for (auto &actor : actors)
	{
		if (actor->status.isEnemy)enemies.push_back(actor);
		else players.push_back(actor);
	}
}

void Main::normalEncount(int _p_lv, int _eneLevel, int _battleID)
{
	//敵は1~4体
	short ene_num{ 1 };

	//プレイヤーのレベルがある程度高かったら敵が複数体出現
	if (_p_lv > _eneLevel * 5 - 2)ene_num += GetRand(3);

	for (int i = 0; i < ene_num; i++)
	{
		int tmp_ID = GetRand(4);
		EnemySpec::Status ene = (toEneStatus[_eneLevel - 1])[tmp_ID];

		//敵のレベルは _eneLevel - 1 * 5 + 0~3
		int ene_lv = (_eneLevel - 1) * 5 + GetRand(3);

		//自分のレベルが1なら敵レベルを0に
		ene_lv *= (_p_lv != 1);

		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//能力値を計算
		h = calcHP(ene.h, ene_lv);
		a = calcStatus(ene.a, ene_lv);
		b = calcStatus(ene.b, ene_lv);
		c = calcStatus(ene.c, ene_lv);
		d = calcStatus(ene.d, ene_lv);
		s = calcStatus(ene.s, ene_lv);

		//回復量を計算
		int r = h - abs(a - c);
		r = max(r / 3, min(a, c));

		Actor::Status e{ _battleID++, 0, ene.name, true, ene_lv, h, a, b, c, d, r, s, };

		int exp = min(300, max(10, 25 * (ene_lv - _p_lv + 5)));
		Enemy* tmpEnemy = new Enemy(e, exp);
		tmpEnemy->setName(ene.name);
		tmpEnemy->setData(ene.filename, 640 / (ene_num + 1) * (i + 1), 100);

		actors.push_back(tmpEnemy);
	}

}

void Main::symbolEncount(int _monsterID, int _battleID)
{
	//MonsterData.hから読み込んでactorsにpush

	short ene_num{ 1 };
	if (_monsterID == 3)ene_num = 3;
	for (int i = 0; i < ene_num; i++)
	{
		EnemySpec::Status ene = toMonster[_monsterID].status;

		int ene_lv = toMonster[_monsterID].Lv;
		int h{ -10 }, a{ -10 }, b{ -10 }, c{ -10 }, d{ -10 }, s{ -10 };

		//能力値を計算
		h = calcHP(ene.h, ene_lv);
		a = calcStatus(ene.a, ene_lv);
		b = calcStatus(ene.b, ene_lv);
		c = calcStatus(ene.c, ene_lv);
		d = calcStatus(ene.d, ene_lv);
		s = calcStatus(ene.s, ene_lv);

		//回復量を計算
		int r = h - abs(a - c);
		r = max(r / 3, min(a, c));

		Actor::Status e{ _battleID++, 0, ene.name, true, ene_lv, h, a, b, c, d, r, s, };

		int exp = 210 / ene_num;
		Enemy* tmpEnemy = new Enemy(e, exp);
		tmpEnemy->setName(ene.name);
		tmpEnemy->setData(ene.filename, 640 / (ene_num + 1) * (i + 1), 100);

		actors.push_back(tmpEnemy);
	}
}




void Main::drawStatus(int _x, int _y, const vector<Actor*>& _actor) const
{
	//描画する範囲の下端
	int bottom = _y + _actor.size() * 40;

	//てきとうに260
	int right = _x + 260;

	//枠を描画
	DrawBox(_x, _y, right, bottom, MyData::GLAY, true);

	//レベルと名前と体力を描画
	short i = 0;
	for (auto &actor : _actor)
	{
		//5とか7とかは要・微調整
		DrawFormatString(_x + 10, _y + 3 + 40 * i, MyData::BLACK, "lv.%d %s %d / %d", actor->status.level, actor->status.name.c_str(), actor->getHP(), actor->status.maxHP);
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

int Main::calcHP(int _HP, int _lv) const
{
	return _HP * _lv * 2 / 7 + 10;
}

int Main::calcStatus(int _value, int _lv) const
{
	return _value * _lv / 7 + 5;
}



//========================================================================
// ここからBattleChildたち
//========================================================================










//========================================================================
// FirstAnimationクラス
//========================================================================
FirstAnimation::FirstAnimation(vector<Actor*> gomi)
{
	initialize();
}

FirstAnimation::~FirstAnimation()
{
	SAFE_DELETE(mChild);
}

void FirstAnimation::initialize()
{
	mTime = 0;

	//どのアニメーションにするかを乱数で決定
	auto seed = GetRand(3);

	switch (seed)
	{
	case 0:mChild = new Anime1(); break;
	case 1:mChild = new Anime2(); break;
	case 2:mChild = new Anime3(); break;
	case 3:mChild = new Anime4(); break;
	default:assert(!"不正なAnime");
	}
}

//引数は使わない
BattleChild* FirstAnimation::update(ActionController*, StringController*, vector<Actor*> _actors)
{
	BattleChild* next = this;

	mTime++;
	if (mTime > 60)next = new Decide(_actors);

	return next;

}

void FirstAnimation::draw(ActionController*) const
{
	mChild->draw(mTime);
}

void FirstAnimation::Anime1::draw(int _time) const
{
	DrawBox(0, 0, 640, 480 - _time * 8, MyData::BLACK, true);
}

void FirstAnimation::Anime2::draw(int _time) const
{
	DrawBox(0, _time * 8, 640, 480, MyData::BLACK, true);
}

void FirstAnimation::Anime3::draw(int _time) const
{
	int draw_x1{ _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y1{ _time * 4 };
	int draw_x2{ 640 - _time * 16 / 3 };//16 / 3 = 320 / 60
	int draw_y2{ 480 - _time * 4 };
	DrawBox(draw_x1, draw_y1, draw_x2, draw_y2, MyData::BLACK, true);
}

void FirstAnimation::Anime4::draw(int _time) const
{
	//最初は0, _timeが60で255
	int val{ 255 * _time / 60 };
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - val);
	DrawBox(0, 0, 640, 480, GetColor(val, val, val), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
	doneNum += (players[doneNum])->attack(_sController, enemies, players);

	//全てのplayerの行動が決まったら
	if(doneNum >= (int)players.size())
	{
		//敵の行動を決める
		for (auto& ene : enemies)
		{
			ene->attack(_sController, enemies, players);
		}

		while (!act_que.empty())
		{
			//やられていなかったらActionControllerに追加
			if (act_que.front()->isAlive())
			{
				//逃げていないなら
				_aController->addAction((act_que.front())->getAction());
				assert(act_que.front()->getAction() && "不正なaction");
			}

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
	(players[doneNum])->draw(enemies, players);
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

	//バトル終了
	bool win = isWin(_actors);//敵が全滅しているか
	bool lose = isLose(_actors);//味方が全滅しているか

	if (win || lose)
	{
		mFinTime++;
		updateMessage(_sController, win);
		
		if (mFinTime == 105)
		{
			int exp{ 0 };
			for (const auto& e : _actors)
			{
				if (e->status.isEnemy)exp += e->getExp();
			}
			next = new Result(exp * win);
		}
	}
	else//バトル中
	{
		bool battleDone = _aController->update(_sController, _actors);

		//逃げていたら
		if (_aController->escapeBattle())
		{
			return new Result(0);
		}

		//ターン終了時にバトルが終わっていなかったら行動選択へ
		if (battleDone && !(isWin(_actors) || isLose(_actors)))
		{
			next = new Decide(_actors);
		}
		//ターン終了と同時にバトルが終わった場合は行動選択をせずに終わる
	}
	
	return next;
}

void Battle::draw(ActionController* _aController) const
{
	_aController->draw();
}


//========================================================================
// 内部private関数
//========================================================================
bool Battle::isWin(const vector<Actor*> _actors) const 
{
	bool f_enemy{ false };

	//f_playerとf_enemyにそれぞれisAlive()を足す(論理和)
	for(auto* act : _actors) 
	{
		if (act->status.isEnemy)f_enemy |= act->isAlive();
		
	}

	//f_enemyについて...
	//EnemyのHPがすべてゼロならfalseのまま
	//HPがゼロでないActorが一つでもあればtrueになる
	return !f_enemy;
}

bool Battle::isLose(const vector<Actor*> _actors) const
{
	bool f_player{ false };
	//f_playerとf_enemyにそれぞれisAlive()を足す(論理和)
	for (auto* act : _actors)
	{
		if (!act->status.isEnemy) f_player |= act->isAlive();
	}

	//f_playerについて...
	//PlayerのHPがすべてゼロならfalseのまま
	//HPがゼロでないActorが一つでもあればtrueになる
	return !f_player;
}


void Battle::updateMessage(StringController* _sController, bool _win)
{
	if (mFinTime == 45)
	{
		//かったら
		if(_win)_sController->addMessage("てきをたおした！");
		//まけたら
		else _sController->addMessage("まけてしまった...");
	}
}

int Battle::calcExp(vector<Actor*> _actors)
{
	int value = 0;
	for (auto& act : _actors)
	{
		value += act->getExp();
	}
	return value;
}


//========================================================================
// Resultクラス
//========================================================================
Result::Result(int _exp) :
mGetExp(_exp)
{
	initialized = false;
}

Result::~Result()
{
	ResultPlayers.clear();
	ResultPlayers.shrink_to_fit();
}

void Result::initialize(vector<Actor*> _actors)
{
	mTime = 0;

	//ResultStatusを初期化
	for (auto& act : _actors)
	{
		if(!act->status.isEnemy)ResultPlayers.push_back(new ResultStatus(act, mGetExp));
	}
	
	mBackImg = LoadGraph("Data/Image/ResultBack.png");

	initialized = true;
	DeleteSoundMem(mBGM);
	PlaySoundFile("Data/Sound/win.mp3", DX_PLAYTYPE_BACK);
}

BattleChild* Result::update(ActionController* _aController, StringController* _sController, vector<Actor*> _actors)
{
	if (!initialized)initialize(_actors);

	BattleChild* next = this;

	mTime++;

	for (auto& player : ResultPlayers)
	{
		player->update();
	}

	//Fieldに行く前にセーブ
	if (goField())saveData();

	return next;
}

void Result::draw(ActionController* _aController) const
{
	DrawFormatString(0, 60, MyData::WHITE, "Result");
	DrawGraph(0, 0, mBackImg, true);
	
	if (ResultPlayers.size() >= 1)ResultPlayers[0]->draw(0, 0);
	if (ResultPlayers.size() >= 2)ResultPlayers[1]->draw(320, 0);
	if (ResultPlayers.size() >= 3)ResultPlayers[2]->draw(0, 240);
	if (ResultPlayers.size() >= 4)ResultPlayers[3]->draw(320, 240);
}

//次のシーケンスに行くか
bool Result::goField() const
{
	bool goNext = false;

	for (auto& player : ResultPlayers)
	{
		goNext |= player->goNext();
	}
	
	return goNext;
}

void Result::saveData()
{
	std::ofstream fout("Data/Text/PlayerData.txt");
	for (auto& player : ResultPlayers)
	{
		fout << player->getSaveString() << std::endl;
	}
}


//=================================
//内部クラス
//=================================
Result::ResultStatus::ResultStatus(Actor* _actor, int _mGetExp)
{
	//立ち絵のロード
	mImg = LoadGraph(getFileName(toCharacter[_actor->status.charaID].fileName).c_str());

	initialize(_actor, _mGetExp);
}

void Result::ResultStatus::initialize(Actor* _actor, int _mGetExp)
{
	charaID = _actor->status.charaID;
	name = _actor->status.name;

	mTime = 0;

	mLevelUp = false;
	mLevelTime = 60;

	//今の経験値バーの位置
	mNowExp = _actor->getExp() % CharacterData::nextExp;

	//目標の経験値バーの位置
	mAfterExp = mNowExp + _mGetExp;

	//経験値の総合計
	mAllExp = _actor->getExp() + _mGetExp;

	name = _actor->status.name;

}

void Result::ResultStatus::update()
{
	mTime++;

	//mAfterExpまで経験値を増やす
	mNowExp = min(mNowExp + 1, mAfterExp);

	//経験値がいっぱいになったらレベルアップ
	if (mNowExp % CharacterData::nextExp == (CharacterData::nextExp - 1) &&
		mNowExp != mAfterExp)
	{
		mLevelUp = true;
		mLevelTime = 0;
		mTime = 0;
	}

	mLevelTime += mLevelUp;
	mLevelUp = mLevelTime < 30;
}

void Result::ResultStatus::draw(int _x, int _y) const
{
	//背景と立ち絵を描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawBox(_x + 5, _y + 5, _x + 320, _y + 240, MyData::WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
	DrawGraph(_x + 90, _y, mImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//経験値バーの書く場所を計算
	int exp = mNowExp % CharacterData::nextExp;
	int draw_x = 186 * (exp + 1) / CharacterData::nextExp;

	//各キャラのレベルと名前を表示
	string expInfo = "Lv." + std::to_string(1 + (mAllExp -mAfterExp + mNowExp) / 100) + " " + name;
	DrawString(_x + 10, _y + 170, expInfo.c_str(), MyData::WHITE);

	//経験値バーを描画
	DrawBox(_x + 10, _y + 190, _x + 200, _y + 230, MyData::WHITE, false);
	DrawBox(_x + 12, _y + 192, _x + 12 + draw_x, _y + 228, MyData::WHITE, true);

	//レベルアップ!
	if(mLevelUp)DrawFormatString(_x + 20, _y + 150, MyData::WHITE, "Level Up!");
}

string Result::ResultStatus::getSaveString()
{
	return std::to_string(charaID) + " " + name + " " + std::to_string(mAllExp);
}

bool Result::ResultStatus::goNext() const
{
	//レベルアップから1秒後にZキーまたは3秒後にreturn
	return (mTime > 60 && Input_Z()) || mTime > 180;
}

//toCharacter.fileNameから画像の名前を生成
const string Result::ResultStatus::getFileName(char* _fileName) const
{
	string fileName = "Data/Image/Character/up_";
	fileName += _fileName;
	fileName += ".png";

	return fileName;
}



}
}
}
}