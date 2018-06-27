//*****************************************************************************************************************************
//
//		チュートリアルシーン
//
//*****************************************************************************************************************************
#ifndef _SCENETUTORIAL_H_
#define _SCENETUTORIAL_H_
#include "system\\Scene.h"

//*****************************************************************************************************************************
//
//		チュートリアル進行マネージャー
//
//*****************************************************************************************************************************

class TutoOperater
{
public:
	TutoOperater();
	~TutoOperater();
private:
	enum STATE {
		INIT = 0,			//初期化
		BEGIN,				//初期データ入力
		MOVE, 
		
		//ゲーム概要説明
		GAMERULE_BEGIN,
		GAMERULE,			
		//プレイヤー操作移動説明
		PLAYER_MOVE_BEGIN,
		PLAYER_MOVE,	
		//ピント操作説明
		PINTO_MOVE_BEGIN,
		PINTO_MOVE,	
		//敵の倒し方説明
		ENEMY_DWON_BEGIN,
		ENEMY_DWON,	
		//ピントロック説明
		PINTO_LOCK_BEGIN,
		PINTO_LOCK,
		//例ゲージ説明
		EXORCISE_BEGIN,
		EXORCISE,
		//マルチフォーカス説明
		MULTIFOCUS_BEGIN,
		MULTIFOCUS,
		//再ゲーム説明
		REGAMERULE_BEGIN,
		REGAMERULE,
		END,
	};
	enum IWORK {
		state_up_flg = 0,
		messege_end,
		enemy_pop,
		//
		move_x_ok,
		move_y_ok,
		//
	};

	OBJ2D operater;
	OBJ2D master_char;
	OBJ2D suboperater;
	int state;
	int clear_flg;

	int iwork[16];

	SPR_DATA spr_tutomaster = SPR_DATA{ spr_data::Enemy3,0,0,128,128,-64,-32,0 };
	//ゲームルール説明
	SPR_DATA spr_gamerulr[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 0,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 1,680,128,-680,-128,0},
		SPR_LOOP, 
	};
	//プレイヤー移動説明
	SPR_DATA spr_player_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 2,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	//ピント操作説明
	SPR_DATA spr_pinto_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 3,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	//敵撃破説明
	SPR_DATA spr_out_enemy_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 4,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 5,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	SPR_DATA spr_pintrock_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 6,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 7,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 8,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	SPR_DATA spr_exorcise_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 9,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 10,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 11,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	SPR_DATA spr_multifocus_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 12,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	SPR_DATA spr_gamerule_move[5] =
	{
		SPR_DATA{ spr_data::UI9,0,128 * 13,680,128,-680,-128,0 },
		SPR_DATA{ spr_data::UI9,0,128 * 14,680,128,-680,-128,0 },
		SPR_LOOP,
	};

	void R1_effect(Effect* obj) {
		switch (obj->state)
		{
		case 0:
			obj->data;//R1 吹き出しデータ
			state++;
		case 1:
			if (obj->parent->move == null) {
				obj->clear();
				break;
			}
			obj->pos = obj->parent->pos;
			break;
		default:
			break;
		}
	}
	void up_effect(Effect* obj) {
		switch (obj->state)
		{
		case 0:
			obj->data;//R1 吹き出しデータ
			state++;
		case 1:
			if (obj->parent->move == null) {
				obj->clear();
				break;
			}
			obj->pos = obj->parent->pos;
			break;
		default:
			break;
		}
	}
	

public:
	void Init();
	void Update();
	void Render();
	void clear();
private:

	void TutoOperater::pagenext();

	//int get_state() { return state; }
	//int get_clear_flg() { return clear_flg; }
};

//*****************************************************************************************************************************
//
//		チュートリアルシーン
//
//*****************************************************************************************************************************


class	sceneTutorial : public Scene
{
private:
	iexView*	view;
	int state;
	int timer;
	int count_down_timer;
	int count_down;
	int scene_timer;
	int stage_no;
	OBJ2D center;
	TutoOperater tuto_operator;
public:

	//MAP*		map;
	//Player*	player;
	//OBJ2D* bg;
	//OBJ2D* fg;

	//Enemy* enemy;

	~sceneTutorial();
	//	初期化
	bool Initialize();
	void UnInit();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

};



#endif //_SCENETUTORIAL_H_




