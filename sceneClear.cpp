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



//SPR_DATA clear = { 0,192,192,768,128,0,0,600,100 };
SPR_DATA clear_batu = { 1,0,0,64,64,-32,-32 };	//�~
SPR_DATA clear_enemy_yellow = { 2,64*0,64*0,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_green  = { 2,64*0,64*1,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_pink   = { 2,64*0,64*2,64,64,-32,-32}; //enemy_�s���N
SPR_DATA clear_enemy_blue   = { 2,64*0,64*3,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_white  = { 2,64*0,64*4,64,64,-32,-32}; //enemy_��
SPR_DATA clear_enemy_kari = { 4,0,0,64,64,-32,-32 };		//enemy_kari
SPR_DATA clear_ranking = { 5,0,254,270,360,0,0 };	//�����L���O����6
SPR_DATA clear_result = { 1,0,380,295,68,-295/2,-68/2 };	//RESULT
SPR_DATA clear_LIFE = { 1,0,64*9,64+20,36,0,0 };		//LIFE
SPR_DATA clear_MAXCOMBO = { 1,0,64*7,64*3-12,36,0,0 };	//MAXCOMBO
SPR_DATA clear_TIME = { 1,0,64*8,86,36,0,0 };		//TIME
SPR_DATA clear_TOTAL = { 1,0,64*10,64*2,36,0,0 };		//TOTAL
SPR_DATA clear_psb = { 7,0,1120,474,98,-474/2,-98/2}; //PushStartButton
SPR_DATA clear_back = { 8,0,0,960,540,0,0 }; //�Q�[���N���A���
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
	{ 8,"DATA\\Scene\\crear.png" },
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

	f = 110;
	g = -140;
	h = -210;
	j = -280;
	m = 100;
	score = pScore->getScore();			//�Q�[���I������score
	newscore = score;					//score�ۑ�
	hp = pPlayer->hp;					//�Q�[���I������hp
	maxcombo = pScore->getMaxCombo();	//�Q�[���I������maxcombo
	gametimer = pNumber->n_timer/60;	//�Q�[���I������time
	life_pos = V2(640+f, 375+g);		//life�̈ʒu
	comb_pos = V2(640+f, 425+g);		//comb�̈ʒu
	time_pos = V2(640+f, 475+g);		//time�̈ʒu
	totl_pos = V2(640+f, 525+g);		//totl�̈ʒu
	clear_psb_argb = 0xFFFFFFFF;		//PushStartButton�̐F
	dim_argb = 0xDD000000;				//�t�F�[�h�C��,�Ó]�̐F

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
		case 0: //�t�F�[�h�C��
			spr_data::Render(V2(0,0), &clear_back); //�Q�[���N���A���
			iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,dim_argb,0); //�t�F�[�h�C��
			dim_argb = pMain->fade_in(dim_argb,0x11000000);
			if ( dim_argb<0x11000000 ) {
				dim_argb = 0x00000000;
				state++;
			}
			break;
		case 1: //�Q�[���N���A��ʕ\��
			spr_data::Render(V2(0,0), &clear_back); //�Q�[���N���A���
			//PushStartButton--------------------------------------------------------------
			if ( timer++>=40 ) {
				if ( (timer%70*2)>=70 ) clear_psb_argb = 0xFFFFFFFF;
				else clear_psb_argb = 0x00000000;
				spr_data::Render(V2(480,500),&clear_psb,clear_psb_argb,0);
			}
			//-----------------------------------------------------------------------------
			if ( KEY_Get(KEY_SPACE)==3 ) {
				timer = 0;
				state++;
			}
			break;
		case 2: //�Ó]
			spr_data::Render(V2(0,0), &clear_back); //�Q�[���N���A���
			iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,dim_argb,0); //�Ó]
			dim_argb = pMain->fade_out(dim_argb,0x11000000);
			if ( dim_argb>0x77000000 ) state++;
			break;
		case 3:
			if ( timer++>10 ) {
				state++;
				timer = 0;
			}
			break;
		case 4:
			spr_data::Render(V2(0,0), &clear_back); //�Q�[���N���A���
			iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,dim_argb,0); //�Ó]
			spr_data::Render(V2(SCREEN_WIDTH/2, 50), &clear_result); //RESULT����

			//enemy
			if (timer>0) spr_data::Render(V2(260+h, 120+m + 75 * 0), &clear_enemy_kari);
			if (timer>0) spr_data::Render(V2(260+h, 120+m + 75 * 1), &clear_enemy_yellow);
			if (timer>0) spr_data::Render(V2(260+h, 120+m + 75 * 2), &clear_enemy_green);
			if (timer>0) spr_data::Render(V2(560+j, 120+m + 75 * 0), &clear_enemy_pink);
			if (timer>0) spr_data::Render(V2(560+j, 120+m + 75 * 1), &clear_enemy_blue);
			if (timer>0) spr_data::Render(V2(560+j, 120+m + 75 * 2), &clear_enemy_white);

			//�~
			if (timer>0) spr_data::Render(V2(350+h, 130+m + 75 * 0), &clear_batu);
			if (timer>0) spr_data::Render(V2(350+h, 130+m + 75 * 1), &clear_batu);
			if (timer>0) spr_data::Render(V2(350+h, 130+m + 75 * 2), &clear_batu);
			if (timer>0) spr_data::Render(V2(650+j, 130+m + 75 * 0), &clear_batu);
			if (timer>0) spr_data::Render(V2(650+j, 130+m + 75 * 1), &clear_batu);
			if (timer>0) spr_data::Render(V2(650+j, 130+m + 75 * 2), &clear_batu);

			//�G���Ƃ�kill��
			if (timer>50) Scene::Render2(V2(400+h, 130+m + 75 * 0), &clear_number[0], pEnemy_Kill->getKill_num_Each(kari));
			if (timer>65) Scene::Render2(V2(400+h, 130+m + 75 * 1), &clear_number[0], pEnemy_Kill->getKill_num_Each(yellow));
			if (timer>80) Scene::Render2(V2(400+h, 130+m + 75 * 2), &clear_number[0], pEnemy_Kill->getKill_num_Each(green));
			if (timer>95) Scene::Render2(V2(700+j, 130+m + 75 * 0), &clear_number[0], pEnemy_Kill->getKill_num_Each(pink));
			if (timer>110) Scene::Render2(V2(700+j, 130+m + 75 * 1), &clear_number[0], pEnemy_Kill->getKill_num_Each(blue));
			if (timer>125) Scene::Render2(V2(700+j, 130+m + 75 * 2), &clear_number[0], pEnemy_Kill->getKill_num_Each(white));


			//�I������HP�`��-----------------------------------------------------------------------------
			if (timer>0) spr_data::Render(V2(390+f, 340+g), &clear_LIFE);
			if ( timer>160 ) {
				if ( life_pos.y<=(480-125) ) Scene::Render2(life_pos,&clear_number[0],hp);
			}
			//�I������MAXCOMBO�`��-----------------------------------------------------------------------
			if (timer>0) spr_data::Render(V2(390+f,390+g),&clear_MAXCOMBO);
			if ( timer>180 ) {
				if ( comb_pos.y<=(480-125) ) Scene::Render2(comb_pos,&clear_number[0],maxcombo);
			}
			//�I������TIME�`��---------------------------------------------------------------------------
			if (timer>0) spr_data::Render(V2(390+f,440+g),&clear_TIME);
			if ( timer>200 ) {
				if ( time_pos.y<=(480-125) ) Scene::Render2(time_pos,&clear_number[0],gametimer);
			}
			//TOTAL�`��-------------------------------------------------------------------------------------------
			if (timer>0) spr_data::Render(V2(390+f,490+g),&clear_TOTAL);
			if ( timer>220 ) Scene::Render2(totl_pos, &clear_number[0], newscore);

			//TOTAL���Z
			if ( timer==280 ) {
				hp *= 100*2;
				maxcombo *= 100*2;
				gametimer *= 100;
			}

			//�ړ�����--------------------------------------------
			if ( timer>320 && timer<330 ) {
				life_pos.y-=4; //30��ɍs��
				comb_pos.y-=4; //30��ɍs��
				time_pos.y-=4; //30��ɍs��
			}
			if ( timer>340 ) {
				if ( life_pos.y<(480-120) ) life_pos.y += 10;
				if ( comb_pos.y<(480-120) ) comb_pos.y += 10;
				if ( time_pos.y<(480-120) ) time_pos.y += 10;
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

			//3�l�����Z����score�ɂȂ�܂�++
			if ( timer>350 ) {
				if ( (score+hp+maxcombo+gametimer)>newscore ) newscore+=51;
				else {
					newscore = score+hp+maxcombo+gametimer;
					//PushStartButton--------------------------------------------------------------
					if ( (timer%70*2)>=70 ) clear_psb_argb = 0xFFFFFFFF;
					else clear_psb_argb = 0x00000000;
					spr_data::Render(V2(480,500),&clear_psb,clear_psb_argb,0);
					//-----------------------------------------------------------------------------
				}
				if ( KEY_Get(KEY_SPACE)==3 ) newscore = score+hp+maxcombo+gametimer;
			}


			//�X�L�b�v--------------------------------------
			if ( KEY_Get(KEY_SPACE)==3 && timer<280) {
				timer = 279; //TOTAL���Z�O�܂ŃX�L�b�v
			}

			timer++;
			break;
		case 5:
			spr_data::Render(V2(0,0), &clear_back); //�Q�[���N���A���
			iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,dim_argb,0); //�Ó]
			 //�����L���O�`��-----------------------------------------------------------------------------------
			spr_data::Render(V2(320, 40), &clear_ranking);
			drawRankings(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 -100, ranks, ranks_update_info, &clear_number[0]);
			//--------------------------------------------------------------------------------------------------
			spr_data::Render(V2(280,425), &clear_TOTAL); //TOTAL
			Scene::Render2(V2(480,490-30), &clear_number[0], newscore); //����̃X�R�A
			if (timer>=40) {	//��莞�Ԍo������
				//PushStartButton--------------------------------------------------------------
				if ( (timer%70*2)>=70 ) clear_psb_argb = 0xFFFFFFFF;
				else clear_psb_argb = 0x0000000;
				spr_data::Render(V2(480,500),&clear_psb,clear_psb_argb,0);
				//-----------------------------------------------------------------------------
				if ( KEY_Get(KEY_SPACE)==3||timer>60*20 ) {
					MainFrame->ChangeScene(new sceneTitle()); //�^�C�g����
					//state++;
					//dim_argb = 0x00000000;
				}
			}
			timer++;
			break;
		//case 6: //�t�F�[�h�A�E�g
		//	iexPolygon::Rect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,0,dim_argb,0);
		//	dim_argb = pMain->fade_out(dim_argb);
		//	if ( dim_argb>0xEE000000 ) {
		//		dim_argb = 0xFF000000;
		//		MainFrame->ChangeScene(new sceneTitle()); //�^�C�g����
		//	}
		//	break;
		default:
			break;
	}

	//char str[128];
	//sprintf_s(str, 128, "score:%d", pEnemy_Kill->getKill_num_Each(pink));
	//IEX_DrawText(str, 300, 300, 128, 16, 0xFFFF0000);
	//sprintf_s(str, 128, "kill:%d", pScore->kill_num);
	//IEX_DrawText(str, 300, 300, 128, 16, 0xFFFF0000);
}