#include	"iExtreme.h"

//*****************************************************************************
//
//		２Ｄオブジェクト
//
//*****************************************************************************
//------------------------------------------------------
//	コンストラクタ
//------------------------------------------------------
iex2DObj::iex2DObj( char* filename )
{
	//	情報初期化
	width = height = 0;
	lpSurface = NULL;

	//	テクスチャ読み込み
	lpTexture = iexTexture::Load(filename);
	if( lpTexture == NULL ) return;

	//	サイズ保存
	D3DSURFACE_DESC	sd;
	lpTexture->GetLevelDesc( 0, &sd );
	width  = sd.Width;
	height = sd.Height;
	//	メインサーフェス取得
	lpTexture->GetSurfaceLevel( 0, &lpSurface );
}

iex2DObj::iex2DObj( DWORD width, DWORD height, BYTE flag )
{
	//	情報初期化
	this->width = this->height = 0;
	lpSurface = NULL;

	D3DFORMAT	fmt = D3DFMT_R8G8B8;
	DWORD		usage = 0;
	D3DPOOL		pool = D3DPOOL_MANAGED;

	switch( flag ){
	case IEX2D_RENDERTARGET:	//	レンダー可能
					usage = D3DUSAGE_RENDERTARGET;
					fmt = iexSystem::ScreenFormat;
					pool = D3DPOOL_DEFAULT;
					break;
	case IEX2D_FLOAT2:	//	レンダー可能
					usage = D3DUSAGE_RENDERTARGET;
					fmt = D3DFMT_G32R32F;
					pool = D3DPOOL_DEFAULT;
					break;
	case IEX2D_FLOAT:	//	レンダー可能
					usage = D3DUSAGE_RENDERTARGET;
					fmt = D3DFMT_R32F;
					pool = D3DPOOL_DEFAULT;
					break;

	case IEX2D_USEALPHA:		//	透明度付
					fmt = D3DFMT_A8R8G8B8;
					break;
	case IEX2D_SYSTEMMEM:
					fmt = iexSystem::ScreenFormat;
					pool = D3DPOOL_SYSTEMMEM;
					break;
	}
	dwFlags= 0;
	//	テクスチャ作成
	D3DXCreateTexture( iexSystem::Device, width, height, 0, usage, fmt, pool, &lpTexture );
	if( lpTexture == NULL ) return;

	//	サイズ保存
	D3DSURFACE_DESC	sd;
	lpTexture->GetLevelDesc( 0, &sd );
	this->width  = sd.Width;
	this->height = sd.Height;
	//	メインサーフェス取得
	lpTexture->GetSurfaceLevel( 0, &lpSurface );
}

//*****************************************************************************
//	レンダーターゲット設定
//*****************************************************************************
void	iex2DObj::RenderTarget( int index )
{
	iexSystem::Device->SetRenderTarget( index,lpSurface );
}


//*****************************************************************************
//	レンダリング
//*****************************************************************************

void iex2DObj::Render()
{
	TLVERTEX	v[4];
	//	全画面設定
	v[0].sx = v[2].sx = 0;
	v[1].sx = v[3].sx = iexSystem::ScreenWidth - 0.5f;
	v[0].sy = v[1].sy = 0;
	v[2].sy = v[3].sy = iexSystem::ScreenHeight - 0.5f;

	v[0].tu = v[2].tu = 0;
	v[1].tu = v[3].tu = 1;
	v[0].tv = v[1].tv = 0;
	v[2].tv = v[3].tv = 1;

	v[0].color = v[1].color = v[2].color = v[3].color = 0xFFFFFFFF;
	v[0].sz    = v[1].sz    = v[2].sz    = v[3].sz    = 0;
	v[0].rhw   = v[1].rhw   = v[2].rhw   = v[3].rhw   = 1.0f;

	iexPolygon::Render2D( v, 2, this, RS_COPY );
}

