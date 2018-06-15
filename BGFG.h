#ifndef _LAND_SCAPE_H_
#define _LAND_SCAPE_H_

#define FG_MAX (64)
#define BG_MAX (64)
class LAND_SCAPE_OBJ;
struct LAND_SCAPE_DATA {
	enum {
		BG = 0,
		FG = 1,
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
		bool type,
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
};



typedef class LAND_SCAPE_OBJ :public OBJ2DEX
{
public:

	
	void(*move)(LAND_SCAPE_OBJ*);
	bool init_fg;

	void clear() {
		OBJ2DEX::clear();
		init_fg = 0;
		move = nullptr;
		sz = 0;
		z = 0;
	}
	int sz;
	int z;


	void Init();
	void Update();
	void Render();

}BGOBJ, FGOBJ;




class BG {
public:
	BG();
	~BG();
	BGOBJ* obj[BG_MAX];
	void Init();
	void Update();
	void Render();

private:
};

#define FG_MAX (64)
#define BG_MAX (64)



//class FGOBJ :public OBJ2DEX
//{
//public:
//	void(*move)(FGOBJ*);
//	bool init_fg;
//	int z;
//
//
//	void clear() {
//		OBJ2DEX::clear();
//		init_fg = 0;
//		move = nullptr;
//	}
//	sz = 0
//	void Init();
//	void Update();
//	void Render();
//
//};

class FG
{
public:
	FG();
	~FG();
	FGOBJ* obj[64];

	void Init();
	void Update();
	void Render();

private:
};



class LandScape :public Singleton<LandScape>
{
public:
	BG backobj;
	FG flontobj;
	int timer;
	LAND_SCAPE_DATA* data;

	BGOBJ bg;

	int z;


	void Init(int stage_no);
	void setMainBG(SPR_DATA* BG, void(*move)(FGOBJ*)) {
		bg.data = BG;
		bg.move = move;
	}

	void searchSet(int type = 0 ,V2 pos = V2(0, 0), V2 spd = V2(0, 0), void(*move)(FGOBJ*) = nullptr, OBJ2D* parent = nullptr,int _z = 0) {
		LAND_SCAPE_OBJ** obj;
		type ? obj = backobj.obj : obj = flontobj.obj;
  		for (int i = 0; i < FG_MAX; i++) {
			if (obj[i] && obj[i]->init_fg)continue;
			if (!obj[i])obj[i] = new LAND_SCAPE_OBJ;
			obj[i]->clear();//Aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
			obj[i]->pos = pos;
			obj[i]->spd = spd;
			obj[i]->move = move;
			obj[i]->init_fg = true;
			obj[i]->parent = parent;
			obj[i]->z = _z;
			break;
		}

	}
	void stage_update();
	void Update();
	/*{
		stage_update();
		bg.Update();
		backobj.Update();
		flontobj.Update();
	}
*/
	void RenderBG() {
		bg.Render();
		//for (int i= 0; i < BG_MAX;i++) {
		//	backobj.Render();
		//}
	}
	void RenderFG() {
		for (int i= 0; i < BG_MAX; i++) {
			flontobj.Render();
		}

	}


private:
};

void MainBG(LAND_SCAPE_OBJ*);
void BG_pc(LAND_SCAPE_OBJ*);
void BG_container(LAND_SCAPE_OBJ*);

#define pLandScape (LandScape::getInstance())


#endif // !_LAND_SCAPE_

