
#ifndef _OBJ2D_H_
#define _OBJ2D_H_ 

struct Animetion {
	public:
	SPR_DATA* data;
	int frameNum;
};

class OBJ2D
{
public:
	OBJ2D() {
	}
	~OBJ2D() {
		 //if (tex) { delete tex; tex = NULL;}
	}
	
	V2 pos;
	V2 spd;
	V2 size;

	int				key;		//�L�[���
	int				state;		// ���
	int				timer;		// �^�C�}�[�i�g�����͎��R�j
	int				type;
	SPR_DATA*		data;


	int sc_w;
	int sc_h;

	int anime_timer;
	int anime_no;
	//	iex2DObj* tex;
	void(*move)(OBJ2D*);
	OBJ2D* parent;
		
	bool reflect;

	virtual void clear();			// �����o�ϐ��̃N���A
	
	virtual void Init();
	virtual void Update();			// �ړ�
	virtual void Render();			// �`��
	void OBJ2D::Render(char* teah);//�V�F�[�_�[�g�p�`��p
	spr_data::CUSTOM custom;


private:

};

#define	ANIM_FLG_LOOP	-1		//	�A�j���[�V�������[�v	
#define	ANIM_FLG_STOP	-2		//	�A�j���[�V������~	


class OBJ2DEX : public OBJ2D
{
public:

	int aframe;
	int animeNO;
	int anime_timer;

	SPR_DATA* animeData;
	SPR_DATA**	data_box;

	//OBJ2DEX() {clear();};
	//virtual ~OBJ2DEX() {clear();};

	virtual void clear() {
		OBJ2D::clear();
		aframe = 0;
		animeNO = 0;
		animeData = nullptr;
		anime_timer = 0;
		data_box = nullptr;
	}

	virtual void animetion() {
		aframe++;
		if (animeData)
		{
			if (aframe > animeData[animeNO].frameNum)
			{
				aframe = 0;
				animeNO++;
				//if (animeData[animeNO].no < 0)
				//{
				//	animeNO = 0;
				//}
				switch (animeData[animeNO].no)
				{
				case ANIM_FLG_STOP:	animeNO--;	break;
				case ANIM_FLG_LOOP:	animeNO = 0;	break;
				}
			}
			data = &animeData[animeNO];
		}
	}

};

#define	SPR_STOP		SPR_DATA{ ANIM_FLG_STOP,	   0, 0,  0,  0,   0,   0 }
#define	SPR_LOOP		SPR_DATA{ ANIM_FLG_LOOP,	   0, 0,  0,  0,   0,   0 }



bool Judge(OBJ2D *obj1, OBJ2D *obj2);

void line_rect(V2 center, V2 ofs, DWORD color,int centMode);
void line_rect(float centerx, float centery, float ofsetx, float ofsety, DWORD  color, int centMode);
inline void drawline(V2 center, V2 ofs, DWORD color);

#endif 
