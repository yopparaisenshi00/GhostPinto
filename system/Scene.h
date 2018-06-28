#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
//
//		�V�[�����N���X
//
//*****************************************************************************

class Scene {
public:
	UINT fade_argb; //�t�F�[�h�p

	//	�����E���
	Scene(){}
	virtual ~Scene(){}
	//	������
	virtual bool Initialize(){ return true; }
	//	�X�V�E�`��
	virtual void Update(){}
	virtual void Render(){}
	virtual void UnInit(){}

	//���l�`��֐�(�����������`��)
	void Render2(V2 pos,SPR_DATA* data,int num)
	{
		int _num = num;
		int count = 0;

		//�����𒲂ׂ�------------------
		while ( _num>=10 ) { //10�ȏ�Ȃ�
			_num /= 10;		//10�Ŋ�����
			count++;		//x�ʒu���炵�J�E���g
		}


		//�`��---------------------------
		do {
			_num = num % 10;	//1���ڒ��o
			num /= 10;			//�ꌅ�ڔr��
			spr_data::Render(V2(pos.x+count*32,pos.y),&data[_num]); //�J�E���g���E�ɕ`��
			count--;
		} while ( num>0 );
	}

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



//class Fade_In :public Singleton<Fade_In>
//{
//public:
//	Fade_In();
//	~Fade_In();
//	virtual bool Initialize() { return true; }
//
//	void Update();
//	void Render();
//	void UnInit();
//
//private:
//
//};
//
//Fade_In::Fade_In()
//{
//}
//
//Fade_In::~Fade_In()
//{
//}
//
//class Fade_Out :public Singleton<Fade_Out>
//{
//public:
//	
//private:
//
//};
//*****************************************************************************
#endif
