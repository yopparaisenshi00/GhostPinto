#ifndef _SOUND_H_
#define _SOUND_H_


enum {
	BGM_MAIN,	//メインBGM
	BGM_TITLE,	//タイトルBGM

	SE_PINTO,	//ピントが合った時
	SE_JUSTPINTO,	//ジャストピントの時
	SE_EXT,		//消滅
	SE_RETURN,	//霊力復帰
	SE_LOSS,	//霊力消失
	SE_DAMAGE,	//ダメージ
	SE_MULCH_FIRE,	//マルチフォーカス使用時
	SE_MULCH_STOCK,	//マルチフォーカスが溜まった時
	SE_LOCK //LOCK
};


void Sound_Load();
void Sound_Release();


#endif // !_SOUND_H_