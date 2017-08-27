#pragma once
#pragma comment(lib, "d3d11.lib")

#include <d3d11_1.h>
#include <boost/shared_ptr.hpp>
#include <directxcolors.h>
#include "resource.h"


class DirectXFunctions
{
public:
	explicit DirectXFunctions(HINSTANCE__* hinstance);

	void releaseObjects() const;
	bool initScene();
	void updateScene();
	void drawScene();
private:
	void initializeDirectX(HINSTANCE__* hinstance);

};
