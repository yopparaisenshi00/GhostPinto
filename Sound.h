#ifndef _SOUND_H_
#define _SOUND_H_


static enum {
	BGM_MAIN = 0,	//メインBGM
	BGM_TITLE,	//タイトルBGM

	SE_COUNT,	//スタートカウント
	SE_LOCK,	//ロックした時
	SE_PINTO,	//ピントが合った時
	SE_JUSTPINTO,	//ジャストピントで敵を倒した時
	SE_EXT,		//消滅
	SE_RETURN,	//霊力復帰
	SE_LOSS,	//霊力消失
	SE_DAMAGE,	//ダメージ
	SE_MULCH_FIRE,	//マルチフォーカス使用時
	SE_MULCH_STOCK,	//マルチフォーカスが溜まった時
};


void Sound_Load();
void Sound_Release();


#endif // !_SOUND_H_