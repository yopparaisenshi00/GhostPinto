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
public:
	~sceneOver();
	bool Initialize();
	void Update();
	void Render();
	bool gameover_se_flg;
};

//*****************************************************************************
#endif
