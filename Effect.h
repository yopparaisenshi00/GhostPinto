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
	float f_work[16];
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
	TRG shift_multierror_trg;
	TRG shift_jast_trg;


	V2 get_shift_objects() {
		return shift_objects;
	}
	V2 get_shift_all() {
		return shift_all;
	}

	void add_all(V2);
	void add_object(V2);
	void add_multierror(V2);
	void add_jast(V2);

	void Init();
	void Update();
	void Render();
private:

	void Shift_Update();

	V2 shift_objects;
	V2 shift_all;
	V2 shift_multierror;
	V2 shift_jast;
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

void Ext(Effect*);				//敵消滅エフェクト
void CircleExt(Effect*);		//丸エフェクト
void CircleExt_lightB(Effect*);	//丸エフェクト_水色
void ParticleExt_c(Effect*);	//パーティクルエフェクト(散らばる●)
void ParticleExt_k(Effect*);	//パーティクルエフェクト(散らばるキラキラ)
void Lock(Effect*);				//Lockエフェクト
void Combo(Effect*);			//Comboエフェクト
void ComboText(Effect*);		//Comboテキストエフェクト
void dust(Effect*);				//塵エフェクト
void noAction(Effect*);			//スカエフェクト
void gameclear_aggre(Effect*);		//ゲームクリア時エフェクト_集合
void gameclear_kirakira(Effect*);	//ゲームクリア時エフェクトキラキラ
void gameclear_eight(Effect*);		//ゲームクリア時エフェクト8方向
void gameclear(Effect*);			//ゲームクリア時エフェクト
void Eval_agree(Effect* obj);			//評価用_集合
void Eval(Effect*);					//評価用テキスト
void Eval_combo_text(Effect*);		//評価用コンボテキスト
void Eval_jastpinto_text(Effect*);	//評価用ジャストピントテキスト
void Eval_combo(Effect*);			//評価用コンボ
void Eval_jastpinto(Effect*);		//評価用ジャストピント



#endif // !_EFFECT_H_
