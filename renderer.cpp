//=============================================================================
//
// 儗儞僟儕儞僌張棟 [renderer.cpp]
// Author : 
//
//=============================================================================
#include "renderer.h"
#include "camera.h"



//*********************************************************
// 峔憿懱
//*********************************************************
// 儅僥儕傾儖梡掕悢僶僢僼傽峔憿懱
struct MATERIAL_CBUFFER
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	int			noTexSampling;
	int			PolyLine;
	float		Dummy;				// 16byte嫬奅梡
};

// 儔僀僩梡僼儔僌峔憿懱
struct LIGHTFLAGS
{
	int			Type;		//儔僀僩僞僀僾乮enum LIGHT_TYPE乯
	int         OnOff;		//儔僀僩偺僆儞or僆僼僗僀僢僠
	int			Dummy[2];
};

// 儔僀僩梡掕悢僶僢僼傽峔憿懱
struct LIGHT_CBUFFER
{
	D3DXVECTOR4	Direction[LIGHT_MAX];	// 儔僀僩偺曽岦
	D3DXVECTOR4	Position[LIGHT_MAX];	// 儔僀僩偺埵抲
	D3DXCOLOR	Diffuse[LIGHT_MAX];		// 奼嶶岝偺怓
	D3DXCOLOR	Ambient[LIGHT_MAX];		// 娐嫬岝偺怓
	D3DXCOLOR	Specular[LIGHT_MAX];
	D3DXVECTOR4	Attenuation[LIGHT_MAX];	// 尭悐棪
	LIGHTFLAGS	Flags[LIGHT_MAX];		// 儔僀僩庬暿
	int			Enable;					// 儔僀僥傿儞僌桳岠丒柍岠僼儔僌
	int			Dummy[3];				// 16byte嫬奅梡
};

struct CameraBufferType
{
	D3DXVECTOR3 cameraPosition;
	float padding;  // 用于确保结构体大小为16字节
};

//*****************************************************************************
// 僌儘乕僶儖曄悢:
//*****************************************************************************
D3D_FEATURE_LEVEL       g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           g_D3DDevice = NULL;
ID3D11DeviceContext*    g_ImmediateContext = NULL;
IDXGISwapChain*         g_SwapChain = NULL;
ID3D11RenderTargetView* g_RenderTargetView = NULL;
ID3D11DepthStencilView* g_DepthStencilView = NULL;

ID3D11VertexShader*     g_VertexShader = NULL;
ID3D11PixelShader*      g_PixelShader = NULL;
ID3D11InputLayout*      g_VertexLayout = NULL;
ID3D11Buffer*			g_WorldBuffer = NULL;
ID3D11Buffer*			g_ViewBuffer = NULL;
ID3D11Buffer*			g_ProjectionBuffer = NULL;
ID3D11Buffer*			g_CameraPosBuffer = NULL;
ID3D11Buffer*			g_MaterialBuffer = NULL;
ID3D11Buffer*			g_LightBuffer = NULL;
ID3D11Buffer*			g_InverseBuffer = NULL;

ID3D11DepthStencilState* g_DepthStateEnable;
ID3D11DepthStencilState* g_DepthStateDisable;

ID3D11BlendState*		g_BlendStateNone;
ID3D11BlendState*		g_BlendStateAlphaBlend;
ID3D11BlendState*		g_BlendStateAdd;
ID3D11BlendState*		g_BlendStateSubtract;
BLEND_MODE				g_BlendStateParam;

ID3D11RasterizerState*	g_RasterStateCullOff;
ID3D11RasterizerState*	g_RasterStateCullCW;
ID3D11RasterizerState*	g_RasterStateCullCCW;

static D3DXCOLOR		g_BorderColor;

static MATERIAL_CBUFFER	g_Material;
static LIGHT_CBUFFER	g_Light;


//*****************************************************************************
// 僾儘僩僞僀僾愰尵
//*****************************************************************************
static void SetLightBuffer(void);


ID3D11Device* GetDevice( void )
{
	return g_D3DDevice;
}


