#include "IceCaves.h"
#pragma comment(lib, "windowscodecs.lib")
#include "PlayerControl.h"

PlayerControl controler;
int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
	)
{
	UINT scrnWidth = 800, scrnHeight = 600;

	IceCaves *app = new IceCaves();
	if (app)
	{
		if (SUCCEEDED(app->Initialize(scrnWidth, scrnHeight)))
		{
			app->Run();
		}
	}

	delete app;

	return 0;
}
