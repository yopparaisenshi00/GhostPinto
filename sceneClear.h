#ifndef __SCENECLEAR_H__
#define __SCENECLEAR_H__

//*****************************************************************************
//
//		�Q�[���N���A�V�[���N���X
//
//*****************************************************************************


class sceneClear : public Scene
{
private:
	int state;
	int timer;

	int score;
	int newscore;
	int gametimer;
	V2 time_pos;

	//�����L���O-------------------------------
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