ID3D11DeviceContext* GetDeviceContext( void )
{
	return g_ImmediateContext;
}


void SetDepthEnable( bool Enable )
{
	if( Enable )
		g_ImmediateContext->OMSetDepthStencilState( g_DepthStateEnable, NULL );
	else
		g_ImmediateContext->OMSetDepthStencilState( g_DepthStateDisable, NULL );

}

void SetBlendState(BLEND_MODE bm)
{
	g_BlendStateParam = bm;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	switch (g_BlendStateParam)
	{
	case BLEND_MODE_NONE:
		g_ImmediateContext->OMSetBlendState(g_BlendStateNone, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ALPHABLEND:
		g_ImmediateContext->OMSetBlendState(g_BlendStateAlphaBlend, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ADD:
		g_ImmediateContext->OMSetBlendState(g_BlendStateAdd, blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_SUBTRACT:
		g_ImmediateContext->OMSetBlendState(g_BlendStateSubtract, blendFactor, 0xffffffff);
		break;
	}
}

void SetCullingMode(CULL_MODE cm)
{
	switch (cm)
	{
	case CULL_MODE_NONE:
		g_ImmediateContext->RSSetState(g_RasterStateCullOff);
		break;
	case CULL_MODE_FRONT:
		g_ImmediateContext->RSSetState(g_RasterStateCullCW);
		break;
	case CULL_MODE_BACK:
		g_ImmediateContext->RSSetState(g_RasterStateCullCCW);
		break;
	}
}

void SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am)
{
	// 僒儞僾儔乕僗僥乕僩愝掕
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));

	switch (fm)
	{
	case FILTER_MODE_POINT:
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	case FILTER_MODE_LINEAR:
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case FILTER_MODE_ANISOTROPIC:
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		break;
	}

	//僥僋僗僠儍偺傾僪儗僢僔儞僌儌乕僪偺愝掕		
	switch (am)
	{
	case ADDRESS_MODE_WRAP:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	case ADDRESS_MODE_MIRROR:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
		break;
	case ADDRESS_MODE_CLAMP:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	case ADDRESS_MODE_BORDER:
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		break;
	}

	samplerDesc.BorderColor[0] = g_BorderColor.r;
	samplerDesc.BorderColor[1] = g_BorderColor.g;
	samplerDesc.BorderColor[2] = g_BorderColor.b;
	samplerDesc.BorderColor[3] = g_BorderColor.a;

	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	g_D3DDevice->CreateSamplerState(&samplerDesc, &samplerState);

	g_ImmediateContext->PSSetSamplers(0, 1, &samplerState);

	samplerState->Release();
	samplerState = NULL;
}

void SetSamplerBorderColor(D3DXCOLOR col)
{
	g_BorderColor = col;
}

void SetAlphaTestEnable(BOOL flag)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	if(flag)
		blendDesc.AlphaToCoverageEnable = TRUE;
	else
		blendDesc.AlphaToCoverageEnable = FALSE;

	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	switch(g_BlendStateParam)
	{
	case BLEND_MODE_NONE:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	case BLEND_MODE_ALPHABLEND:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	case BLEND_MODE_ADD:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	case BLEND_MODE_SUBTRACT:
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		break;
	}

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	g_D3DDevice->CreateBlendState(&blendDesc, &blendState);
	g_ImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	if (blendState != NULL)
		blendState->Release();
}


void SetWorldViewProjection2D( void )
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);
	GetDeviceContext()->UpdateSubresource(g_WorldBuffer, 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	GetDeviceContext()->UpdateSubresource(g_ViewBuffer, 0, NULL, &view, 0, 0);

	D3DXMATRIX worldViewProjection;
	D3DXMatrixOrthoOffCenterLH(&worldViewProjection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);
	GetDeviceContext()->UpdateSubresource( g_ProjectionBuffer, 0, NULL, &worldViewProjection, 0, 0 );
}


