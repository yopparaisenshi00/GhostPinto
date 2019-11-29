#include "iextreme.h"
#include "system\System.h"

#include "Game.h"
#include "Frame.h"
#include "Player.h"
#include "Effect.h"
#include "MAP.h"
#include "Enemy.h"
#include "Sound.h"
#include "sceneMain.h"

SPR_DATA p_spr_data[] = {
	{ spr_data::Player1,0,0,64,64,-32,-32 },
	{ spr_data::UI5,0,0,32,32,-16,-16 },//hp�A�C�R��
	{ spr_data::UI5,32,32,32,192,16,0 },//���|�Q�[�W�O��
	{ spr_data::UI5,96,32,32,0,16,192 },//���|�Q�[�W����
	{ spr_data::UI5,96,32,32,0,16,192 },//���|�Q�[�W����
};
SPR_DATA multi[] = { //�}���`�t�H�[�J�X�Q�[�W
	{ spr_data::UI3, 64 * 0, 32 * 17,	64,32,-32,-16 },
	{ spr_data::UI3, 64 * 1, 32 * 17,	64,32,-32,-16 },
	{ spr_data::UI3, 64 * 2, 32 * 17,	64,32,-32,-16 },
};


SPR_DATA p_wait[] = { //�ҋ@
	{ spr_data::Player1, 64 * 0, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 3, 64 * 0,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 4, 64 * 0,	64,64,-32,-32 },
};
SPR_DATA p_work_u[] = { //��ړ�
	{ spr_data::Player1, 64 * 0, 64 * 1,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 1,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 1,	64,64,-32,-32 },
};
SPR_DATA p_work_r[] = { //�E�ړ�
	{ spr_data::Player1, 64 * 0, 64 * 2,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 2,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 2,	64,64,-32,-32 },
};
SPR_DATA p_work_l[] = { //���ړ�
	{ spr_data::Player1, 64 * 0, 64 * 3,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 3,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 3,	64,64,-32,-32 },
};
SPR_DATA p_work_d[] = { //���ړ�
	{ spr_data::Player1, 64 * 0, 64 * 4,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 4,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 4,	64,64,-32,-32 },
};
SPR_DATA p_damage[] = { //�_���[�W
	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 0, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 10,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 10,	64,64,-32,-32 },
};
SPR_DATA p_over[] = { //�Q�[���I�[�o�[
	{ spr_data::Player1, 64 * 0, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 11,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 3, 64 * 11,	64,64,-32,-32 },
};
SPR_DATA p_clear[] = { //�Q�[���N���A
	{ spr_data::Player1, 64 * 0, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 3, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 0, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 1, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 2, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 3, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 4, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 5, 64 * 12,	64,64,-32,-32 },
	{ spr_data::Player1, 64 * 6, 64 * 12,	64,64,-32,-32 },
};



//Player::Player()
//{
//
//}

Player::~Player()
{

}

void Player::Init() {
	clear();
	sc_w = SCROLL_RIGHT;
	sc_h = SCREEN_HEIGHT / 2;
	hp = 0;
	mltfcs.clear();


	hp = P_HP_MAX;
	pos = D3DXVECTOR2(960, 512);
	size = D3DXVECTOR2(PLAYER_SIZE / 8, PLAYER_SIZE / 8);
	fear_flg = false;

 	g.pos = pos + D3DXVECTOR2(-30,0);

	state++;
	//fearstd = ((float)192 / (float)FERE_MAX);
}

void Player::Init(V2 _pos) {
	Init();
	pos = _pos;
}

void Player::Update() {
	move();//�ړ��A����؂�ւ���
	anime();//�A�j���[�V����
	judge();
}
void Player::R_Update() {
//	move();
	anime();//�A�j���[�V����
	judge();
}

//�����֐�
D3DCOLOR Player::Light(D3DCOLOR color) {
	if ( color>=0x11FFFFFF ) color -= 0x66000000;
	else color = 0x00FFFFFF;
	return color;
}

