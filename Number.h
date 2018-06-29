#ifndef _NUMBERS_H_
#define _NUMBERS_H_
//*****************************************************************************
//
//		�i���o�[�֘A�N���X
//
//*****************************************************************************
#define DIGIT_MAX			6	//�\�������̍ő�
#define DIGIT_SIZE			64	//�����摜��1�����̑傫��
#define NUM_DIGIT_1LINE		5	//�����摜��1��ɕ���ł��鐔
#define DIGIT_CHANGE_TIMER	2

#define RED		(UINT)0xFFff5e5e //�ԐF
#define YELLOW	(UINT)0xFFe2d600 //���F
#define WHITE	(UINT)0xFFFFFFFF //���F

#define RB1 (UINT)0xFFe65ffc	//���F
#define RB2 (UINT)0xFFff8426	//�I�����W�F
#define RB3 (UINT)0xFFffe942	//���F
#define RB4 (UINT)0xFF8dff42	//�ΐF
#define RB5 (UINT)0xFF58eaef	//���F
#define RB6 (UINT)0xFF5e9bff	//�F

#define FRASHSPD1 10
#define FRASHSPD2 5

class Number : public OBJ2DEX, public Singleton<Number>
{
private:
	int digitDispSize;		//���l�\���̍ۂ̕����T�C�Y
	struct tagDIGIT
	{
		BYTE	val;	//�l
		int		x, y;	//�\���ʒu
		int		w, h;
		int		timer;
	}digit[DIGIT_MAX];
	int front = 0;
	int after = 0;
	D3DCOLOR gametimer_argb;
	D3DCOLOR exorcise_argb;


	struct EVAL {
		V2 p_pos;

		int addscore,combo,just,total;

		V2 result_pos;
		V2 time_pos;
		V2 combo_pos;
		V2 just_pos;
		V2 total_pos;

		int alpha;
		spr_data::CUSTOM custom;

		bool flg;

		int timer;

		int iwork;
	};
	EVAL eval;




public:
	Number();
	~Number();
	void Init();
	void eval_agree();
	void Frash_Color_two(Number* obj,int num,D3DCOLOR argb1, D3DCOLOR argb2);
	void Number::Frash_Color_rainbow(Number* obj,int num,
		D3DCOLOR argb1,D3DCOLOR argb2,D3DCOLOR argb3,
		D3DCOLOR argb4,D3DCOLOR argb5,D3DCOLOR argb6);
	void Update(int timer);
	void Render();
	int n_timer;

	//CUSTOM custom;
	iex2DObj*	numImage;			//�X�R�A�摜
	SPR_DATA*	data;
	void SetSize(int size);
	void SetNum(int num, int digit_max);
	//void Update(int digit_max);
	void AddScale(int n, float scale);	//�X�R�A���Z�̊g��\��
	void Render(int x, int y, int digit_max); //�w�蕪�`��
	void Render2(int x, int y, int num);		//�����������`��
	void Render3(int x, int y, int digit_max, D3DCOLOR argb);
	//���l�`��֐�(�w���l�`��(num) + �w�蕪�`�� + color)           (digitmax = �\��������)
	void RenderFree(int x, int y, int num, int digit_max, int _digitDispSize, D3DCOLOR argb);


};
#define pNumber (Number::getInstance())


#endif // !_NUMBERS_H_#endif // !_NUMBERS_H_