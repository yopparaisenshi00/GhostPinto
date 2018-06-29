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
Number gametimer;	//ゲームタイマー
Number gametimer2;	//ゲームタイマー2
Number crushnum;	//撃破数
Number crushnum2;	//撃破目標数
Number exorcisetimer; //霊力タイマー
Number eval_addscore;	//コンボリザルト用撮影スコア
Number eval_combo;		//コンボリザルト用コンボ数
Number eval_justpinto;	//コンボリザルト用ジャストピント
Number eval_total;		//コンボリザルト用TOTAL


SPR_DATA ui_data[] = {
	{ spr_data::UI6,  0,190,  120,40,  0,0 },//SCORE
	{ spr_data::UI6,  0,250,  120,40,  0,0 },//NORMA
	{ spr_data::UI6,  0,64*11,  32*7,40,  0,0,  (int)((32*7)*0.75f),(int)(40*0.6f) },//COMBORESULT------
	{ spr_data::UI6,  0,64*12,  32*6,40,  0,0,  (int)((32*6)*0.75f),(int)(40*0.6f) },//TIMETOSHOOT
	{ spr_data::UI6,  0,64*13,  32*6,40,  0,0,  (int)((32*6)*0.75f),(int)(40*0.6f) },//COMBO COUNT
	{ spr_data::UI6,  0,64*14,  32*6,40,  0,0,  (int)((32*6)*0.75f),(int)(40*0.6f) },//JUST COUNT
	{ spr_data::UI6,  0,64*15,  32*7,40,  0,0,  (int)((32*7)*0.90f),(int)(40*0.75f) },//TOTAL SCORE
	{ spr_data::Number,  64*2,64*2,64,64,-32,-32,42,42 },//スラッシュ
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
	numImage = new iex2DObj("DATA\\Public\\number.png");
	score.numImage = numImage;
	gametimer.numImage = numImage;
	gametimer2.numImage = numImage;
	crushnum.numImage = numImage;
	crushnum2.numImage = numImage;
	exorcisetimer.numImage = numImage;
	eval_addscore.numImage = numImage;
	eval_combo.numImage = numImage;
	eval_justpinto.numImage = numImage;
	eval_total.numImage = numImage;

	score.SetSize(32);			//スコア文字サイズ設定
	gametimer.SetSize(64);		//ゲームタイマー (上2ケタ)文字サイズ設定
	gametimer2.SetSize((int)(64 * 0.6f));	//ゲームタイマー2(下2ケタ)文字サイズ設定
	crushnum.SetSize((int)(64 * 0.6f));		//撃破数文字サイズ設定
	crushnum2.SetSize((int)(64 * 0.6f));		//撃破数文字サイズ設定
	exorcisetimer.SetSize((int)(64 * 0.6f));	//霊力タイマーサイズ設定
	eval_addscore.SetSize((int)(32 * 0.7f));
	eval_combo.SetSize((int)(32 * 0.7f));
	eval_justpinto.SetSize((int)(32 * 0.7f));
	eval_total.SetSize((int)(32 * 0.9f));

	//右下
	//eval.result_pos =	V2(680,320+0);
	//eval.time_pos =		V2(680,320+40);
	//eval.combo_pos =	V2(680,320+80);
	//eval.just_pos =		V2(680,320+120);
	//eval.total_pos =	V2(680,320+160);

	//左真ん中
	eval.result_pos =	V2(-10,200+0);
	eval.time_pos =		V2(-10,200+40);
	eval.combo_pos =	V2(-10,200+80);
	eval.just_pos =		V2(-10,200+120);
	eval.total_pos =	V2(5,200+160);

	//左上
	//eval.result_pos =	V2(150,20+0);
	//eval.time_pos =		V2(150,20+40);
	//eval.combo_pos =	V2(150,20+80);
	//eval.just_pos =		V2(150,20+120);
	//eval.total_pos =	V2(150,20+160);


	eval_addscore.custom.scaleMode = CENTER;
	eval_combo.custom.scaleMode = CENTER;
	eval_justpinto.custom.scaleMode = CENTER;
	eval_total.custom.scaleMode = CENTER;
	eval.custom.scaleMode = CENTER;

	eval_addscore.custom.scaleY = eval_addscore.custom.scaleX	=2.0f;
	eval_combo.custom.scaleY = eval_combo.custom.scaleX			=2.0f;
	eval_justpinto.custom.scaleY = eval_justpinto.custom.scaleX =2.0f;
	eval_total.custom.scaleY = eval_total.custom.scaleX			=2.0f;
	eval.custom.scaleY = eval.custom.scaleX						=2.0f;

	eval.custom.argb = 0xFFFFFFFF;
	eval.alpha = 0;
}

