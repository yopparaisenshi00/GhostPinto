#include	"iExtreme.h"

//**************************************************************************************************
//
//		�|���S���`��	
//
//**************************************************************************************************

//*****************************************************************************
//	�R�c�|���S��
//*****************************************************************************
//------------------------------------------------------
//		�Œ�@�\��	
//------------------------------------------------------
void	iexPolygon::Render3D( LPLVERTEX lpVertex, int Num, iex2DObj* lpObj, DWORD dwFlags )
{
	LPDEVICE	lpDevice = iexSystem::Device;
	//	���[���h�s��ݒ�
	Matrix	mat( 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 );
	lpDevice->SetTransform( D3DTS_WORLD, (D3DMATRIX*)&mat );

	//	�����_�[�X�e�[�g�X�V
	if( lpObj ) iexRenderState::Set( dwFlags & 0x0F, NULL, lpObj->GetTexture() );
	 else		iexRenderState::Set( dwFlags & 0x0F, NULL, NULL );

	lpDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	 //	�����_�����O
	lpDevice->SetFVF(D3DFVF_LVERTEX);
	lpDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, Num, lpVertex, sizeof(LVERTEX) );

	lpDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//------------------------------------------------------
//		�V�F�[�_�[��
//------------------------------------------------------
void	iexPolygon::Render3D( LPLVERTEX lpVertex, int Num, iex2DObj* lpObj, iexShader* shader, char* name )
{
	LPDEVICE	lpDevice = iexSystem::Device;
	//	�V�F�[�_�[�̓K�p
	DWORD pass = shader->Begine(name);

	// ���[�J��-�ˉe�ϊ��s��
	Matrix m = matView * matProjection;
	shader->SetMatrix( &m );

	lpDevice->SetFVF(D3DFVF_LVERTEX);
	if( lpObj ) shader->SetTexture( lpObj->GetTexture() );

	for( DWORD p=0 ; p<pass ; p++ )
	{
		shader->BeginePass(p);
		shader->CommitChanges();
		//	�����_�����O
		lpDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, Num, lpVertex, sizeof(LVERTEX) );
		shader->EndPass();
	}
	shader->End();
}

//*****************************************************************************
//	�Q�c�|���S��
//*****************************************************************************
//------------------------------------------------------
//		�Œ�@�\��	
//------------------------------------------------------
void	iexPolygon::Render2D( LPTLVERTEX v, int Num, iex2DObj* lpObj, DWORD dwFlags )
{
	LPDEVICE	lpDevice = iexSystem::Device;

	if( lpObj ) iexRenderState::Set( dwFlags & 0x0F, NULL, lpObj->GetTexture() );
	 else iexRenderState::Set( dwFlags & 0x0F, NULL, NULL );

	//	�����_�����O	
	lpDevice->SetFVF(D3DFVF_TLVERTEX);
	lpDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, Num, v, sizeof(TLVERTEX) );
}

//------------------------------------------------------
//		�V�F�[�_�[��
//------------------------------------------------------
void	iexPolygon::Render2D( LPTLVERTEX v, int Num, iex2DObj* lpObj, iexShader* shader, char* name )
{
	LPDEVICE	lpDevice = iexSystem::Device;
	//	�V�F�[�_�[�̓K�p
	DWORD pass = shader->Begine(name);

	lpDevice->SetFVF(D3DFVF_TLVERTEX);
	if( lpObj ) shader->SetTexture( lpObj->GetTexture() );

	for( DWORD p=0 ; p<pass ; p++ )
	{
		shader->BeginePass(p);
		shader->CommitChanges();
		//	�����_�����O
		lpDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, Num, v, sizeof(TLVERTEX) );
		shader->EndPass();
	}
	shader->End();
}

//*****************************************************************************
//	��`�`��
//*****************************************************************************
//------------------------------------------------------
//		�Œ�@�\��	
//------------------------------------------------------
void	iexPolygon::Rect( int DstX, int DstY, int DstW, int DstH, DWORD dwFlags, DWORD color, float z )
{
	TLVERTEX	v[4];

	v[0].sx = v[2].sx = (FLOAT)DstX;
	v[1].sx = v[3].sx = (FLOAT)(DstX+DstW);

	v[0].sy = v[1].sy = (FLOAT)DstY;
	v[2].sy = v[3].sy = (FLOAT)(DstY+DstH);

	v[0].sz    = v[1].sz    = v[2].sz    = v[3].sz    = z;
	v[0].color = v[1].color = v[2].color = v[3].color = color;
	v[0].rhw   = v[1].rhw   = v[2].rhw   = v[3].rhw   = 1.0f;

	Render2D( v, 2, NULL, dwFlags );
} 

