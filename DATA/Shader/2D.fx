texture Texture;
sampler DecaleSamp = sampler_state
{
    Texture = <Texture>;
    MinFilter = POINT;//LINEAR;
    MagFilter = POINT;//LINEAR;
    MipFilter = NONE;

    AddressU = WRAP;
    AddressV = WRAP;
};

sampler DecaleSamp2 = sampler_state
{
    Texture = <Texture>;
    MinFilter = GAUSSIANQUAD;
    MagFilter = GAUSSIANQUAD;
    MipFilter = NONE;

    AddressU = CLAMP;
    AddressV = CLAMP;
};

// -------------------------------------------------------------
// 頂点シェーダからピクセルシェーダに渡すデータ
// -------------------------------------------------------------
struct VS_OUTPUT_G
{
    float4 Pos			: POSITION;
	float2 Tex			: TEXCOORD0;
    float4 Color		: COLOR0;

};
// depth用
//struct VS_OUTPUT_G
//{
//	float4 Pos			: POSITION;
//	float2 Tex			: TEXCOORD0;
//	float4 Color		: COLOR0;
//
//};

// -------------------------------------------------------------
// 頂点シェーダプログラム
// -------------------------------------------------------------
VS_OUTPUT_G VS_pass1 (
      float4 Pos    : POSITION,          // モデルの頂点
      float2 Tex    : TEXCOORD0,	         // テクスチャ座標
      float4 Color  : COLOR0
){
    VS_OUTPUT_G Out;        // 出力データ
    
    // 位置座標
    Out.Pos = Pos;
    Out.Tex = Tex;
    Out.Color = Color;
    return Out;
}


// -------------------------------------------------------------
// ピクセルシェーダプログラム
// -------------------------------------------------------------
float4 PS_pass2(VS_OUTPUT_G In) : COLOR
{
	return In.Color * tex2D( DecaleSamp2, In.Tex );
}

