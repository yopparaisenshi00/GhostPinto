#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
//
//		シーン基底クラス
//
//*****************************************************************************

class Scene {
public:
	UINT fade_argb; //フェード用

	//	生成・解放
	Scene(){}
	virtual ~Scene(){}
	//	初期化
	virtual bool Initialize(){ return true; }
	//	更新・描画
	virtual void Update(){}
	virtual void Render(){}
	virtual void UnInit(){}

	//数値描画関数(桁数分だけ描画)
	void Render2(V2 pos,SPR_DATA* data,int num)
	{
		int _num = num;
		int count = 0;

		//桁数を調べる------------------
		while ( _num>=10 ) { //10以上なら
			_num /= 10;		//10で割って
			count++;		//x位置ずらしカウント
		}


		//描画---------------------------
		do {
			_num = num % 10;	//1桁目抽出
			num /= 10;			//一桁目排除
			spr_data::Render(V2(pos.x+count*32,pos.y),&data[_num]); //カウント分右に描画
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
