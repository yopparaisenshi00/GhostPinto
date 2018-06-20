//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************
#ifndef _SCENE_MAIN_H_
#define _SCENE_MAIN_H_
#include "system\\Scene.h"


class	sceneMain : public Scene
{
private:
	iexView*	view;
	int state;
	int timer;
	int count_down_timer;
	int count_down;
	int scene_timer;
	int stage_no;
public:

	//MAP*		map;
	//Player*	player;
	//OBJ2D* bg;
	//OBJ2D* fg;

	//Enemy* enemy;
	
	~sceneMain();
	//	������
	bool Initialize();
	void UnInit();
	//	�X�V�E�`��
	void Update();	//	�X�V
	void Render();	//	�`��

};



#define COMBO_BONUS 2 //�R���{�{�[�i�X�X�R�A(�{�[�i�X�X�R�A * �R���{��)
#define COMBO_TIME 120 //�R���{�����^�C��
class Score:public OBJ2D ,public Singleton<Score>
{
private:
	//------------------------------
	//�ϐ�
	//------------------------------
	int score;//�X�R�A
	int combo;//�R���{��
	int maxcombo;//�ő�R���{��
	int combotimer;//�R���{�����^�C�}�[
	//------------------------------
	//�֐�
	//------------------------------
	//������
	void clear() {
		OBJ2D::clear();
		score = 0;
		combo = 0;
		maxcombo = 0;
		combotimer = 0;
		kill_num = 0;
	}
public:
	int kill_num;

	//�����ݒ�
	void Init() {
		clear();
	}

	//�X�V
	void Update() {
		combotimer++;
		if (combotimer > COMBO_TIME || combo == 0) {
			combo = 0;
			combotimer = 0;
		}
		if ( maxcombo<combo ) { //�ő�R���{���ۑ�
			maxcombo = combo;
		}
	}

	//�X�R�A���Z(�f���Ă����)
	void add_ClearlyScore(int add) {
		score += add;
	}
	//�X�R�A���Z(�|������)
	void add_KillScore(int add) {
		score += add + (combo * COMBO_BONUS);
		combotimer = 0;
		combo++;
		kill_num++;
	}

	//�X�R�A��Ԃ�
	int getScore() {
		return score;
	}
	//���j����Ԃ�
	int getKill_num() {
		return kill_num;
	}
	//�R���{����Ԃ�
	int getCombo() {
		return combo;
	}
	//�ő�R���{����Ԃ�
	int getMaxCombo() {
		return maxcombo;
	}


	void Render() {
		int x = 800;
		int y = 0;
	}

};

#define pScore (Score::getInstance())

#endif //_SCENE_MAIN_H_