//------------------------------------------------------
//		�V�F�[�_�[��
//------------------------------------------------------
void	iexPolygon::Rect( int DstX, int DstY, int DstW, int DstH, iexShader* shader, char* name, DWORD color, float z )
{
	TLVERTEX	v[4];

	v[0].sx = v[2].sx = (FLOAT)DstX;
	v[1].sx = v[3].sx = (FLOAT)(DstX+DstW);

	v[0].sy = v[1].sy = (FLOAT)DstY;
	v[2].sy = v[3].sy = (FLOAT)(DstY+DstH);

	v[0].sz    = v[1].sz    = v[2].sz    = v[3].sz    = z;
	v[0].color = v[1].color = v[2].color = v[3].color = color;
	v[0].rhw   = v[1].rhw   = v[2].rhw   = v[3].rhw   = 1.0f;

	Render2D( v, 2, NULL, shader, name );
}

//**************************************************************************************************
//
//		�ߋ���IEX�Ƃ̌݊��p
//
//**************************************************************************************************

//*****************************************************************************
//
//		�R�c�|���S���֘A
//
//*****************************************************************************

//
//		�R�c�|���S�������_�����O
//
void	IEX_Render3DPolygon( LPVERTEX v, iex2DObj* lpObj, DWORD dwFlags, DWORD color )
{
	LVERTEX	workV[4];
	
	for( int i=0 ; i<4 ; i++ )
	{
		workV[i].x = v[i].x;
		workV[i].y = v[i].y;
		workV[i].z = v[i].z;
		workV[i].tu = v[i].tu;
		workV[i].tv = v[i].tv;
		workV[i].color = color;
	}
	iexPolygon::Render3D( workV, 2, lpObj, dwFlags );
}

void	IEX_Render3DPolygon( Vector3 p[4], float tu[4], float tv[4], iex2DObj* lpObj, DWORD dwFlags, DWORD color )
{
	LVERTEX	workV[4];

	for( int i=0 ; i<4 ; i++ )
	{
		workV[i].x = p[i].x;
		workV[i].y = p[i].y;
		workV[i].z = p[i].z;
		workV[i].tu = tu[i];
		workV[i].tv = tv[i];
		workV[i].color = color;
	}
	iexPolygon::Render3D( workV, 2, lpObj, dwFlags );
}

//
//		�X�g���b�v�|���S�������_�����O
//
void	IEX_RenderStripPolygon( LPLVERTEX lpVertex, int StripNum, iex2DObj* lpObj, DWORD dwFlags )
{
	iexPolygon::Render3D( lpVertex, StripNum, lpObj, dwFlags );
}


//
//		�Q�c�|���S�������_�����O
//

void	IEX_Render2DPolygon( LPTLVERTEX v, int NumPoly, iex2DObj* lpObj, DWORD dwFlags )
{
	iexPolygon::Render2D( v, NumPoly, lpObj, dwFlags );
}

void	IEX_Render2DPolygon( float* vx, float* vy, float* tu, float* tv, int NumPoly, iex2DObj* lpObj, DWORD dwFlags, DWORD* color )
{
	int		i;
	TLVERTEX	v[34];

	if( NumPoly > 32 ) NumPoly = 32;

	for( i=0 ; i<NumPoly+2 ; i++ ){
		//	���_���ݒ�
		v[i].sx = vx[i];
		v[i].sy = vy[i];
		v[i].sz = .0f;
		v[i].tu = tu[i];
		v[i].tv = tv[i];
		v[i].color = color[i];
		v[i].rhw   = 1.0f;
	}
	iexPolygon::Render2D( v, NumPoly, lpObj, dwFlags );
} 

void	IEX_Render2DPolygon( float* vx, float* vy, float* tu, float* tv, int NumPoly, iex2DObj* lpObj, DWORD dwFlags, DWORD color )
{
	int		i;
	TLVERTEX	v[34];

	if( NumPoly > 32 ) NumPoly = 32;

	for( i=0 ; i<NumPoly+2 ; i++ ){
		//	���_���ݒ�
		v[i].sx = vx[i];
		v[i].sy = vy[i];
		v[i].sz = .0f;
		v[i].tu = tu[i];
		v[i].tv = tv[i];
		v[i].color = color;
		v[i].rhw   = 1.0f;
	}
	iexPolygon::Render2D( v, NumPoly, lpObj, dwFlags );
} 

//
//		��`�`��
//

void	IEX_DrawRectZ( int DstX, int DstY, int DstW, int DstH, float z, DWORD dwFlags, DWORD color )
{
	iexPolygon::Rect( DstX, DstY, DstW, DstH, dwFlags, color, z );
} 

void	IEX_DrawRect( int DstX, int DstY, int DstW, int DstH, DWORD dwFlags, DWORD color )
{
	iexPolygon::Rect( DstX, DstY, DstW, DstH, dwFlags, color, .0f );
}

