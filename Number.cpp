//*****************************************************************************
//
//			制限時間
//
//*****************************************************************************
#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Player.h"
#include "Frame.h"
#include "Number.h"
#include "sceneMain.h"


Number score;		//スコア
Number combo;		//コンボ
Number gametimer;	//ゲームタイマー
Number gametimer2;	//ゲームタイマー2
Number crushnum;	//撃破数
Number crushnum2;	//撃破目標数
Number exorcisetimer; //霊力タイマー


SPR_DATA ui_data[] = {
	{ spr_data::UI6,  0,190,  120,40,  0,0 },//SCORE
	{ spr_data::UI6,  0,125,  120,40,  0,0 },//COMBO
	{ spr_data::UI6,  0,250,  120,40,  0,0 },//NORMA　※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※
};


//static SPR_DATA anime_Number_data[] = {
//	SPR_DATA{spr_data::Ext, 64*0, 0, 64, 64, -32, -32}, //0
//	SPR_DATA{spr_data::Ext, 64*1, 0, 64, 64, -32, -32}, //1
//	SPR_DATA{spr_data::Ext, 64*2, 0, 64, 64, -32, -32}, //2
//	SPR_DATA{spr_data::Ext, 64*3, 0, 64, 64, -32, -32}, //3
//	SPR_DATA{spr_data::Ext, 64*4, 0, 64, 64, -32, -32}, //4
//	SPR_DATA{spr_data::Ext, 64*0,64, 64, 64, -32, -32}, //5
//	SPR_DATA{spr_data::Ext, 64*1,64, 64, 64, -32, -32}, //6
//	SPR_DATA{spr_data::Ext, 64*2,64, 64, 64, -32, -32}, //7
//	SPR_DATA{spr_data::Ext, 64*3,64, 64, 64, -32, -32}, //8
//	SPR_DATA{spr_data::Ext, 64*4,64, 64, 64, -32, -32}, //9
//	SPR_DATA{			-1,	   0, 0,  0,  0,   0,   0}
//};


Number::Number() {
	//score.data = &anime_Number_data[0];
	score.numImage = new iex2DObj("DATA\\Public\\number.png");
	combo.numImage = new iex2DObj("DATA\\Public\\number.png");
	gametimer.numImage = new iex2DObj("DATA\\Public\\number.png");
	gametimer2.numImage = new iex2DObj("DATA\\Public\\number.png");
	crushnum.numImage = new iex2DObj("DATA\\Public\\number.png");
	crushnum2.numImage = new iex2DObj("DATA\\Public\\number.png");
	exorcisetimer.numImage = new iex2DObj("DATA\\Public\\number.png");


	score.SetSize(32);			//スコア文字サイズ設定
	combo.SetSize(32);			//コンボ文字サイズ設定
	gametimer.SetSize(64);		//ゲームタイマー (上2ケタ)文字サイズ設定
	gametimer2.SetSize((int)(64 * 0.6f));	//ゲームタイマー2(下2ケタ)文字サイズ設定
	crushnum.SetSize((int)(64 * 0.6f));		//撃破数文字サイズ設定
	crushnum2.SetSize((int)(64 * 0.6f));		//撃破数文字サイズ設定
	exorcisetimer.SetSize((int)(64 * 0.6f));	//霊力タイマーサイズ設定

												//score.custom.clear();
												//gametimer.custom.clear();
												//gametimer2.custom.clear();

												//score.custom.scaleMode = CENTER;
												//gametimer.custom.scaleMode = CENTER;
												//gametimer2.custom.scaleMode = CENTER;

												//score.custom.scaleY = score.custom.scaleX = 1;
												//gametimer.custom.scaleY = gametimer.custom.scaleX = 1;
												//gametimer.custom.scaleX = gametimer.custom.scaleY = 1;

}

Number::~Number() {

}

void Number::Init() {

}

void Number::Update(int timer) {
	score.SetNum(pScore->getScore(), 5);			//スコア処理
	combo.SetNum(pScore->getCombo(), 5);			//コンボ処理
	combo.AddScale();							//コンボ加算時の拡大表示	
	if ((timer / 60)>10) gametimer_argb = 0xFFFFFFFF; //白
	else gametimer_argb = 0xFFFF0000; //10秒未満なら赤
	gametimer.SetNum(timer / 60, 2);				//ゲームタイマー (上2ケタ)処理
	gametimer2.SetNum(timer % 60, 2);			//ゲームタイマー2(下2ケタ)処理
	crushnum.SetNum(pScore->getKill_num(), 2);	//撃破数処理
	crushnum2.SetNum(50, 2);	//撃破数処理
								//				 ↑ステージに応じて変更
	exorcisetimer.SetNum(pFrame->exorciseDwon_timer / 60 + 1, 1);	//霊力タイマー処理
	n_timer = timer;
}


