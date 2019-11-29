#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

//*****************************************************************************
//
//		タイトルシーンクラス
//
//*****************************************************************************


class sceneTitle : public Scene
{
private:
	int timer;
	int state;
	OBJ2D bg;
	OBJ2D ppsk;
	OBJ2D titleName;
	OBJ2D titleChar;
	OBJ2D s_Enemy_b;
	OBJ2D s_Enemy_s;

	OBJ2D* moveobj_data[6] = {
		&bg,
		&ppsk,
		&titleName,
		&titleChar,
		&s_Enemy_b,
		&s_Enemy_s,
	};

	int dust_timer;
	bool key_flg;

public:
	~sceneTitle();
	bool Initialize();
	void Update();
	void Render();
	void Frash_Color(OBJ2D* obj,int num,D3DCOLOR argb1, D3DCOLOR argb2) {
		obj->timer++;
		if ((obj->timer % (num * 2)) <  num) obj->custom.argb = argb1;
		if ((obj->timer % (num * 2)) >= num) obj->custom.argb = argb2;
	}
};


//*****************************************************************************
#endif
