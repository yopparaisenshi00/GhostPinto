#include "iextreme.h"
#include "Ranking.h"




// for Ranking
int saveData(char *filename, int _score)
{
	FILE *fp;
	int rank[RANKS_MAX] = { 0 }, info = RANKS_MAX;

	if (loadData(filename, rank) == 1)
	{
		//スコア入れ替え処理
		for (int i = 0; i < RANKS_MAX; i++) //5thまで繰り返し
		{
			if (_score >= rank[i])
			{
				for (int j = RANKS_MAX - 1; j > i; j--)
				{
					rank[j] = rank[j - 1];
				}
				rank[i] = _score;
				info = i;
				break;
			}
		}
	}
	else
	{
		rank[0] = _score;
		info = 0;
	}
	if (fopen_s(&fp, filename, "wb") != 0)
	{
		printf("file open error!\n");
		return -1;
	}
	if (fwrite(rank, sizeof(int), RANKS_MAX, fp) == 0)
	{
		if (ferror(fp))
		{
			printf("write error!\n");
			return -2;
		}
	}
	fclose(fp);

	return info;
}


int loadData(char *filename, int rank[])
{
	FILE *fp;

	if (fopen_s(&fp, filename, "rb") != 0)
	{
		printf("file open error!\n");
		return -1;
	}
	if (fread(rank, sizeof(int), RANKS_MAX, fp) == 0)
	{
		if (ferror(fp))
		{
			printf("read error!\n");
			return -3;
		}
	}
	fclose(fp);
	return 1;
}






void drawRankings(int _x, int _y, int ranks[], int _rank_update_info, SPR_DATA* data)
{
	//_x -= 70;	//
	//_y -= 65;	//

	/////////////////////////////////////////////////////////
	////文字描画
	//if (_ranksImageData)
	//{
	//	_ranksImageData->draw(Vector3(_x+70,_y+65,0));
	//}
	/////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////
	//スコア描画
	for (int i = 0; i < RANKS_MAX; i++) //5thまで繰り返し
	{
		//描画(新しくランクインしたスコアは赤く光る)
		if (_rank_update_info == i){
			//Render3(V2(_x, _y+i*64-34), &data[0], ranks[i]);
			Render3(V2(_x,_y+i*64-34),&data[0],ranks[i],0xFFFF0000); //赤
		}
		else{
			//Render3(V2(_x, _y+i*64-34), &data[0], ranks[i]);
			Render3(V2(_x,_y+i*64-34),&data[0],ranks[i],0xFFFFFFFF); //白
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
}



void Render3(V2 pos,SPR_DATA* data,int num,D3DCOLOR color)
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
		spr_data::Render(V2(pos.x+count*32,pos.y),&data[_num],color,0); //カウント分右に描画
		count--;
	} while ( num>0 );
}