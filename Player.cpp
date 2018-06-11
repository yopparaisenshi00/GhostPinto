#include "iextreme.h"
#include "system\System.h"

#include "Game.h"
#include "Frame.h"
#include "Player.h"
#include "Effect.h"
#include "MAP.h"
#include "Enemy.h"
#include "Sound.h"
#include "sceneMain.h"

SPR_DATA p_spr_data[] = {
	{ spr_data::Player1,0,0,64,64,-32,-32 },
	{ spr_data::UI5,0,0,32,32,-16,-16 },//hpアイコン
	{ spr_data::UI5,32,32,32,192,16,0 },//恐怖ゲージ外側
	{ spr_data::UI5,96,32,32,0,16,192 },//恐怖ゲージ内側
	{ spr_data::UI5,96,32,32,0,16,192 },//恐怖ゲージ内側
};
SPR_DATA multi[] = { //マルチフォーカスゲージ
	{ spr_data::UI3, 64 * 0, 32 * 17,	64,32,-32,-16 },
	{ spr_data::UI3, 64 * 1, 32 * 17,	64,32,-32,-16 },
	{ spr_data::UI3, 64 * 2, 32 * 17,	64,32,-32,-16 },
};


SPR_DATA p_wait[] = { //待機
	{ spr_data::Player1, 64 * 0, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 3, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 4, 64 * 0,	64,64,-32,-32 },
};
SPR_DATA p_work_u[] = { //上移動
	{ spr_data::Player1, 64 * 0, 64 * 1,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 1,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 1,	64,64,-32,-32 },
};
SPR_DATA p_work_r[] = { //右移動
	{ spr_data::Player1, 64 * 0, 64 * 2,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 2,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 2,	64,64,-32,-32 },
};
SPR_DATA p_work_l[] = { //左移動
	{ spr_data::Player1, 64 * 0, 64 * 3,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 3,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 3,	64,64,-32,-32 },
};
SPR_DATA p_work_d[] = { //下移動
	{ spr_data::Player1, 64 * 0, 64 * 4,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 4,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 4,	64,64,-32,-32 },
};
//SPR_DATA p_damage[] = { //ダメージ
//	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 1, 64 * 10,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 0, 64 * 11,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 0, 64 * 11,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 1, 64 * 11,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 2, 64 * 11,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 3, 64 * 11,	64,64,-32,-32 },
//	{ spr_data::Player1, 64 * 3, 64 * 11,	64,64,-32,-32 },
//};
SPR_DATA p_damage[] = { //ダメージ
	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 10,	64,64,-32,-32 },
};
SPR_DATA p_over[] = { //ゲームオーバー
	{ spr_data::Player1, 64 * 0, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 0, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 3, 64 * 11,	64,64,-32,-32 },
};



//Player::Player()
//{
//
//}

Player::~Player()
{

}

void Player::Init() {
	clear();
	sc_w = SCROLL_RIGHT;
	sc_h = SCREEN_HEIGHT / 2;
	hp = 0;
	mltfcs.clear();

	hp = 3;
	pos = D3DXVECTOR2(960, 270);
	size = D3DXVECTOR2(PLAYER_SIZE / 8, PLAYER_SIZE / 8);
	fear_flg = false;

	state++;
	//fearstd = ((float)192 / (float)FERE_MAX);
}
void Player::Update() {
	move();//移動、操作切り替え等
	anime();//アニメーション
	judge();
}
void Player::R_Update() {
	anime();//アニメーション
	judge();
}

