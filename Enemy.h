#ifndef _ENEMY_H_
#define _ENEMY_H_

#define ENEMY_MAX (256)
#define DAMAGE_MAX (700) //iran

//エネミーＨＰ群
#define ENEMY_HP_A (700)//漂う奴
#define ENEMY_HP_B (600)//普通の奴
#define ENEMY_HP_C (700)//ワープする奴
#define ENEMY_HP_D (700)//Z値移動する奴
#define ENEMY_HP_E (1300)//でかい奴
#define ENEMY_HP_F (900)//トンボ


#define DAMAGE_LINE (3.6) 
#ifndef PINTO_MAX

	#define PINTO_MAX (90)

#endif // !PINTO_MAX
#define INIT_ANGLE		(180.0f*D3DX_PI/180.0f)		//最初の角度(ラジアン)

#define DRAGIN_SCALE (192)//ジャストピント巻き込みサイズ

#define C_scale		1.0f		//子の大きさ
#define N_scale		1.5f		//通常敵の大きさ
#define B_scale		2.5f		//デカイ敵の大きさ

#define rand_PINTO		(10000)//敵のZ値ランダム
//#define rand_PINTO		((rand()%(PINTO_MAX*2)) -PINTO_MAX)	//敵のZ値ランダム
#define DAMAGE (10)
#define JUSTPINTO_SIZE (2)

//enum {
//	Init,//初期設定
//	Main,//基本行動
//	Special1,//特技
//	Special2,//特技
//	Dead,//死亡演出
//	Clear,//初期化
//};
struct STAGE_DATA {
	int appearTime;
	void(*moveType)(Enemy*);
	V2 pos, speed, speedAcc, speedMax;
	int z;

	STAGE_DATA(
		int _appearTime,			//出現time
		void(*_moveType)(Enemy*),	//関数
		V2 _pos,					//座標
		V2 _speed,					//速度
		V2 _speedAcc,				//加速度
		V2 _speedMax,				//最大速度
		int _z							//Z値
		)
		:appearTime(_appearTime),
		moveType(_moveType),
		pos(_pos),
		speed(_speed),
		speedAcc(_speedAcc),
		speedMax(_speedMax),
		z(_z) {};



};

//敵の識別
enum {
	yellow,
	green,
	pink,
	blue,
	white,
	kari,
};


class Enemy_Kill :public OBJ2D, public Singleton<Enemy_Kill>
{
private:
	//初期化
	void clear() {
		OBJ2D::clear();

		kill_num_yellow = 0;
		kill_num_green = 0;
		kill_num_pink = 0;
		kill_num_blue = 0;
		kill_num_white = 0;
		kill_num_kari = 0;
	}

public:
	//----------------------------------------------
	//敵ごとのkill数用変数
	//----------------------------------------------
	int kill_num_yellow;
	int kill_num_green;
	int kill_num_pink;
	int kill_num_blue;
	int kill_num_white;
	int kill_num_kari;

	//初期設定
	void Init() {
		clear();
	}

	//更新
	void Update() {}

	//敵ごとのkill数を返す
	int getKill_num_Each(int state) {
		switch (state) {
		case yellow: return kill_num_yellow; break;
		case green:	 return kill_num_green;  break;
		case pink:	 return kill_num_pink;	 break;
		case blue:	 return kill_num_blue;	 break;
		case white:	 return kill_num_white;  break;
		case kari:	 return kill_num_kari;	 break;
		default:	 return 0;				 break;
		}
	}
};
#define pEnemy_Kill (Enemy_Kill::getInstance())


class Enemy:public OBJ2DEX
{
public:
	Enemy();
	~Enemy();
	//----------------------------------------------
	//基本情報変数
	//----------------------------------------------
	Vector2 spdAcc;		// 加速度
	Vector2 spdMax;		// 最大速度

	int damage;		//撃退ゲージ
	int damageMAX;	//撃退ゲージMAX
	int alpha ;
	int count;
	int score; //スコア

	float z;		//ピント座標
	struct ui {
		D3DCOLOR argb; //UI_ARGB
		float angle;//UI_angle
		spr_data::CUSTOM custom;
	};
	ui u;

	bool damageflg; //撃退ゲージフラグ
	bool rangeflg;	//範囲判定フラグ
	bool init_fg;
	bool z_flg;
	bool noHit_flg;
	bool zlock_flg;

	int Dot_timer;
	int Dot_alpha;
	D3DCOLOR Dot_argb;