//�}���`�t�H�[�J�X����
void Player::mlt_Update() {
	//�Q�[�W�g��
	if ( mltfcs.old_lv<mltfcs.lv ) {
		g.custom.scaleMode = CENTER;
		g.custom.scaleX = g.custom.scaleY = 3.0f;
	}
	//�Q�[�W�k��
	else if ( mltfcs.old_lv==mltfcs.lv ) {
		g.custom.scaleMode = CENTER;
		g.custom.scaleX = g.custom.scaleY -= 0.2f;
		if ( g.custom.scaleX<=1.0f ) g.custom.scaleX = g.custom.scaleY = 1.0f;
	}
	//�g�����甭��
	if ( mltfcs.old_lv!=mltfcs.lv ) g.argb = 0xFFFFFFFF;	
	if ( g.argb>=0x11FFFFFF ) g.argb -= 0x11000000;
	else g.argb = 0x00FFFFFF;

	mltfcs.old_lv = mltfcs.lv;
}

void Player::move() {
	int axisx = KEY_Get(KEY_AXISX);



	attr = pMAP->getAttr(pos.x, pos.y - height / 2);	// �̂̒��S�t�߂̒n�`�����̎擾

	switch (state)
	{
	case 0:
		hp = 3;
		size = D3DXVECTOR2(PLAYER_SIZE / 8, PLAYER_SIZE / 8);
		fear_flg = false;

		state++;
	case 1:
		//-----------------------------------------------------------
		//  �ړ�
		//----------------------------------------------------------
		if ( hp>0 && (pScore->getKill_num()<CLEAR_KILLNUM)/* || timer <= 0*/ ) {
			//----------------------------
			//Y��
			//----------------------------
			Y_move();

			//----------------------------
			//  X��
			//----------------------------
			X_move();
		}

		//-----------------------------------------------------------
		//  �}���`�t�H�[�J�X
		//-----------------------------------------------------------
		if (KEY_Get(MULTIFOCUS_KEY) == 3 && (mltfcs.lv==3)) {
			pFrame->use_Multifocus(mltfcs.lv);
			mltfcs.lv = 0;
			pEffect_Manager->searchSet(pos, V2(6.0f,0.3f), Multifocus); //MF�g�p���G�t�F�N�g
			pEffect_Manager->searchSet(pos, V2(-8.0f,0.35f), Multifocus); //MF�g�p���G�t�F�N�g
			pEffect_Manager->searchSet(pos, V2(4.0f,0.75f), Multifocus); //MF�g�p���G�t�F�N�g
			pEffect_Manager->searchSet(pos, V2(-6.0f,0.8f), Multifocus); //MF�g�p���G�t�F�N�g
			//mltfcs.add_point(0);
		}
		else if ( KEY_Get(MULTIFOCUS_KEY)==3 && (mltfcs.lv<3) ) {
			pEffect_Manager->searchSet(V2(12, 6), V2(8, 3), Shake); //�U��
		}

		mlt_Update();
		//-----------------------------------------------------------


		//-----------------------------------------------------------
		//  �s���g���b�N
		//-----------------------------------------------------------
		if (KEY_Get(PINTOLOCK_KEY) == 3) {
			pFrame->use_lockPinto();
			IEX_PlaySound(SE_LOCK, FALSE);	//LOCK��SE
			pEffect_Manager->searchSet(pos, V2(-6.0f,0.8f), noAction); //
		}
		//-----------------------------------------------------------
		//pD_TEXT->set_Text(pos + V2(40,40),"PintoSize",pFrame->getPintoSize(),0xFFFFFFFF);
		

		break;
	case 3:

		break;
	default:
		break;
	}
	//-------------------------------------------
	//���
	//-------------------------------------------


	//-------------------------------------------

	//-------------------------------------------
	//��Ԉُ�A�_���[�W���G��
	//
	//
	if (s.nodamage) {
		nodamage_timer--;
		if (nodamage_timer < 0) {
			s.nodamage = false;
			s.old_nodamage = false;
		}
	}
	//-------------------------------------------
}