void SetWorldMatrix( D3DXMATRIX *WorldMatrix )
{
	D3DXMATRIX world;
	world = *WorldMatrix;
	D3DXMatrixTranspose(&world, &world);

	GetDeviceContext()->UpdateSubresource( g_WorldBuffer, 0, NULL, &world, 0, 0 );
}


void SetViewMatrix( D3DXMATRIX *ViewMatrix )
{
	D3DXMATRIX view;
	view = *ViewMatrix;
	D3DXMatrixTranspose(&view, &view);

	GetDeviceContext()->UpdateSubresource(g_ViewBuffer, 0, NULL, &view, 0, 0);
}

void SetProjectionMatrix( D3DXMATRIX *ProjectionMatrix )
{
	D3DXMATRIX projection;
	projection = *ProjectionMatrix;
	D3DXMatrixTranspose(&projection, &projection);

	GetDeviceContext()->UpdateSubresource(g_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M)
{
	DirectX::XMMATRIX A = M;
	A.r[3] = DirectX::XMVectorSet(0.0,0.0,0.0,1.0);
	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
	if (!DirectX::XMVector3Equal(det, DirectX::XMVectorZero()))
	{
		// 矩阵可逆，可以安全地计算逆矩阵
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, A)); 
	}
	else
	{
		return DirectX::XMMatrixIdentity();
	}
}

void SetInverseMatrix(DirectX::XMMATRIX& worldMtx )
{
	DirectX::XMMATRIX inverse = InverseTranspose(worldMtx);
	GetDeviceContext()->UpdateSubresource(g_InverseBuffer, 0, NULL, &inverse, 0, 0);
}

void SetMaterial( MATERIAL Material )
{
	g_Material.Diffuse = Material.Diffuse;
	g_Material.Ambient = Material.Ambient;
	g_Material.Specular = Material.Specular;
	g_Material.Emission = Material.Emission;
	g_Material.Shininess = Material.Shininess;
	g_Material.noTexSampling = Material.noTexSampling;
	g_Material.PolyLine = Material.Polyline;

	GetDeviceContext()->UpdateSubresource(g_MaterialBuffer, 0, NULL, &g_Material, 0, 0);
}

void SetLightBuffer(void)
{
	GetDeviceContext()->UpdateSubresource(g_LightBuffer, 0, NULL, &g_Light, 0, 0);
}

void SetLightEnable(BOOL flag)
{
	// 僼儔僌傪峏怴偡傞
	g_Light.Enable = flag;

	SetLightBuffer();
}

void SetLight(int index, LIGHT *pLight)
{
	//斖埻僄儔乕
	if (index > 9 || index < 0) return;

	g_Light.Position[index] = D3DXVECTOR4(pLight->Position.x, pLight->Position.y, pLight->Position.z, 0.0f);
	g_Light.Direction[index] = D3DXVECTOR4(pLight->Direction.x, pLight->Direction.y, pLight->Direction.z, 0.0f);
	g_Light.Specular[index]=pLight->Specular;
	g_Light.Diffuse[index] = pLight->Diffuse;
	g_Light.Ambient[index] = pLight->Ambient;
	g_Light.Flags[index].Type = pLight->Type;
	g_Light.Flags[index].OnOff = pLight->Enable;
	g_Light.Attenuation[index].x = pLight->Attenuation;

	SetLightBuffer();
}

void UpdateCameraPos(D3DXVECTOR3 pos)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT hr = GetDeviceContext()->Map(g_CameraPosBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	if (SUCCEEDED(hr))
	{
		CameraBufferType* camerapos = (CameraBufferType*)msr.pData;
		camerapos->cameraPosition = pos;
		GetDeviceContext()->Unmap(g_CameraPosBuffer, 0);
	}

	
}

//=============================================================================
// 弶婜壔張棟
//=============================================================================
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// 僨僶僀僗丄僗儚僢僾僠僃乕儞丄僐儞僥僉僗僩惗惉
	DWORD deviceFlags = 0;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	//僨僶僢僌暥帤弌椡梡愝掕
