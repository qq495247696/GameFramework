/*********************************************************************
 * \file   DirectXAPI.cpp
 * \brief   
 * \author MA HANGLONG
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "DirectXAPI.h"
#include "Texture.h"
#include "ConstantBuffer.h"
HRESULT DirectXAPI::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
	DWORD deviceFlags = 0;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
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

	//デバッグ文字出力用設定
#if defined(_DEBUG) && defined(DEBUG_DISP_TEXTOUT)
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;
	deviceFlags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		deviceFlags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		_swapChain.GetAddressOf(),
		_d3dDevice.GetAddressOf(),
		&_featureLevel,
		_immediateContext.GetAddressOf());
	if (FAILED(hr))
		return hr;

	//デバッグ文字出力用設定
#if defined(_DEBUG) && defined(DEBUG_DISP_TEXTOUT)
	hr = _swapChain->ResizeBuffers(0, SCREEN_WIDTH, SCREEN_HEIGHT, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE);
	if (FAILED(hr))
		return hr;
#endif

	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	_d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, _renderTargetView.GetAddressOf());
	pBackBuffer->Release();



	//ステンシル用テクスチャー作成
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = sd.BufferDesc.Width;
	td.Height = sd.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc = sd.SampleDesc;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	_d3dDevice->CreateTexture2D(&td, NULL, &depthTexture);

	//ステンシルターゲット作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	_d3dDevice->CreateDepthStencilView(depthTexture, &dsvd, _depthStencilView.GetAddressOf());

	_immediateContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());


	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &vp);



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;
	_d3dDevice->CreateRasterizerState(&rd, _rasterStateCullOff.GetAddressOf());

	rd.CullMode = D3D11_CULL_FRONT;
	_d3dDevice->CreateRasterizerState(&rd, _rasterStateCullCW.GetAddressOf());

	rd.CullMode = D3D11_CULL_BACK;
	_d3dDevice->CreateRasterizerState(&rd, _rasterStateCullCCW.GetAddressOf());

	// カリングモード設定（CCW）
	SetCullingMode(CULL_MODE_BACK);




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
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
	_d3dDevice->CreateBlendState(&blendDesc, _blendStateAlphaBlend.GetAddressOf());

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	_d3dDevice->CreateBlendState(&blendDesc, _blendStateNone.GetAddressOf());

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	_d3dDevice->CreateBlendState(&blendDesc, _blendStateAdd.GetAddressOf());

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	_d3dDevice->CreateBlendState(&blendDesc, _blendStateSubtract.GetAddressOf());

	// アルファブレンド設定
	SetBlendState(BLEND_MODE_ALPHABLEND);


	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	_d3dDevice->CreateDepthStencilState(&depthStencilDesc, _depthStateEnable.GetAddressOf());//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	_d3dDevice->CreateDepthStencilState(&depthStencilDesc, _depthStateDisable.GetAddressOf());//深度無効ステート

	_immediateContext->OMSetDepthStencilState(_depthStateEnable.Get(), NULL);




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	_borderColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	samplerDesc.BorderColor[0] = _borderColor.r;//BORDERの色を指定
	samplerDesc.BorderColor[1] = _borderColor.g;
	samplerDesc.BorderColor[2] = _borderColor.b;
	samplerDesc.BorderColor[3] = _borderColor.a;

	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	_d3dDevice->CreateSamplerState(&samplerDesc, &samplerState);

	_immediateContext->PSSetSamplers(0, 1, &samplerState);
	samplerState->Release();


	// 頂点シェーダコンパイル・生成
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;
	DWORD shFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG) && defined(DEBUG_SHADER)
	shFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", shFlag, 0, NULL, &pVSBlob, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR);
	}

	_d3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, _vertexShader.GetAddressOf());

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	_d3dDevice->CreateInputLayout(layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		_vertexLayout.GetAddressOf());

	pVSBlob->Release();


	// ピクセルシェーダコンパイル・生成
	ID3DBlob* pPSBlob = NULL;
	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "PixelShaderPolygon", "ps_4_0", shFlag, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR);
	}

	_d3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, _pixelShader.GetAddressOf());

	pPSBlob->Release();
	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	//ワールドマトリクス
	_d3dDevice->CreateBuffer(&hBufferDesc, NULL, _worldBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(0, 1, _worldBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(0, 1, _worldBuffer.GetAddressOf());

	//ビューマトリクス
	_d3dDevice->CreateBuffer(&hBufferDesc, NULL, _viewBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(1, 1, _viewBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(1, 1, _viewBuffer.GetAddressOf());

	//プロジェクションマトリクス
	_d3dDevice->CreateBuffer(&hBufferDesc, NULL, _projectionBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(2, 1, _projectionBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(2, 1, _projectionBuffer.GetAddressOf());

	//マテリアル情報
	hBufferDesc.ByteWidth = sizeof(MATERIAL_CBUFFER);
	_d3dDevice->CreateBuffer(&hBufferDesc, NULL, _materialBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(3, 1, _materialBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(3, 1, _materialBuffer.GetAddressOf());

	//ライト情報
	hBufferDesc.ByteWidth = sizeof(LIGHT_CBUFFER);
	_d3dDevice->CreateBuffer(&hBufferDesc, NULL, _lightBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(4, 1, _lightBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(4, 1, _lightBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
	_d3dDevice->CreateBuffer(&hBufferDesc, NULL, _inverseBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(6, 1, _inverseBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(6, 1, _inverseBuffer.GetAddressOf());

	// 入力レイアウト設定
	_immediateContext->IASetInputLayout(_vertexLayout.Get());

	// シェーダ設定
	_immediateContext->VSSetShader(_vertexShader.Get(), NULL, 0);
	_immediateContext->PSSetShader(_pixelShader.Get(), NULL, 0);


	//ライト初期化
	ZeroMemory(&_lightCBuffer, sizeof(LIGHT_CBUFFER));
	_lightCBuffer.Direction[0] = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f);
	_lightCBuffer.Diffuse[0] = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
	_lightCBuffer.Ambient[0] = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	SetLightBuffer();


	//マテリアル初期化
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
	_d3dDevice->CreateBuffer(&cbd, NULL, _cameraPosBuffer.GetAddressOf());
	_immediateContext->VSSetConstantBuffers(5, 1, _cameraPosBuffer.GetAddressOf());
	_immediateContext->PSSetConstantBuffers(5, 1, _cameraPosBuffer.GetAddressOf());

	return S_OK;
}

void DirectXAPI::UnInit()
{

}

void DirectXAPI::Clear(float r, float g, float b, float a)
{
	float ClearColor[4] = { r, g, b, a };
	_immediateContext->ClearRenderTargetView(_renderTargetView.Get(), ClearColor);
	_immediateContext->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DirectXAPI::Present()
{
	_swapChain->Present(0, 0);
}

void DirectXAPI::SetDepthEnable(bool Enable)
{
	if (Enable)
		_immediateContext->OMSetDepthStencilState(_depthStateEnable.Get(), NULL);
	else
		_immediateContext->OMSetDepthStencilState(_depthStateDisable.Get(), NULL);

}

void DirectXAPI::SetBlendState(BLEND_MODE bm)
{
	_blendStateParam = bm;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	switch (_blendStateParam)
	{
	case BLEND_MODE_NONE:
		_immediateContext->OMSetBlendState(_blendStateNone.Get(), blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ALPHABLEND:
		_immediateContext->OMSetBlendState(_blendStateAlphaBlend.Get(), blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_ADD:
		_immediateContext->OMSetBlendState(_blendStateAdd.Get(), blendFactor, 0xffffffff);
		break;
	case BLEND_MODE_SUBTRACT:
		_immediateContext->OMSetBlendState(_blendStateSubtract.Get(), blendFactor, 0xffffffff);
		break;
	}
}

void DirectXAPI::SetCullingMode(CULL_MODE cm)
{
	switch (cm)
	{
	case CULL_MODE_NONE:
		_immediateContext->RSSetState(_rasterStateCullOff.Get());
		break;
	case CULL_MODE_FRONT:
		_immediateContext->RSSetState(_rasterStateCullCW.Get());
		break;
	case CULL_MODE_BACK:
		_immediateContext->RSSetState(_rasterStateCullCCW.Get());
		break;
	}
}

void DirectXAPI::SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am)
{
	// サンプラーステート設定
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

	//テクスチャのアドレッシングモードの設定		
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

	samplerDesc.BorderColor[0] = _borderColor.r;
	samplerDesc.BorderColor[1] = _borderColor.g;
	samplerDesc.BorderColor[2] = _borderColor.b;
	samplerDesc.BorderColor[3] = _borderColor.a;

	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	_d3dDevice->CreateSamplerState(&samplerDesc, &samplerState);

	_immediateContext->PSSetSamplers(0, 1, &samplerState);

	samplerState->Release();
	samplerState = NULL;
}

void DirectXAPI::SetSamplerBorderColor(D3DXCOLOR col)
{
	_borderColor = col;
}

void DirectXAPI::SetAlphaTestEnable(BOOL flag)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	if (flag)
		blendDesc.AlphaToCoverageEnable = TRUE;
	else
		blendDesc.AlphaToCoverageEnable = FALSE;

	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	switch (_blendStateParam)
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
	_d3dDevice->CreateBlendState(&blendDesc, &blendState);
	_immediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

	if (blendState != NULL)
		blendState->Release();
}


void DirectXAPI::SetWorldViewProjection2D(void)
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	D3DXMatrixTranspose(&world, &world);
	GetDeviceContext()->UpdateSubresource(_worldBuffer.Get(), 0, NULL, &world, 0, 0);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	GetDeviceContext()->UpdateSubresource(_viewBuffer.Get(), 0, NULL, &view, 0, 0);

	D3DXMATRIX worldViewProjection;
	D3DXMatrixOrthoOffCenterLH(&worldViewProjection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);
	GetDeviceContext()->UpdateSubresource(_projectionBuffer.Get(), 0, NULL, &worldViewProjection, 0, 0);
}


void DirectXAPI::SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	D3DXMATRIX world;
	world = *WorldMatrix;
	D3DXMatrixTranspose(&world, &world);

	_immediateContext->UpdateSubresource(_worldBuffer.Get(),0, NULL, &world, 0, 0);
}


void DirectXAPI::SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	D3DXMATRIX view;
	view = *ViewMatrix;
	D3DXMatrixTranspose(&view, &view);

	GetDeviceContext()->UpdateSubresource(_viewBuffer.Get(), 0, NULL, &view, 0, 0);
}

void DirectXAPI::SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	D3DXMATRIX projection;
	projection = *ProjectionMatrix;
	D3DXMatrixTranspose(&projection, &projection);

	GetDeviceContext()->UpdateSubresource(_projectionBuffer.Get(), 0, NULL, &projection, 0, 0);
}

DirectX::XMMATRIX DirectXAPI::InverseTranspose(DirectX::CXMMATRIX M)
{
	DirectX::XMMATRIX A = M;
	A.r[3] = DirectX::XMVectorSet(0.0, 0.0, 0.0, 1.0);
	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
	if (!DirectX::XMVector3Equal(det, DirectX::XMVectorZero()))
	{
		// ｾﾘﾕ�ｿﾉﾄ譽ｬｿﾉﾒﾔｰｲﾈｫｵﾘｼﾆﾋ翔貔ﾘﾕ�
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, A));
	}
	else
	{
		return DirectX::XMMatrixIdentity();
	}
}

void DirectXAPI::SetInverseMatrix(DirectX::XMMATRIX& worldMtx)
{
	DirectX::XMMATRIX inverse = InverseTranspose(worldMtx);
	GetDeviceContext()->UpdateSubresource(_inverseBuffer.Get(), 0, NULL, &inverse, 0, 0);
}

void DirectXAPI::SetMaterial(MATERIAL Material)
{
	_materialCBuffer.Diffuse = Material.Diffuse;
	_materialCBuffer.Ambient = Material.Ambient;
	_materialCBuffer.Specular = Material.Specular;
	_materialCBuffer.Emission = Material.Emission;
	_materialCBuffer.Shininess = Material.Shininess;
	_materialCBuffer.noTexSampling = Material.noTexSampling;
	_materialCBuffer.PolyLine = Material.Polyline;

	GetDeviceContext()->UpdateSubresource(_materialBuffer.Get(), 0, NULL,& _materialCBuffer, 0, 0);
}

void DirectXAPI::SetLightBuffer(void)
{
	GetDeviceContext()->UpdateSubresource(_lightBuffer.Get(), 0, NULL, &_lightCBuffer, 0, 0);
}

void DirectXAPI::DebugTextOut(char* text, int x, int y)
{
#if defined(_DEBUG) && defined(DEBUG_DISP_TEXTOUT)
	HRESULT hr;

	//バックバッファからサーフェスを取得する
	IDXGISurface1* pBackSurface = NULL;
	hr = _swapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackSurface);

	if (SUCCEEDED(hr))
	{
		//取得したサーフェスからデバイスコンテキストを取得する
		HDC hdc;
		hr = pBackSurface->GetDC(FALSE, &hdc);

		if (SUCCEEDED(hr))
		{
			//文字色を白に変更
			SetTextColor(hdc, RGB(255, 255, 255));
			//背景を透明に変更
			SetBkMode(hdc, TRANSPARENT);

			RECT rect;
			rect.left = 0;
			rect.top = 0;
			rect.right = SCREEN_WIDTH;
			rect.bottom = SCREEN_HEIGHT;

			//テキスト出力
			DrawText(hdc, text, (int)strlen(text), &rect, DT_LEFT);

			//デバイスコンテキストを解放する
			pBackSurface->ReleaseDC(NULL);
		}
		//サーフェスを解放する
		pBackSurface->Release();

		//レンダリングターゲットがリセットされるのでセットしなおす
		_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView.Get());
	}
#endif
}

void DirectXAPI::SetLightEnable(BOOL flag)
{
	// フラグを更新する
	_lightCBuffer.Enable = flag;

	SetLightBuffer();
}

void DirectXAPI::SetLight(int index, LIGHT* pLight)
{
	//範囲エラー
	if (index > 9 || index < 0) return;

	_lightCBuffer.Position[index] = D3DXVECTOR4(pLight->Position.x, pLight->Position.y, pLight->Position.z, 0.0f);
	_lightCBuffer.Direction[index] = D3DXVECTOR4(pLight->Direction.x, pLight->Direction.y, pLight->Direction.z, 0.0f);
	_lightCBuffer.Specular[index] = pLight->Specular;
	_lightCBuffer.Diffuse[index] = pLight->Diffuse;
	_lightCBuffer.Ambient[index] = pLight->Ambient;
	_lightCBuffer.Flags[index].Type = pLight->Type;
	_lightCBuffer.Flags[index].OnOff = pLight->Enable;
	_lightCBuffer.Attenuation[index].x = pLight->Attenuation;

	SetLightBuffer();
}

void DirectXAPI::UpdateCameraPos(D3DXVECTOR3 pos)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT hr = GetDeviceContext()->Map(_cameraPosBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	if (SUCCEEDED(hr))
	{
		CameraBufferType* camerapos = (CameraBufferType*)msr.pData;
		camerapos->cameraPosition = pos;
		GetDeviceContext()->Unmap(_cameraPosBuffer.Get(), 0);
	}
}