void Player::anime() {
	anime_timer++;
	if (anime_timer > 6) {
		anime_no++;
		anime_timer = 0;
	}

	//�W�F�b�g�G�t�F�N�g
	if (jet_eff_timer++>10) {
		pEffect_Manager->searchSet(V2(pos.x, pos.y + 25), V2(0, 0), Jet);
		jet_eff_timer = 0;
	}

	//�v���C���[����G�t�F�N�g
	if (spd.x != 0.0f || spd.y != 0.0f) { //�v���C���[���ړ����Ă���
		if (p_eff_timer++>8) {
			pEffect_Manager->searchSet(V2(pos.x - rand() % 20, pos.y - rand() % 20), V2(0, 0), P_particle);
			pEffect_Manager->searchSet(V2(pos.x - rand() % 20, pos.y + rand() % 20), V2(0, 0), P_particle);
			pEffect_Manager->searchSet(V2(pos.x + rand() % 20, pos.y - rand() % 20), V2(0, 0), P_particle);
			pEffect_Manager->searchSet(V2(pos.x + rand() % 20, pos.y + rand() % 20), V2(0, 0), P_particle);
			p_eff_timer = 0;
		}
	}

	//�Q�[���I�[�o�[
	if (hp <= 0) {
		//hp = 0;
		if ( damage_se_flg==false ) {
			IEX_PlaySound(SE_DAMAGE,FALSE); //�_���[�W
			damage_se_flg = true;
		}
		if (anime_no >=4) anime_no = 0;
		data = &p_over[anime_no];
	}
	//�Q�[���N���A
	else if ((pScore->getKill_num() >= CLEAR_KILLNUM)/* || timer == 0*/) {
		if ( (anime_no==9)&&(anime_timer==1) ) {
			pEffect_Manager->searchSet(pos, V2(5, 5), gameclear_aggre);
			for (int i = 0; i<5; i++) pEffect_Manager->searchSet(pos, V2((float)(rand()%8-4),(float)(rand()%8-4)), ParticleExt_k);	//�p�[�e�B�N���G�t�F�N�g�L���L��
		}
		if ( anime_no>=10 )anime_no = 10;
		data = &p_clear[anime_no];
	}

	//�_���[�W
	else if (s.old_nodamage == false && s.nodamage == true) {
		if ( damage_se_flg==false ) {
			IEX_PlaySound(SE_DAMAGE,FALSE); //�_���[�W
			damage_se_flg = true;
		}
		//pEffect_Manager->searchSet(V2(pos.x,pos.y+(rand()%20-10)),V2(0,0),P_damage);
		//pEffect_Manager->searchSet(V2(pos.x,pos.y+(rand()%20-10)),V2(0,0),P_damage);
		//pEffect_Manager->searchSet(V2(pos.x,pos.y+(rand()%20-10)),V2(0,0),P_damage);
		//pEffect_Manager->searchSet(V2(pos.x,pos.y+(rand()%20-10)),V2(0,0),P_damage);
		pEffect_Manager->searchSet(V2(6, 2), V2(3, 4), Shake); //�_���[�W�U��

		if (reflect) {
			if ( anime_no>=5 ) {
				s.old_nodamage = true;
				anime_no = 0;
				damage_se_flg = false;
			}
			data = &p_damage[anime_no]; //���_���[�W
		}
		else {
			if ( anime_no>=5 ) {
				s.old_nodamage = true;
				anime_no = 0;
				damage_se_flg = false;
			}
			data = &p_damage[anime_no]; //�E�_���[�W
		}
	}

	//�ҋ@
	else if ((spd.x == 0) && (spd.y == 0)) {
		if (reflect) {
			if (anime_no >=5)anime_no = 0;
			data = &p_wait[anime_no]; //�ҋ@
		}
		else {
			if (anime_no >=5)anime_no = 0;
			data = &p_wait[anime_no]; //�ҋ@
		}
	}

	//��ړ�		     ��spd.x����Βl2����
	else if ((spd.y != 0) && (spd.x>-2 && spd.x<2)) {
		if (spd.y<0) {
			if (anime_no >=3)anime_no = 0;
			data = &p_work_u[anime_no]; //��ړ�
		}
		else {
			if (anime_no >=3)anime_no = 0;
			data = &p_work_d[anime_no]; //���ړ�
		}
	}

	//���ړ�,�ȂȂ߈ړ�
	else {
		if (reflect) {
			if (anime_no >=3)anime_no = 0;
			data = &p_work_l[anime_no]; //���ړ�
		}
		else {
			if (anime_no >=3)anime_no = 0;
			data = &p_work_r[anime_no]; //�E�ړ�
		}
	}



	//�_���[�W���_��
	if (s.nodamage && hp>0) {
		if (nodamage_timer & 0x02) {
			data = nullptr;
		}
	}

}

