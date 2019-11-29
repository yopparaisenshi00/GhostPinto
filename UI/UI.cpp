#include	"iextreme.h"			//	IEXライブラリ(全般)
#include	"system/system.h"		//	IEXライブラリ(システム)
#include	"Misc/Misc.h"				//	ゲーム汎用
#include	"Player/Player.h"				//	プレイヤー
#include	"Player/Frame.h"				//	ピント
#include	"Enemy/Enemy.h"				//　敵用
#include	"Map/MAP.h"					//  マップチップ
#include	"UI.h"


//SPR_DATA P_Status = { spr_data::UI7,0,0,128,128,0,0,160,160 }; //プレイヤー+緑リング
//SPR_DATA hp_gauge = { spr_data::UI1,0,0,128,128,-64,-64 }; //HP減少用黒リング
//SPR_DATA hp_gauge_frame = { spr_data::,0,0,128,128,-64,-64 }; //ゲージ枠

SPR_DATA P_Status[4] = {
	{ spr_data::UI7,0,128 * 3,128,128,0,0,160,160 }, //プレイヤーHP0
	{ spr_data::UI7,0,128 * 2,128,128,0,0,160,160 }, //プレイヤーHP1
	{ spr_data::UI7,0,128 * 1,128,128,0,0,160,160 }, //プレイヤーHP2
	{ spr_data::UI7,0,128 * 0,128,128,0,0,160,160 }  //プレイヤーHP3
};



UI::UI()
{
	custom.scaleMode = LEFTTOP;
	h.old_hp = 3;
	h.flg = false;
}

UI::~UI()
{

}


void UI::Init() {
	custom.scaleMode = LEFTTOP;
	h.old_hp = 3;
	h.flg = false;
}
void UI::Update() {

	HP_Update();

}

void UI::HP_Update() {

	if ( h.old_hp!=pPlayer->hp ) { //hpが減ったら
		h.custom.scaleX = h.custom.scaleY = 1.3f; //拡大
		h.flg = true;
	}
	else { //それ以外
		if ( h.custom.scaleX>1.0f ) h.custom.scaleX = h.custom.scaleY -= 0.03f;  //拡大されていたら縮小

		if ( h.flg==true ) {
			if ( h.custom.scaleX<1.0f ) {
				h.custom.scaleX = h.custom.scaleY = 1.15f; //さらに拡大
				h.flg = false;
			}
		}
	}

	h.old_hp = pPlayer->hp;

}

void UI::Render() {
	//spr_data::Render(V2(-2,-2),&P_Status); //プレイヤー+緑リング

	////HP減少用黒リング
	//spr_data::Render(V2(200,200), &hp_gauge, 0xFFFFFFFF, angle);
	//for ( int i = 0; i<pPlayer->hp; i++ ){

	//	//徐々に
	//	//if ( angle < 45-(hp*15) ) { //HPが3だったら0度
	//	//	angle++;
	//	//}

	//	//一瞬
	//	angle = 45-(pPlayer->hp*15); //HPが3だったら0度
	//}

	////spr_data::Render(V2(-2,-2),&hp_gauge_frame); //ゲージ枠



	//spr_data::Render(V2(-2, -2), &P_Status[pPlayer->hp]); //プレイヤーHP
	spr_data::Render(V2(-2, -2), &P_Status[pPlayer->hp],&h.custom,0xFFFFFFFF); //プレイヤーHP


}
