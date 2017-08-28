#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11_1.h>
#include <boost/shared_ptr.hpp>
#include <directxcolors.h>
#include "resource.h"
#include "ColorData.h"
#include "EngineConfiguration.h"

class DirectXFunctions
{
private:
	HINSTANCE _hinstance;
	IDXGISwapChain* _swapChain;
	ID3D11Device* _d3d11Device;
	ID3D11DeviceContext* _d3d11DevCon;
	ID3D11RenderTargetView* _renderTargetView;
	ColorData _bgColor;
	EngineConfiguration& _configuration;	

	DXGI_MODE_DESC _bufferDescription;
	DXGI_SWAP_CHAIN_DESC _swapChainDescription;
	HWND _hwnd;

	void initBuffer();	
public:	
	explicit DirectXFunctions(HWND hWnd, HINSTANCE hinstance, EngineConfiguration& configuration);
	void initializeDirectX();
	void releaseObjects() const;
	bool initScene();
	void updateScene();
	void drawScene();
};
