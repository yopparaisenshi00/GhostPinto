#include	"iextreme.h"		
#include	"system/system.h"	
#include    "Obj2D.h"

void OBJ2D::Init() {

}

void OBJ2D::Update() {

}

void OBJ2D::Render() {
	//spr_data::obj[data->no]->Render(pos.x,pos.y,data->dx,data->dy,data->sx,data->sy, data->ofsx, data->ofsy,0,0xFFFFFFFF,(0.0f));
	spr_data::Render(pos, data);
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




