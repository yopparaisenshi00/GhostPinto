//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************
#ifndef _SCENE_MAIN_H_
#define _SCENE_MAIN_H_
#include "system\\Scene.h"


class	sceneMain : public Scene
{
private:
	iexView*	view;
	int state;
	int timer;
	int count_down_timer;
	int count_down;
	int scene_timer;
	int stage_no;
public:

	//MAP*		map;
	//Player*	player;
	//OBJ2D* bg;
	//OBJ2D* fg;

	//Enemy* enemy;
	
	~sceneMain();
	//	初期化
	bool Initialize();
	void UnInit();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

};



#define COMBO_BONUS 2 //コンボボーナススコア(ボーナススコア * コンボ数)
#define COMBO_TIME 120 //コンボ持続タイム
class Score:public OBJ2D ,public Singleton<Score>
{
private:
	//------------------------------
	//変数
	//------------------------------
	int score;//スコア
	int combo;//コンボ数
	int maxcombo;//最大コンボ数
	int combotimer;//コンボ持続タイマー
	//------------------------------
	//関数
	//------------------------------
	//初期化
	void clear() {
		OBJ2D::clear();
		score = 0;
		combo = 0;
		maxcombo = 0;
		combotimer = 0;
		kill_num = 0;
	}
public:
	int kill_num;

	//初期設定
	void Init() {
		clear();
	}

	//更新
	void Update() {
		combotimer++;
		if (combotimer > COMBO_TIME || combo == 0) {
			combo = 0;
			combotimer = 0;
		}
		if ( maxcombo<combo ) { //最大コンボ数保存
			maxcombo = combo;
		}
	}

	//スコア加算(映っている間)
	void add_ClearlyScore(int add) {
		score += add;
	}
	//スコア加算(倒した後)
	void add_KillScore(int add) {
		score += add + (combo * COMBO_BONUS);
		combotimer = 0;
		combo++;
		kill_num++;
	}

	//スコアを返す
	int getScore() {
		return score;
	}
	//撃破数を返す
	int getKill_num() {
		return kill_num;
	}
	//コンボ数を返す
	int getCombo() {
		return combo;
	}
	//最大コンボ数を返す
	int getMaxCombo() {
		return maxcombo;
	}


	void Render() {
		int x = 800;
		int y = 0;
	}

};

#define pScore (Score::getInstance())

#endif //_SCENE_MAIN_H_




