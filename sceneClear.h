#ifndef __SCENECLEAR_H__
#define __SCENECLEAR_H__

//*****************************************************************************
//
//		ゲームクリアシーンクラス
//
//*****************************************************************************


class sceneClear : public Scene
{
private:
	int state;
	int timer;

	int score;
	int newscore;
	int hp;
	int maxcombo;
	int gametimer;
	V2 life_pos;
	V2 comb_pos;
	V2 time_pos;
	V2 totl_pos;
	D3DCOLOR clear_psb_argb;

	float f,g,h,j,m,n;

	//ランキング-------------------------------
	int ranks[5];
	int ranks_update_info;
	char ranksFileName[128];
	//-----------------------------------------

public:
	~sceneClear();
	bool Initialize();
	void Update();
	void Render();
};

//*****************************************************************************
#endif
