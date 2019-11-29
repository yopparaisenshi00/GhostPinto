#pragma once
#ifndef UI_H_
#define UI_H_

class UI :public OBJ2D,public Singleton<UI>
{
public:
	UI();
	~UI();
	
	void Init();
	void Update();
	void HP_Update();
	void Render();

	struct HP {
		spr_data::CUSTOM custom;
		int old_hp;
		bool flg;
	};
	HP h;

private:
	//float angle;
};

#define pUI UI::getInstance()
#endif // !UI_H_
