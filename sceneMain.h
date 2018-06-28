//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************
#ifndef _SCENE_MAIN_H_
#define _SCENE_MAIN_H_
#include "system\\Scene.h"

#define CLEAR_KILLNUM (4)
#define COUNT_DOWN_TIME (2)
class	sceneMain : public Scene ,public Singleton<sceneMain>
{
private:
	iexView*	view;
	int state;
	int timer;
	int count_down_timer;
	int count_down;
	int scene_timer;
	int stage_no;
	UINT fade_argb;
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


	UINT fade_out(UINT argb,UINT spd) {
		//argb += 0x11000000;
		argb += spd;
		return argb;
	}
	UINT fade_in(UINT argb,UINT spd) {
		//argb -= 0x11000000;
		argb -= spd;
		return argb;
	}
};
#define pMain (sceneMain::getInstance())




#define COMBO_BONUS 2 //�R���{�{�[�i�X�X�R�A(�{�[�i�X�X�R�A * �R���{��)
#define COMBO_TIME 100 //�R���{�����^�C��
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
		addscore = 0;
		eval_justpinto = 0;
	}
public:
	int kill_num;
	int addscore;		//�R���{���U���g_�B�e�X�R�A
	int eval_justpinto; //�R���{���U���g_�W���X�g�s���g��
	int comboscore;		//�R���{���U���g_�R���{���X�R�A

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
		addscore += add; //�R���{���r�؂��܂�add���ۑ�
	}
	//�X�R�A���Z(�|������)
	void add_KillScore(int add) {
		score += add + (combo * COMBO_BONUS)/*+(eval_justpinto*200)*/;
		comboscore += add+(combo * COMBO_BONUS);
		combotimer = 0;
		//eval_justpinto = 0;
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
	//�R���{���U���g_�B�e�X�R�A
	int getAddscore() {
		return addscore;
	}
	//�R���{���U���g_�W���X�g�s���g��
	int getEval_justpinto() {
		return eval_justpinto;
	}
	//�R���{���U���g_�R���{���X�R�A
	int getcomboscore() {
		return comboscore;
	}
	//�R���{���U���g_�R���{�^�C�}�[
	int getcombotimer() {
		return combotimer;
	}


	void Render() {
		int x = 800;
		int y = 0;
	}

};

#define pScore (Score::getInstance())

#endif //_SCENE_MAIN_H_