float4 PS_pass1(VS_OUTPUT_G In) : COLOR
{   
    float4 Color;
    float4 temp;


	temp = tex2D( DecaleSamp, In.Tex );
	Color = temp*8;

	//	横	14t
	temp = tex2D( DecaleSamp, In.Tex + float2( + 0.002f, 0 )) + tex2D( DecaleSamp, In.Tex + float2( - 0.002f, 0 ) );
	Color += temp*4;
	
	temp = tex2D( DecaleSamp, In.Tex + float2( + 0.006f, 0 )) + tex2D( DecaleSamp, In.Tex + float2( - 0.005f, 0 ) );
	Color += temp*2;

	temp = tex2D( DecaleSamp, In.Tex + float2( + 0.01f, 0 )) + tex2D( DecaleSamp, In.Tex + float2( - 0.008f, 0 ) );
	Color += temp;

	//	縦	14t
	temp = tex2D( DecaleSamp, In.Tex + float2( 0, + 0.002f )) + tex2D( DecaleSamp, In.Tex + float2( 0, - 0.002f ) );
	Color += temp*4;
	
	temp = tex2D( DecaleSamp, In.Tex + float2( 0, + 0.006f )) + tex2D( DecaleSamp, In.Tex + float2( 0, - 0.005f ) );
	Color += temp*2;

	temp = tex2D( DecaleSamp, In.Tex + float2( 0, + 0.01f )) + tex2D( DecaleSamp, In.Tex + float2( 0, - 0.008f ) );
	Color += temp;


	//	上横	8t	
	temp = tex2D( DecaleSamp, In.Tex + float2( + 0.002f, -0.002f )) + tex2D( DecaleSamp, In.Tex + float2( - 0.002f, -0.002f ) );
	Color += temp*4;
	
	//	下横	8t
	temp = tex2D( DecaleSamp, In.Tex + float2( + 0.002f, +0.002f )) + tex2D( DecaleSamp, In.Tex + float2( - 0.002f, +0.002f ) );
	Color += temp*4;
	
	Color /= 52;
	
    return (Color );
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

float4 PS_pass3(VS_OUTPUT_G In) : COLOR
{
	float4	Color;
	float4 temp;
	
	temp = tex2D(DecaleSamp, In.Tex);
	Color = temp * 4;//8
	
					 //	横	14t
	temp = tex2D(DecaleSamp, In.Tex + float2(+0.004f, 0)) + tex2D(DecaleSamp, In.Tex + float2(-0.004f, 0));
	Color += temp * 4;//16
	
	temp = tex2D(DecaleSamp, In.Tex + float2(+0.012f, 0)) + tex2D(DecaleSamp, In.Tex + float2(-0.01f, 0));
	Color += temp * 4;//24
	
	temp = tex2D(DecaleSamp, In.Tex + float2(+0.02f, 0)) + tex2D(DecaleSamp, In.Tex + float2(-0.016f, 0));
	Color += temp * 4;//32
	
					  //	縦	14t
	temp = tex2D(DecaleSamp, In.Tex + float2(0, +0.004f)) + tex2D(DecaleSamp, In.Tex + float2(0, -0.004f));
	Color += temp * 4;//40
	
	temp = tex2D(DecaleSamp, In.Tex + float2(0, +0.012f)) + tex2D(DecaleSamp, In.Tex + float2(0, -0.01f));
	Color += temp * 4;//48
	
	temp = tex2D(DecaleSamp, In.Tex + float2(0, +0.02f)) + tex2D(DecaleSamp, In.Tex + float2(0, -0.016f));
	Color += temp * 8;//64
	
	
					  //	上横	8t	
	temp = tex2D(DecaleSamp, In.Tex + float2(+0.004f, -0.004f)) + tex2D(DecaleSamp, In.Tex + float2(-0.004f, -0.004f));
	Color += temp * 8;//80
	
					  //	下横	8t
	temp = tex2D(DecaleSamp, In.Tex + float2(+0.004f, +0.004f)) + tex2D(DecaleSamp, In.Tex + float2(-0.004f, +0.004f));
	Color += temp * 8;//92
	
	Color /= 92;
	
	return (Color* In.Color);
}

float FPower;
float FSize;

float4 PS_pass4(VS_OUTPUT_G In) : COLOR
{
	float4 Color = 0;
	float4 Color2 = 0;
	float4 temp0;
	float4 temp1;
	float4 temp2;
	float4 temp3;
	float4 temp4;
	float4 temp5;
	float4 temp6;
	float4 temp7;
	float4 temp8;
	float2 tpos;
	float2 tpos2;

	float z = FPower;
	float mz = FSize;
	z = trunc(z * 50) / 50;

	if (0.05 > z) {
		Color = tex2D(DecaleSamp, In.Tex);
	} 
	else if(0.5 > z){
		//sample
		//tpos = float2(trunc((In.Tex.x) * 1000) / 1000, trunc((In.Tex.y) * 1000) / 1000);
		//tpos2 = float2(trunc((In.Tex.x) * 1000) / 1000, trunc((In.Tex.y) * 1000) / 1000);
		int Reduced = 1000 * (1 - z);

		Color2 = tex2D(DecaleSamp, In.Tex);
		tpos = float2(trunc(In.Tex.x * Reduced )/ Reduced ,trunc(In.Tex.y * Reduced )/Reduced );
		temp0 = tex2D(DecaleSamp, tpos);
		
		tpos = float2(trunc((In.Tex.x + 0.002f) * Reduced ) / Reduced ,trunc(In.Tex.y * Reduced ) / Reduced );
		tpos2= float2(trunc((In.Tex.x - 0.002f) * Reduced ) / Reduced , trunc(In.Tex.y * Reduced ) / Reduced );
		temp1 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
		
		tpos = float2(trunc((In.Tex.x + 0.004f) * Reduced ) / Reduced , trunc((In.Tex.y) * Reduced ) / Reduced );
		tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced ) / Reduced , trunc((In.Tex.y) * Reduced ) / Reduced );
		temp2 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
		
		tpos = float2(trunc((In.Tex.x + 0.008f) * Reduced ) / Reduced , trunc((In.Tex.y) * Reduced ) / Reduced );
		tpos2 = float2(trunc((In.Tex.x - 0.008f) * Reduced ) / Reduced , trunc((In.Tex.y) * Reduced ) / Reduced );
		temp3 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

		//	縦	14t
		
		tpos = float2(trunc((In.Tex.x ) * Reduced ) / Reduced , trunc((In.Tex.y +  0.002f) * Reduced ) / Reduced );
		tpos2 = float2(trunc((In.Tex.x ) * Reduced ) / Reduced , trunc((In.Tex.y - 0.002f) * Reduced ) / Reduced );
		temp4 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

		tpos = float2(trunc((In.Tex.x ) * Reduced) / Reduced, trunc((In.Tex.y +   0.004) * Reduced) / Reduced);
		tpos2 = float2(trunc((In.Tex.x ) * Reduced ) / Reduced , trunc((In.Tex.y - 0.004) * Reduced ) / Reduced );
		temp5 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);


		tpos = float2(trunc((In.Tex.x )* Reduced ) / Reduced , trunc((In.Tex.y +  0.008f) * Reduced ) / Reduced );
		tpos2 = float2(trunc((In.Tex.x) * Reduced ) / Reduced , trunc((In.Tex.y - 0.008f) * Reduced ) / Reduced );
		temp6 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

		//	上横	8t	
		tpos = float2(trunc((In.Tex.x + 0.004f) * Reduced ) / Reduced , trunc((In.Tex.y  + 0.004f) * Reduced ) / Reduced );
		tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced ) / Reduced , trunc((In.Tex.y + 0.004f) * Reduced ) / Reduced );
		temp7 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
		//Color += temp[] * 2;     //84
		//	下横	8t
		tpos = float2(trunc((In.Tex.x + 0.004f) * Reduced ) / Reduced , trunc((In.Tex.y - 0.004f) * Reduced ) / Reduced );
		tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced ) / Reduced , trunc((In.Tex.y - 0.004f) * Reduced ) / Reduced );
		temp8 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
		int count = 0 ;

		if (temp0.a > 0) {
			Color += temp0 * 4; count += 4;
		}
		if (temp1.a > 0) {
			Color += temp1 * 2; count += 4;
		}
		if (temp2.a > 0) {
			Color += temp2 * 2; count += 4;
		}
		if (temp3.a > 0) {
			Color += temp3 * 2; count += 4;
		}
		if (temp4.a > 0) {
			Color += temp4 * 2; count += 4;
		}
		if (temp5.a > 0) {
			Color += temp5 * 2; count += 4;
		}
		if (temp6.a > 0) {
			Color += temp6 * 2; count += 4;
		}
		if (temp7.a > 0) {
			Color += temp7; count += 2;
		}
		if (temp8.a > 0) {
			Color += temp8; count += 2;
		}

		float alpha = Color.a / 42;
		Color /= count;
		Color.a = alpha;

		z /= 0.5; 
		
		Color *= (int)(z * 10);
		Color2 *= (int)((1 - z) * 10);


		Color += Color2;

		Color /= (((int)(z * 10)) + ((int)((1 - z) * 10)));


	//	Color /= ((int)(z * 10)) + ((int)((1 - z) * 10));
	//	//Color * xx;
	//	//Color * xx;

	//	//Color += Color2;
	//	//Color /= 2;
	}
	else {

		//COLOR1
		{
			int Reduced = 1000 * (1 - z);

			Color2 = tex2D(DecaleSamp, In.Tex);
			tpos = float2(trunc(In.Tex.x * Reduced) / Reduced, trunc(In.Tex.y * Reduced) / Reduced);
			temp0 = tex2D(DecaleSamp, tpos);

			tpos = float2(trunc((In.Tex.x +  0.002f) * Reduced) / Reduced, trunc(In.Tex.y * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.002f) * Reduced) / Reduced, trunc(In.Tex.y * Reduced) / Reduced);
			temp1 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			tpos = float2(trunc((In.Tex.x + 0.004f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			temp2 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			tpos = float2(trunc((In.Tex.x +  0.008f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.008f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			temp3 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			//	縦	14t

			tpos = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y +  0.002f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y - 0.002f) * Reduced) / Reduced);
			temp4 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			tpos = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y +	0.004) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y - 0.004) * Reduced) / Reduced);
			temp5 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);


			tpos = float2(trunc((In.Tex.x)* Reduced) / Reduced, trunc((In.Tex.y +   0.008f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y - 0.008f) * Reduced) / Reduced);
			temp6 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			//	上横	8t	
			tpos = float2(trunc((In.Tex.x +  0.004f) * Reduced) / Reduced, trunc((In.Tex.y + 0.004f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced) / Reduced, trunc((In.Tex.y + 0.004f) * Reduced) / Reduced);
			temp7 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
			//Color += temp[] * 2;     //84
			//	下横	8t
			tpos = float2(trunc((In.Tex.x + 0.004f) * Reduced) / Reduced, trunc((In.Tex.y - 0.004f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced) / Reduced, trunc((In.Tex.y - 0.004f) * Reduced) / Reduced);
			temp8 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
			int count = 0;

			if (temp0.a > 0) {
				Color += temp0 * 4; count += 4;
			}
			if (temp1.a > 0) {
				Color += temp1 * 2; count += 4;
			}
			if (temp2.a > 0) {
				Color += temp2 * 2; count += 4;
			}
			if (temp3.a > 0) {
				Color += temp3 * 2; count += 4;
			}
			if (temp4.a > 0) {
				Color += temp4 * 2; count += 4;
			}
			if (temp5.a > 0) {
				Color += temp5 * 2; count += 4;
			}
			if (temp6.a > 0) {
				Color += temp6 * 2; count += 4;
			}
			if (temp7.a > 0) {
				Color += temp7; count += 2;
			}
			if (temp8.a > 0) {
				Color += temp8; count += 2;
			}

			float alpha = Color.a / 32;
			Color /= count;
			Color.a = alpha;
		}
		// 4 8 8 8 16 16 16 4 4
		
		//COLOR2
		{
			
			int Reduced = 1000 * z;

			tpos = float2(trunc(In.Tex.x * Reduced) / Reduced, trunc(In.Tex.y * Reduced) / Reduced);
			temp0 = tex2D(DecaleSamp, tpos);

			tpos = float2(trunc((In.Tex.x +	0.004f) * Reduced) / Reduced, trunc(In.Tex.y * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.004f) * Reduced) / Reduced, trunc(In.Tex.y * Reduced) / Reduced);
			temp1 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			tpos = float2(trunc((In.Tex.x + 0.008f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.008f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			temp2 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			tpos = float2(trunc((In.Tex.x + 0.010f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.010f) * Reduced) / Reduced, trunc((In.Tex.y) * Reduced) / Reduced);
			temp3 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			//	縦	14t
			tpos = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y + 0.004f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.008f) * Reduced) / Reduced, trunc((In.Tex.y - 0.008f) * Reduced) / Reduced);
			temp4 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			tpos = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y + 0.008) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y - 0.008) * Reduced) / Reduced);
			temp5 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);


			tpos = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y + 0.010f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x) * Reduced) / Reduced, trunc((In.Tex.y - 0.010f) * Reduced) / Reduced);
			temp6 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			//	上横	8t	
			tpos = float2(trunc((In.Tex.x + 0.008f) * Reduced) / Reduced, trunc((In.Tex.y + 0.008f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.008f) * Reduced) / Reduced, trunc((In.Tex.y + 0.008f) * Reduced) / Reduced);
			temp7 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);
			//Color += temp[] * 2;     //84
			//	下横	8t
			tpos = float2(trunc((In.Tex.x + 0.008f) * Reduced) / Reduced, trunc((In.Tex.y - 0.008f) * Reduced) / Reduced);
			tpos2 = float2(trunc((In.Tex.x - 0.008f) * Reduced) / Reduced, trunc((In.Tex.y - 0.008f) * Reduced) / Reduced);
			temp8 = tex2D(DecaleSamp2, tpos) + tex2D(DecaleSamp2, tpos2);

			int count2 = 0;

			if (temp0.a > 0) {
				Color2 += temp0 * 2; count2 += 2;
			}
			if (temp1.a > 0) {
				Color2 += temp1 * 2; count2 += 4;
			}
			if (temp2.a > 0) {
				Color2 += temp2 * 2; count2 += 4;
			}
			if (temp3.a > 0) {
				Color2 += temp3 * 2; count2 += 4;
			}
			if (temp4.a > 0) {
				Color2 += temp4 * 2; count2 += 4;
			}
			if (temp5.a > 0) {
				Color2 += temp5 * 2; count2 += 4;
			}
			if (temp6.a > 0) {
				Color2 += temp6 * 2; count2 += 4;
			}
			if (temp7.a > 0) {
				Color2 += temp7 * 4; count2 += 8;
			}
			if (temp8.a > 0) {
				Color2 += temp8 * 4; count2 += 8;
			}

			float alpha = Color2.a / 42;
			Color2 /= count2;
			Color2.a = alpha;
			//z *= 2;
		}

		z = (z - 0.5)/0.5;
		//z = trunc(z * 10) / 10;
		Color *= (1 - z);
		Color2 *= (z);


		Color += Color2;

		//Color /= (((int)(z * 10)) + ((int)((1 - z) * 10)));
		
	}
	return (Color * In.Color);
}

