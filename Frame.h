#ifndef _FRAME_H_
#define _FRAME_H_
//ピント情報
#define FRAME_ACT (1.5f)		//加速度
#define FRAME_ACT_MAX (4.0f)	//最大加速度
#define FRAME_ACT_R (2.5f)	//加速度抵抗
#define FRAME_SIZE (774)


#define MALTIFOCUS_TIME (180)

#define DAMAGE_SIZE (90)
//フォーカス
//#define PINTO_ACT (0.55f)
//#define PINTO_ACT_MAX (4.0f)
//#define PINTO_ACT_R (0.4f)

#define PINTO_X_USE (false)//計算にX軸を使う
#define PINTO_Y_USE (true)//計算にY軸を使う

#define MLTFCS_MAXLV (3)
//#define PINTO_ACT (5.0f)
#define PINTO_ACT (2.5 * (f_spd * f_spd))

#define PINTO_POSY (480)
#define PINTO_MAX (90)

//----------------------------------------------------------------------
//		霊力
//----------------------------------------------------------------------
#define EXORCISE_MAX (100) //霊力最大値 
#define PINTO_COST_S (20.0f * 0.01666F) //ピント操作消費量/f
#define PINTO_DOWN_TIME (60*3) //UIダウンタイム
#define KILL_CURE (15 - (10 * (obj->sz / PINTOMODE_DEFAULT)))	//エネミー撃破時＿霊力回復量
#define EXORCISE_AUTOHEEL (5.5)	//自然回復
#define EXORCISE_AUTOHEEL_TIME (90)//自然回復開始時間
//----------------------------------------------------------------------



#define PINTO_SENSITIVE (100.0f) //感度 1000 ~ -1000

#define PINTOMODE_READY (-1)
#define PINTOMODE_DEFAULT (12)
#define PINTOMODE_MULTIFOCUSLV1 (24)
#define PINTOMODE_MULTIFOCUSLV2 (56)
#define PINTOMODE_MULTIFOCUSLV3 (90)


class Frame:public OBJ2D ,public Singleton<Frame>
{
public:
	//Frame();

	//~Frame();
	void Init();
	void Update();
	void Render();
	
	void SetMain();
	
	void R_Update();

	bool lock_flg;
	bool exorciseDwon_flg;
	bool multifocus_flg;
	TRG lockPinto_trg;
//-----------------------------------------------------
//
// ピント用変数、関数
//
//-----------------------------------------------------
	void f_move();
	void exorcise_Update();

	bool move_flg;//回転読み取り
	int exorciseDwon_timer;
	float Get_f_z();
	float getPintoSize();
	int multifocus_timer;
	void add_Exorcise(float);
	void use_Multifocus(int);
	void use_lockPinto();
private:
	float act;
	float exorcise;				//霊力数値　1 ～ 100
	float angle;
	float axisx;
	float axisy;
	float f_z;	//ピント値
	float f_spd;//ピント変更速度
	int f_timer;
	float pintoSize;
	D3DCOLOR pinto_argb;
	bool multi_flg;

	D3DCOLOR argb;		//色(霊力ゲージ点滅用)
	float old_exorcise; //比較用霊力数値(霊力ゲージ点滅用)
	int flash_timer;	//点滅timer(霊力ゲージ点滅用)
	bool flash_flg;
	D3DCOLOR out_argb;
	int count;


	//////////////////////////////////////
	//振動
	int vibTimer;
	int vibTimerMax;
	float vibWidth;
	float vibX, vibY;
	void Vib_Set(float width, int timer);
	void Vib_Update();
	//////////////////////////////////////

};


#endif // !_FRAME_H_

#define pFrame (Frame::getInstance())