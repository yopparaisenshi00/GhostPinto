//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************
#ifndef _SCENE_MAIN_H_
#define _SCENE_MAIN_H_
#include "system\\Scene.h"

#define CLEAR_KILLNUM (4)
#define COUNT_DOWN_TIME (2)
class	sceneMain : public Scene ,public Singleton<sceneMain>
{
private:
	iexView*	view;
	int state;
	int timer;
	int count_down_timer;
	int count_down;
	int scene_timer;
	int stage_no;
	UINT fade_argb;
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


	UINT fade_out(UINT argb,UINT spd) {
		//argb += 0x11000000;
		argb += spd;
		return argb;
	}
	UINT fade_in(UINT argb,UINT spd) {
		//argb -= 0x11000000;
		argb -= spd;
		return argb;
	}
};
#define pMain (sceneMain::getInstance())




#define COMBO_BONUS 2 //コンボボーナススコア(ボーナススコア * コンボ数)
#define COMBO_TIME 100 //コンボ持続タイム
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
		addscore = 0;
		eval_justpinto = 0;
	}
public:
	int kill_num;
	int addscore;		//コンボリザルト_撮影スコア
	int eval_justpinto; //コンボリザルト_ジャストピント数
	int comboscore;		//コンボリザルト_コンボ分スコア

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
		addscore += add; //コンボが途切れるまでadd分保存
	}
	//スコア加算(倒した後)
	void add_KillScore(int add) {
		score += add + (combo * COMBO_BONUS)/*+(eval_justpinto*200)*/;
		comboscore += add+(combo * COMBO_BONUS);
		combotimer = 0;
		//eval_justpinto = 0;
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
	//コンボリザルト_撮影スコア
	int getAddscore() {
		return addscore;
	}
	//コンボリザルト_ジャストピント数
	int getEval_justpinto() {
		return eval_justpinto;
	}
	//コンボリザルト_コンボ分スコア
	int getcomboscore() {
		return comboscore;
	}
	//コンボリザルト_コンボタイマー
	int getcombotimer() {
		return combotimer;
	}


	void Render() {
		int x = 800;
		int y = 0;
	}

};

#define pScore (Score::getInstance())

#endif //_SCENE_MAIN_H_




