#include "iextreme.h"
#include "system\System.h"
#include "system\Framework.h"
#include "Game.h"
#include "sceneMain.h"
#include "sceneTitle.h"
#include "sceneClear.h"
#include "Enemy.h"
#include "Number.h"
#include "Ranking.h"
//#include "MAP.h"
//#include "sceneMain.h"





//SPR_DATA clear = { 0,200,0,1280,960,0,0 };
//SPR_DATA clear = { 0,192,192,640,128,-320,-64 };
SPR_DATA clear = { 0,192,192,768,128,0,0,600,100 };
SPR_DATA clear_batu = { 1,0,0,64,64,-32,-32 };	//×
SPR_DATA clear_enemy_yellow = { 2,64*0,64*0,64,64,-32,-32}; //enemy_黄
SPR_DATA clear_enemy_green  = { 2,64*0,64*1,64,64,-32,-32}; //enemy_緑
SPR_DATA clear_enemy_pink   = { 2,64*0,64*2,64,64,-32,-32}; //enemy_ピンク
SPR_DATA clear_enemy_blue   = { 2,64*0,64*3,64,64,-32,-32}; //enemy_青
SPR_DATA clear_enemy_white  = { 2,64*0,64*4,64,64,-32,-32}; //enemy_白
SPR_DATA clear_enemy_kari = { 4,0,0,64,64,-32,-32 };		//enemy_kari
SPR_DATA clear_ranking = { 5,0,254,270,360,0,0 };	//ランキング文字
SPR_DATA clear_result = { 1,0,380,290,70,-145,-35 };	//リザルト
SPR_DATA clear_score = { 5,0,190,120,40,-60,-20 };	//SCORE
SPR_DATA clear_time = { 5,0,800,192,64,-96,-32 };	//Time
SPR_DATA clear_number[10] = {
	{ 3,64*0,64*0,64,64,-32,-32,64/2,64/2 }, //0
	{ 3,64*1,64*0,64,64,-32,-32,64/2,64/2 }, //1
	{ 3,64*2,64*0,64,64,-32,-32,64/2,64/2 }, //2
	{ 3,64*3,64*0,64,64,-32,-32,64/2,64/2 }, //3
	{ 3,64*4,64*0,64,64,-32,-32,64/2,64/2 }, //4
	{ 3,64*0,64*1,64,64,-32,-32,64/2,64/2 }, //5
	{ 3,64*1,64*1,64,64,-32,-32,64/2,64/2 }, //6
	{ 3,64*2,64*1,64,64,-32,-32,64/2,64/2 }, //7
	{ 3,64*3,64*1,64,64,-32,-32,64/2,64/2 }, //8
	{ 3,64*4,64*1,64,64,-32,-32,64/2,64/2 }, //9
};




IMG_DATA img_clear[] = {
	{ 0,"DATA\\Scene\\GAME_CLEAR.png" },
	{ 1,"DATA\\Public\\strings.png" },
	{ 2,"DATA\\CHR\\enemy.png" },
	{ 3,"DATA\\Public\\number.png" },
	{ 4,"DATA\\CHR\\enemy_kari.png" }, //enemy_kari
	{ 5,"DATA\\Public\\strings2.png" }, //ランキング文字
	{ 6,"DATA\\Public\\black.png" }, //背景
	{-1,""},
};



//初期化
bool sceneClear::Initialize()
{
	iexLight::SetFog(800, 1000, 0);
	spr_data::Load(img_clear);
	//ランキング初期化--------------------------------
	ZeroMemory(ranks, sizeof(ranks));
	ranks_update_info = 0;
	memcpy(ranksFileName, "DATA/saveData.dat", 128);
	//------------------------------------------------
	state = 0;
	timer = 0;

	score = 0;
	gametimer = 0;
	newscore = 0;
	V2 time_pos = V2(0,0);

	return TRUE;
}

//解放
sceneClear::~sceneClear()
{
	spr_data::Release();
	state = 0;
	timer = 0;

	score = 0;
	gametimer = 0;
	newscore = 0;
	V2 time_pos = V2(0,0);
}

//更新
void sceneClear::Update()
{
	//if (KEY_Get(KEY_SPACE)==3) {
	//	MainFrame->ChangeScene(new sceneTitle());
	//}
}

