#include <iextreme.h>
#include "Sound.h"

//サウンド読み込み  BGM再生 
void Sound_Load() {
	IEX_SetWAV(BGM_MAIN, "DATA\\Sound\\BGM\\equalzero.wav");
	//IEX_SetWAV(BGM_MAIN,		"DATA\\Sound\\BGM\\Explanation.wav"); 
	//IEX_SetWAV(BGM_MAIN,		"DATA\\Sound\\BGM\\TechPorter.wav"); 
	//IEX_SetWAV(BGM_MAIN,		"DATA\\Sound\\BGM\\tw028.wav"); 
	IEX_SetWAV(BGM_TITLE,		"DATA\\Sound\\BGM\\title.wav"); 

	IEX_SetWAV(SE_RETURN, "DATA\\Sound\\SE\\Alarm0031.wav");
	//IEX_SetWAV(SE_RETURN,		"DATA\\Sound\\SE\\Alarm0032.wav"); 
	//IEX_SetWAV(SE_PINTO,		"DATA\\Sound\\SE\\Cancel0019.wav"); 
	IEX_SetWAV(SE_EXT, "DATA\\Sound\\SE\\item02.wav");
	//IEX_SetWAV(SE_PINTO,		"DATA\\Sound\\SE\\Cosmo0008.wav"); 
	//IEX_SetWAV(SE_PINTO,		"DATA\\Sound\\SE\\Cosmo0019.wav"); 
	IEX_SetWAV(SE_PINTO, "DATA\\Sound\\SE\\Cosmo0020.wav");
	//IEX_SetWAV(SE_EXT,		"DATA\\Sound\\SE\\Decision0102.wav"); 
	//IEX_SetWAV(SE_PINTO,		"DATA\\Sound\\SE\\Decision0129.wav"); 
	//IEX_SetWAV(SE_PINTO,		"DATA\\Sound\\SE\\Decision0141.wav"); 
	//IEX_SetWAV(SE_PINTO,		"DATA\\Sound\\SE\\powerup03.wav"); 
	IEX_SetWAV(SE_LOSS, "DATA\\Sound\\SE\\Select0008.wav");
	IEX_SetWAV(SE_DAMAGE,		"DATA\\Sound\\SE\\damage.wav"); 
	IEX_SetWAV(SE_MULCH_FIRE,	"DATA\\Sound\\SE\\mulch_fire.wav"); 
	IEX_SetWAV(SE_MULCH_STOCK,"DATA\\Sound\\SE\\mulch_stock.wav"); 

	IEX_SetWAV(SE_LOCK,		"DATA\\Sound\\SE\\Camera0024.wav"); 
	//IEX_SetWAV(SE_JUSTPINTO,		"DATA\\Sound\\SE\\Cosmo0007.wav"); 
	//IEX_SetWAV(SE_JUSTPINTO,		"DATA\\Sound\\SE\\Decision0101.wav"); 
	IEX_SetWAV(SE_JUSTPINTO, "DATA\\Sound\\SE\\item02.wav");
}


//サウンド停止(解放は別の所で勝手に行われる)       
void Sound_Release() {
	IEX_StopSound(BGM_MAIN);
	IEX_StopSound(BGM_TITLE);
	IEX_StopSound(SE_JUSTPINTO);
	IEX_StopSound(SE_PINTO);
	IEX_StopSound(SE_EXT);
	IEX_StopSound(SE_RETURN);
	IEX_StopSound(SE_LOSS);
	IEX_StopSound(SE_DAMAGE);
	IEX_StopSound(SE_MULCH_FIRE);
	IEX_StopSound(SE_MULCH_STOCK);
}