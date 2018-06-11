#include "iextreme.h"
#include "system\System.h"
#include "system\Framework.h"
#include "Game.h"
#include "sceneMain.h"
#include "sceneTitle.h"
#include "sceneOver.h"
#include "Enemy.h"
#include "Ranking.h"
//#include "MAP.h"
//#include "sceneMain.h"



//SPR_DATA over = { 0,0,0,1280,960,0,0 };		//GAMEOVER
SPR_DATA over = { 0,192,192,640,128,0,0,600,90 };
SPR_DATA over_batu = { 1,0,0,64,64,-32,-32 };	//~
SPR_DATA over_enemy_yellow = { 2,64 * 0,64 * 0,64,64,-32,-32 }; //enemy_‰©
SPR_DATA over_enemy_green = { 2,64 * 0,64 * 1,64,64,-32,-32 }; //enemy_—Î
SPR_DATA over_enemy_pink = { 2,64 * 0,64 * 2,64,64,-32,-32 }; //enemy_ƒsƒ“ƒN
SPR_DATA over_enemy_blue = { 2,64 * 0,64 * 3,64,64,-32,-32 }; //enemy_Â
SPR_DATA over_enemy_white = { 2,64 * 0,64 * 4,64,64,-32,-32 }; //enemy_”’
SPR_DATA over_enemy_kari = { 4,0,0,64,64,-32,-32 };	//enemy_kari
SPR_DATA over_ranking = { 5,0,254,270,360,0,0 };	//ƒ‰ƒ“ƒLƒ“ƒO•¶Žš
SPR_DATA over_result = { 1,0,380,290,70,-145,-35 };	//ƒŠƒUƒ‹ƒg
SPR_DATA over_score = { 5,0,190,120,40,-60,-20 };	//SCORE
SPR_DATA over_time = { 5,0,800,192,64,-96,-32 };	//Time
SPR_DATA over_number[10] = {
	{ 3,64 * 0,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //0
	{ 3,64 * 1,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //1
	{ 3,64 * 2,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //2
	{ 3,64 * 3,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //3
	{ 3,64 * 4,64 * 0,64,64,-32,-32,64 / 2,64 / 2 }, //4
	{ 3,64 * 0,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //5
	{ 3,64 * 1,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //6
	{ 3,64 * 2,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //7
	{ 3,64 * 3,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //8
	{ 3,64 * 4,64 * 1,64,64,-32,-32,64 / 2,64 / 2 }, //9
};

IMG_DATA overBG = {};


IMG_DATA img_over[] = {
	{ 0,"DATA\\Scene\\GAME_OVER.png" },
	{ 1,"DATA\\Public\\strings.png" },
	{ 2,"DATA\\CHR\\enemy.png" },
	{ 3,"DATA\\Public\\number.png" },
	{ 4,"DATA\\CHR\\enemy_kari.png" }, //enemy_kari
	{ 5,"DATA\\Public\\strings2.png" }, //ƒ‰ƒ“ƒLƒ“ƒO•¶Žš
	{ 6,"DATA\\Public\\black.png" }, //”wŒi
	{ -1,"" },
};



//‰Šú‰»
bool sceneOver::Initialize()
{
	iexLight::SetFog(800, 1000, 0);
	spr_data::Load(img_over);
	//ƒ‰ƒ“ƒLƒ“ƒO‰Šú‰»--------------------------------
	ZeroMemory(ranks, sizeof(ranks));
	ranks_update_info = 0;
	memcpy(ranksFileName, "DATA/saveData.dat", 128);
	//------------------------------------------------
	state = 0;
	timer = 0;
	return TRUE;

	//bg.data = &img_over[6];
}

//‰ð•ú
sceneOver::~sceneOver()
{
	spr_data::Release();
	state = 0;
	timer = 0;
}

//XV
void sceneOver::Update()
{
	//timer++;
	//if ( timer>80&&KEY_Get(KEY_SPACE)==3 ) {
	//	state = 3;
	//}

}

//•`‰æ
void sceneOver::Render()
{
	switch (state) {
		case 0:
			//iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,0x3F000000,0); //ˆÃ“]
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //•”wŒi
																				   //ƒ‰ƒ“ƒLƒ“ƒO------------------------------------------------------
			ranks_update_info = saveData(ranksFileName, pScore->getScore());
			loadData(ranksFileName, ranks);
			//----------------------------------------------------------------
			state++;
			//break;
		case 1:
			//spr_data::Render(V2(0, -20), &over);
			spr_data::Render(V2(200, 200), &over);
			if (KEY_Get(KEY_SPACE) == 3) state=3;
			break;
			//case 2:
			//	iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //•”wŒi
			//	spr_data::Render(V2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-30), &over_result); //ƒŠƒUƒ‹ƒg

			//	if (timer>30) spr_data::Render(V2(260, 340 + 75 * 0), &over_enemy_kari);	//enemy_kari
			//	if (timer>40) spr_data::Render(V2(260, 340 + 75 * 1), &over_enemy_yellow);//enemy_‰©
			//	if (timer>50) spr_data::Render(V2(260, 340 + 75 * 2), &over_enemy_green);//enemy_—Î
			//	if (timer>60) spr_data::Render(V2(560, 340 + 75 * 0), &over_enemy_pink);	//enemy_ƒsƒ“ƒN
			//	if (timer>70) spr_data::Render(V2(560, 340 + 75 * 1), &over_enemy_blue);	//enemy_Â
			//	if (timer>80) spr_data::Render(V2(560, 340 + 75 * 2), &over_enemy_white);//enemy_”’

			//	if (timer>30) spr_data::Render(V2(350, 350 + 75 * 0), &over_batu); //~
			//	if (timer>40) spr_data::Render(V2(350, 350 + 75 * 1), &over_batu); //~
			//	if (timer>50) spr_data::Render(V2(350, 350 + 75 * 2), &over_batu); //~
			//	if (timer>60) spr_data::Render(V2(650, 350 + 75 * 0), &over_batu); //~
			//	if (timer>70) spr_data::Render(V2(650, 350 + 75 * 1), &over_batu); //~
			//	if (timer>80) spr_data::Render(V2(650, 350 + 75 * 2), &over_batu); //~

			//	//“G‚²‚Æ‚Ìkill”
			//	if (timer>30) Scene::Render2(V2(400, 350 + 75 * 0), &over_number[0], pEnemy_Kill->getKill_num_Each(kari));
			//	if (timer>40) Scene::Render2(V2(400, 350 + 75 * 1), &over_number[0], pEnemy_Kill->getKill_num_Each(yellow));
			//	if (timer>50) Scene::Render2(V2(400, 350 + 75 * 2), &over_number[0], pEnemy_Kill->getKill_num_Each(green));
			//	if (timer>60) Scene::Render2(V2(700, 350 + 75 * 0), &over_number[0], pEnemy_Kill->getKill_num_Each(pink));
			//	if (timer>70) Scene::Render2(V2(700, 350 + 75 * 1), &over_number[0], pEnemy_Kill->getKill_num_Each(blue));
			//	if (timer>80) Scene::Render2(V2(700, 350 + 75 * 2), &over_number[0], pEnemy_Kill->getKill_num_Each(white));

			//	if (timer>10) {
			//		//			//pushEnter•`‰æ
			//		if (KEY_Get(KEY_SPACE) == 3) {
			//			state = 3;
			//			timer = 0;
			//		}
			//	}
			//	timer++;
			//	break;
		case 3:
			//iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //•”wŒi
			////ƒ‰ƒ“ƒLƒ“ƒO-------------------------------------------------------------------------------------
			//spr_data::Render(V2(320, 40), &over_ranking);
			//drawRankings(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ranks, ranks_update_info, &over_number[0]);
			////-----------------------------------------------------------------------------------------------
			//spr_data::Render(V2(340,475), &over_score); //SCORE
			//Scene::Render2(V2(480,490), &over_number[0], pScore->getScore()); //¡‰ñ‚ÌƒXƒRƒA
			if (timer>=0) {
							//pushEnter•`‰æ
				if (KEY_Get(KEY_SPACE) == 3) MainFrame->ChangeScene(new sceneTitle()); //ƒ^ƒCƒgƒ‹‚Ö
			}
			//timer++;
			break;
		default:
			break;
	}

	//char str[128];
	//sprintf_s(str, 128, "score:%d", pEnemy_Kill->getKill_num_Each(pink));
	//IEX_DrawText(str, 300, 300, 128, 16, 0xFFFF0000);
	//sprintf_s(str, 128, "kill:%d", pScore->kill_num);
	//IEX_DrawText(str, 300, 300, 128, 16, 0xFFFF0000);
}