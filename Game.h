#pragma once

//*****************************************************************************************************************************
//*****************************************************************************************************************************
//
//			�Q�[���S�̏��w�b�_�[
//										�t�@�C���쐬��:
//										�t�@�C���쐬��:
//
//*****************************************************************************************************************************
//*****************************************************************************************************************************



//*****************************************************************************************************************************
//
//	define��`
//
//*****************************************************************************************************************************
#define		SCREEN_WIDTH		(960)			//	��ʃT�C�Y��
#define		SCREEN_HEIGHT		(540)			//	��ʃT�C�Y��
#include "Obj2D.h"
#include "Template.h"
class Player;
class MAP;
class Enemy;
class BG;
class FG;


enum stage_no {
	tutorial = 0,
	stage1,
};


//////////////////////////////////////////
//�f�o�b�O�p�����\���ȗ����c�[��
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
			IEX_DrawText(text_box[i].text, (int)text_box[i].pos.x, (int)text_box[i].pos.y,256, 16, (int)text_box[i].color);
		}
	}



private:
	//~Debug_text() {}


};

#define pD_TEXT (Debug_text::getInstance())