void Player::move() {
	int axisx = KEY_Get(KEY_AXISX);



	attr = pMAP->getAttr(pos.x, pos.y - height / 2);	// 体の中心付近の地形属性の取得

	switch (state)
	{
	case 0:
		hp = 3;
		pos = D3DXVECTOR2(960, 270);
		size = D3DXVECTOR2(PLAYER_SIZE / 8, PLAYER_SIZE / 8);
		fear_flg = false;

		state++;
	case 1:
		//-----------------------------------------------------------
		//  移動
		//----------------------------------------------------------
		//----------------------------
		//Y軸
		//----------------------------
		Y_move();

		//----------------------------
		//  X軸
		//----------------------------
		X_move();

		//-----------------------------------------------------------
		//  マルチフォーカス
		//-----------------------------------------------------------
		if (KEY_Get(MULTIFOCUS_KEY) == 3 && mltfcs.lv) {
			pFrame->use_Multifocus(mltfcs.lv);

			mltfcs.lv = 0;
			//mltfcs.add_point(0);
		}
		//-----------------------------------------------------------

		//-----------------------------------------------------------
		//  ピントロック
		//-----------------------------------------------------------
		if (KEY_Get(PINTOLOCK_KEY) == 3) {
			pFrame->use_lockPinto();
		}
		//-----------------------------------------------------------
		//pD_TEXT->set_Text(pos + V2(40,40),"PintoSize",pFrame->getPintoSize(),0xFFFFFFFF);
		break;
	case 3:

		break;
	default:
		break;
	}
	//-------------------------------------------
	//霊力
	//-------------------------------------------


	//-------------------------------------------

	//-------------------------------------------
	//状態異常、ダメージ無敵等
	//
	//
	if (s.nodamage) {
		nodamage_timer--;
		if (nodamage_timer < 0) {
			s.nodamage = false;
			s.old_nodamage = false;
		}
	}
	//-------------------------------------------
}


void Player::anime() {
	anime_timer++;
	if (anime_timer > 6) {
		anime_no++;
		anime_timer = 0;
	}

	//ジェットエフェクト
	if (jet_eff_timer++>10) {
		pEffect_Manager->searchSet(V2(pos.x, pos.y + 25), V2(0, 0), Jet);
		jet_eff_timer = 0;
	}

	//プレイヤー後方エフェクト
	if (spd.x != 0.0f || spd.y != 0.0f) { //プレイヤーが移動していて
		if (p_eff_timer++>8) {
			pEffect_Manager->searchSet(V2(pos.x - rand() % 20, pos.y - rand() % 20), V2(0, 0), P_particle);
			pEffect_Manager->searchSet(V2(pos.x - rand() % 20, pos.y + rand() % 20), V2(0, 0), P_particle);
			pEffect_Manager->searchSet(V2(pos.x + rand() % 20, pos.y - rand() % 20), V2(0, 0), P_particle);
			pEffect_Manager->searchSet(V2(pos.x + rand() % 20, pos.y + rand() % 20), V2(0, 0), P_particle);
			p_eff_timer = 0;
		}
	}

	//ゲームオーバー
	if (hp <= 0) {
		if (reflect) {
			if (anime_no > 5)anime_no = 5;
			data = &p_over[anime_no]; //左ダメージ
		}
		else {
			if (anime_no > 5)anime_no = 5;
			data = &p_over[anime_no]; //右ダメージ
		}
	}

	//ダメージ
	else if (s.old_nodamage == false && s.nodamage == true) {
		IEX_PlaySound(SE_DAMAGE, FALSE); //ダメージ
		if (reflect) {
			if (anime_no > 5) s.old_nodamage = true;
			data = &p_damage[anime_no]; //左ダメージ
		}
		else {
			if (anime_no > 5) s.old_nodamage = true;
			data = &p_damage[anime_no]; //右ダメージ
		}
	}

	//待機
	else if ((spd.x == 0) && (spd.y == 0)) {
		if (reflect) {
			if (anime_no > 4)anime_no = 0;
			data = &p_wait[anime_no]; //待機
		}
		else {
			if (anime_no > 4)anime_no = 0;
			data = &p_wait[anime_no]; //待機
		}
	}

	//上移動		     ※spd.xが絶対値2未満
	else if ((spd.y != 0) && (spd.x>-2 && spd.x<2)) {
		if (spd.y<0) {
			if (anime_no > 2)anime_no = 0;
			data = &p_work_u[anime_no]; //上移動
		}
		else {
			if (anime_no > 2)anime_no = 0;
			data = &p_work_d[anime_no]; //下移動
		}
	}

	//横移動,ななめ移動
	else {
		if (reflect) {
			if (anime_no > 2)anime_no = 0;
			data = &p_work_l[anime_no]; //左移動
		}
		else {
			if (anime_no > 2)anime_no = 0;
			data = &p_work_r[anime_no]; //右移動
		}
	}




	if (s.nodamage) {
		if (nodamage_timer & 0x02) {
			data = nullptr;
		}
	}

}