void iex2DObj::Render( iexShader* shader, char* tech )
{
	TLVERTEX	v[4];
	//	全画面設定
	v[0].sx = v[2].sx = 0;
	v[1].sx = v[3].sx = iexSystem::ScreenWidth - 0.5f;
	v[0].sy = v[1].sy = 0;
	v[2].sy = v[3].sy = iexSystem::ScreenHeight - 0.5f;

	v[0].tu = v[2].tu = 0;
	v[1].tu = v[3].tu = 1;
	v[0].tv = v[1].tv = 0;
	v[2].tv = v[3].tv = 1;

	v[0].color = v[1].color = v[2].color = v[3].color = 0xFFFFFFFF;
	v[0].sz    = v[1].sz    = v[2].sz    = v[3].sz    = 0;
	v[0].rhw   = v[1].rhw   = v[2].rhw   = v[3].rhw   = 1.0f;

	iexPolygon::Render2D( v, 2, this, shader, tech );
}

void iex2DObj::Render( int DstX, int DstY, int DstW, int DstH, int SrcX, int SrcY, int width, int height,float angle,
	iexShader* shader, char* tech,DWORD dwFlags, DWORD color, float z)
{
	TLVERTEX	v[4];
	v[0].sx = v[2].sx = (float)DstX;
	v[1].sx = v[3].sx = (float)(DstX+DstW)-0.5f;
	v[0].sy = v[1].sy = (float)DstY;
	v[2].sy = v[3].sy = (float)(DstY+DstH)-0.5f;


	TLVERTEX center;
	center.sx = (float)(DstX + DstW / 2);
	center.sy = (float)(DstY + DstH / 2);
	center.sz = .0;
	
	v[0] = rotationZ(v[0], angle, center);
	v[1] = rotationZ(v[1], angle, center);
	v[2] = rotationZ(v[2], angle, center);
	v[3] = rotationZ(v[3], angle, center);

	v[0].tu = v[2].tu = (float)(SrcX+0.5f)/(float)this->width;
	v[1].tu = v[3].tu = (float)(SrcX+width)/(float)this->width;
	v[0].tv = v[1].tv = (float)(SrcY+0.5f)/(float)this->height;
	v[2].tv = v[3].tv = (float)(SrcY+height)/(float)this->height;

	v[0].color = v[1].color = v[2].color = v[3].color = color;
	v[0].sz    = v[1].sz    = v[2].sz    = v[3].sz    = z;
	v[0].rhw   = v[1].rhw   = v[2].rhw   = v[3].rhw   = 1.0f;

	iexPolygon::Render2D(v, 2, this, shader, tech);
}

void iex2DObj::Render(int DstX, int DstY, int DstW, int DstH, int SrcX, int SrcY, int width, int height, float angle, DWORD dwFlags, DWORD color, float z)
{
	TLVERTEX	v[4];
	v[0].sx = v[2].sx = (float)DstX;
	v[1].sx = v[3].sx = (float)(DstX + DstW) - 0.5f;
	v[0].sy = v[1].sy = (float)DstY;
	v[2].sy = v[3].sy = (float)(DstY + DstH) - 0.5f;

	TLVERTEX center;
	center.sx = (float)(DstX + DstW / 2);
	center.sy = (float)(DstY + DstH / 2);
	center.sz = .0;


	v[0] = rotationZ(v[0], angle, center);
	v[1] = rotationZ(v[1], angle, center);
	v[2] = rotationZ(v[2], angle, center);
	v[3] = rotationZ(v[3], angle, center);

	v[0].tu = v[2].tu = (float)(SrcX + 0.5f) / (float)this->width;
	v[1].tu = v[3].tu = (float)(SrcX + width) / (float)this->width;
	v[0].tv = v[1].tv = (float)(SrcY + 0.5f) / (float)this->height;
	v[2].tv = v[3].tv = (float)(SrcY + height) / (float)this->height;

	v[0].color = v[1].color = v[2].color = v[3].color = color;
	v[0].sz = v[1].sz = v[2].sz = v[3].sz = z;
	v[0].rhw = v[1].rhw = v[2].rhw = v[3].rhw = 1.0f;

	iexPolygon::Render2D(v, 2, this, dwFlags);
}


