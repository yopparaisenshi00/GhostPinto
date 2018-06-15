#ifndef _PLAYER_H_
#define _PLAYER_H_
//X
#define PLAYER_SPDX_MAX			(6)		//X方向移動最高速度
#define PLAYER_AX			(1.0f)		// プレイヤーＸ方向加速度（ノーマル、ジャンプ中）
#define PLAYER_AX1			(0.05f)		// プレイヤーＸ方向加速度（氷上）
#define PLAYER_RX			(0.05f)	// 抵抗

//Y
#define PLAYER_DY			(8)		// Y方向移動最高速度
#define PLAYER_DY2			(3)		// Yスティック弱倒し時

#define PLAYER_AY			(2.5f)	// Ｙ方向加速度
#define PLAYER_AY2			(0.5f)	// Yスティック弱倒し時
#define PLAYER_RY			(0.05)	// 抵抗

#define PLAYER_LIMIT_LEFT	(  0+100)		// プレイヤー移動範囲（左端）
#define PLAYER_LIMIT_RIGHT	(SCREEN_WIDTH -100)		// プレイヤー移動範囲（右端）

#define PLAYER_LIMIT_UP		(  0+40)		// プレイヤー移動範囲（左端）
#define PLAYER_LIMIT_DOWN	(SCREEN_HEIGHT -40)		// プレイヤー移動範囲（右端）

#define PLAYER_WIDTH		(64)			// プレイヤーの横幅÷2
#define PLAYER_SIZE			(32)
#define PLAYER_HEIGHT		(64)				// プレイヤーの高さ（身長）

//#define SCROLL_PLAYER_W		(32)				// スクロール開始座標（左）
#define SCROLL_PLAYER_H		(64)				// スクロール開始座標（右）

#define SCROLL_LEFT (720 - 240)	//左スクロール中心
#define SCROLL_RIGHT (240+240)	//右スクロール中心

#define MULTIFOCUS_KEY KEY_L1 //マルチフォーカスキー設定
#define PINTOLOCK_KEY  KEY_R1 //ピントロックキー設定

//#define SCROLL_LEFT (960/1)
//#define SCROLL_RIGHT (960/3)



//#define FARE_MAX (900)//恐怖度最大値
//#define FERE_UP (1)	//恐怖度上昇速度
//#define FERE_CURE (5) //恐怖度回復速度

#define NODAMEGE_TIME (180)
#define HP_X (100)
#define HP_Y (40)


//------------------------------------------------
//　マルチフォーカス
//------------------------------------------------
#define POINT_MAX (30)
#define USE_POINT (10)
#define MLTFCS_MAX_LV (3)
#define	INIT_MLTFCS (10)
struct MLT_FOCUS {
	
	int point;
	int lv;
	void add_point(int);
	SPR_DATA* data;
	spr_data::CUSTOM custom;

	void clear() {
		point = 0;
		lv = 0;
	}
};


class Player:public OBJ2D, public Singleton<Player>
{
public:

	struct Status {
		bool nodamage;
		bool old_nodamage;
		bool ground;
	};
	
	~Player();

	int hp;			//体力

	Status s;

	bool	jimen_flg;			// true:地面に着地している、false：着地していない
	bool	fear_flg;			// true:恐怖最大、false：それ以外
	
	float	old_x, old_y;		// 更新前のX座標、Y座標
	float	dx, dy;				// 実際に動いたドット数
	int		attr;				// 体の中心付近の地形属性

	float	x_move;				// しかけによる移動量

	float act;
	int anime_timer;
	int nodamage_timer;
	
	MLT_FOCUS mltfcs;			//マルチフォーカス

	float fearstd;				//ゲージ用規格合わせ
	
	int jet_eff_timer;			//
	int p_eff_timer;			//

	int old_mlt;

	struct gage { //ゲージ用
		V2 pos;
		D3DCOLOR argb;
		spr_data::CUSTOM custom;
	};
	gage g;

	virtual void clear();		// メンバ変数のクリア
	
	virtual void Init();
	virtual void Update();		// 移動
	virtual void Render();		// 描画
	void UIRender();
	static const int height = 32;static const int widht = 32;
	void SetMain();
	void judge();
	void suffer_damage();
	void Recoil(V2 enemy_pos, V2 enemy_spd); //ダメージ時の反動
	D3DCOLOR Light(D3DCOLOR color);
	void mlt_Update();

	//void Deat_Enemy() {
	//	
	//}
	//void Deat_Enemy(float heal_num) {

	//}
protected:
	//Player();

	void move();
	void Y_move();
	inline void Get_spdy();

	void X_move();
	inline void Get_spdx();

	void anime();
	
public:

	void Player::R_Update();//ロック

};

#define pPlayer (Player::getInstance())

//
//class P_Manager 
//{
//public:
//	P_Manager();
//	~P_Manager();
//
//private:
//
//};
//
//P_Manager::P_Manager()
//{
//
//}
//
//P_Manager::~P_Manager()
//{
//
//}
#endif // !_PLAYER_H_
