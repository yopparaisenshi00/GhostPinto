#pragma once

//*****************************************************************************************************************************
//*****************************************************************************************************************************
//
//			ゲーム全体情報ヘッダー
//										ファイル作成者:
//										ファイル作成日:
//
//*****************************************************************************************************************************
//*****************************************************************************************************************************



//*****************************************************************************************************************************
//
//	define定義
//
//*****************************************************************************************************************************
#define		SCREEN_WIDTH		(960)			//	画面サイズ幅
#define		SCREEN_HEIGHT		(540)			//	画面サイズ高
#include "Obj2D.h"
#include "Template.h"
class Player;
class MAP;
class Enemy;
class BG;
class FG;

//////////////////////////////////////////
//デバッグ用文字表示簡略化ツール
//////////////////////////////////////////
class Debug_text : public Singleton<Debug_text>
{

private:
	static const int text_max = 256;
	struct text_Box
	{
		V2 pos;
		DWORD color;
		char text[128];
		text_Box() {
			pos = V2(0, 0);
			color = 0;
			memcpy(text, "", 128);
		}
	void clear() {
			//pos = V2(0, 0);
			color = 0;
			//memcpy(text, "", 128);

		}
	};

	text_Box text_box[text_max];

public:

	void Reset() {
		for (int i = 0; i < text_max; i++) {
			text_box[i].clear();
		}
	}
	void set_Text(V2 pos,char* text, float data, DWORD color = 0xFFFFFFFF) {
		for (int i = 0; i < text_max; i++) {
			if (text_box[i].color != 0)continue;
			sprintf_s(text_box[i].text, 128, "%s:%f",text, data);
			text_box[i].color = color;
			text_box[i].pos = pos;
			break;
		}
	}		
	void set_Text(V2 pos, char* text, int data, DWORD color = 0xFFFFFFFF) {
		for (int i = 0; i < text_max; i++) {
			if (text_box[i].color != 0)continue;
			sprintf_s(text_box[i].text, 128, "%s:%d", text, data);
			text_box[i].color = color;
			text_box[i].pos = pos;
			break;
		}
	}

	void Render() {
		for (int i = 0; i < text_max;i++) {
			if (text_box[i].color == 0)continue;
			IEX_DrawText(text_box[i].text, (int)text_box[i].pos.x, (int)text_box[i].pos.y,128, 16, (int)text_box[i].color);
		}
	}



private:
	//~Debug_text() {}


};

#define pD_TEXT (Debug_text::getInstance())



//struct IMG_DATA
//{
//	int		imgNo;			//画像番号
//	int		sx, sy;			//画像切抜X, Y
//	int		sw, sh;			//画像切抜幅、高さ
//	int		ofsX, ofsY;		//オフセット量(横幅の半分、身長)
//	float	scale;			//描画スクール
//};

//class  OBJ2D
//{
//public:
//	float x, y;
//	float mx, my;
//	float dx, dy;
//	float dw, dh;
//	int step, timer;
//	float scaleX, scaleY;			/*Change Object's SIZE*/
//	float setX, setY;				/*Moving until (setX, setY)*/
//	int anime, aFrame, mot_rate;	/*As for Object's Animation*/
//	float angle;					/*Z Rotation angle*/
//	float mAngle;
//	bool centRotate;				/*"true": Rotation by Object's center, "false": Rotation by (centX, centY)*/
//	float centX, centY;
//	int alpha;						/*Change Object's Transparent (0~255)*/
//	int mAlpha;
//	bool reflect;					/*"true": Reflect by Object's center, "false": No reflection*/
//	int iwork[16];
//	iex2DObj*	img;
//	void(*move)(OBJ2D* obj);
//
//	void clear(){
//		x = 0.0f;
//		y = 0.0f;
//		mx = 0.0f;
//		my = 0.0f;
//		dx = 0.0f;
//		dy = 0.0f;
//		dw = 0.0f;
//		dh = 0.0f;
//		step = 0;
//		timer = 0;
//		scaleX = 1.0f;
//		scaleY = 1.0f;
//		setX = 0.0f;
//		setY = 0.0f;
//		anime = 0;
//		aFrame = 0;
//		mot_rate = 1;
//		centRotate = true;
//		centX = 0;
//		centY = 0;
//		angle = 0.0f;
//		mAngle = 0.0f;
//		alpha = 255;
//		mAlpha = 0;
//		reflect = false;
//		ZeroMemory(iwork, sizeof(iwork));
//		img = nullptr;
//		move = nullptr;
//	}
//
//	void draw(){
//		if (img)
//		{
//			//alpha = alpha % 256;
//			if (alpha > 255)
//			{
//				alpha = 255;
//			}
//			if (alpha < 0)
//			{
//				alpha = 0;
//			}
//			DWORD color = alpha << 24 | 0x00FFFFFF;
//			img->Render(x, y, scaleX*dw, scaleY*dh, dx, dy, dw, dh, angle, centRotate, centX, centY, RS_ALPH, color, reflect);
//		}
//	}
//
//	static OBJ2D* searchSet(void(*move)(OBJ2D* obj), float x, float y, OBJ2D* begin, OBJ2D* end) {
//		for (OBJ2D* obj = begin; obj < end; obj++) {
//			if (obj->move) {
//				continue;
//			}
//			obj->x = x;
//			obj->y = y;
//			return obj;
//		}
//		return nullptr;
//	}
//};