Number::~Number() {

}

void Number::Init() {
	eval.flg = false;

}

//点滅関数(二色)
void Number::Frash_Color_two(Number* obj,int num,D3DCOLOR argb1, D3DCOLOR argb2) {
	if ((eval.timer % (num * 2)) <  num) obj->custom.argb = argb1;
	if ((eval.timer % (num * 2)) >= num) obj->custom.argb = argb2;
	//if ((eval.timer % (num * 2)) <  num) obj->custom.argb = argb1;
	//if ( (eval.timer%(num*2))>=num ) {
	//	obj->custom.argb = argb2;
	//	eval.alpha = (int)(255*0.5f);
	//}
}

//点滅関数(虹色)
void Number::Frash_Color_rainbow(Number* obj,int num,
	D3DCOLOR argb1, D3DCOLOR argb2,D3DCOLOR argb3, 
	D3DCOLOR argb4, D3DCOLOR argb5,D3DCOLOR argb6) {
	eval.iwork = eval.timer%num*6+1;
	     if (eval.iwork<=num*1) obj->custom.argb = argb1;	//紫色
	else if (eval.iwork<=num*2) obj->custom.argb = argb2;	//オレンジ色
	else if (eval.iwork<=num*3) obj->custom.argb = argb3;	//黄色
	else if (eval.iwork<=num*4) obj->custom.argb = argb4;	//緑色
	else if (eval.iwork<=num*5) obj->custom.argb = argb5;	//水色
	else if (eval.iwork<=num*6) obj->custom.argb = argb6;	//青色
	else obj->custom.argb = 0xFFFFFFFF;
}