//*****************************************************************************
//	Render with Rotation
//*****************************************************************************
void iex2DObj::customRender(float DstX, float DstY, float DstW, float DstH, float SrcX, float SrcY, float width, float height,
	float angle, bool centRotate, float rotatePosX, float rotatePosY, DWORD dwFlags, DWORD color, bool Reflect,int scaleMode, float z, iexShader* shader, char* tech)
{
	switch (scaleMode)
	{
		case CENTER:
			DstX += (width - DstW) / 2.0f;
			DstY += (height - DstH) / 2.0f;
			break;
		case LEFTTOP:
			break;
		case TOPCENTER:
			DstX += (width - DstW) / 2.0f;
			break;
		case RIGHTTOP:
			DstX += (width - DstW);
			break;
		case RIGHTCENTER:
			DstX += (width - DstW);
			DstY += (height - DstH) / 2.0f;
			break;
		case RIGHTBOTTOM:
			DstX += (width - DstW);
			DstY += (height - DstH);
			break;
		case BOTTOMCENTER:
			DstX += (width - DstW) / 2.0f;
			DstY += (height - DstH);
			break;
		case LEFTBOTTOM:
			DstY += (height - DstH);
			break;
		case LEFTCENTER:
			DstY += (height - DstH) / 2.0f;
			break;
		default:
			break;
	}


	TLVERTEX	v[4];
	v[0].sx = v[2].sx = (float)DstX;
	v[1].sx = v[3].sx = (float)(DstX+DstW)-0.5f;
	v[0].sy = v[1].sy = (float)DstY;
	v[2].sy = v[3].sy = (float)(DstY+DstH)-0.5f;


	TLVERTEX center;
	center.sx = centRotate ? (DstX+DstW/2) : rotatePosX;
	center.sy = centRotate ? (DstY+DstH/2) : rotatePosY;
	center.sz = .0;

	if (angle != 0) {
		float sin = sinf(angle * 0.01745f);
		float cos = cosf(angle * 0.01745f);
	
		v[0] = rotationZ(v[0], sin, cos, center);
		v[1] = rotationZ(v[1], sin, cos , center);
		v[2] = rotationZ(v[2], sin, cos , center);
		v[3] = rotationZ(v[3], sin, cos , center);
	}
	if ( !Reflect )
	{
 
		v[0].tu = v[2].tu = (float)(SrcX+0.5f)/(float)this->width;
		v[1].tu = v[3].tu = (float)(SrcX+width)/(float)this->width;
	}
	else
	{
		v[1].tu = v[3].tu = (float)(SrcX+0.5f)/(float)this->width;
		v[0].tu = v[2].tu = (float)(SrcX+width)/(float)this->width;
	}
	v[0].tv = v[1].tv = (float)(SrcY+0.5f)/(float)this->height;
	v[2].tv = v[3].tv = (float)(SrcY+height)/(float)this->height;

	v[0].color = v[1].color = v[2].color = v[3].color = color;
	v[0].sz = v[1].sz = v[2].sz = v[3].sz = z;
	v[0].rhw = v[1].rhw = v[2].rhw = v[3].rhw = 1.0f;

	if (shader)	iexPolygon::Render2D(v, 2, this, shader, tech);
	else		iexPolygon::Render2D(v,2,this,dwFlags);
}

//void iex2DObj::Render( int DstX, int DstY, int DstW, int DstH, int SrcX, int SrcY, int width, int height, iexShader* shader, char* tech, DWORD color, float z )
//{
//	TLVERTEX	v[4];
//	v[0].sx = v[2].sx = (float)DstX;
//	v[1].sx = v[3].sx = (float)(DstX+DstW)-0.5f;
//	v[0].sy = v[1].sy = (float)DstY;
//	v[2].sy = v[3].sy = (float)(DstY+DstH)-0.5f;
//
//	v[0].tu = v[2].tu = (float)(SrcX+0.5f)/(float)this->width;
//	v[1].tu = v[3].tu = (float)(SrcX+width)/(float)this->width;
//	v[0].tv = v[1].tv = (float)(SrcY+0.5f)/(float)this->height;
//	v[2].tv = v[3].tv = (float)(SrcY+height)/(float)this->height;
//
//	v[0].color = v[1].color = v[2].color = v[3].color = color;
//	v[0].sz    = v[1].sz    = v[2].sz    = v[3].sz    = z;
//	v[0].rhw   = v[1].rhw   = v[2].rhw   = v[3].rhw   = 1.0f;
//
//	iexPolygon::Render2D( v, 2, this, shader, tech );
//}

