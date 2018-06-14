#include "iextreme.h"
#include "Game.h"
#include "Player.h"
#include "Frame.h"
#include "Enemy.h"
#include "Effect.h"
#include "MAP.h"
#include "MiniMap.h"

#define POSX (0)
#define POSY (535)


void MiniMap::Init(int LimitR, int LimitD) {
	ReductionSize = REDUCTIONSIZE;
	Limits = V2(LimitR/ ReductionSize, LimitD/ ReductionSize);
	pos = V2(POSX, POSY);
}
void MiniMap::Update() {
	int MScrX = pMAP->getScrollX();
	int MScrY = pMAP->getScrollY();
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


	iexPolygon::Rect(pos.x, pos.y - Limits.y, Limits.x,Limits.y, 0, 0x5F000000, 0);
	iexPolygon::Rect(pos.x + p_Pps.x - Player_Icon_OFSET, pos.y - Limits.y + p_Pps.y + Player_Icon_OFSET, Player_Icon_SIZE, Player_Icon_SIZE, 0, 0xFFFF0000);
	for (int i = 0; i < count; i++) {
		iexPolygon::Rect(pos.x + E_Pps[i].x- Enemy_Icon_SIZE, pos.y - Limits.y + E_Pps[i].y - Enemy_Icon_SIZE, Enemy_Icon_SIZE, Enemy_Icon_SIZE, 0, 0xFFFFFF00);
	}

	
}