#if defined(_DEBUG) && defined(DEBUG_DISP_TEXTOUT)
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										deviceFlags,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&sd,
										&g_SwapChain,
										&g_D3DDevice,
										&g_FeatureLevel,
										&g_ImmediateContext );
	if( FAILED( hr ) )
		return hr;

	//僨僶僢僌暥帤弌椡梡愝掕
#if defined(_DEBUG) && defined(DEBUG_DISP_TEXTOUT)
	hr = g_SwapChain->ResizeBuffers(0, SCREEN_WIDTH, SCREEN_HEIGHT, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE);
	if (FAILED(hr))
		return hr;
#endif

	// 儗儞僟乕僞乕僎僢僩價儏乕惗惉丄愝掕
	ID3D11Texture2D* pBackBuffer = NULL;
	g_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	g_D3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_RenderTargetView );
	pBackBuffer->Release();



	//僗僥儞僔儖梡僥僋僗僠儍乕嶌惉
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory( &td, sizeof(td) );
	td.Width			= sd.BufferDesc.Width;
	td.Height			= sd.BufferDesc.Height;
	td.MipLevels		= 1;
	td.ArraySize		= 1;
	td.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc		= sd.SampleDesc;
	td.Usage			= D3D11_USAGE_DEFAULT;
	td.BindFlags		= D3D11_BIND_DEPTH_STENCIL;
    td.CPUAccessFlags	= 0;
    td.MiscFlags		= 0;
	g_D3DDevice->CreateTexture2D( &td, NULL, &depthTexture );

	//僗僥儞僔儖僞乕僎僢僩嶌惉
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory( &dsvd, sizeof(dsvd) );
	dsvd.Format			= td.Format;
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags			= 0;
	g_D3DDevice->CreateDepthStencilView( depthTexture, &dsvd, &g_DepthStencilView );

	g_ImmediateContext->OMSetRenderTargets( 1, &g_RenderTargetView, g_DepthStencilView );


	// 價儏乕億乕僩愝掕
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_ImmediateContext->RSSetViewports( 1, &vp );



	// 儔僗僞儔僀僓僗僥乕僩愝掕
	D3D11_RASTERIZER_DESC rd; 
	ZeroMemory( &rd, sizeof( rd ) );
	rd.FillMode = D3D11_FILL_SOLID; 
	rd.CullMode = D3D11_CULL_NONE; 
	rd.DepthClipEnable = TRUE; 
	rd.MultisampleEnable = FALSE; 
	g_D3DDevice->CreateRasterizerState( &rd, &g_RasterStateCullOff );

	rd.CullMode = D3D11_CULL_FRONT;
	g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullCW);

	rd.CullMode = D3D11_CULL_BACK;
	g_D3DDevice->CreateRasterizerState(&rd, &g_RasterStateCullCCW);

	// 僇儕儞僌儌乕僪愝掕乮CCW乯
	SetCullingMode(CULL_MODE_BACK);




	// 僽儗儞僪僗僥乕僩愝掕
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( blendDesc ) );
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState( &blendDesc, &g_BlendStateAlphaBlend );

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateNone);

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateAdd);

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_D3DDevice->CreateBlendState(&blendDesc, &g_BlendStateSubtract);

	// 傾儖僼傽僽儗儞僪愝掕
	SetBlendState(BLEND_MODE_ALPHABLEND);


	// 怺搙僗僥儞僔儖僗僥乕僩愝掕
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	g_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &g_DepthStateEnable );//怺搙桳岠僗僥乕僩

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	g_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &g_DepthStateDisable );//怺搙柍岠僗僥乕僩

	g_ImmediateContext->OMSetDepthStencilState( g_DepthStateEnable, NULL );




	// 僒儞僾儔乕僗僥乕僩愝掕
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	g_BorderColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	samplerDesc.BorderColor[0] = g_BorderColor.r;//BORDER偺怓傪巜掕
	samplerDesc.BorderColor[1] = g_BorderColor.g;
	samplerDesc.BorderColor[2] = g_BorderColor.b;
	samplerDesc.BorderColor[3] = g_BorderColor.a;

	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	g_D3DDevice->CreateSamplerState( &samplerDesc, &samplerState );

	g_ImmediateContext->PSSetSamplers( 0, 1, &samplerState );
	samplerState->Release();


	// 捀揰僔僃乕僟僐儞僷僀儖丒惗惉
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;
	DWORD shFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG) && defined(DEBUG_SHADER)
	shFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", shFlag, 0, NULL, &pVSBlob, &pErrorBlob, NULL);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR );
	}

	g_D3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_VertexShader );

	// 擖椡儗僀傾僂僩惗惉
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE( layout );

	g_D3DDevice->CreateInputLayout( layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&g_VertexLayout );

	pVSBlob->Release();


	// 僺僋僙儖僔僃乕僟僐儞僷僀儖丒惗惉
	ID3DBlob* pPSBlob = NULL;
	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "PixelShaderPolygon", "ps_4_0", shFlag, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR );
	}

	g_D3DDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_PixelShader );
	
	pPSBlob->Release();


	// 掕悢僶僢僼傽惗惉
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	//儚乕儖僪儅僩儕僋僗
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_WorldBuffer);
	g_ImmediateContext->VSSetConstantBuffers(0, 1, &g_WorldBuffer);
	g_ImmediateContext->PSSetConstantBuffers(0, 1, &g_WorldBuffer);

	//價儏乕儅僩儕僋僗
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ViewBuffer);
	g_ImmediateContext->VSSetConstantBuffers(1, 1, &g_ViewBuffer);
	g_ImmediateContext->PSSetConstantBuffers(1, 1, &g_ViewBuffer);

	//僾儘僕僃僋僔儑儞儅僩儕僋僗
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ProjectionBuffer);
	g_ImmediateContext->VSSetConstantBuffers(2, 1, &g_ProjectionBuffer);
	g_ImmediateContext->PSSetConstantBuffers(2, 1, &g_ProjectionBuffer);

	//儅僥儕傾儖忣曬
	hBufferDesc.ByteWidth = sizeof(MATERIAL_CBUFFER);
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_MaterialBuffer);
	g_ImmediateContext->VSSetConstantBuffers(3, 1, &g_MaterialBuffer);
	g_ImmediateContext->PSSetConstantBuffers(3, 1, &g_MaterialBuffer);

	//儔僀僩忣曬
	hBufferDesc.ByteWidth = sizeof(LIGHT_CBUFFER);
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_LightBuffer);
	g_ImmediateContext->VSSetConstantBuffers(4, 1, &g_LightBuffer);
	g_ImmediateContext->PSSetConstantBuffers(4, 1, &g_LightBuffer);

	hBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_InverseBuffer);
	g_ImmediateContext->VSSetConstantBuffers(6, 1, &g_InverseBuffer);
	g_ImmediateContext->PSSetConstantBuffers(6, 1, &g_InverseBuffer);

	// 擖椡儗僀傾僂僩愝掕
	g_ImmediateContext->IASetInputLayout( g_VertexLayout );

	// 僔僃乕僟愝掕
	g_ImmediateContext->VSSetShader( g_VertexShader, NULL, 0 );
	g_ImmediateContext->PSSetShader( g_PixelShader, NULL, 0 );


	//儔僀僩弶婜壔
	ZeroMemory(&g_Light, sizeof(LIGHT_CBUFFER));
	g_Light.Direction[0] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);
	g_Light.Diffuse[0] = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	g_Light.Ambient[0] = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	SetLightBuffer();


	//儅僥儕傾儖弶婜壔
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(CameraBufferType);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	g_D3DDevice->CreateBuffer(&cbd, NULL, &g_CameraPosBuffer);
	g_ImmediateContext->VSSetConstantBuffers(5, 1, &g_CameraPosBuffer);
	g_ImmediateContext->PSSetConstantBuffers(5, 1, &g_CameraPosBuffer);

	return S_OK;
}