//float4 PS_pass4(VS_OUTPUT_G In) : COLOR
//{
//	float4 Color = 0;
//	float4 Color2 = 0;
//	float4 temp0;
//	float4 temp1;
//	float4 temp2;
//	float4 temp3;
//	float4 temp4;
//	float4 temp5;
//	float4 temp6;
//	float4 temp7;
//	float4 temp8;
//	float2 tpos;
//	float z = FPower;
//	float mz = FSize;
//
//	if (0.1 > z) {
//		Color = tex2D(DecaleSamp, In.Tex);
//	}
//	else if (0.6 > z) {
//
//
//		Color2 = temp0 = tex2D(DecaleSamp, In.Tex);
//
//		//	横	14t
//		temp1 = tex2D(DecaleSamp2, In.Tex + float2(+0.004f, 0)) + tex2D(DecaleSamp2, In.Tex + float2(-0.004f, 0));
//		//Color += temp[] * 4;//16
//
//		temp2 = tex2D(DecaleSamp2, In.Tex + float2(+0.012f, 0)) + tex2D(DecaleSamp2, In.Tex + float2(-0.01f, 0));
//		//Color += temp[] * 4;//24
//
//		temp3 = tex2D(DecaleSamp2, In.Tex + float2(+0.02f, 0)) + tex2D(DecaleSamp2, In.Tex + float2(-0.016f, 0));
//		//Color += temp[] * 4;//32
//
//		//	縦	14t
//		temp4 = tex2D(DecaleSamp2, In.Tex + float2(0, +0.004f)) + tex2D(DecaleSamp2, In.Tex + float2(0, -0.004f));
//		//Color += temp[] * 8;//48
//		temp5 = tex2D(DecaleSamp2, In.Tex + float2(0, +0.012f)) + tex2D(DecaleSamp2, In.Tex + float2(0, -0.01f));
//		//Color += temp[] * 8;//64
//		temp6 = tex2D(DecaleSamp2, In.Tex + float2(0, +0.02f)) + tex2D(DecaleSamp2, In.Tex + float2(0, -0.016f));
//		//Color += temp[] * 8;//80
//
//		//	上横	8t	
//		temp7 = tex2D(DecaleSamp2, In.Tex + float2(+0.004f, -0.004f)) + tex2D(DecaleSamp2, In.Tex + float2(-0.004f, -0.004f));
//		//Color += temp[] * 2;     //84
//		//	下横	8t
//		temp8 = tex2D(DecaleSamp2, In.Tex + float2(+0.004f, +0.004f)) + tex2D(DecaleSamp2, In.Tex + float2(-0.004f, +0.004f));
//		int count = 0;
//
//		if (temp0.a > 0) {
//			Color += temp0 * 4; count += 4;
//		}
//		if (temp1.a > 0) {
//			Color += temp1 * 2; count += 4;
//		}
//		if (temp2.a > 0) {
//			Color += temp2 * 2; count += 4;
//		}
//		if (temp3.a > 0) {
//			Color += temp3 * 2; count += 4;
//		}
//		if (temp4.a > 0) {
//			Color += temp4 * 4; count += 8;
//		}
//		if (temp5.a > 0) {
//			Color += temp5 * 4; count += 8;
//		}
//		if (temp6.a > 0) {
//			Color += temp6 * 4; count += 8;
//		}
//		if (temp7.a > 0) {
//			Color += temp7; count += 2;
//		}
//		if (temp8.a > 0) {
//			Color += temp8; count += 2;
//		}
//
//		float alpha = Color.a / 42;
//		Color /= count;
//		Color.a = alpha;
//
//		z /= 1;
//
//		Color *= (int)(z * 10);
//		Color2 *= (int)((1 - z) * 10);
//
//
//		Color += Color2;
//
//		Color /= (((int)(z * 10)) + ((int)((1 - z) * 10)));
//
//
//		//	Color /= ((int)(z * 10)) + ((int)((1 - z) * 10));
//		//	//Color * xx;
//		//	//Color * xx;
//
//		//	//Color += Color2;
//		//	//Color /= 2;
//	}
//	else {
//		// 4 8 8 8 16 16 16 4 4
//		temp0 = tex2D(DecaleSamp2, In.Tex);
//		//Color += temp[] * 4;//4
//		//Color2 += temp[] * 4;//4
//		//横	14t
//
//		temp1 = tex2D(DecaleSamp2, In.Tex + float2(+0.004f, 0)) + tex2D(DecaleSamp2, In.Tex + float2(-0.004f, 0));
//		//Color += temp[] * 2;//8
//		//Color2 += temp[] * 4;//12
//
//		temp2 = tex2D(DecaleSamp2, In.Tex + float2(+0.012f, 0)) + tex2D(DecaleSamp2, In.Tex + float2(-0.01f, 0));
//		//Color += temp[] * 2;//12
//		//Color2 += temp[] * 4;//20
//
//		temp3 = tex2D(DecaleSamp2, In.Tex + float2(+0.02f, 0)) + tex2D(DecaleSamp2, In.Tex + float2(-0.016f, 0));
//		//Color += temp[] * 2;//16
//		//Color2 += temp[] * 4;//28
//
//		//	縦	14t
//		temp4 = tex2D(DecaleSamp2, In.Tex + float2(0, +0.004f)) + tex2D(DecaleSamp2, In.Tex + float2(0, -0.004f));
//		//Color += temp[] * 4;//24
//		//Color2 += temp[] * 2;//32
//
//		temp5 = tex2D(DecaleSamp2, In.Tex + float2(0, +0.012f)) + tex2D(DecaleSamp2, In.Tex + float2(0, -0.01f));
//		//Color += temp[] * 4;//32
//		//Color2 += temp[] * 2;//36
//
//		temp6 = tex2D(DecaleSamp2, In.Tex + float2(0, +0.02f)) + tex2D(DecaleSamp2, In.Tex + float2(0, -0.016f));
//		//Color += temp[] * 4;//40
//		//Color2 += temp[] * 2;//40
//
//		//	上横	8t	
//		temp7 = tex2D(DecaleSamp2, In.Tex + float2(+0.016f, -0.0016f)) + tex2D(DecaleSamp2, In.Tex + float2(-0.016f, -0.016f));
//		//Color += temp[];//80
//		//Color2 += temp[] * 4;//48
//
//		//	下横	8t
//		temp8 = tex2D(DecaleSamp2, In.Tex + float2(+0.016f, +0.016f)) + tex2D(DecaleSamp2, In.Tex + float2(-0.016f, +0.016f));
//
//		//Color += temp[];//92
//		//Color2 += temp[] * 4;//56
//
//		int count = 0;
//		int count2 = 0;
//
//		if (temp0.a > 0) {
//			Color += temp0 * 4; count += 4;
//			Color2 += temp0 * 4; count2 += 4;
//		}
//		if (temp1.a > 0) {
//			Color += temp1 * 2; count += 4;
//			Color2 += temp1 * 4; count2 += 8;
//		}
//		if (temp2.a > 0) {
//			Color += temp2 * 2; count += 4;
//			Color2 += temp2 * 4; count2 += 8;
//		}
//		if (temp3.a > 0) {
//			Color += temp3 * 2; count += 4;
//			Color2 += temp3 * 4; count2 += 8;
//		}
//		if (temp4.a > 0) {
//			Color += temp4 * 4; count += 8;
//			Color2 += temp4 * 2; count2 += 4;
//		}
//		if (temp5.a > 0) {
//			Color += temp5 * 4; count += 8;
//			Color2 += temp5 * 2; count2 += 4;
//		}
//		if (temp6.a > 0) {
//			Color += temp6 * 4; count += 8;
//			Color2 += temp6 * 2; count2 += 4;
//		}
//		if (temp7.a > 0) {
//			Color += temp7; count += 2;
//			Color2 += temp7 * 4; count2 += 8;
//		}
//		if (temp8.a > 0) {
//			Color += temp8; count += 2;
//			Color2 += temp8 * 4; count2 += 8;
//		}
//
//		float alpha = Color.a / 42;
//		Color /= count;
//		Color.a = alpha;
//
//		alpha = Color2.a / 56;
//		Color2 /= count2;
//		Color2.a = alpha;
//
//		//z *= 2;
//		z *= 0.5;
//		Color *= (int)(z * 10);
//		Color2 *= (int)((1 - z) * 10);
//
//
//		Color += Color2;
//
//		Color /= (((int)(z * 10)) + ((int)((1 - z) * 10)));
//
//	}
//	return (Color * In.Color);
//}



