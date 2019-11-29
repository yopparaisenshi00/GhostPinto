#include "iextreme.h"
#include "Game.h"
#include "MAP.h"
#include "Frame.h"
#include "Player.h"
#include "Sound.h"
#include "sceneMain.h"

enum {
	pinto_s = spr_data::UI1,
	pinto_a = spr_data::UI2,
	flame_out = spr_data::UI3,
	pinto_l = spr_data::UI4,

};

enum {
	INIT,
	READY,
	MOVE,
};

// フレーム画像
SPR_DATA spr_flame_out = { flame_out,0,0,1024,540,-512,-270 };
SPR_DATA spr_pinto_l = { pinto_l,0,0,774,774,-774/2,-774/2 };
SPR_DATA spr_pinto_l_MF = { pinto_l,0,0,774,774,-(int)(774*0.92f)/2,-(int)(774*0.92f)/2,(int)(774*0.92f),(int)(774*0.92f) }; 

SPR_DATA spr_pinto_a2 = { pinto_a,0,0,128,128,-64,-64 };
SPR_DATA spr_exorcise_frame= { flame_out,0,32*18,32,64,0,0 };


void Frame::clear() {
	OBJ2D::clear();
	f_z = 0;
	lock_flg = false;
	sc_w = 0;
	sc_h = 0;
	angle = 0;
	axisx = 0;
	axisy = 0;
	exorcise = 0;
	f_timer = 0;
	exorciseDwon_flg = 0;
	exorciseDwon_timer = 0;
	move_flg = 0;
	argb = 0xFFFFFF00;	//霊力ゲージ点滅用
	old_exorcise = 0;	//霊力ゲージ点滅用
	flash_timer = 0;	//霊力ゲージ点滅用
	flash_flg = false;	//霊力ゲージ点滅用

	pinto_argb = 0xFFFFFFFF; //白
	multi_flg = false;
	out_argb = 0xFF000000; //黒
	count = 0;
	multifocus_timer = 0;

	D3DCOLOR light_argb = 0; //発光用

}
void Frame::Init() {
	clear();
}

void Frame::Update() {
	//if (pPlayer->fear_flg) {
	//	state = 3;
	//	lock_flg = true;
	//}

	switch (state)
	{
		// 初期化
	case INIT:
		pos = V2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
		sc_w = 0;
		sc_h = 0;
		size = V2(240/2,160/2);
		exorcise = EXORCISE_MAX;
		old_exorcise = EXORCISE_MAX;
		flash_timer = 0;
		flash_flg = false;

		pinto_argb = 0xFFFFFFFF; //白
		state = MOVE;
		break;
	case MOVE:
		// 
		f_move();
		exorcise_Update();


		//マルチフォーカス処理
		if (multifocus_flg == true && multi_flg == false) multi_flg = true;
		if (multifocus_flg == false && multi_flg == true) {
			pinto_argb = 0xFFFFFFFF; //falseなら白にする
			multi_flg = false;
		}

		if (multifocus_timer>0 && multi_flg == true) {
			//if (multifocus_timer % 12 == 0) { //15回に分けて(12で割った余りが0の時)
			//	//pinto_argb += 0x00001111; //徐々に白に
			//	if ( pinto_argb>=0xFFFFDDDD ) pinto_argb=0xFFFFFFFF;
			//	else pinto_argb += 0x00001111; //徐々に白に
			//}
			//pinto_argb = Frash_Color_pinto(multifocus_timer,30,pinto_argb,0xFFff5151,0xFFff7051,0xFFff7f51,0xFFff7051);
			if(60<=multifocus_timer) pinto_argb = Frash_Color_pinto(multifocus_timer,35,pinto_argb,0xFFff1111,0xFFff6666,0xFFffa0a0);
			else pinto_argb = Frash_Color_pinto(multifocus_timer,10,pinto_argb,0xFFff1111,0xFFff6666,0xFFffa0a0);
		}



		///////////////////////////////////////////////////////////////////////////////////
		//frame_out(黒枠)処理
		if (pPlayer->nodamage_timer > 150) { //プレイヤーがダメージを受けたら(30fの間)
			if ((pPlayer->nodamage_timer % 8)<  4) out_argb = 0xFF000000;	//点滅処理	黒色
			if ((pPlayer->nodamage_timer % 8) >= 4) out_argb = 0xFFFF0000;	//			赤色
		}
		else out_argb = 0xFF000000; //黒色
		///////////////////////////////////////////////////////////////////////////////////

		//pD_TEXT->set_Text(V2(600, 200), "PL_trg_t", lockPinto_trg == true, 0xFFFFFFFF);
		//pD_TEXT->set_Text(V2(600, 216), "PL_trg_f", lockPinto_trg == false, 0xFFFFFFFF);
		//pD_TEXT->set_Text(V2(600, 232), "PL_trg_02", lockPinto_trg == 0x02, 0xFFFFFFFF);
		//pD_TEXT->set_Text(V2(600, 248), "PL_trg_01", lockPinto_trg == 0x01, 0xFFFFFFFF);

		break;
	default:
		break;
	}

}

