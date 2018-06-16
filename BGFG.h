#ifndef _LAND_SCAPE_H_
#define _LAND_SCAPE_H_


#define _DEBUG_REDUCEDLINE_RENDER_ //縮尺サイズのライン描画 (大元)

#define _DEBUG_REDUCEDLINE_TOP_ //縮尺サイズのライン描画TOP
#define _DEBUG_REDUCEDLINE_BOT_ //縮尺サイズのライン描画BOT
#define _DEBUG_REDUCEDLINE_CENTER_ //縮尺サイズのライン描画CENTER

class LAND_SCAPE_OBJ;
typedef struct LAND_SCAPE_DATA {

	enum {
		CENTER = 0,
		TOP = 1,
		BOT = 2,
	};

	int type;
	int appearTime;
	void(*moveType)(LAND_SCAPE_OBJ*);
	V2	pos, 
		scale,
		speed,
		speedAcc,
		speedMax;
	
	int z;
	int effectTime;
	
	OBJ2D* parent;

	LAND_SCAPE_DATA(
		int type,
		int _appearTime,				//出現タイム
		void(*_moveType)(LAND_SCAPE_OBJ*),	//関数
		V2 _pos,					//座標
		V2 _speed,					//速度
		V2 _speedAcc,				//加速度
		V2 _speedMax,				//最大速度
		int _z							//Z値
		)
		:
		type(type),
		appearTime(_appearTime),
		moveType(_moveType),
		pos(_pos),
		speed(_speed),
		speedAcc(_speedAcc),
		speedMax(_speedMax),
		z(_z) {};
}LAND_SCAPE_DATA,LSD;



typedef class LAND_SCAPE_OBJ :public OBJ2DEX
{
public:

	
	void(*move)(LAND_SCAPE_OBJ*);
	bool init_fg;
	float sz;
	float z;
	


	void clear() {
		OBJ2DEX::clear();
		wpos = V2(0,0);
		init_fg = 0;
		move = nullptr;
		sz = 0;
		z = 0;
	}
	V2 wpos;//ワールド座標

	void Init();
	void Update();
	void Render();

}BGOBJ, FGOBJ;



//class BG {
//public:
//	BG();
//	~BG();
//	BGOBJ* obj[BG_MAX];
//	void Init();
//	void Update();
//	void Render();
//
//private:
//};

#define LANDSCAPE_MAX (256)

//class FG
//{
//public:
//	FG();
//	~FG();
//	FGOBJ* obj[64];
//
//	void Init();
//	void Update();
//	void Render();
//
//private:
//};

#define BG_REDUCED_LV_MAX 5
#define FG_REDUCED_LV_MAX 2

class LandScape :public Singleton<LandScape>
{
public:
	//BG backobj;
	//FG flontobj;
	
	int timer;				//出現等制御用
	LAND_SCAPE_DATA* data;	//BG配置データポインタ

	BGOBJ bg; //　メイン(最奥)
	LAND_SCAPE_OBJ* LandScapeObjs[256];

	void Init(int stage_no);
	void setMainBG(SPR_DATA* BG, void(*move)(FGOBJ*)) {
		bg.data = BG;
		bg.move = move;
	}

	void searchSet(int type = 0 ,V2 pos = V2(0, 0), V2 spd = V2(0, 0), void(*move)(FGOBJ*) = nullptr, OBJ2D* parent = nullptr,int _z = 0) {
		//LandScapeObjs;
		//LAND_SCAPE_OBJ** obj;
  		for (int i = 0; i < LANDSCAPE_MAX; i++) {
			if (LandScapeObjs[i] && LandScapeObjs[i]->init_fg)continue;
			if (!LandScapeObjs[i])LandScapeObjs[i] = new LAND_SCAPE_OBJ;

			LandScapeObjs[i]->clear();//
			LandScapeObjs[i]->wpos = pos;
			LandScapeObjs[i]->spd = spd;
			LandScapeObjs[i]->move = move;
			LandScapeObjs[i]->init_fg = true;
			LandScapeObjs[i]->parent = parent;
			LandScapeObjs[i]->z = _z;
			LandScapeObjs[i]->type = type;
			break;
		}

	}

	void stage_update();
	void Update();
	void RenderBG();
	void RenderFG();
	void add_RenderObj(LAND_SCAPE_OBJ* obj, int z); 
	//{
	//	if (z > -1) { //0以上なら背景、以下なら前景
	//		BG_RenderBox[z].data[(BG_RenderBox[z].count++)] = obj;
	//	}
	//	else {
	//		z *= -1;
	//		z -= 1;
	//		FG_RenderBox[z].data[FG_RenderBox[z].count++] = obj;
	//	}
	//}
private:

	struct ReducedObj {
		float bot;
		V2 pos;
		void Init(float);
		void Update();
		void Render();
		float Reduced_level;
		LAND_SCAPE_OBJ* data[LANDSCAPE_MAX];
		int count;
		void clear() {
			pos = V2(0,0);
			Reduced_level = 0;
			ZeroMemory(data,sizeof(data[LANDSCAPE_MAX]));
			count = 0;
		}
	};

	ReducedObj BG_RenderBox[BG_REDUCED_LV_MAX];
	ReducedObj FG_RenderBox[FG_REDUCED_LV_MAX];
	
public:
	
};

void MainBG(LAND_SCAPE_OBJ*);
void BG_pc(LAND_SCAPE_OBJ*);
void BG_container(LAND_SCAPE_OBJ*);
void BG_Capsule_l(LAND_SCAPE_OBJ*);
void BG_Capsule_d(LAND_SCAPE_OBJ*);
void BG_Fly_mini_capsule_l(LAND_SCAPE_OBJ*);
void BG_Fly_mini_capsule_d(LAND_SCAPE_OBJ*);
void BG_Fly_mini_capsule_m(LAND_SCAPE_OBJ*);
void BG_Fly_capsule_l(LAND_SCAPE_OBJ*);
void BG_Fly_capsule_d(LAND_SCAPE_OBJ*);
void BG_Fly_capsule_m(LAND_SCAPE_OBJ*);
void BG_Mini_capsule_l(LAND_SCAPE_OBJ*);
void BG_Mini_capsule_d(LAND_SCAPE_OBJ*);
void BG_Break_capsule_u(LAND_SCAPE_OBJ*);
void BG_Display_a(LAND_SCAPE_OBJ*);
void BG_Display_b(LAND_SCAPE_OBJ*);
void BG_Display_c(LAND_SCAPE_OBJ*);
void BG_Display_d(LAND_SCAPE_OBJ*);

#define pLandScape (LandScape::getInstance())


#endif // !_LAND_SCAPE_