//描画
void sceneClear::Render()
{
	switch (state) {
		case 0:
			//iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,0x3F000000,0); //暗転
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //黒背景
			state++;
			//break;
		case 1:
			//spr_data::Render(V2(0, -50), &clear);
			spr_data::Render(V2(200,200), &clear);
			score = pScore->getScore();			//ゲーム終了時のscore
			newscore = score;					//ゲーム終了時のscore
			gametimer = pNumber->n_timer/60;	//ゲーム終了時のtime
			time_pos = V2(570, 410);			//timeの位置
			if (KEY_Get(KEY_SPACE) == 3) state++;
			break;
		case 2:
			timer++;
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //黒背景
			spr_data::Render(V2(SCREEN_WIDTH/2, 50), &clear_result); //リザルト

			if (timer>30) spr_data::Render(V2(260, 120 + 75 * 0), &clear_enemy_kari);	//enemy_kari
			if (timer>40) spr_data::Render(V2(260, 120 + 75 * 1), &clear_enemy_yellow);	//enemy_黄
			if (timer>50) spr_data::Render(V2(260, 120 + 75 * 2), &clear_enemy_green);	//enemy_緑
			if (timer>60) spr_data::Render(V2(560, 120 + 75 * 0), &clear_enemy_pink);	//enemy_ピンク
			if (timer>70) spr_data::Render(V2(560, 120 + 75 * 1), &clear_enemy_blue);	//enemy_青
			if (timer>80) spr_data::Render(V2(560, 120 + 75 * 2), &clear_enemy_white);	//enemy_白

			if (timer>30) spr_data::Render(V2(350, 130 + 75 * 0), &clear_batu); //×
			if (timer>40) spr_data::Render(V2(350, 130 + 75 * 1), &clear_batu); //×
			if (timer>50) spr_data::Render(V2(350, 130 + 75 * 2), &clear_batu); //×
			if (timer>60) spr_data::Render(V2(650, 130 + 75 * 0), &clear_batu); //×
			if (timer>70) spr_data::Render(V2(650, 130 + 75 * 1), &clear_batu); //×
			if (timer>80) spr_data::Render(V2(650, 130 + 75 * 2), &clear_batu); //×

																				//敵ごとのkill数
			if (timer>30) Scene::Render2(V2(400, 130 + 75 * 0), &clear_number[0], pEnemy_Kill->getKill_num_Each(kari));
			if (timer>40) Scene::Render2(V2(400, 130 + 75 * 1), &clear_number[0], pEnemy_Kill->getKill_num_Each(yellow));
			if (timer>50) Scene::Render2(V2(400, 130 + 75 * 2), &clear_number[0], pEnemy_Kill->getKill_num_Each(green));
			if (timer>60) Scene::Render2(V2(700, 130 + 75 * 0), &clear_number[0], pEnemy_Kill->getKill_num_Each(pink));
			if (timer>70) Scene::Render2(V2(700, 130 + 75 * 1), &clear_number[0], pEnemy_Kill->getKill_num_Each(blue));
			if (timer>80) Scene::Render2(V2(700, 130 + 75 * 2), &clear_number[0], pEnemy_Kill->getKill_num_Each(white));


			if (timer>100) spr_data::Render(V2(390, 390), &clear_time); //Time
			if ( timer>100 ) {
				if ( time_pos.y<=480 )Scene::Render2(time_pos,&clear_number[0],gametimer); //終了時のtime
			}
			if (timer>120) spr_data::Render(V2(390,480), &clear_score); //SCORE
			if (timer>120) Scene::Render2(V2(570,490), &clear_number[0], score); //スコア


																				 //time移動処理--------------------------------------------
			if ( timer>130 && timer<140 ) {
				if ( time_pos.y>(410-30) ) time_pos.y-=4; //30上に行く
			}
			if ( timer>150 ) {
				if ( time_pos.y<480 ) time_pos.y += 10;
			}
			//--------------------------------------------------------

			if (KEY_Get(KEY_SPACE) == 3 && score==(newscore+gametimer*10)) {
				//ランキング------------------------------------------------------
				ranks_update_info = saveData(ranksFileName, score);
				loadData(ranksFileName, ranks);
				//----------------------------------------------------------------
				timer = 0;
				state++;
			}

			//timeを加算したscoreになるまで++
			if ( timer>160 ) {
				if ( (newscore+gametimer*10)>score ) score+=6;
				if ( KEY_Get(KEY_SPACE)==3 ) {
					score = newscore+gametimer*10;
				}
			}

			break;

		case 3:
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //黒背景
			 //ランキング-------------------------------------------------------------------------------------
			spr_data::Render(V2(320, 40), &clear_ranking);
			drawRankings(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 -100, ranks, ranks_update_info, &clear_number[0]);
			//-----------------------------------------------------------------------------------------------
			spr_data::Render(V2(340,475), &clear_score); //SCORE
			Scene::Render2(V2(480,490), &clear_number[0], score); //今回のスコア
			if (timer>=0) {	//一定時間経ったら
										//pushEnter描画
				if (KEY_Get(KEY_SPACE) == 3) MainFrame->ChangeScene(new sceneTitle()); //タイトルへ
			}
			timer++;
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