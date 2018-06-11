#ifndef _RANKING_H_
#define _RANKING_H_


#define RANKS_MAX (5)

int saveData(char *filename, int _score);
int loadData(char *filename, int rank[]);

void drawRankings(int _x,int _y,int ranks[],int _rank_update_info,SPR_DATA* data);
//void Render3(V2 pos,SPR_DATA* data,int num);
void Render3(V2 pos,SPR_DATA* data,int num,D3DCOLOR color);


#endif // !_RANKING_H_
