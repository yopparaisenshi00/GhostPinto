#include "iextreme.h"


void iexTRIGGERS::Add_Data(iexTRIGGER* _data) {
	
	switch (swap)
	{
	case 0x00:
		pData1[data1_count] = _data;
		data1_count++;
		break;
	case 0x01:
		pData2[data2_count] = _data;
		data2_count++;
		break;
	default:
		break;
	}
}

void iexTRIGGERS::Update() {
	switch (swap)
	{
	case 0x00:
		Update(pData1,data1_count, pData2, data2_count);
		break;
	case 0x01:		
		Update(pData2, data2_count,pData1, data1_count);
		break;
	default:
		swap = 0;
		break;
	}

	swap++;
	swap &= 0x01;

}
iexTRIGGERS::iexTRIGGERS():data1_count(0), data2_count(0), swap(0){
	for (int i = 0; i < dataMax; i++) {
		pData1[i] = NULL;
		pData2[i] = NULL;

	}
}
iexTRIGGERS::~iexTRIGGERS() {
	for (int i = 0; i < dataMax; i++) {
		pData1[i] = NULL;
		pData2[i] = NULL;
	}
}

inline void iexTRIGGERS::Update(iexTRIGGER** trg_data, int &trg_count, iexTRIGGER** release_data, int &release_count) {

	for (int i = 0; i < release_count; i++) {
		if (release_data[i]) {
			*release_data[i] &= 0x01;
			release_data[i] = NULL;
		}
	}
	release_count = 0;

	for (int i = 0; i < trg_count; i++) {
		if (trg_data[i]) {
			*trg_data[i] |= 0x02;
			*trg_data[i] &= 0x02;
		}
	}

}

//void iexTRIGGER::operator=(int _flg) {
//	static iexTRIGGERS* triggers = iexTRIGGERS::GetIncetance();
//	if (_flg) {
//		if (trg == 0x01) {
//			return;
//		}
//		trg = 0x01;
//		triggers->Add_Data(this);
//	}
//	else {
//		trg &= 0x10;
//	}
//}

void iexTRIGGER::operator=(bool _flg) {
	static iexTRIGGERS* triggers = iexTRIGGERS::GetIncetance();
	if (_flg) {
		//if (trg && 0x01) {
		//	return;
		//}
		trg = 0x01;
		triggers->Add_Data(this);
	}
	else {
		trg &= 0x02;
	}
}



int iexTRIGGER::operator==(int _flg) {
	return (trg & _flg);
}

int iexTRIGGER::operator==(bool _flg) {
	return (trg & 0x01) == _flg;
}

int iexTRIGGER::operator!=(int _flg) {
	return trg != _flg;
}
void iexTRIGGER::operator &= (int state){
	trg &= state;
}

void iexTRIGGER::operator |= (int state) {
	trg |= state;
}

