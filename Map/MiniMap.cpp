#include "iextreme.h"
#include "Misc/Misc.h"
#include "Player/Player.h"
#include "Player/Frame.h"
#include "Enemy/Enemy.h"
#include "Effect/Effect.h"
#include "Map/MAP.h"
#include "Map/MiniMap.h"



void MiniMap::Init(float LimitR, float LimitD) {
	ReductionSize = REDUCTIONSIZE;
	Limits = V2(LimitR/ ReductionSize, LimitD/ ReductionSize);

}
void MiniMap::Update() {
	float MScrX = pMAP->getScrollX();
	float MScrY = pMAP->getScrollY();
	//プレイヤー情報取得計算
	
	p_Pps = pPlayer->pos; 
	p_Pps = V2(((p_Pps.x + MScrX) / ReductionSize), (p_Pps.y + MScrY) / ReductionSize);

	//エネミー情報取得計算
	count = 0;
	Enemy_Manager* em = pEnemy_Manager;
	for (int i = 0; i < ENEMY_MAX; i++)	{
		if (!em->enemy[i] || !em->enemy[i]->init_fg || !em->enemy[i]->noHit_flg)continue;
		E_Pps[count] = em->enemy[i]->pos;
		E_Pps[count] = V2(((E_Pps[count].x + MScrX) / ReductionSize), (E_Pps[count].y + MScrY) / ReductionSize);
		count++;
	}
}
void MiniMap::Render() {

	// ミニマップ背景
	int x, y, d, h;
	x = 0;
	y = 540 - (int)Limits.y;
	d = (int)Limits.x;
	h = (int)Limits.y;
	iexPolygon::Rect(x,y,d ,h, 0, 0x5F000000, 0);

	// ミニマップ　プレイヤー (赤)
	x = (int)p_Pps.x - Player_Icon_OFSET;
	y = (int)(535 - Limits.y + p_Pps.y + Player_Icon_OFSET);
	d = Player_Icon_SIZE;
	h = Player_Icon_SIZE;
	iexPolygon::Rect(x, y,d ,h, 0, 0xFFFF0000);

	// ミニマップ　敵　(黄)
	for (int i = 0; i < count; i++) {
		x = (int)(E_Pps[i].x - Enemy_Icon_SIZE);
		y =(int)(540 - Limits.y + E_Pps[i].y - Enemy_Icon_SIZE);
		d = Enemy_Icon_SIZE;
		h = Enemy_Icon_SIZE;
		iexPolygon::Rect(x,y ,d ,h , 0, 0xFFFFFF00);
	}

	
}