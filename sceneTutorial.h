//*****************************************************************************************************************************
//
//		メインシーン
//
//*****************************************************************************************************************************
#ifndef _SCENETUTORIAL_H_
#define _SCENETUTORIAL_H_
#include "system\\Scene.h"


class	sceneTutorial : public Scene
{
private:
	iexView*	view;
	int state;
	int timer;
	int count_down_timer;
	int count_down;
	int scene_timer;
	int stage_no;
	OBJ2D center;

public:

	//MAP*		map;
	//Player*	player;
	//OBJ2D* bg;
	//OBJ2D* fg;

	//Enemy* enemy;

	~sceneTutorial();
	//	初期化
	bool Initialize();
	void UnInit();
	//	更新・描画
	void Update();	//	更新
	void Render();	//	描画

};

#endif //_SCENETUTORIAL_H_




