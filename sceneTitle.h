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

public:
	~sceneTitle();
	bool Initialize();
	void Update();
	void Render();
};

//*****************************************************************************
#endif