//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
//float4 PS_pass4(VS_OUTPUT_G In) : COLOR
//{
//	float4	Color;
//	float4 temp;
//	float z = In.Pos.z;
//
//temp = tex2D(DecaleSamp, In.Tex);
//Color = temp * 4;//8
//
//				 //	横	14t
//temp = tex2D(DecaleSamp, In.Tex + float2(+0.004f, 0)) + tex2D(DecaleSamp, In.Tex + float2(-0.004f, 0));
//Color += temp * 4;//16
//
//temp = tex2D(DecaleSamp, In.Tex + float2(+0.012f, 0)) + tex2D(DecaleSamp, In.Tex + float2(-0.01f, 0));
//Color += temp * 4;//24
//
//temp = tex2D(DecaleSamp, In.Tex + float2(+0.02f, 0)) + tex2D(DecaleSamp, In.Tex + float2(-0.016f, 0));
//Color += temp * 4;//32
//
//				  //	縦	14t
//temp = tex2D(DecaleSamp, In.Tex + float2(0, +0.004f)) + tex2D(DecaleSamp, In.Tex + float2(0, -0.004f));
//Color += temp * 4;//40
//
//temp = tex2D(DecaleSamp, In.Tex + float2(0, +0.012f)) + tex2D(DecaleSamp, In.Tex + float2(0, -0.01f));
//Color += temp * 4;//48
//
//temp = tex2D(DecaleSamp, In.Tex + float2(0, +0.02f)) + tex2D(DecaleSamp, In.Tex + float2(0, -0.016f));
//Color += temp * 8;//64
//
//
//				  //	上横	8t	
//temp = tex2D(DecaleSamp, In.Tex + float2(+0.004f, -0.004f)) + tex2D(DecaleSamp, In.Tex + float2(-0.004f, -0.004f));
//Color += temp * 8;//80
//
//				  //	下横	8t
//temp = tex2D(DecaleSamp, In.Tex + float2(+0.004f, +0.004f)) + tex2D(DecaleSamp, In.Tex + float2(-0.004f, +0.004f));
//Color += temp * 8;//92
//
//Color /= 92;
//
//return (Color* In.Color);
//}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■



