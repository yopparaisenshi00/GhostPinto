
#ifndef _MINIMAP_H_
#define	_MINIMAP_H_

//#define REDUCTIONSIZE 8

#define REDUCTIONSIZE 10
#define Player_Icon_SIZE 8
#define  Enemy_Icon_SIZE 3

#define Player_Icon_OFSET (Player_Icon_SIZE/2)
#define Enemy_Icon_OFSET (Enemy_Icon_SIZE/2)
class MiniMap :public OBJ2D
{
	V2 p_Pps; //プレイヤー座標
	V2 E_Pps[256]; //プレイヤー座標


public:
	float ReductionSize;
	V2 Limits;
	int count;


	MiniMap(){}
	~MiniMap(){}


	void Init(float LimitR, float LimitD);
	void Update();
	void Render();
	void clear() {
		ReductionSize = 0;
		Limits = V2(0,0);
		count = 0;
	}


private:




};



#endif // !_MINIMAP_H_
