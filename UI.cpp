#include	"iextreme.h"			//	IEX���C�u����(�S��)
#include	"system/system.h"		//	IEX���C�u����(�V�X�e��)
#include	"Game.h"				//	�Q�[���ėp
#include	"Player.h"				//	�v���C���[
#include	"Frame.h"				//	�s���g
#include	"Enemy.h"				//�@�G�p
#include	"MAP.h"					//  �}�b�v�`�b�v
#include	"UI.h"


//SPR_DATA P_Status = { spr_data::UI7,0,0,128,128,0,0,160,160 }; //�v���C���[+�΃����O
//SPR_DATA hp_gauge = { spr_data::UI1,0,0,128,128,-64,-64 }; //HP�����p�������O
//SPR_DATA hp_gauge_frame = { spr_data::,0,0,128,128,-64,-64 }; //�Q�[�W�g

SPR_DATA P_Status[4] = {
	{ spr_data::UI7,0,128 * 3,128,128,0,0,160,160 }, //�v���C���[HP0
	{ spr_data::UI7,0,128 * 2,128,128,0,0,160,160 }, //�v���C���[HP1
	{ spr_data::UI7,0,128 * 1,128,128,0,0,160,160 }, //�v���C���[HP2
	{ spr_data::UI7,0,128 * 0,128,128,0,0,160,160 }  //�v���C���[HP3
};



UI::UI()
{

}

UI::~UI()
{

}


void UI::Init() {

}
void UI::Update() {

}
void UI::Render() {
	//spr_data::Render(V2(-2,-2),&P_Status); //�v���C���[+�΃����O

	////HP�����p�������O
	//spr_data::Render(V2(200,200), &hp_gauge, 0xFFFFFFFF, angle);
	//for ( int i = 0; i<pPlayer->hp; i++ ){

	//	//���X��
	//	//if ( angle < 45-(hp*15) ) { //HP��3��������0�x
	//	//	angle++;
	//	//}

	//	//��u
	//	angle = 45-(pPlayer->hp*15); //HP��3��������0�x
	//}

	////spr_data::Render(V2(-2,-2),&hp_gauge_frame); //�Q�[�W�g



	spr_data::Render(V2(-2, -2), &P_Status[pPlayer->hp]); //�v���C���[HP


}
