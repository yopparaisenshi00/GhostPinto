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
public:
	Number();
	~Number();
	void Init();
	void Update(int timer);
	void Render();
	int n_timer;

	//CUSTOM custom;
	iex2DObj*	numImage;			//�X�R�A�摜
	SPR_DATA*	data;
	void SetSize(int size);
	void SetNum(int num, int digit_max);
	//void Update(int digit_max);
	void AddScale();	//�X�R�A���Z�̊g��\��
	void Render(int x, int y, int digit_max); //�w�蕪�`��
	void Render2(int x, int y, int num);		//�����������`��
	void Render3(int x, int y, int digit_max, D3DCOLOR argb);
	//���l�`��֐�(�w���l�`��(num) + �w�蕪�`�� + color)           (digitmax = �\��������)
	void RenderFree(int x, int y, int num, int digit_max, int _digitDispSize, D3DCOLOR argb);


};
#define pNumber (Number::getInstance())


#endif // !_NUMBERS_H_#endif // !_NUMBERS_H_