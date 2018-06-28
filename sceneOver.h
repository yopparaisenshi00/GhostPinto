#ifndef __SCENEOVER_H__
#define __SCENEOVER_H__

//*****************************************************************************
//
//		ゲームオーバーシーンクラス
//
//*****************************************************************************


class sceneOver : public Scene
{
private:
	int state;
	int timer;

	D3DCOLOR over_psb_argb;
	D3DCOLOR fade_over;
public:
	~sceneOver();
	bool Initialize();
	void Update();
	void Render();
};

//*****************************************************************************
#endif