// -------------------------------------------------------------
// テクニック
// -------------------------------------------------------------
technique gauss
{
    pass P0
    {
 		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		// シェーダ
        VertexShader = compile vs_3_0 VS_pass1();
		PixelShader  = compile ps_3_0 PS_pass1();
    }
}

technique gauss2
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		// シェーダ
		VertexShader = compile vs_3_0 VS_pass1();
		PixelShader = compile ps_3_0 PS_pass3();
	}
}

technique depth
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		// シェーダ
		VertexShader = compile vs_3_0 VS_pass1();
		PixelShader = compile ps_3_0 PS_pass4();
	}
}

technique copy
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		// シェーダ
        VertexShader = compile vs_3_0 VS_pass1();
        PixelShader  = compile ps_3_0 PS_pass2();
    }
}

technique add
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = one;
		// シェーダ
        VertexShader = compile vs_3_0 VS_pass1();
        PixelShader  = compile ps_3_0 PS_pass2();
    }
}


//------------------------------------------------------
//		スクリーンフィルタ
//------------------------------------------------------
float	contrast = 1.8;
float	chroma	= .9f;
float3	ScreenColor = { 1.0f, 1.9f, 1.1f };

struct VS_M
{
    float4 Pos		: POSITION;
    float4 Color	: COLOR0;
    float2 Tex		: TEXCOORD0;
};