//**************************************************************************************************
//
//		過去のIEXとの互換用
//
//**************************************************************************************************

//void	IEX_Render2DObject( int DstX, int DstY, int DstW, int DstH, iex2DObj* lpObj, int SrcX, int SrcY, int width, int height, DWORD dwFlags, DWORD color )
//{
//	if( !lpObj ) return;
//	lpObj->Render(DstX, DstY, DstW, DstH, SrcX, SrcY, width, height, dwFlags, color );
//}

TLVERTEX iex2DObj::rotationZ(TLVERTEX _coord,float sin ,float cos, TLVERTEX _center)
{
	TLVERTEX P, Pr;
	P.sx = _coord.sx - _center.sx;
	P.sy = _coord.sy - _center.sy;
	P.sz = 0/*_coord.z - _center.z*/;
	// rotation
	Pr.sx = P.sx*cos - P.sy*sin + _center.sx;
	Pr.sy = P.sy*cos + P.sx*sin + _center.sy;
	Pr.sz = 0;
	return Pr;
}

TLVERTEX iex2DObj::rotationZ(TLVERTEX _coord, float _angle, TLVERTEX _center)
{
	TLVERTEX P, Pr;
	float angle;
	angle = _angle * D3DX_PI / 180;
	P.sx = _coord.sx - _center.sx;
	P.sy = _coord.sy - _center.sy;
	P.sz = 0/*_coord.z - _center.z*/;
	// rotation
	Pr.sx = P.sx*cosf(angle) - P.sy*sinf(angle) + _center.sx;
	Pr.sy = P.sy*cosf(angle) + P.sx*sinf(angle) + _center.sy;
	Pr.sz = 0;
	return Pr;
}


iex2DObj* spr_data::obj[spr_data::MAX_TEXTURE];

void spr_data::Load(IMG_DATA* data) {
	Release();
	for (int no = 0; no < MAX_TEXTURE; no++) {
		if (data[no].no <= -1)break;
		obj[data[no].no] = new iex2DObj(data[no].name);
	}
}
void spr_data::Release() {
	for (int no = 0; no < MAX_TEXTURE; no++) {
		if (obj[no]) {
			delete obj[no];
			obj[no] = NULL;
		}
	}
}
void spr_data::Render(V2 pos ,SPR_DATA* data) {
	obj[data->no]->Render((int)pos.x + data->ofsx, (int)pos.y + data->ofsy, data->dw, data->dh, data->dx, data->dy, data->sx,data->sy, .0f,RS_COPY, 0xFFFFFFFF, .0f);
}
void spr_data::Render(V2 pos, SPR_DATA* data,UINT color,float angle) {
	obj[data->no]->Render((int)pos.x + data->ofsx, (int)pos.y + data->ofsy, data->dw, data->dh, data->dx, data->dy, data->sx, data->sy,angle, RS_COPY, color);
}
void spr_data::Render(V2 pos,SPR_DATA* data,UINT color,float angle,iexShader* shader,char* tech) {
	obj[data->no]->Render((int)pos.x + data->ofsx, (int)pos.y + data->ofsy, data->dw, data->dh, data->dx, data->dy, data->sx,data->sy,angle,shader,tech,RS_COPY,color);
}
void spr_data::Render(V2 pos, SPR_DATA* data, CUSTOM* custom ,D3DCOLOR argb, iexShader* shader, char* tech) {
	obj[data->no]->customRender(
		pos.x+data->ofsx + custom->ef_ofsX,pos.y + data->ofsy + custom->ef_ofsY,
		custom->scaleX * data->dw, custom->scaleY * data->dh,
		data->dx,data->dy,
		data->sx,data->sy,
		custom->angle,custom->centRotate,custom->centX, custom->centY,RS_ALPH,
		argb,custom->reflectX, custom->scaleMode,0.0f, shader,tech);

}