void Player::Render() {
	if (data)spr_data::Render(pos, data);
}
void Player::UIRender() {

	V2 gage1 = V2(960 - 30, 420);
	for (int i = 0; i < 3; i++)
	{
		//iexPolygon::Rect((int)gage.x, (int)gage.y,100,24,0,0xFFFF0000);
		spr_data::Render(V2(gage1.x, gage1.y), &multi[0]);
		gage1 += V2(0, 45);
	}
	V2 gage = V2(960 - 30, 420);
	for (int i = 0; i < mltfcs.lv; i++)
	{
		//iexPolygon::Rect((int)gage.x, (int)gage.y,100,24,0,0xFFFF0000);
		spr_data::Render(V2(gage.x, gage.y), &multi[2]);
		gage += V2(0, 45);
	}
	iexPolygon::Rect((int)pos.x, (int)pos.y, 1, 1, 0, 0xFFFF0000);


	////横
	//iexPolygon::Rect((int)(pos.x - size.x), (int)(pos.y + size.y), (int)(size.x * 2), 1, 0, 0xFFFF0000);
	//iexPolygon::Rect((int)(pos.x - size.x), (int)(pos.y - size.y), (int)(size.x * 2), 1, 0, 0xFFFF0000);

	//////縦
	//iexPolygon::Rect((int)(pos.x + size.x), (int)(pos.y - size.y), 1, (int)size.y * 2, 0, 0xFFFF0000);
	//iexPolygon::Rect((int)(pos.x - size.x), (int)(pos.y - size.y), 1, (int)size.y * 2, 0, 0xFFFF0000);

}

void Player::judge() {//
	if (s.nodamage)return;
	Enemy** enemy = pEnemy_Manager->enemy;
	for (int i = 0; i < ENEMY_MAX; i++) {
		//存在チェック
		if (!enemy[i] || !enemy[i]->init_fg)continue;
		//判定処理
		if ((enemy[i]->noHit_flg) && Judge(this, enemy[i])) {
			suffer_damage();
			Recoil(enemy[i]->pos, enemy[i]->spd); //ダメージ時の反動
		}
	}
}

void Player::clear() {
	OBJ2D::clear();
	nodamage_timer = 0;
	anime_timer = 0;
	dx = 0;
	dy = 0;
	attr = 0;
	act = 0;

	jimen_flg = false;
	fear_flg = false;


	jet_eff_timer = 0;
	p_eff_timer = 0;
}

void Player::SetMain() {
	pMAP->SetCenter((OBJ2D*)(this));
}

void Player::suffer_damage() {
	hp -= 1;
	s.nodamage = true;
	nodamage_timer = NODAMEGE_TIME;
}

void Player::Recoil(V2 enemy_pos, V2 enemy_spd) {
	V2 dist = enemy_pos - pos; //二間の距離
	D3DXVec2Normalize(&dist, &dist);

	//x移動してたら
	if (spd.x<-1 || spd.x>1) spd.x = -dist.x*10.0f;
	//y移動してたら
	if (spd.y<-1 || spd.y>1) spd.y = -dist.y*10.0f;
	//移動してなくて.enemyspdも0なら
	//if ( spd.x==spd.y==enemy_spd.x==enemy_spd.y==0.0f ) spd = -dist*10.0f;
	if (spd == enemy_spd == 0.0f) spd = -dist*10.0f;
	//enemyspdに比例した反動
	if (enemy_spd != 0)	spd -= enemy_spd*2.0f;
}

void Player::Y_move() {

	jimen_flg = false;										// 着地していない
	old_y = pos.y;											// 更新前のY座標を保存
															//spd.y += PLAYER_AY;										// 重力加速度の加算
	Get_spdy();
	pos.y += spd.y;											// 落下
	dy = pos.y - old_y;										// 実際に動いたドット数																// 落下したとき
	if (dy > 0) {
		// MAPとのあたりチェック
		if (pMAP->isFloor(pos.x, pos.y + (PLAYER_HEIGHT / 2), 0)) {	// 地面にめり込んだとき
			bg_crt_down(this);								// 地面ぎりぎりの場所にする
			jimen_flg = true;								// 着地状態
		}
	}

}

