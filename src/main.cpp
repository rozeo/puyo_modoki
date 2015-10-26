#include "../h/dxApp.h"
#include <DxLib_GCC.h>
#include <time.h>

#define WIDTH  420
#define HEIGHT 480

int WINAPI WinMain( HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nCmdShow ){

	srand((unsigned)time(NULL));

	dxApp *app = new dxApp(WIDTH,HEIGHT,DX_SCREEN_BACK,TRUE);

	SetAlwaysRunFlag(TRUE);

	if(app->Init() != 0)
		return -1;

	return app->run();
}