//評価用関数
void Number::eval_agree() {

	if ( pScore->getcombotimer()>=COMBO_TIME && (pScore->getCombo()>=5) ) {
		eval.addscore = pScore->getAddscore();				//保存
		eval.combo = pScore->getCombo();				//保存
		int comboscore = pScore->getcomboscore();
		eval.just = pScore->getEval_justpinto();			//保存
		eval.total = eval.addscore+comboscore/*+eval.just*200*/;	//TOTAL計算

		eval_addscore.SetNum(eval.addscore,3);	//撮影スコア（映してる間増加するスコア）
		eval_combo.SetNum(eval.combo,2);		//倒した数
		eval_justpinto.SetNum(eval.just,2);		//ジャストピントを決めた数
		eval_total.SetNum(eval.total,4);		//TOTAL

		eval.flg = true;
	}

	if ( eval.flg == true ) eval.timer++;


	//移動処理-------------------------------------------------

	if ( (1<=eval.timer) && (eval.timer<=60) ) { //
		if(eval.addscore>=3000)			Frash_Color_rainbow(&eval_addscore,FRASHSPD1,RB1,RB2,RB3,RB4,RB5,RB6);
		else if(eval.addscore>=1000)	Frash_Color_two(&eval_addscore,FRASHSPD2,YELLOW,WHITE);
		else							Frash_Color_two(&eval_addscore,FRASHSPD2,RED,WHITE);

		if(eval.combo>=20)		Frash_Color_rainbow(&eval_combo,FRASHSPD1,RB1,RB2,RB3,RB4,RB5,RB6);
		else if(eval.combo>=10)	Frash_Color_two(&eval_combo,FRASHSPD2,YELLOW,WHITE);
		else					Frash_Color_two(&eval_combo,FRASHSPD2,RED,WHITE);

		if(eval.just>=15)		Frash_Color_rainbow(&eval_justpinto,FRASHSPD1,RB1,RB2,RB3,RB4,RB5,RB6);
		else if(eval.just>=10)	Frash_Color_two(&eval_justpinto,FRASHSPD2,YELLOW,WHITE);
		else					Frash_Color_two(&eval_justpinto,FRASHSPD2,RED,WHITE);

		if(eval.total>=10000)		Frash_Color_rainbow(&eval_total,FRASHSPD1,RB1,RB2,RB3,RB4,RB5,RB6);
		else if(eval.total>=5000)	Frash_Color_two(&eval_total,FRASHSPD2,YELLOW,WHITE);
		else						Frash_Color_two(&eval_total,FRASHSPD2,RED,WHITE);


		eval_addscore.custom.scaleY = eval_addscore.custom.scaleX	-=0.1f;
		eval_combo.custom.scaleY = eval_combo.custom.scaleX			-=0.1f;
		eval_justpinto.custom.scaleY = eval_justpinto.custom.scaleX -=0.1f;
		eval_total.custom.scaleY = eval_total.custom.scaleX			-=0.1f;
		eval.custom.scaleY = eval.custom.scaleX						-=0.1f;
		if ( eval_addscore.custom.scaleX = eval_addscore.custom.scaleY		<=1.0f )	eval_addscore.custom.scaleX = eval_addscore.custom.scaleY	= 1.0f;
		if ( eval_combo.custom.scaleX = eval_combo.custom.scaleY			<=1.0f )	eval_combo.custom.scaleX = eval_combo.custom.scaleY			= 1.0f;
		if ( eval_justpinto.custom.scaleX = eval_justpinto.custom.scaleY	<=1.0f )	eval_justpinto.custom.scaleX = eval_justpinto.custom.scaleY = 1.0f;
		if ( eval_total.custom.scaleX = eval_total.custom.scaleY			<=1.0f )	eval_total.custom.scaleX = eval_total.custom.scaleY			= 1.0f;
		if ( eval.custom.scaleX = eval.custom.scaleY						<=1.0f )	eval.custom.scaleX = eval.custom.scaleY						= 1.0f;

		//if ( (eval.timer%8)<4 ) {
		//	custom.argb = 0xFFff7a7a;
		//}
		//if ( (eval.timer%8)>=4 ) {
		//	custom.argb = 0xFFFFFFFF;
		//}
		eval.alpha += 50;
		if ( eval.alpha>=(int)(255*1.0f) ) eval.alpha = (int)(255*1.0f);
	}

	//文字色(白)
	if( 60<eval.timer ){
		eval.alpha = (int)(255*1.0f);
		custom.argb = 0xFFFFFFFF;
		eval_addscore.custom.argb = 0xFFFFFFFF;
		eval_combo.custom.argb = 0xFFFFFFFF;
		eval_justpinto.custom.argb = 0xFFFFFFFF;
		eval_total.custom.argb = 0xFFFFFFFF;
	}

	//縦縮小
	if ( 130<eval.timer ) {
		eval_addscore.	custom.scaleY -=0.2f;
		eval_combo.		custom.scaleY -=0.2f;
		eval_justpinto.	custom.scaleY -=0.2f;
		eval_total.		custom.scaleY -=0.2f;
		eval.custom.scaleY			  -=0.2f;
		if ( eval_addscore.custom.scaleY<=0 )	eval_addscore.custom.scaleY = 0.0f;
		if ( eval_combo.custom.scaleY<=0 )		eval_combo.custom.scaleY = 0.0f;
		if ( eval_justpinto.custom.scaleY<=0 )	eval_justpinto.custom.scaleY = 0.0f;
		if ( eval_total.custom.scaleY<=0 )		eval_total.custom.scaleY = 0.0f;
		if ( eval.custom.scaleY<=0 )			eval.custom.scaleY = 0.0f;
	}

	//初期化
	if ( 150<eval.timer ) {
		eval.flg = false;
		eval.timer = 0;
		pScore->addscore = 0;
		//pScore->eval_justpinto = 0;
		pScore->comboscore = 0;
		eval.alpha = 0;
		eval_addscore.custom.scaleX = eval_addscore.custom.scaleY	= 2.0f;
		eval_combo.custom.scaleX = eval_combo.custom.scaleY			= 2.0f;
		eval_justpinto.custom.scaleX = eval_justpinto.custom.scaleY = 2.0f;
		eval_total.custom.scaleX = eval_total.custom.scaleY			= 2.0f;
		eval.custom.scaleX = eval.custom.scaleY						= 2.0f;
	}
}