void Number::Render() {
	score.Render(790, 60, 5);								//スコア描画
	//combo.Render2(580, 130, pScore->getCombo());			//コンボ描画
	gametimer.Render3(400, 15, 2, gametimer_argb);			//ゲームタイマー (上2ケタ)描画
	gametimer2.Render3(400 + 125, 39, 2, gametimer_argb);	//ゲームタイマー2(下2ケタ)描画
	crushnum.Render(775, 150, 2);								//撃破数描画
	crushnum2.Render(875, 150, 2);							//撃破数描画
	if (pFrame->exorciseDwon_timer>0) {					//霊力タイマー
		exorcisetimer.Render(450, 150, 1);					//霊力タイマー描画
	}
	spr_data::Render(V2(750, 20), &ui_data[0]);	//　SCORE
	//spr_data::Render(V2(550,100),&ui_data[1]);	//　COMBO
	spr_data::Render(V2(750, 100), &ui_data[2]);	//　撃破数
}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	関数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//表示文字サイズ変更関数
void Number::SetSize(int size)
{
	if (size > 0)	digitDispSize = size;
	if (size < 0)	digitDispSize = DIGIT_SIZE;
}


//数値設定関数         
void  Number::SetNum(int num, int digit_max)
{
	for (int i = 0; i < digit_max; i++)
	{
		digit[i].val = num % 10;	//  一の位を抽出
		digit[i].x = 0;
		digit[i].y = 0;
		digit[i].w = digit[i].h = 1;
		digit[i].timer = 0;
		num /= 10;					//  桁を1つシフト
	}
}


//加算時の拡大表示
void Number::AddScale() {
	after = pScore->getCombo(); //今のコンボ数
	if (after>front) { //コンボが入ったら
		custom.scaleMode = CENTER;
		//custom.scaleY = custom.scaleX = rand() % 40/100.0f + 1; //　1＋(0.0～0.4)倍
		custom.scaleY = custom.scaleX = 1.8f; //　1.4倍
	}
	else { //コンボが入っていなかったら
		custom.scaleMode = CENTER;
		custom.scaleY = custom.scaleX = 1.0f;
	}
	front = after; //今のコンボ数を前のコンボ数として保存

}


//数値描画関数(桁数分だけ描画)
void  Number::Render2(int x, int y, int num)
{
	//表示文字数処理
	int digit_max = 0;
	for (int i = 0; i<5; i++) {
		digit_max++;
		if (num<10) break;
		num /= 10;
	}

	x += digitDispSize * digit_max;  //  一の位から描画するので右端にずらす

	for (int i = 0; i<digit_max; i++)
	{
		x -= digitDispSize;
		int  sx = (digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		numImage->customRender(
			x + digit[i].x - 3, y + digit[i].y,														//描画位置x,描画位置y
			custom.scaleX*digitDispSize*digit[i].w, custom.scaleY*digitDispSize*digit[i].h,		//描画幅x,描画幅y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//切抜位置x,切抜位置y, 文字サイズ,文字サイズ
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			custom.argb, custom.reflectX, custom.scaleMode);
	}
}


//数値描画関数(指定分描画)           (digitmax = 表示文字数)  
void  Number::Render(int x, int y, int digit_max)
{
	x += digitDispSize * digit_max;  //  一の位から描画するので右端にずらす

	for (int i = 0; i<digit_max; i++)
	{
		x -= digitDispSize;
		int  sx = (digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		//if (i == 2) x -= digitDispSize / 2;		//2ケタ目で間をあける	※コンマの際に使う？

		numImage->customRender(
			x + digit[i].x - 3, y + digit[i].y,														//描画位置x,描画位置y
			custom.scaleX*digitDispSize*digit[i].w, custom.scaleY*digitDispSize*digit[i].h,		//描画幅x,描画幅y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//切抜位置x,切抜位置y, 文字サイズ,文字サイズ
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			custom.argb, custom.reflectX, custom.scaleMode);
	}
	//numImage->Render(		//：
	//	x + 57, y,
	//	digitDispSize, digitDispSize,
	//	0 * 64, 2 * 64, DIGIT_SIZE, DIGIT_SIZE);
}


//数値描画関数(指定分描画+color)           (digitmax = 表示文字数)  
void  Number::Render3(int x, int y, int digit_max, D3DCOLOR argb)
{
	x += digitDispSize * digit_max;  //  一の位から描画するので右端にずらす

	for (int i = 0; i<digit_max; i++)
	{
		x -= digitDispSize;
		int  sx = (digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		numImage->customRender(
			x + digit[i].x - 3, y + digit[i].y,														//描画位置x,描画位置y
			custom.scaleX*digitDispSize*digit[i].w, custom.scaleY*digitDispSize*digit[i].h,		//描画幅x,描画幅y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//切抜位置x,切抜位置y, 文字サイズ,文字サイズ
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			argb, custom.reflectX, custom.scaleMode);
	}
}
