
#ifndef _OBJ2D_H_
#define _OBJ2D_H_ 

class Animetion {
	Animetion() {}

	SPR_DATA* data;

};

class OBJ2D
{
public:
	OBJ2D() {
	}
	~OBJ2D() {
		 //if (tex) { delete tex; tex = NULL;}
	}
	
	V2 pos;
	V2 spd;
	V2 size;

	int				key;		//キー情報
	int				state;		// 状態
	int				timer;		// タイマー（使い方は自由）
	int				type;
	SPR_DATA*		data;
	SPR_DATA**		data_box;


	int sc_w;
	int sc_h;

	int anime_timer;
	int anime_no;
	//	iex2DObj* tex;
	
	OBJ2D* parent;

	
	bool reflect;

	virtual void clear();			// メンバ変数のクリア
	
	virtual void Init();
	virtual void Update();			// 移動
	virtual void Render();			// 描画

	spr_data::CUSTOM custom;

private:

};

#define	ANIM_FLG_LOOP	-1		//	アニメーションループ	
#define	ANIM_FLG_STOP	-2		//	アニメーション停止	


class OBJ2DEX : public OBJ2D
{
public:

	int aframe;
	int animeNO;
	int anime_timer;

	SPR_DATA* animeData;

	//OBJ2DEX() {clear();};
	//virtual ~OBJ2DEX() {clear();};

	virtual void clear() {
		OBJ2D::clear();
		aframe = 0;
		animeNO = 0;
		animeData = nullptr;
		anime_timer = 0;
	}

	virtual void animation() {
		aframe++;

		if (animeData)
		{
			//aframe++;
			if (aframe > animeData[animeNO].frameNum)
			{
				aframe = 0;
				animeNO++;
				//if (animeData[animeNO].no < 0)
				//{
				//	animeNO = 0;
				//}
				switch (animeData[animeNO].no)
				{
				case ANIM_FLG_STOP:	animeNO--;	break;
				case ANIM_FLG_LOOP:	animeNO = 0;	break;
				}
			}
			data = &animeData[animeNO];
		}
	};
};

#define	SPR_STOP		SPR_DATA{ ANIM_FLG_STOP,	   0, 0,  0,  0,   0,   0 }
#define	SPR_LOOP		SPR_DATA{ ANIM_FLG_LOOP,	   0, 0,  0,  0,   0,   0 }




bool Judge(OBJ2D *obj1, OBJ2D *obj2);
#endif 