//=============================================================================
// 廔椆張棟
//=============================================================================
void UninitRenderer(void)
{
	// 僆僽僕僃僋僩夝曻
	if (g_DepthStateEnable)		g_DepthStateEnable->Release();
	if (g_DepthStateDisable)	g_DepthStateDisable->Release();

	if (g_BlendStateNone)		g_BlendStateNone->Release();
	if (g_BlendStateAlphaBlend) g_BlendStateAlphaBlend->Release();
	if (g_BlendStateAdd)		g_BlendStateAdd->Release();
	if (g_BlendStateSubtract)	g_BlendStateSubtract->Release();

	if (g_RasterStateCullOff)	g_RasterStateCullOff->Release();
	if (g_RasterStateCullCW)	g_RasterStateCullCW->Release();
	if (g_RasterStateCullCCW)	g_RasterStateCullCCW->Release();

	// 僆僽僕僃僋僩夝曻
	if (g_WorldBuffer)			g_WorldBuffer->Release();
	if (g_ViewBuffer)			g_ViewBuffer->Release();
	if (g_ProjectionBuffer)		g_ProjectionBuffer->Release();
	if( g_MaterialBuffer )		g_MaterialBuffer->Release();
	if( g_VertexLayout )		g_VertexLayout->Release();
	if( g_VertexShader )		g_VertexShader->Release();
	if( g_PixelShader )			g_PixelShader->Release();

	if( g_ImmediateContext )	g_ImmediateContext->ClearState();
	if( g_RenderTargetView )	g_RenderTargetView->Release();
	if( g_SwapChain )			g_SwapChain->Release();
	if( g_ImmediateContext )	g_ImmediateContext->Release();
	if( g_D3DDevice )			g_D3DDevice->Release();
	if (g_CameraPosBuffer)		g_CameraPosBuffer->Release();
	if (g_InverseBuffer)			g_InverseBuffer->Release();
}



