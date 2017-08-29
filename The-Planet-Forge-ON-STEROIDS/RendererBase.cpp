#include "RendererBase.h"

RendererBase::RendererBase(HWND hwnd, HINSTANCE hinstance, EngineConfiguration& configuration)
{
	_directXFunctions = new DirectXFunctions(hwnd, hinstance, configuration);
}

RendererBase::~RendererBase()
{
	delete _directXFunctions;
}

void RendererBase::BeginFrame()
{
}

void RendererBase::EndFrame()
{
}
