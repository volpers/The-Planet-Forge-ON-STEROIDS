#pragma once
#include "DirectXFunctions.h"

class RendererBase
{
private:
	DirectXFunctions* _directXFunctions;
	
public:
	RendererBase(HWND hwnd, HINSTANCE hinstance, EngineConfiguration& configuration);
	virtual ~RendererBase();
	virtual void Initialize() = 0;
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;

	virtual void BeginFrame();	
	virtual void EndFrame();

};