//=============================================================================
// 僶僢僋僶僢僼傽僋儕傾
//=============================================================================
void Clear(void)
{
	// 僶僢僋僶僢僼傽僋儕傾
	float ClearColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	g_ImmediateContext->ClearRenderTargetView( g_RenderTargetView, ClearColor );
	g_ImmediateContext->ClearDepthStencilView( g_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


//=============================================================================
// 僾儗僛儞僩
//=============================================================================
void Present(void)
{
	g_SwapChain->Present( 0, 0 );
}


//=============================================================================
// 僨僶僢僌梡僥僉僗僩弌椡
//=============================================================================
void DebugTextOut(char* text, int x, int y)
{
#if defined(_DEBUG) && defined(DEBUG_DISP_TEXTOUT)
	HRESULT hr;

	//僶僢僋僶僢僼傽偐傜僒乕僼僃僗傪庢摼偡傞
	IDXGISurface1* pBackSurface = NULL;
	hr = g_SwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackSurface);

	if (SUCCEEDED(hr))
	{
		//庢摼偟偨僒乕僼僃僗偐傜僨僶僀僗僐儞僥僉僗僩傪庢摼偡傞
		HDC hdc;
		hr = pBackSurface->GetDC(FALSE, &hdc);

		if (SUCCEEDED(hr))
		{
			//暥帤怓傪敀偵曄峏
			SetTextColor(hdc, RGB(255, 255, 255));
			//攚宨傪摟柧偵曄峏
			SetBkMode(hdc, TRANSPARENT);

			RECT rect;
			rect.left = 0;
			rect.top = 0;
			rect.right = SCREEN_WIDTH;
			rect.bottom = SCREEN_HEIGHT;

			//僥僉僗僩弌椡
			DrawText(hdc, text, (int)strlen(text), &rect, DT_LEFT);

			//僨僶僀僗僐儞僥僉僗僩傪夝曻偡傞
			pBackSurface->ReleaseDC(NULL);
		}
		//僒乕僼僃僗傪夝曻偡傞
		pBackSurface->Release();

		//儗儞僟儕儞僌僞乕僎僢僩偑儕僙僢僩偝傟傞偺偱僙僢僩偟側偍偡
		g_ImmediateContext->OMSetRenderTargets(1, &g_RenderTargetView, g_DepthStencilView);
	}
#endif
}