//発光関数
D3DCOLOR Light(D3DCOLOR color) {
	if ( color>=0x11FFFFFF ) color -= 0x03000000;
	else color = 0x00FFFFFF;
	return color;
}

D3DCOLOR Frame::Frash_Color_pinto(int timer,int num,D3DCOLOR argb,D3DCOLOR argb1,D3DCOLOR argb2,D3DCOLOR argb3) {
	int work = timer%num*4+1;
	     if ( work<=num*1 ) argb = argb1;
	else if ( work<=num*2 ) argb = argb2;
	else if ( work<=num*3 ) argb = argb3;
	else if ( work<=num*4 ) argb = argb2;
	return argb;
}


void Frame::Render() {

	spr_data::Render(V2((int)(pPlayer->pos.x + 30-2), (int)(pPlayer->pos.y-40-4)), &spr_exorcise_frame );

	//iexPolygon::Rect(160,30,exorcise*2,30,0,0xFFFFFF00,0); //霊力ゲージ描画(上にずらした)
	//iexPolygon::Rect(20,180,30,exorcise*2,0,0xFFFFFF00,0); //霊力ゲージ描画(縦 ※sceneMain変更)
	if (!pFrame->exorciseDwon_flg) {
		iexPolygon::Rect((int)(pPlayer->pos.x + 30), (int)((pPlayer->pos.y-40) + (50-exorcise/2)), 10, (int)(exorcise/2), 0, argb, 0); //霊力ゲージ描画(プレイヤー右上)
		//spr_data::Render(V2((int)(pPlayer->pos.x + 30),(int)(pPlayer->pos.y-40)), &spr_exorcise_frame); //霊力ゲージ枠
		//iexPolygon::Rect((int)(pPlayer->pos.x + 30), (int)((pPlayer->pos.y - 40) + (200 - exorcise * 2)), 10, (int)(exorcise / 2), 0, argb, 0); //霊力ゲージ描画(プレイヤー右上)
		//iexPolygon::Rect((int)pos.x, (int)pos.y, 1, 1, 0, 0xFFFF0000);
	}

	//if ( multifocus_flg ) {
	//	iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, light_argb, 0); //白
	//	light_argb = Light(light_argb);	//マルチフォーカスを使ったら発光
	//}
	//else light_argb = 0xCCFFFFFF;	//マルチフォーカスを使ったら発光

	spr_data::Render(V2((SCREEN_WIDTH / 2) +custom.ef_ofsX, (SCREEN_HEIGHT / 2)), &spr_pinto_l, pinto_argb, pFrame->Get_f_z() * 0.25f);
	if(0<multifocus_timer)spr_data::Render(V2((SCREEN_WIDTH / 2) +custom.ef_ofsX, (SCREEN_HEIGHT / 2)), &spr_pinto_l_MF, pinto_argb, pFrame->Get_f_z() * 0.25f);

	spr_data::Render(V2((SCREEN_WIDTH / 2) +custom.ef_ofsX, (SCREEN_HEIGHT / 2)), &spr_flame_out, out_argb, 0);
	if (pFrame->exorciseDwon_flg) {
		iexPolygon::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0x3F000000, 0);
	}

}

