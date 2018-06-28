#ifndef _ENEMY_H_
#define _ENEMY_H_

#define ENEMY_MAX (256)
#define DAMAGE_MAX (700) //iran

//�G�l�~�[�g�o�Q
#define ENEMY_HP_A (700)//�Y���z
#define ENEMY_HP_B (600)//���ʂ̓z
#define ENEMY_HP_C (700)//���[�v����z
#define ENEMY_HP_D (700)//Z�l�ړ�����z
#define ENEMY_HP_E (1300)//�ł����z
#define ENEMY_HP_F (900)//�g���{


#define DAMAGE_LINE (3.6) 
#ifndef PINTO_MAX

	#define PINTO_MAX (90)

#endif // !PINTO_MAX
#define INIT_ANGLE		(180.0f*D3DX_PI/180.0f)		//�ŏ��̊p�x(���W�A��)

#define DRAGIN_SCALE (192)//�W���X�g�s���g�������݃T�C�Y

#define C_scale		1.0f		//�q�̑傫��
#define N_scale		1.5f		//�ʏ�G�̑傫��
#define B_scale		2.5f		//�f�J�C�G�̑傫��

#define rand_PINTO		(10000)//�G��Z�l�����_��
//#define rand_PINTO		((rand()%(PINTO_MAX*2)) -PINTO_MAX)	//�G��Z�l�����_��
#define DAMAGE (10)
#define JUSTPINTO_SIZE (2)

//enum {
//	Init,//�����ݒ�
//	Main,//��{�s��
//	Special1,//���Z
//	Special2,//���Z
//	Dead,//���S���o
//	Clear,//������
//};
struct STAGE_DATA {
	int appearTime;
	void(*moveType)(Enemy*);
	V2 pos, speed, speedAcc, speedMax;
	int z;

	STAGE_DATA(
		int _appearTime,			//�o��time
		void(*_moveType)(Enemy*),	//�֐�
		V2 _pos,					//���W
		V2 _speed,					//���x
		V2 _speedAcc,				//�����x
		V2 _speedMax,				//�ő呬�x
		int _z							//Z�l
		)
		:appearTime(_appearTime),
		moveType(_moveType),
		pos(_pos),
		speed(_speed),
		speedAcc(_speedAcc),
		speedMax(_speedMax),
		z(_z) {};



};

//�G�̎���
enum {
	yellow,
	green,
	pink,
	blue,
	white,
	kari,
};


class Enemy_Kill :public OBJ2D, public Singleton<Enemy_Kill>
{
private:
	//������
	void clear() {
		OBJ2D::clear();

		kill_num_yellow = 0;
		kill_num_green = 0;
		kill_num_pink = 0;
		kill_num_blue = 0;
		kill_num_white = 0;
		kill_num_kari = 0;
	}

public:
	//----------------------------------------------
	//�G���Ƃ�kill���p�ϐ�
	//----------------------------------------------
	int kill_num_yellow;
	int kill_num_green;
	int kill_num_pink;
	int kill_num_blue;
	int kill_num_white;
	int kill_num_kari;

	//�����ݒ�
	void Init() {
		clear();
	}

	//�X�V
	void Update() {}

	//�G���Ƃ�kill����Ԃ�
	int getKill_num_Each(int state) {
		switch (state) {
		case yellow: return kill_num_yellow; break;
		case green:	 return kill_num_green;  break;
		case pink:	 return kill_num_pink;	 break;
		case blue:	 return kill_num_blue;	 break;
		case white:	 return kill_num_white;  break;
		case kari:	 return kill_num_kari;	 break;
		default:	 return 0;				 break;
		}
	}
};
#define pEnemy_Kill (Enemy_Kill::getInstance())


class Enemy:public OBJ2DEX
{
public:
	Enemy();
	~Enemy();
	//----------------------------------------------
	//��{���ϐ�
	//----------------------------------------------
	Vector2 spdAcc;		// �����x
	Vector2 spdMax;		// �ő呬�x

	int damage;		//���ރQ�[�W
	int damageMAX;	//���ރQ�[�WMAX
	int alpha ;
	int count;
	int score; //�X�R�A

	float z;		//�s���g���W
	struct ui {
		D3DCOLOR argb; //UI_ARGB
		float angle;//UI_angle
		spr_data::CUSTOM custom;
	};
	ui u;

	bool damageflg; //���ރQ�[�W�t���O
	bool rangeflg;	//�͈͔���t���O
	bool init_fg;
	bool z_flg;
	bool noHit_flg;
	bool zlock_flg;

	int Dot_timer;
	int Dot_alpha;
	D3DCOLOR Dot_argb;

	SPR_DATA**	Anime_Box;
	int flash_timer;