void Number::Update(int timer) {
	//score.AddScale(pScore->getScore(),1.25f);
	score.SetNum(pScore->getScore(), 5);		//スコア処理
	if ((timer / 60)>10) gametimer_argb = 0xFFFFFFFF;	//白
	else gametimer_argb = 0xFFFF0000;					//10秒未満なら赤
	//gametimer.AddScale((int)(timer/60),1.5f);
	//gametimer2.AddScale((int)(timer/60),1.5f);
	gametimer.SetNum(timer / 60, 2);			//ゲームタイマー (上2ケタ)処理
	gametimer2.SetNum(timer % 60, 2);			//ゲームタイマー2(下2ケタ)処理
	crushnum.AddScale(pScore->getKill_num(),1.7f);	//撃破数加算時の拡大表示
	crushnum.SetNum(pScore->getKill_num(), 2);	//撃破数処理
	crushnum2.SetNum(60, 2);					//撃破数処理(ステージに応じて変更)

	if ( (pFrame->exorciseDwon_timer==180) || (pFrame->exorciseDwon_timer==120) ||
		(pFrame->exorciseDwon_timer==60) ) {
		exorcise_argb = 0xFFFF3333;
	}
	//if ( (pFrame->exorciseDwon_timer!=180) || (pFrame->exorciseDwon_timer!=120) ||
	//	(pFrame->exorciseDwon_timer!=60) ) {
	//	exorcise_argb += 0x00001111;
	//	//if ( exorcise_argb>=0xFFFFBBBB ) exorcise_argb = WHITE;
	//	if ( exorcise_argb==WHITE ) exorcise_argb = WHITE;
	//}
	else {
		//exorcise_argb += 0x00001111;
		//if ( exorcise_argb>=0xFFFFBBBB ) exorcise_argb = WHITE;
		if ( exorcise_argb==WHITE ) exorcise_argb = WHITE;
		else exorcise_argb += 0x00001111;
	}

	exorcisetimer.SetNum(pFrame->exorciseDwon_timer / 60 + 1, 1);	//霊力タイマー処理
	eval_agree();
	n_timer = timer;
}


