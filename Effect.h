#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_


//#define EFF_MAX 256
#define EFF_MAX 512
class Effect : public OBJ2DEX
{
public:
	Effect();
	~Effect();
	//bool delete_flg;

	bool init_fg;
	int alpha;
	int i_work[16];
	void(*move)(Effect*);
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void clear();



	//void update();
	//void render();
protected:

};








class Effect_Manager :public Singleton<Effect_Manager>
{
public:
	Effect* effect[EFF_MAX];
	void searchSet(V2 pos = V2(0, 0), V2 spd = V2(0, 0), void(*move)(Effect*) = nullptr, OBJ2D* parent = nullptr);
	//bool shift_objects_flg;
	//bool shift_all_flg;
	TRG shift_objects_trg;
	TRG shift_all_trg;

	V2 get_shift_objects() {
		return shift_objects;
	}
	V2 get_shift_all() {
		return shift_all;
	}

	void add_all(V2);
	void add_object(V2);

	void Init();
	void Update();
	void Render();
private:

	void Shift_Update();

	V2 shift_objects;
	V2 shift_all;
};


#define pEffect_Manager (Effect_Manager::getInstance())



void framerotate(Effect*);
void Extinction(Effect*);
void kemuri(Effect*);
void TeleportExt(Effect*);
void Just_pinto(Effect *obj);
void pinto_lock(Effect *obj);

void Jet(Effect *obj);
void P_particle(Effect *obj);
void P_damage(Effect *obj);
void Multifocus(Effect *obj);
void fade_In(Effect* obj);
void fade_Out(Effect* obj);
void Shake(Effect* obj);

void Ext(Effect*);				//�G���ŃG�t�F�N�g
void CircleExt(Effect*);		//�ۃG�t�F�N�g
void CircleExt_lightB(Effect*);	//�ۃG�t�F�N�g_���F
void ParticleExt_c(Effect*);	//�p�[�e�B�N���G�t�F�N�g(�U��΂遜)
void ParticleExt_k(Effect*);	//�p�[�e�B�N���G�t�F�N�g(�U��΂�L���L��)
void Lock(Effect*);				//Lock�G�t�F�N�g
void Combo(Effect*);			//Combo�G�t�F�N�g
void ComboText(Effect*);		//Combo�e�L�X�g�G�t�F�N�g
void dust(Effect*);				//�o�G�t�F�N�g
void noAction(Effect*);			//�X�J�G�t�F�N�g
void gameclear(Effect*);		//�Q�[���N���A���G�t�F�N�g
void gameclear_a(Effect*);		//�Q�[���N���A���G�t�F�N�g
void gameclear_aggre(Effect*);	//�Q�[���N���A���G�t�F�N�g_�W��

#endif // !_EFFECT_H_
