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
public:
	~sceneTitle();
	bool Initialize();
	void Update();
	void Render();
};

//*****************************************************************************
#endif
