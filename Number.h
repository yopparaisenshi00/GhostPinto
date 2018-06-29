#ifndef _NUMBERS_H_
#define _NUMBERS_H_
//*****************************************************************************
//
//		ナンバー関連クラス
//
//*****************************************************************************
#define DIGIT_MAX			6	//表示桁数の最大
#define DIGIT_SIZE			64	//数字画像の1文字の大きさ
#define NUM_DIGIT_1LINE		5	//数字画像の1列に並んでいる数
#define DIGIT_CHANGE_TIMER	2

#define RED		(UINT)0xFFff5e5e //赤色
#define YELLOW	(UINT)0xFFe2d600 //黄色
#define WHITE	(UINT)0xFFFFFFFF //白色

#define RB1 (UINT)0xFFe65ffc	//紫色
#define RB2 (UINT)0xFFff8426	//オレンジ色
#define RB3 (UINT)0xFFffe942	//黄色
#define RB4 (UINT)0xFF8dff42	//緑色
#define RB5 (UINT)0xFF58eaef	//水色
#define RB6 (UINT)0xFF5e9bff	//青色

#define FRASHSPD1 10
#define FRASHSPD2 5

class Number : public OBJ2DEX, public Singleton<Number>
{
private:
	int digitDispSize;		//数値表示の際の文字サイズ
	struct tagDIGIT
	{
		BYTE	val;	//値
		int		x, y;	//表示位置
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
	iex2DObj*	numImage;			//スコア画像
	SPR_DATA*	data;
	void SetSize(int size);
	void SetNum(int num, int digit_max);
	//void Update(int digit_max);
	void AddScale(int n, float scale);	//スコア加算の拡大表示
	void Render(int x, int y, int digit_max); //指定分描画
	void Render2(int x, int y, int num);		//桁数分だけ描画
	void Render3(int x, int y, int digit_max, D3DCOLOR argb);
	//数値描画関数(指数値描画(num) + 指定分描画 + color)           (digitmax = 表示文字数)
	void RenderFree(int x, int y, int num, int digit_max, int _digitDispSize, D3DCOLOR argb);


};
#define pNumber (Number::getInstance())


#endif // !_NUMBERS_H_#endif // !_NUMBERS_H_