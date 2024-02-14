#pragma once
#include<map>
#include<string>
#include<wrl.h>
#include<DirectXMath.h>
#include "RenderInfo.h"
#include "ConstantBuffer.h"

using namespace Microsoft::WRL;
class DirectXAPI
{
public:
	DirectXAPI()
	{
	}

	~DirectXAPI()
	{

	}

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void UnInit();
	void Clear(float r, float g, float b, float a);
	void Present();


	void SetDepthEnable(bool Enable);
	void SetBlendState(BLEND_MODE bm);
	void SetCullingMode(CULL_MODE cm);
	void SetLightEnable(BOOL flag);
	void SetAlphaTestEnable(BOOL flag);
	void SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am);
	void SetSamplerBorderColor(D3DXCOLOR col);

	void SetWorldViewProjection2D(void);
	void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX invMtx);

	void SetMaterial(MATERIAL Material);
	void SetLight(int index, LIGHT* pLight);
	void SetLightBuffer(void);
	void DebugTextOut(char* text, int x, int y);
	void UpdateCameraPos(D3DXVECTOR3 pos);
	void SetInverseMatrix(DirectX::XMMATRIX& worldMtx);

	ComPtr<ID3D11DeviceContext>GetDeviceContext()const{  return _immediateContext; }
	ComPtr<ID3D11Device>GetDevice()const{return _d3dDevice;}
private:


	D3D_FEATURE_LEVEL							_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ComPtr<ID3D11Device>						_d3dDevice;
	ComPtr<ID3D11DeviceContext>					_immediateContext;
	ComPtr<IDXGISwapChain>						_swapChain;
	ComPtr<ID3D11RenderTargetView>				_renderTargetView;
	ComPtr<ID3D11DepthStencilView>				_depthStencilView;
	ComPtr<ID3D11VertexShader>					_vertexShader;
	ComPtr<ID3D11PixelShader>					_pixelShader;
	ComPtr<ID3D11InputLayout>					_vertexLayout;
	ComPtr<ID3D11Buffer>						_worldBuffer;
	ComPtr<ID3D11Buffer>						_viewBuffer;
	ComPtr<ID3D11Buffer>						_projectionBuffer;
	ComPtr<ID3D11Buffer>						_cameraPosBuffer;
	ComPtr<ID3D11Buffer>						_materialBuffer;
	ComPtr<ID3D11Buffer>						_lightBuffer;
	ComPtr<ID3D11Buffer>						_inverseBuffer;
	ComPtr<ID3D11DepthStencilState>				_depthStateEnable;
	ComPtr<ID3D11DepthStencilState>				_depthStateDisable;
	ComPtr<ID3D11BlendState>					_blendStateNone;
	ComPtr<ID3D11BlendState>					_blendStateAlphaBlend;
	ComPtr<ID3D11BlendState>					_blendStateAdd;
	ComPtr<ID3D11BlendState>					_blendStateSubtract;
	ComPtr<ID3D11RasterizerState>				_rasterStateCullOff;
	ComPtr<ID3D11RasterizerState>				_rasterStateCullCW;
	ComPtr<ID3D11RasterizerState>				_rasterStateCullCCW;
	ComPtr<IDWriteFactory>						_DWriteFactory;
	ComPtr<IDWriteTextFormat>					_TextFormat;
	ComPtr<IDWriteTextLayout>					_TextLayout;


	D3DXCOLOR									_borderColor;
	MATERIAL_CBUFFER							_materialCBuffer;
	LIGHT_CBUFFER								_lightCBuffer;
	BLEND_MODE									_blendStateParam;
};
