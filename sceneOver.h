#ifndef __SCENEOVER_H__
#define __SCENEOVER_H__

//*****************************************************************************
//
//		�Q�[���I�[�o�[�V�[���N���X
//
//*****************************************************************************


class sceneOver : public Scene
{
private:
	int state;
	int timer;

	//�����L���O-------------------------------
	int ranks[5];
	int ranks_update_info;
	char ranksFileName[128];
	//-----------------------------------------
	
public:
	~sceneOver();
	bool Initialize();
	void Update();
	void Render();
};

//*****************************************************************************
#endif