	SPR_DATA**	Anime_Box;
	int flash_timer;

	float f_work[16]; //フリー
	
	void(*move)(Enemy*);//行動関数ポインタ
	//---------------------------------------------

	//----------------------------------------------
	//******
	//----------------------------------------------
	
	float dx, dy;
	float dist;
	float XCENTER;  //回転の中心
	float YCENTER;  //回転の中心
	float ANGLE;
	float ANGLEspd; //回転速度
	float RADIUS;   //半径
	float sz;		//フレームとのピント差
	//関数
	//OBJ継承関数---------------------------------------
	virtual void Init(); //
	virtual void Update();

	virtual void Render();//描画処理
	virtual void UIRender();//UI描画処理

	virtual void clear();
	//---------------------------------------------------
	// 
	//-----------------------------------------------------
	virtual void UIUpdate();//UI描画更新
	virtual void DotLine();//破線描画


	virtual void animetion() {
		anime_timer++;
		if (anime_timer > 3) {
			//anime_no++;
			aframe++;
			anime_timer = 0;
		}


		if (animeData)
		{
			//aframe++;
			if (aframe > animeData[animeNO].frameNum)
			{
				aframe = 0;
				animeNO++;
				if (animeData[animeNO].no < 0)
				{
					animeNO = 0;
				}
			}
			data = &animeData[animeNO];
		}
	}
	//-----------------------------------------------------

protected:
	
};


class Enemy_Manager:public Singleton<Enemy_Manager>
{
public:
	Enemy* enemy[ENEMY_MAX];
	int timer;


	void searchSet(V2 pos = V2(0, 0), V2 spd = V2(0, 0), void(*move)(Enemy*) = nullptr,float _z = 0,Enemy* parent = NULL);
	void searchSet(void(*_move)(Enemy*), V2 &_pos = Vector2(0, 0), V2 &_spd = Vector2(0, 0), V2 &_spdAcc = Vector2(0, 0),
		V2 &_spdMax = Vector2(0, 0), float _z = 0) {
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i] && enemy[i]->init_fg) {
				continue;
			}
			if (!enemy[i])enemy[i] = new Enemy;
			enemy[i]->move = _move;
			enemy[i]->pos = _pos;
			enemy[i]->spd = _spd;
			enemy[i]->spdAcc = _spdAcc;
			enemy[i]->spdMax = _spdMax;
			(_z == rand_PINTO) ? enemy[i]->z = ((rand() % (PINTO_MAX * 2)) - PINTO_MAX): enemy[i]->z = _z;
			enemy[i]->init_fg = true;
			return;
		}
		return;
	}




	void Init(int stageNo = 0);
	void Update();
	void Render();
	void UIUpdate();
	void UIRender();
	void clear() {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!enemy[i])continue;
			enemy[i]->clear();
		}
		data = NULL;
		data2 = NULL; 
	}
// エネミー共通関数
	void damage_Calculation(Enemy*);
	void jast_dragIn(Enemy*);
	float get_sz(float z);//フレームとのピントの差計算

protected:

	void Enemy_Manager::stageUpdate();
	STAGE_DATA* data;
	STAGE_DATA* data2;
	int stageNo;


	//Enemy_Manager();
	//~Enemy_Manager();
};


#define pEnemy_Manager (Enemy_Manager::getInstance()) 



void Base(Enemy*);			//動かない敵
void Teleport(Enemy* obj);	//瞬間移動する敵
void Sudden(Enemy* obj);	//近づいたら姿を現す敵
void Normal(Enemy* obj);	//襲ってくる敵					
void Tombo(Enemy* obj);		//敵突進
void zMove(Enemy* obj);		//襲ってくる敵
void Big(Enemy* obj);		//デカイ(向かってくる)

void Aggre(Enemy* obj);			//集合体制御
void Aggre_parent(Enemy* obj);	//集合体＿親
void Aggre_child(Enemy* obj);	//集合体＿子


void Rotation_Aggre_4(Enemy* obj);	//集合体制御(Rotetion)左
void Rotation(Enemy* obj);	//回転浮遊
//void Tutorial(Enemy* obj); //チュートリアル用
void tuto_Base(Enemy* obj);//チュートリアル用(倒し方)
void tuto_rock(Enemy* obj);//チュートリアル用(ピントロック)
void tuto_justpinto(Enemy* obj);//チュートリアル用(ジャストピント)
void tuto_multifocus(Enemy* obj);//チュートリアル用(マルチフォーカス)

#endif // !_ENEMY_H_