void Number::Render() {
	//score.Render(780, 35, 5);								//スコア描画
	score.Render(790, 60, 5);								//スコア描画
	gametimer.Render3(400, 15, 2, gametimer_argb);			//ゲームタイマー (上2ケタ)描画
	gametimer2.Render3(400 + 125, 39, 2, gametimer_argb);	//ゲームタイマー2(下2ケタ)描画
	crushnum.Render(750, 124, 2);							//撃破数描画
	spr_data::Render(V2(865, 180), &ui_data[7]);			//スラッシュ
	crushnum2.Render(875, 150, 2);							//撃破数描画
	if (pFrame->exorciseDwon_timer>0) {						//霊力タイマー
		exorcisetimer.Render3(450, 150, 1,exorcise_argb);					//霊力タイマー描画
	}
	spr_data::Render(V2(750, 20), &ui_data[0]);		//SCORE
	spr_data::Render(V2(750, 100), &ui_data[1]);	//撃破数

	if ( eval.flg && (pScore->getKill_num() < CLEAR_KILLNUM)/* || timer <= 0*/ && (eval.combo>=5) ) {
		eval.custom.argb = (eval.alpha << 24 | custom.argb << 8 >> 8);
		eval_addscore.custom.argb= (eval.alpha << 24 | eval_addscore.custom.argb << 8 >> 8);
		eval_combo.custom.argb = (eval.alpha << 24 | eval_combo.custom.argb << 8 >> 8);
		eval_justpinto.custom.argb = (eval.alpha << 24 | eval_justpinto.custom.argb << 8 >> 8);
		eval_total.custom.argb = (eval.alpha << 24 | eval_total.custom.argb << 8 >> 8);
		eval_addscore.Render3(	eval.time_pos.x  +205+5,  eval.time_pos.y	-14,3,eval_addscore.custom.argb);
		eval_combo.Render3(		eval.combo_pos.x +205+5,  eval.combo_pos.y-14,2,eval_combo.custom.argb);
		eval_justpinto.Render3(	eval.just_pos.x  +205+5,  eval.just_pos.y	-14,2,eval_justpinto.custom.argb);
		eval_total.Render3(		eval.total_pos.x +190+5,  eval.total_pos.y-14,4,eval_total.custom.argb);
		spr_data::Render(eval.result_pos,&ui_data[2],&eval.custom,eval.custom.argb);//コンボリザルト------------------------
		spr_data::Render(eval.time_pos,&ui_data[3],&eval.custom,eval_addscore.custom.argb);	//TIMETOSHOOT：撮影スコア（映してる間増加するスコア）
		spr_data::Render(eval.combo_pos,&ui_data[4],&eval.custom,eval_combo.custom.argb);	//COMBO COUNT：倒した数
		spr_data::Render(eval.just_pos,&ui_data[5],&eval.custom,eval_justpinto.custom.argb);	//JUST COUNT ：ジャストピントを決めた数
		spr_data::Render(eval.total_pos,&ui_data[6],&eval.custom,eval_total.custom.argb);	//TOTAL SCORE：コンボで稼いだ得点
	}
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
void Number::AddScale(int n, float scale) {
	after = n; //今の数
	if (after>front) { //前の数と比べて増えたら
		custom.scaleMode = BOTTOMCENTER;
		custom.scaleX = custom.scaleY = scale; //拡大
	}
	else { //変わってなかったら
		custom.scaleMode = BOTTOMCENTER;
		if ( custom.scaleX>1.0f ) custom.scaleY = custom.scaleX -= 0.2f;
		else custom.scaleY = custom.scaleX = 1.0f;
	}
	front = after; //今の数を前の数として保存

}


//数値描画関数(桁数分だけ描画)
void  Number::Render2(int x, int y, int num)
{
	int _num = num;
	int digit_max = 0;

	while ( _num>=10 ) { //10以上なら
		_num /= 10;		//10で割って
		digit_max++;		//x位置ずらしカウント
	}

	x += digitDispSize * digit_max;  //  一の位から描画するので右端にずらす

	for (int i = 0; i < digit_max; i++)
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

	for (int i = 0; i < digit_max; i++)
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

	for (int i = 0; i < digit_max; i++)
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


//数値描画関数(指数値描画(num) + 指定分描画 + color)           (digitmax = 表示文字数)
void  Number::RenderFree(int x, int y, int num, int digit_max, int _digitDispSize, D3DCOLOR argb = 0xFFFFFFFF)
{
	int Size = _digitDispSize;
	Number::tagDIGIT _digit[DIGIT_MAX];
	for (int i = 0; i < digit_max; i++)
	{
		_digit[i].val = num%10;//  一の位を抽出
		_digit[i].x = 0;
		_digit[i].y = 0;
		_digit[i].w = _digit[i].h = 1;
		_digit[i].timer = 0;
		num /= 10;					//  桁を1つシフト
	}
	for (int i = 0; i < digit_max; i++) {
		x -= Size * i;
		int  sx = (_digit[i].val % NUM_DIGIT_1LINE) * DIGIT_SIZE;
		int  sy = (_digit[i].val / NUM_DIGIT_1LINE) * DIGIT_SIZE;

		numImage->customRender(
			x + _digit[i].x - 3, y + _digit[i].y,														//描画位置x,描画位置y
			custom.scaleX*Size *_digit[i].w, custom.scaleY*Size *_digit[i].h,		//描画幅x,描画幅y
			sx, sy,
			DIGIT_SIZE, DIGIT_SIZE,														//切抜位置x,切抜位置y, 文字サイズ,文字サイズ
			custom.angle, custom.centRotate, custom.centX, custom.centY, RS_ALPH,
			argb, custom.reflectX, custom.scaleMode);
	}
}



