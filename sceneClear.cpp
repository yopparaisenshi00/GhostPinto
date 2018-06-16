#include "iextreme.h"
#include "system\System.h"
#include "system\Framework.h"
#include "Game.h"
#include "sceneMain.h"
#include "sceneTitle.h"
#include "sceneClear.h"
#include "Enemy.h"
#include "Number.h"
#include "Player.h"
#include "Ranking.h"
//#include "MAP.h"
//#include "sceneMain.h"




//SPR_DATA clear = { 0,200,0,1280,960,0,0 };
//SPR_DATA clear = { 0,192,192,640,128,-320,-64 };
SPR_DATA clear = { 0,192,192,768,128,0,0,600,100 };
SPR_DATA clear_batu = { 1,0,0,64,64,-32,-32 };	//�~
SPR_DATA clear_enemy_yellow = { 2,64*0,64*0,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_green  = { 2,64*0,64*1,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_pink   = { 2,64*0,64*2,64,64,-32,-32}; //enemy_�s���N
SPR_DATA clear_enemy_blue   = { 2,64*0,64*3,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_white  = { 2,64*0,64*4,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_kari = { 4,0,0,64,64,-32,-32 };		//enemy_kari
SPR_DATA clear_ranking = { 5,0,254,270,360,0,0 };	//�����L���O����
SPR_DATA clear_result = { 1,0,380,290,70,-145,-35 };	//���U���g
SPR_DATA clear_score = { 5,0,190,120,40,-60,-20 };	//SCORE
SPR_DATA clear_time = { 5,0,800,192,64,-96,-32 };	//Time
SPR_DATA clear_psb = { 7,0,576,419,31,-419/2,-31/2/*,459,40*/}; //PushStartButton
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
	{ 5,"DATA\\Public\\strings2.png" }, //�����L���O����
	{ 6,"DATA\\Public\\black.png" }, //�w�i
	{ 7,"DATA\\Scene\\title.png" },
	{-1,""},
};



//������
bool sceneClear::Initialize()
{
	iexLight::SetFog(800, 1000, 0);
	spr_data::Load(img_clear);
	//�����L���O������--------------------------------
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

//���
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

//�X�V
void sceneClear::Update()
{
	//if (KEY_Get(KEY_SPACE)==3) {
	//	MainFrame->ChangeScene(new sceneTitle());
	//}
}

//�`��
void sceneClear::Render()
{
	switch (state) {
		case 0:
			f = 200;
			g = -130;
			h = -210;
			j = -260;
			m = 100;
			//iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,0x3F000000,0); //�Ó]
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //���w�i
			score = pScore->getScore();			//�Q�[���I������score
			newscore = score;					//score�ۑ�
			hp = pPlayer->hp;					//�Q�[���I������hp
			maxcombo = pScore->getMaxCombo();	//�Q�[���I������maxcombo
			gametimer = pNumber->n_timer/60;	//�Q�[���I������time
			life_pos = V2(570+f, 355+g);			//life�̈ʒu
			comb_pos = V2(570+f, 405+g);			//comb�̈ʒu
			time_pos = V2(570+f, 455+g);			//time�̈ʒu
			psb_argb = 0xFFFFFFFF;
			state++;
			//break;
		case 1:
			//spr_data::Render(V2(0, -50), &clear);
			spr_data::Render(V2(200,200), &clear); //�Q�[���N���A�\��

			if ( timer>=40 ) {
				if ( (timer%70*2)>=70 ) psb_argb = 0xFFFFFFFF;
				else psb_argb = 0xFF000000;
				spr_data::Render(V2(480,500),&clear_psb,psb_argb,0); //PushStartButton 01
			}
			timer++;
			if ( KEY_Get(KEY_SPACE)==3 ) {
				timer = 0;
				state++;
			}
			break;
		case 2:
			timer++;
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //���w�i
			spr_data::Render(V2(SCREEN_WIDTH/2, 50), &clear_result); //���U���g

			if (timer>30) spr_data::Render(V2(260+h, 120+m + 75 * 0), &clear_enemy_kari);	//enemy_kari
			if (timer>40) spr_data::Render(V2(260+h, 120+m + 75 * 1), &clear_enemy_yellow);	//enemy_��
			if (timer>50) spr_data::Render(V2(260+h, 120+m + 75 * 2), &clear_enemy_green);	//enemy_��
			if (timer>60) spr_data::Render(V2(560+j, 120+m + 75 * 0), &clear_enemy_pink);	//enemy_�s���N
			if (timer>70) spr_data::Render(V2(560+j, 120+m + 75 * 1), &clear_enemy_blue);	//enemy_��
			if (timer>80) spr_data::Render(V2(560+j, 120+m + 75 * 2), &clear_enemy_white);	//enemy_��

			if (timer>30) spr_data::Render(V2(350+h, 130+m + 75 * 0), &clear_batu); //�~
			if (timer>40) spr_data::Render(V2(350+h, 130+m + 75 * 1), &clear_batu); //�~
			if (timer>50) spr_data::Render(V2(350+h, 130+m + 75 * 2), &clear_batu); //�~
			if (timer>60) spr_data::Render(V2(650+j, 130+m + 75 * 0), &clear_batu); //�~
			if (timer>70) spr_data::Render(V2(650+j, 130+m + 75 * 1), &clear_batu); //�~
			if (timer>80) spr_data::Render(V2(650+j, 130+m + 75 * 2), &clear_batu); //�~

																				//�G���Ƃ�kill��
			if (timer>30) Scene::Render2(V2(400+h, 130+m + 75 * 0), &clear_number[0], pEnemy_Kill->getKill_num_Each(kari));
			if (timer>40) Scene::Render2(V2(400+h, 130+m + 75 * 1), &clear_number[0], pEnemy_Kill->getKill_num_Each(yellow));
			if (timer>50) Scene::Render2(V2(400+h, 130+m + 75 * 2), &clear_number[0], pEnemy_Kill->getKill_num_Each(green));
			if (timer>60) Scene::Render2(V2(700+j, 130+m + 75 * 0), &clear_number[0], pEnemy_Kill->getKill_num_Each(pink));
			if (timer>70) Scene::Render2(V2(700+j, 130+m + 75 * 1), &clear_number[0], pEnemy_Kill->getKill_num_Each(blue));
			if (timer>80) Scene::Render2(V2(700+j, 130+m + 75 * 2), &clear_number[0], pEnemy_Kill->getKill_num_Each(white));



			//������-------------------------------------------------------------------------------------------------------------------------------------------------------
			if ( timer>100 ) {
				spr_data::Render(V2(390+f, 340+g), &clear_score);									//HP����
				if ( life_pos.y<=(480-125) ) Scene::Render2(life_pos,&clear_number[0],hp);	//�I������HP
			}
			if ( timer>120 ) {
				spr_data::Render(V2(390+f,390+g),&clear_score);									//MAXCOMBO����
				if ( comb_pos.y<=(480-125) ) Scene::Render2(comb_pos,&clear_number[0],maxcombo);	//�I������MAXCOMBO
			}
			if ( timer>140 ) {
				spr_data::Render(V2(390+f,440+g),&clear_score);									//Time����
				if ( time_pos.y<=(480-125) ) Scene::Render2(time_pos,&clear_number[0],gametimer);	//�I������time
			}

			if ( timer>160 ) {
				spr_data::Render(V2(390+f,490+g),&clear_score);				//SCORE����
				Scene::Render2(V2(570+f,505+g), &clear_number[0], newscore);	//�X�R�A
			}

			if ( timer==190 ) {
				hp *= 100*2;
				maxcombo *= 100*2;
				gametimer *= 100;
			}

			//�ړ�����--------------------------------------------
			if ( timer>230 && timer<240 ) {
				life_pos.y-=4; //30��ɍs��
				comb_pos.y-=4; //30��ɍs��
				time_pos.y-=4; //30��ɍs��
			}
			if ( timer>250 ) {
				if ( life_pos.y<(480-125) ) life_pos.y += 10;
				if ( comb_pos.y<(480-125) ) comb_pos.y += 10;
				if ( time_pos.y<(480-125) ) time_pos.y += 10;
			}
			//--------------------------------------------------------


			if (KEY_Get(KEY_SPACE) == 3 && newscore==(score+hp+maxcombo+gametimer)) {
				//�����L���O------------------------------------------------------
				ranks_update_info = saveData(ranksFileName, newscore);
				loadData(ranksFileName, ranks);
				//----------------------------------------------------------------
				timer = 0;
				state++;
			}

			//time�����Z����score�ɂȂ�܂�++
			if ( timer>260 ) {
				if ( (score+hp+maxcombo+gametimer)>newscore ) newscore+=41;
				else {
					newscore = score+hp+maxcombo+gametimer;
					if ( (timer%70*2)>=70 ) psb_argb = 0xFFFFFFFF;
					else psb_argb = 0xFF000000;
					spr_data::Render(V2(480,500),&clear_psb,psb_argb,0); //PushStartButton 01
				}
				if ( KEY_Get(KEY_SPACE)==3 ) {
					newscore = score+hp+maxcombo+gametimer;
				}
			}
			break;

		case 3:
			iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0xFF000000, 0); //���w�i
			 //�����L���O-------------------------------------------------------------------------------------
			spr_data::Render(V2(320, 40), &clear_ranking);
			drawRankings(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 -100, ranks, ranks_update_info, &clear_number[0]);
			//-----------------------------------------------------------------------------------------------
			spr_data::Render(V2(340,475-30), &clear_score); //SCORE
			Scene::Render2(V2(480,490-30), &clear_number[0], newscore); //����̃X�R�A
			if (timer>=40) {	//��莞�Ԍo������
				if ( (timer%70*2)>=70 ) psb_argb = 0xFFFFFFFF;
				else psb_argb = 0xFF000000;
				spr_data::Render(V2(480,500),&clear_psb,psb_argb,0); //PushStartButton 01
				if (KEY_Get(KEY_SPACE) == 3) MainFrame->ChangeScene(new sceneTitle()); //�^�C�g����
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