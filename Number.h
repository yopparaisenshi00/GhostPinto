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
public:
	Number();
	~Number();
	void Init();
	void Update(int timer);
	void Render();
	int n_timer;

	//CUSTOM custom;
	iex2DObj*	numImage;			//スコア画像
	SPR_DATA*	data;
	void SetSize(int size);
	void SetNum(int num, int digit_max);
	//void Update(int digit_max);
	void AddScale();	//スコア加算の拡大表示
	void Render(int x, int y, int digit_max); //指定分描画
	void Render2(int x, int y, int num);		//桁数分だけ描画
	void Render3(int x, int y, int digit_max, D3DCOLOR argb);
	//数値描画関数(指数値描画(num) + 指定分描画 + color)           (digitmax = 表示文字数)
	void RenderFree(int x, int y, int num, int digit_max, int _digitDispSize, D3DCOLOR argb);


};
#define pNumber (Number::getInstance())


#endif // !_NUMBERS_H_#endif // !_NUMBERS_H_