//======================================
// 霊力更新
//======================================
void Frame::R_Update() {
	//if (pPlayer->fear_flg) {
	//	state = 3;
	//	lock_flg = true;
	//}
	switch (state)
	{
	case INIT:
		pos = V2((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
		sc_w = 0;
		sc_h = 0;
		size = V2(240 / 2, 160 / 2);
		exorcise = EXORCISE_MAX;
		state = MOVE;
		break;
	case MOVE:
		//f_move();
		exorcise_Update();
		pintoSize = PINTOMODE_READY;

		break;
	default:
		break;
	}
}


void Frame::f_move() {

	float old_axisx = axisx;
	float old_axisy = axisy;
	axisx = (float)(KEY_Get(KEY_AXISX2));
	axisy = (float)(KEY_Get(KEY_AXISY2));
	if (!move_flg) {
		if (axisx < PINTO_SENSITIVE && axisx > -PINTO_SENSITIVE && axisy < PINTO_SENSITIVE && axisy > -PINTO_SENSITIVE) 
		{ 
			move_flg = false; 		
		}
		else move_flg = true;
	}
	else {
		//if (axisx < PINTO_SENSITIVE && axisx > -PINTO_SENSITIVE&& 
		//	axisy < PINTO_SENSITIVE && axisy > -PINTO_SENSITIVE) 
		//{ 
		
		if (axisy < PINTO_SENSITIVE && axisy > -PINTO_SENSITIVE)
		{

			move_flg = false;
			return;
		}

		f_spd = 0;
		if(PINTO_X_USE)
			f_spd += axisx * 0.001f;				//パッドを1～-1に変換
		if(PINTO_Y_USE)
			f_spd += axisy * 0.001f;				//パッドを1～-1に変換
		
		f_spd *= PINTO_ACT;
		f_z += f_spd;
		while(f_z < -PINTO_MAX)f_z += PINTO_MAX * 2;
		while(f_z > PINTO_MAX) f_z += -PINTO_MAX * 2;

		
	}

	if (multifocus_flg) {
		if (multifocus_timer > 0) {
			multifocus_timer--;
		}
		else
		{
			multifocus_flg = false;
		}
	}
	else pintoSize = PINTOMODE_DEFAULT;

	
}

//----------------------------------------------------------------------------------------------------
//　霊力データ更新
//----------------------------------------------------------------------------------------------------
void Frame::exorcise_Update() {

	// ダウン中ならダイマー更新
	// ダウンしていないならダウンチェック
	if (exorciseDwon_flg)
	{
		if (exorciseDwon_timer-- < 0) { //霊力ダウンタイマー
			exorciseDwon_timer = 0;
			exorciseDwon_flg = false;
			exorcise = EXORCISE_MAX;
			IEX_PlaySound(SE_RETURN, FALSE); //霊力復活のSE　
		}
	}
	else
	{
		axisy = (float)(KEY_Get(KEY_AXISY2));		// スティック情報取得
		if (0 > axisy) { axisy *= -1; }						// 負の値なら逆転
		if (axisy < 100)axisy = 0;							// スティック感度以下なら0
		axisy *= 0.001f;									// スティック情報 0～1に正規化 
		// 操作量計算
		float Ex = (PINTO_COST_S)*(axisy);//  
		exorcise -= Ex;
		
		//霊力ダウンチェック(効果:UI一時削除)
		if (0 >= exorcise) {						//霊力が0以下なら霊力ダウン
			if (exorcise)exorcise = 0;			//霊力初期化
			exorciseDwon_timer = PINTO_DOWN_TIME;	//ダウンタイム設定
			exorciseDwon_flg = true;				//霊力ダウンフラグ
			IEX_PlaySound(SE_LOSS, FALSE);			//霊力が0のSE
		}
		
		// 未操作時霊力自然回復
		if (!move_flg) {
			if (f_timer++ > EXORCISE_AUTOHEEL_TIME) {
				f_timer &= 0x0000FFFF;
				add_Exorcise(EXORCISE_AUTOHEEL);
			}
		}
		else {
			f_timer = 0;
		}
	}
	//******************************************************************************************************
	//霊力ゲージ点滅
	if (exorcise!=EXORCISE_MAX &&
		old_exorcise != (exorcise-EXORCISE_AUTOHEEL)) flash_flg = true; //霊力ゲージがMAXではなく,自然回復以外の変化があれば

	if (flash_flg == true) {
		if ( exorcise<(EXORCISE_MAX/3) && flash_timer++<60 ) {
			if ((flash_timer % 14) <  7) argb = 0xFFff765e;	//点滅処理	赤色
			if ((flash_timer % 14) >= 7) argb = 0xFFFFFF00;	//　		黄色
		}
		else if (flash_timer++<60) { //指定秒数の間
			if ((flash_timer % 14) <  7) argb = 0xFFFFFFFF;	//点滅処理	白色
			if ((flash_timer % 14) >= 7) argb = 0xFFFFFF00;	//　		黄色
		}
		else { //指定秒数経ったら
			argb = 0xFFFFFF00; //黄色
			flash_timer = 0;
			flash_flg = false;
		}
	}
	old_exorcise = exorcise; //変化前の霊力ゲージを保存
	//******************************************************************************************************

	//UIダウンタイマー更新
	//pD_TEXT->set_Text(V2(400, 260), "multiF_timer", multifocus_timer, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(400, 280), "multiF_flg", (int)multifocus_flg, 0xFFFFFFFF);
	//pD_TEXT->set_Text(V2(400, 240), "exorcise", exorcise,0xFFFFFF00);

}

//----------------------------------------------------------------------------------------------------
//  ピント取得,ピントサイズ取得
//----------------------------------------------------------------------------------------------------
float Frame::Get_f_z() {
	return f_z;
}
float Frame::getPintoSize() {
	return pintoSize;
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//  霊力回復
//----------------------------------------------------------------------------------------------------
void Frame::add_Exorcise(float add) {
	
	if (exorciseDwon_flg)return;
	exorcise += add;
	if (100 < exorcise)exorcise = EXORCISE_MAX;
	if ( 0 > exorcise)exorcise = 0;
}

//----------------------------------------------------------------------------------------------------
//  マルチフォーカス使用、設定
//----------------------------------------------------------------------------------------------------
void Frame::use_Multifocus(int power) {
	multifocus_timer = MALTIFOCUS_TIME;
	multifocus_flg = true;
	IEX_PlaySound(SE_MULCH_FIRE, FALSE); //マルチフォーカス使用時

	switch (power)
	{
	case 1:
		pintoSize = PINTOMODE_MULTIFOCUSLV1;
		break;
	case 2:
		pintoSize = PINTOMODE_MULTIFOCUSLV2;
		break;
	case 3:
		pintoSize = PINTOMODE_MULTIFOCUSLV3;
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------------------------------
//  ピントロック使用、設定
//----------------------------------------------------------------------------------------------------
void Frame::use_lockPinto() {
	if(!exorciseDwon_flg){
		f_timer &= 0;
		//exorcise -= USE_PINTOLOCK; //Enemy_Manager::damage_Calculationに移行
		lockPinto_trg = true;
	}
}

//----------------------------------------------------------------------------------------------------
//  ピントの差を計算
//----------------------------------------------------------------------------------------------------
float Frame::get_sz(float z) {
	float sz = 0;
	float ez = z;
	float fz = pFrame->Get_f_z();

	if (fz > ez) {
		sz = (fz) - (ez);
	}
	else {
		sz = (ez) - (fz);
	}
	return sz;
}
