#pragma once
#ifndef _UI_H_
#define _UI_H_

class UI :public OBJ2D,public Singleton<UI>
{
public:
	UI();
	~UI();
	
	void Init();
	void Update();
	void Render();

	
private:
	//float angle;
};

#define pUI UI::getInstance()
#endif // !_UI_H_
