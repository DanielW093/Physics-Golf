#include "stdafx.h"
#include "MyGame.h"

CMyGame game;
CGameApp app;

int main(int argc, char* argv[])
{
	app.OpenWindow(1024, 768, "GFC Golf");
	//app.OpenFullScreen(800, 600, 24);
	app.SetClearColor(CColor::White());
	app.Run(&game);
	return(0);
}