void Player::Render() {
	if (data)spr_data::Render(pos, data);
}
void Player::UIRender() {
	//�}���`�t�H�[�J�X�`��------------------------------------------------------
	g.pos = D3DXVECTOR2(960-30, 420);
	for (int i = 0; i < 3; i++)
	{
		spr_data::Render(V2(g.pos.x+custom.ef_ofsX, g.pos.y), &multi[0]); //�}���`�t�H�[�J�X��
		g.pos += V2(0, 45);
	}
	g.pos = D3DXVECTOR2(960-30, 420);
	for (int i = 0; i < mltfcs.lv; i++)
	{
		spr_data::Render(V2(g.pos.x+custom.ef_ofsX,g.pos.y),&multi[2],&g.custom,0xFFFFFFFF); //�}���`�t�H�[�J�X��
		spr_data::Render(V2(g.pos.x+custom.ef_ofsX,g.pos.y),&multi[1],&g.custom,g.argb); //��
		g.pos += V2(0, 45);
	}
	//---------------------------------------------------------------------------

	//iexPolygon::Rect((int)pos.x, (int)pos.y, 1, 1, 0, 0xFFFF0000);

	//line_rect(pos, V2(size.x * custom.scaleX, size.y * custom.scaleY), 0xFFFFFFFF, custom.scaleMode);
}

void Player::judge() {//
	if (s.nodamage)return;
	Enemy** enemy = pEnemy_Manager->enemy;
	for (int i = 0; i < ENEMY_MAX; i++) {
		//���݃`�F�b�N & �o�����㓖���蔻��Ȃ�
		//									   enemy[i]->state == APPEARANCE
		if (!enemy[i] || !enemy[i]->init_fg ||(enemy[i]->state == 2))continue;
		//���菈��
		if ((enemy[i]->noHit_flg) && Judge(this, enemy[i])) {
			suffer_damage();
			Recoil(enemy[i]->pos, enemy[i]->spd); //�_���[�W���̔���
			break;
		}
	}
}

void Player::clear() {
	OBJ2D::clear();
	nodamage_timer = 0;
	anime_no = 0;
	anime_timer = 0;
	dx = 0;
	dy = 0;
	attr = 0;
	act = 0;

	jimen_flg = false;
	fear_flg = false;
	damage_se_flg = false;

	jet_eff_timer = 0;
	p_eff_timer = 0;

	g.pos = D3DXVECTOR2(960-30, 420);
}

void Player::SetMain() {
	pMAP->SetCenter((OBJ2D*)(this));
}

void Player::suffer_damage() {
	hp -= 1;
	if ( hp<0 ) hp = 0;
	s.nodamage = true;
	nodamage_timer = NODAMEGE_TIME;
}

void Player::Recoil(V2 enemy_pos, V2 enemy_spd) {
	V2 dist = enemy_pos - pos; //��Ԃ̋���
	D3DXVec2Normalize(&dist, &dist);

	//x�ړ����Ă���
	if (spd.x<-1 || spd.x>1) spd.x = -dist.x*10.0f;
	//y�ړ����Ă���
	if (spd.y<-1 || spd.y>1) spd.y = -dist.y*10.0f;
	//�ړ����ĂȂ���.enemyspd��0�Ȃ�
	if (spd == enemy_spd == 0.0f) spd = -dist*10.0f;
	//enemyspd�ɔ�Ⴕ������
	if (enemy_spd != 0)	spd -= enemy_spd*1.2f;
}

void Player::Y_move() {

	jimen_flg = false;			// ���n���Ă��Ȃ�
	old_y = pos.y;				// �X�V�O��Y���W��ۑ�
	//spd.y += PLAYER_AY;		// �d�͉����x�̉��Z
	Get_spdy();
	pos.y += spd.y;				// ����
	dy = pos.y - old_y;			// ���ۂɓ������h�b�g��																// ���������Ƃ�
	//if (dy > 0) {
	//	// MAP�Ƃ̂�����`�F�b�N
	//	if (pMAP->isFloor(pos.x, pos.y + (PLAYER_HEIGHT / 2), 0)) {	// �n�ʂɂ߂荞�񂾂Ƃ�
	//		bg_crt_down(this);								// �n�ʂ��肬��̏ꏊ�ɂ���
	//		jimen_flg = true;								// ���n���
	//	}
	//}

}

