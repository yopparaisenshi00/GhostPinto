#include	<time.h>
#include	"iextreme.h"
#include	"system.h"
#include    "Sound.h"

//*****************************************************************************************************************************
//
//
//
//*****************************************************************************************************************************

iexShader*	shader;
iexShader*	shader2D;

//*****************************************************************************************************************************
//
//*****************************************************************************************************************************
void	SYSTEM_Initialize()
{
	//	WL[έθ
	//                 ͺ@ «@ ©@ ¨@					   ~   ’        L1   L2   L3   R1   R2   R3   Sta        Sel
	KEYSET	keyset = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 'Z', 'X', 'C', 'V',  'A', 'Q', '1', 'Q', 'W', VK_SHIFT, VK_RETURN, VK_SPACE };
	KEY_Asign(keyset);

	//	Rg[[ZbeBO(DUALSHOCK2-ELECOM JC-PS101USV)
	//                 ΆX²   ΆY²   EX²   EY²    ~ ’     L1 L2 L3   R1 R2 R3   Sta Sel
	PADSET	padset = { AXIS_X, AXIS_Y, AXIS_Z, AXIS_RZ, 1, 2, 3, 4,   7, 5,11,   8, 6,12,   9, 10 };
	//KEY_PadAsign( padset );
	//KEY_PadAsign( iexInput::ps101 );		// ELECOM JC-PS101USV
	//KEY_PadAsign( iexInput::sixaxis );	// PS3 SIXAXIS DUALSHOCK3
	KEY_PadAsign(iexInput::xbox360);	// XBOX360 Controller

	//	VF[_[Ηέέ
	shader = new iexShader("DATA\\SHADER\\3DEx.fx");
	shader2D = new iexShader("DATA\\SHADER\\2D.fx");
	//	p[eBNVXeϊ»

	//randΦέθ
	srand((unsigned int)time(NULL));
	Sound_Load();

}

void	SYSTEM_Release()
{
	delete	shader;
	delete	shader2D;
	IEX_Release();
	Sound_Release();

}