#include "stdafx.h"
#include "DirectXFunctions.h"
#include <DirectXColors.h>

using namespace DirectX;

DirectXFunctions::DirectXFunctions(HWND hwnd, HINSTANCE hinstance, EngineConfiguration& configuration) : _hinstance(hinstance), _swapChain(nullptr), _d3d11Device(nullptr), _d3d11DevCon(nullptr), _renderTargetView(nullptr), _configuration(configuration), _hwnd(hwnd)
{
}

void DirectXFunctions::initializeDirectX()
{
	initBuffer();
}

void DirectXFunctions::releaseObjects() const
{	
	//Release the COM Objects we created
	_swapChain->Release();
	_d3d11Device->Release();
	_d3d11DevCon->Release();

}

bool DirectXFunctions::initScene()
{
	return true;
}

void DirectXFunctions::updateScene()
{	
	//Update the colors of our scene
	_bgColor.colormodr += _bgColor.colormodr * 0.00005f;
	_bgColor.green += _bgColor.colormodg * 0.00002f;
	_bgColor.blue += _bgColor.colormodb * 0.00001f;

	if (_bgColor.red >= 1.0f || _bgColor.red <= 0.0f)
		_bgColor.colormodr *= -1;
	if (_bgColor.green >= 1.0f || _bgColor.green <= 0.0f)
		_bgColor.colormodg *= -1;
	if (_bgColor.blue >= 1.0f || _bgColor.blue <= 0.0f)
		_bgColor.colormodb *= -1;	
}

void DirectXFunctions::drawScene()
{	
	//Clear our backbuffer to the updated color
	float bgColor[4] = {_bgColor.red, _bgColor.green, _bgColor.blue, 1.0f};
	
	_d3d11DevCon->ClearRenderTargetView(_renderTargetView, bgColor);
	
	//Present the backbuffer to the screen
	_swapChain->Present(0, 0);	
}

void DirectXFunctions::initBuffer()
{
	HRESULT hresult;

	ZeroMemory(&_bufferDescription, sizeof(DXGI_MODE_DESC));

	_bufferDescription.Width = _configuration.WINDOW_WIDTH;
	_bufferDescription.Height = _configuration.WINDOW_HEIGHT;
	_bufferDescription.RefreshRate.Numerator = 60;
	_bufferDescription.RefreshRate.Denominator = 1;
	_bufferDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_bufferDescription.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_bufferDescription.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	ZeroMemory(&_swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	_swapChainDescription.BufferDesc = _bufferDescription;
	_swapChainDescription.SampleDesc.Count = 1;
	_swapChainDescription.SampleDesc.Quality = 0;
	_swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_swapChainDescription.BufferCount = 1;
	_swapChainDescription.OutputWindow = _hwnd;
	_swapChainDescription.Windowed = TRUE;
	_swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Create our SwapChain
	hresult = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &_swapChainDescription, &_swapChain, &_d3d11Device, NULL, &_d3d11DevCon);

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	hresult = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	//Create our Render Target
	hresult = _d3d11Device->CreateRenderTargetView(BackBuffer, nullptr, &_renderTargetView);
	BackBuffer->Release();

	//Set our Render Target
	_d3d11DevCon->OMSetRenderTargets(1, &_renderTargetView, nullptr);
}