//�p�b�h��񂩂瑬�x���v�Z
inline void Player::Get_spdy() {
	int axisy = KEY_Get(KEY_AXISY);//�p�b�h���擾

	if (axisy > 100.0f || axisy < -100.0f) {//�p�b�h�����x�ȏ�
		float spdy;
		spdy = (float)axisy;
		spdy *= 0.001f;					//�p�b�h��1�`-1�ɕϊ�
		spdy += get_Resist(attr, spdy);	// �R�́i��R�j�̉��Z
		float max = spdy * 5;			//�ō����x�l�ݒ�


		if (spdy > 0) {
			if (spd.y >= max) {			//�ō����x�`�F�b�N
				spd.y = max;
			}
			else {
				spd.y += spdy * 0.5f;	//���x�ɉ����x��ǉ�
			}
		}
		if (spdy < 0) {
			if (spd.y <= max) {			//�ō����x�`�F�b�N
				spd.y = max;
			}
			else {
				spd.y += spdy * 0.5f;	//���x�ɉ����x��ǉ�
			}
		}

	}
	else {
		if (pos.y != 0) {
			if (0.01 > spd.y && -0.01< spd.y) {
				spd.y = 0;
			}
			else spd.y -= spd.y * 0.07f;
		}
	}

}

void Player::X_move() {
	jimen_flg = false;										// ���n���Ă��Ȃ�
	old_x = pos.x;											// �X�V�O��Y���W��ۑ�
															//spd.y += PLAYER_AY;										// �d�͉����x�̉��Z
	Get_spdx();
	pos.x += spd.x;											// ����
	dx = pos.x - old_x;										// ���ۂɓ������h�b�g��																// ���������Ƃ�
}

inline void Player::Get_spdx() {
	int axisx = KEY_Get(KEY_AXISX);
	if (axisx > 100.0f || axisx < -100.0f) {
		if (axisx < 0) { sc_w = SCROLL_LEFT; reflect = true; }
		if (axisx > 0) { sc_w = SCROLL_RIGHT; reflect = false; }

		float spdx;
		spdx = (float)axisx;
		spdx *= 0.001f;	//1�ɐ��K��

		spdx += get_Resist(attr, spdx);						// �R�́i��R�j�̉��Z
		float max = spdx * PLAYER_SPDX_MAX;
		if (spdx > 0) {
			if (spd.x >= max) {
				spd.x = max;
			}
			else {
				spd.x += spdx * PLAYER_AX;
			}
		}
		if (spdx < 0) {
			if (spd.x <= max) {
				spd.x = max;
			}
			else {
				spd.x += spdx * PLAYER_AX;
			}
		}

	}
	else {
		if (pos.x != 0) {
			if (0.01 > spd.x && -0.01< spd.x) {
				spd.x = 0;
			}
			else spd.x -= spd.x * PLAYER_RX;
		}
	}

	if (PLAYER_LIMIT_LEFT > pos.x) { pos.x = PLAYER_LIMIT_LEFT; }
	if (PLAYER_LIMIT_RIGHT < pos.x) { pos.x = PLAYER_LIMIT_RIGHT; }

	if (PLAYER_LIMIT_UP > pos.y) { pos.y = PLAYER_LIMIT_UP; }
	if (PLAYER_LIMIT_DOWN < pos.y) { pos.y = PLAYER_LIMIT_DOWN; }

}



//�{�c
//void fear() {
////���|�x
////
//float distancex = (pFrame->pos.x - pos.x);
//float distancey = (pFrame->pos.y - pos.y);

//if ((distancex > FRAME_SIZE_W) || (distancex < -FRAME_SIZE_W)||(distancey > FRAME_SIZE_H) || (distancey  < -FRAME_SIZE_H)){
//		fear += FERE_UP;
//}
//else { 
//	if (fear > 0)fear -= FERE_CURE;
//}
//
//if (fear >= FEAR_MAX) {
//	fear = FEAR_MAX;
//	fear_flg = true;
//	pFrame->SetMain();
//}
//else
//{
//	if (fear_flg)fear_flg = false;
//}
//float ofs = fear * fearstd;
//p_spr_data[3].dy = 0 + (ofs);
//p_spr_data[3].ofsy = (192) - (ofs);
//-------------------------------------------
//}


void MLT_FOCUS::add_point(int add) {
	point += add;
	while (point > USE_POINT) {
		if (lv < MLTFCS_MAX_LV) {
			lv++;
			IEX_PlaySound(SE_MULCH_STOCK, FALSE); //�}���`�t�H�[�J�X�����܂�����
			point -= USE_POINT;
		}
		else point = USE_POINT;

	}
	if (point < 0) {
		point = 0;
	}
}