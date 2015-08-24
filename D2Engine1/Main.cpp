#include "GrafixD2.h"
#include "IceCaves.h"
//ID2D1HwndRenderTarget *m_pRenderTarget;
Game* game = NULL;
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	);
#pragma comment(lib, "windowscodecs.lib")


int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
	)
{
	BOOL done = FALSE;
	MSG     msg;
	
	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			GrafixD2 grafix;
			
			if (SUCCEEDED(grafix.Initialize()))
			{
				 game = new IceCaves(grafix);
				 game->dt.start();
				while (!done)									
				{
					if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						if (msg.message == WM_QUIT)				
						{
							done = TRUE;						
						}
						else									
						{
							TranslateMessage(&msg);				
							DispatchMessage(&msg);				
						}
					}
					else										
					{
						
						if (!game->Run())	
						{
							done = TRUE;
						}


					}
				}
				game->ShutDown();
				SAFE_DELETE(game);
			}
		}
		
		CoUninitialize();
	}
	
	return 0;
}
