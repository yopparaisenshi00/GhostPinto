#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Frame.h"
#include "MAP.h"
#include "BGFG.h"
#include "stage_data.h"


enum 
{
	BG_CASE = spr_data::BG2,
	BG_PC = spr_data::BG3,
	BG_PIPE = spr_data::BG4,
};




SPR_DATA spr_pc[] = {
	SPR_DATA{ BG_PC,0,0,248,157,-124,-157,0 } ,
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,1 },
};
SPR_DATA spr_container[] = {
	SPR_DATA{ BG_PC,0,256,248,256 + 157 ,-232,-157 ,0},
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,1 }
};


enum {
	INIT = 0,	//‰ŠúÝ’è
	BEGIN,	//
	BEGIN2,	//
	
	MOVE,	//ˆÚ“®ˆ—
	MOVE2,	//
	MOVE3,	//
	MOVE4,	//
	MOVE5,	//

	CLEAR,	//‰Šú‰»
};


void LandScape::Init(int stage_no) {
	bg.Init();
	backobj.Init();
	flontobj.Init();
	timer = 0;
	data = &stage1_bg_effct[stage_no];
}


void LandScape::Update() {
	stage_update();
	bg.Update();
	backobj.Update();
	flontobj.Update();
}
void LandScape::stage_update() {
	timer++;
	//timer‚ÅŠÇ—
	while (data->appearTime <= timer)
	{
		if (data->appearTime<0) {
			data++;
			break;
		}
		if (data->moveType == nullptr) break;
		searchSet(data->type,data->pos - V2(pMAP->getScrollX(), pMAP->getScrollY()), data->speed,data->moveType,nullptr,data->z);
		data++;
	}


}


//---------------------------------------------------------------
//
// ”wŒi
//
//---------------------------------------------------------------
BG::BG()
{

}

BG::~BG()
{
			
}

void BG::Init() {
	
	for (int i = 0; i < BG_MAX; i++) {
		if (obj[i])obj[i]->Init();
	}
}



void BG::Update() {
	for (int i = 0; i < BG_MAX; i++) {
		if (obj[i] && obj[i]->move)
			obj[i]->Update();
	}
}
void BG::Render() {
	for (int i = 0; i < BG_MAX;i++ ) {
		if(obj[i])obj[i]->Render();
	}
}




void LAND_SCAPE_OBJ::Init() {
	clear();
}

void LAND_SCAPE_OBJ::Update() {
	if (move)move(this);
	animation();
}


void LAND_SCAPE_OBJ::Render() {
	if (!data)return;
		shader2D->SetValue("FPower",sz);
		spr_data::Render(pos, data,&custom,0xFFFFFFFF, shader2D, "depth");
}


void BackMain(BGOBJ* obj) {
	
}


//---------------------------------------------------------------
//
//	‘OŒi
//
//---------------------------------------------------------------

FG::FG()
{
	}

FG::~FG()
{

}

void FG::Init() {
	for (int i = 0; i < BG_MAX; i++) {
		if (obj[i])obj[i]->Init();
	}

}

void FG::Update() {

	for (int i = 0; i < BG_MAX; i++) {
		if (obj[i] && obj[i]->move)
			obj[i]->Update();
	}


	///////////////////////////////////////////////////////////////////////////////////


	


}

void FG::Render() {
	for (int i = 0; i < BG_MAX; i++) {
		if (obj[i])obj[i]->Render();
	}
}

void MainBG(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:

	case BEGIN:
		
	default:
		break;
	}
}

void BG_pc(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->animeData = spr_pc;
		obj->data = &spr_pc[0];
		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}
void BG_container(LAND_SCAPE_OBJ* obj) {
	switch (obj->state)
	{
	case INIT:
		obj->animeData = spr_container;
		obj->data = &spr_container[0];
		obj->state = BEGIN;
		break;
	case BEGIN:

	default:
		break;
	}

}


//void FGOBJ::Init() {
//	clear();
//	data = nullptr;
//	z = 0;
//	sz = 0;
//}
//
//void FGOBJ::Update() {
//	if (move)move(this);
//	animation();
//}
//
//
//void FGOBJ::Render() {
//	if (!data)return;
//	shader2D->SetValue("FPower", sz);
//	spr_data::Render(pos, data, &custom, 0xFFFFFFFF, shader2D, "depth");
//}
