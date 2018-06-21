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
	SPR_DATA* bg;
	SPR_DATA* ppsk;
	SPR_DATA* titleName;
	SPR_DATA* titleChar;
	SPR_DATA* s_Enemy_b;
	SPR_DATA* s_Enemy_s;
public:
	~sceneTitle();
	bool Initialize();
	void Update();
	void Render();
};

//*****************************************************************************
#endif
