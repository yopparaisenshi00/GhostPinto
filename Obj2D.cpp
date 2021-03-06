#include	"iextreme.h"		
#include	"system/system.h"	
#include    "Obj2D.h"

void OBJ2D::Init() {
	clear();
}

void OBJ2D::Update() {
	if (move)move(this);
}

void OBJ2D::Render() {
	//spr_data::obj[data->no]->Render(pos.x,pos.y,data->dx,data->dy,data->sx,data->sy, data->ofsx, data->ofsy,0,0xFFFFFFFF,(0.0f));
	if(data)
	spr_data::Render(pos, data,&custom,custom.argb,nullptr,nullptr);	
}
void OBJ2D::Render(char* teah) {
	if (data)
		//spr_data::obj[data->no]->Render(pos.x,pos.y,data->dx,data->dy,data->sx,data->sy, data->ofsx, data->ofsy,0,0xFFFFFFFF,(0.0f));
	spr_data::Render(pos, data, &custom, custom.argb,shader2D, teah);
}

void OBJ2D::clear() {
	pos = V2(0, 0);
	spd = V2(0, 0);
	size = V2(0, 0);
	state = 0;
	timer = 0;
	type = 0;
	data = NULL;
	
	sc_w = 0;
	sc_h = 0;
	key  = 0;

	parent = 0;
	reflect = false;

	

	custom.clear();
}

bool Judge(OBJ2D *obj1, OBJ2D *obj2)
{
	if (obj1->pos.x + obj1->size.x < obj2->pos.x - obj2->size.x) return false;
	if (obj2->pos.x + obj2->size.x < obj1->pos.x - obj1->size.x) return false;
	if (obj1->pos.y + obj1->size.y < obj2->pos.y - obj2->size.y) return false;
	if (obj2->pos.y + obj2->size.y < obj1->pos.y - obj1->size.y) return false;

	return true;
}


void line_rect(V2 center = V2(0, 0), V2 ofs = V2(0,0), DWORD color = 0xFFFFFFFF, int centMode = 0) {
	switch (centMode)
	{
	case CENTER:
		drawline(center, ofs, color);
		break;
	case LEFTTOP:
		drawline(center - ofs, ofs, color);
		break;
	case TOPCENTER:
		drawline(center + V2(0,ofs.y), ofs, color);
		break;
	case RIGHTTOP:
		drawline(center + V2(ofs.x,-ofs.y), ofs, color);
		break;
	case RIGHTCENTER:
		drawline(center + V2(ofs.x, 0), ofs, color);
		break;
	case RIGHTBOTTOM:
		drawline(center + ofs, ofs, color);
		break;
	case BOTTOMCENTER:
		drawline(center - V2(0,ofs.y), ofs, color);
		break;
	case LEFTBOTTOM:
		drawline(center + V2(ofs.y,-ofs.y), ofs, color);
		break;
	case LEFTCENTER:
		drawline(center - V2(ofs.x, 0), ofs, color);
		break;
	default:
		break;
	}
}
void line_rect(float centerx = 0, float centery = 0, float ofsetx = 0, float ofsety = 0, DWORD  color = 0xFFFFFFFF, int centMode = 0) {
	line_rect(V2(centerx, centery), V2(ofsetx, ofsety), color,centMode);
}

inline void drawline(V2 center, V2 ofs, DWORD color) {
	iexPolygon::Rect((int)(center.x - ofs.x), (int)(center.y + ofs.y), (int)(ofs.x * 2), 1, 0, color);
	iexPolygon::Rect((int)(center.x - ofs.x), (int)(center.y - ofs.y), (int)(ofs.x * 2), 1, 0, color);

	//////�c
	iexPolygon::Rect((int)(center.x + ofs.x), (int)(center.y - ofs.y), 1, (int)ofs.y * 2, 0, color);
	iexPolygon::Rect((int)(center.x - ofs.x), (int)(center.y - ofs.y), 1, (int)ofs.y * 2, 0, color);
}