//------------------------------------------------------
//		基本頂点シェーダー	
//------------------------------------------------------
VS_M VS_Master( VS_M In ){
	return In;
}

//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------
float4 PS_Master( VS_M In) : COLOR
{   
	float4	OUT;

	float3	col = tex2D( DecaleSamp, In.Tex );

	col = ((col-0.5f)*contrast) + 0.5f;

	float	avr = (col.r + col.g + col.b) / 3;
	col = (col-avr) * chroma + avr;

	//	ピクセル色決定
	OUT.rgb = col * ScreenColor;
	OUT.w = 1;
	
	return OUT;
}


//------------------------------------------------------
//
//------------------------------------------------------
technique Mastering
{
    pass P0
    {
		AlphaBlendEnable = false;
		BlendOp          = Add;
		SrcBlend         = one;
		DestBlend        = zero;

		VertexShader = compile vs_2_0 VS_Master();
		PixelShader  = compile ps_2_0 PS_Master();
    }
}


//------------------------------------------------------
//		パーティクル
//------------------------------------------------------

float3 LightDir = { 0.707f,0.707f,-0.707f };

texture NormalMap;	//	法線マップテクスチャ
sampler NormalSamp = sampler_state
{
    Texture = <NormalMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Wrap;
    AddressV = Wrap;
};

//------------------------------------------------------
//		基本頂点シェーダー	
//------------------------------------------------------
VS_M VS_Particle( VS_M In ){
	return In;
}

//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------
float4 PS_Particle( VS_M In) : COLOR
{   
	float4	OUT;

	//	ライト計算
	float3 N = tex2D( NormalSamp, In.Tex ).xyz * 2.0f - 1.0f;
	float rate = max( 0, dot( -LightDir, N ) );
	float4	col = tex2D( DecaleSamp2, In.Tex );
	//	ピクセル色決定
	OUT = In.Color * col;
	OUT.rgb *= rate;
	
	return OUT;
}


//------------------------------------------------------
//
//------------------------------------------------------
technique Particle
{
    pass P0
    {
		AlphaBlendEnable = true;
		BlendOp          = Add;
		SrcBlend         = SrcAlpha;
		DestBlend        = InvSrcAlpha;
		ZWriteEnable     = false;

		VertexShader = compile vs_3_0 VS_Particle();
		PixelShader  = compile ps_3_0 PS_Particle();
    }
}