//パッド情報から速度を計算
inline void Player::Get_spdy() {
	int axisy = KEY_Get(KEY_AXISY);//パッド情報取得

	if (axisy > 100.0f || axisy < -100.0f) {//パッドが感度以上
		float spdy;
		spdy = (float)axisy;
		spdy *= 0.001f;					//パッドを1～-1に変換
		spdy += get_Resist(attr, spdy);	// 抗力（抵抗）の加算
		float max = spdy * 5;			//最高速度値設定


		if (spdy > 0) {
			if (spd.y >= max) {			//最高速度チェック
				spd.y = max;
			}
			else {
				spd.y += spdy * 0.5f;	//速度に加速度を追加
			}
		}
		if (spdy < 0) {
			if (spd.y <= max) {			//最高速度チェック
				spd.y = max;
			}
			else {
				spd.y += spdy * 0.5f;	//速度に加速度を追加
			}
		}

	}
	else {
		if (pos.y != 0) {
			if (0.01 > spd.y && -0.01< spd.y) {
				spd.y = 0;
			}
			else spd.y -= spd.y * 0.07f;
		}
	}

}

void Player::X_move() {
	jimen_flg = false;										// 着地していない
	old_x = pos.x;											// 更新前のY座標を保存
															//spd.y += PLAYER_AY;										// 重力加速度の加算
	Get_spdx();
	pos.x += spd.x;											// 落下
	dx = pos.x - old_x;										// 実際に動いたドット数																// 落下したとき
}

inline void Player::Get_spdx() {
	int axisx = KEY_Get(KEY_AXISX);
	if (axisx > 100.0f || axisx < -100.0f) {
		if (axisx < 0) { sc_w = SCROLL_LEFT; reflect = true; }
		if (axisx > 0) { sc_w = SCROLL_RIGHT; reflect = false; }

		float spdx;
		spdx = (float)axisx;
		spdx *= 0.001f;	//1に正規化

		spdx += get_Resist(attr, spdx);						// 抗力（抵抗）の加算
		float max = spdx * PLAYER_SPDX_MAX;
		if (spdx > 0) {
			if (spd.x >= max) {
				spd.x = max;
			}
			else {
				spd.x += spdx * PLAYER_AX;
			}
		}
		if (spdx < 0) {
			if (spd.x <= max) {
				spd.x = max;
			}
			else {
				spd.x += spdx * PLAYER_AX;
			}
		}

	}
	else {
		if (pos.x != 0) {
			if (0.01 > spd.x && -0.01< spd.x) {
				spd.x = 0;
			}
			else spd.x -= spd.x * PLAYER_RX;
		}
	}

	if (PLAYER_LIMIT_LEFT > pos.x) { pos.x = PLAYER_LIMIT_LEFT; }
	if (PLAYER_LIMIT_RIGHT < pos.x) { pos.x = PLAYER_LIMIT_RIGHT; }

	if (PLAYER_LIMIT_UP > pos.y) { pos.y = PLAYER_LIMIT_UP; }
	if (PLAYER_LIMIT_DOWN < pos.y) { pos.y = PLAYER_LIMIT_DOWN; }

}



//ボツ
//void fear() {
////恐怖度
////
//float distancex = (pFrame->pos.x - pos.x);
//float distancey = (pFrame->pos.y - pos.y);

//if ((distancex > FRAME_SIZE_W) || (distancex < -FRAME_SIZE_W)||(distancey > FRAME_SIZE_H) || (distancey  < -FRAME_SIZE_H)){
//		fear += FERE_UP;
//}
//else { 
//	if (fear > 0)fear -= FERE_CURE;
//}
//
//if (fear >= FEAR_MAX) {
//	fear = FEAR_MAX;
//	fear_flg = true;
//	pFrame->SetMain();
//}
//else
//{
//	if (fear_flg)fear_flg = false;
//}
//float ofs = fear * fearstd;
//p_spr_data[3].dy = 0 + (ofs);
//p_spr_data[3].ofsy = (192) - (ofs);
//-------------------------------------------
//}


void MLT_FOCUS::add_point(int add) {
	point += add;
	while (point > USE_POINT) {
		if (lv < MLTFCS_MAX_LV) {
			lv++;
			IEX_PlaySound(SE_MULCH_STOCK, FALSE); //マルチフォーカスが溜まった時
			point -= USE_POINT;
		}
		else point = USE_POINT;

	}
	if (point < 0) {
		point = 0;
	}
}