	float f_work[16]; //�t���[
	
	void(*move)(Enemy*);//�s���֐��|�C���^
	//---------------------------------------------

	//----------------------------------------------
	//******
	//----------------------------------------------
	
	float dx, dy;
	float dist;
	float XCENTER;  //��]�̒��S
	float YCENTER;  //��]�̒��S
	float ANGLE;
	float ANGLEspd; //��]���x
	float RADIUS;   //���a
	float sz;		//�t���[���Ƃ̃s���g��
	//�֐�
	//OBJ�p���֐�---------------------------------------
	virtual void Init(); //
	virtual void Update();

	virtual void Render();//�`�揈��
	virtual void UIRender();//UI�`�揈��

	virtual void clear();
	//---------------------------------------------------
	// 
	//-----------------------------------------------------
	virtual void UIUpdate();//UI�`��X�V
	virtual void DotLine();//�j���`��


	virtual void animetion() {
		anime_timer++;
		if (anime_timer > 3) {
			//anime_no++;
			aframe++;
			anime_timer = 0;
		}


		if (animeData)
		{
			//aframe++;
			if (aframe > animeData[animeNO].frameNum)
			{
				aframe = 0;
				animeNO++;
				if (animeData[animeNO].no < 0)
				{
					animeNO = 0;
				}
			}
			data = &animeData[animeNO];
		}
	}
	//-----------------------------------------------------

protected:
	
};


class Enemy_Manager:public Singleton<Enemy_Manager>
{
public:
	Enemy* enemy[ENEMY_MAX];
	int timer;


	void searchSet(V2 pos = V2(0, 0), V2 spd = V2(0, 0), void(*move)(Enemy*) = nullptr,float _z = 0,Enemy* parent = NULL);
	void searchSet(void(*_move)(Enemy*), V2 &_pos = Vector2(0, 0), V2 &_spd = Vector2(0, 0), V2 &_spdAcc = Vector2(0, 0),
		V2 &_spdMax = Vector2(0, 0), float _z = 0) {
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i] && enemy[i]->init_fg) {
				continue;
			}
			if (!enemy[i])enemy[i] = new Enemy;
			enemy[i]->move = _move;
			enemy[i]->pos = _pos;
			enemy[i]->spd = _spd;
			enemy[i]->spdAcc = _spdAcc;
			enemy[i]->spdMax = _spdMax;
			(_z == rand_PINTO) ? enemy[i]->z = ((rand() % (PINTO_MAX * 2)) - PINTO_MAX): enemy[i]->z = _z;
			enemy[i]->init_fg = true;
			return;
		}
		return;
	}




	void Init(int stageNo = 0);
	void Update();
	void Render();
	void UIUpdate();
	void UIRender();
	void clear() {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!enemy[i])continue;
			enemy[i]->clear();
		}
		data = NULL;
		data2 = NULL; 
	}
// �G�l�~�[���ʊ֐�
	void damage_Calculation(Enemy*);
	void jast_dragIn(Enemy*);
	float get_sz(float z);//�t���[���Ƃ̃s���g�̍��v�Z

protected:

	void Enemy_Manager::stageUpdate();
	STAGE_DATA* data;
	STAGE_DATA* data2;
	int stageNo;


	//Enemy_Manager();
	//~Enemy_Manager();
};


#define pEnemy_Manager (Enemy_Manager::getInstance()) 



void Base(Enemy*);			//�����Ȃ��G
void Teleport(Enemy* obj);	//�u�Ԉړ�����G
void Sudden(Enemy* obj);	//�߂Â�����p�������G
void Normal(Enemy* obj);	//�P���Ă���G					
void Tombo(Enemy* obj);		//�G�ːi
void zMove(Enemy* obj);		//�P���Ă���G
void Big(Enemy* obj);		//�f�J�C(�������Ă���)

void Aggre(Enemy* obj);			//�W���̐���
void Aggre_parent(Enemy* obj);	//�W���́Q�e
void Aggre_child(Enemy* obj);	//�W���́Q�q


void Rotation_Aggre_4(Enemy* obj);	//�W���̐���(Rotetion)��
void Rotation(Enemy* obj);	//��]���V
//void Tutorial(Enemy* obj); //�`���[�g���A���p
void tuto_Base(Enemy* obj);//�`���[�g���A���p(�|����)
void tuto_rock(Enemy* obj);//�`���[�g���A���p(�s���g���b�N)
void tuto_justpinto(Enemy* obj);//�`���[�g���A���p(�W���X�g�s���g)
void tuto_multifocus(Enemy* obj);//�`���[�g���A���p(�}���`�t�H�[�J�X)

#endif // !_ENEMY_H_
