#include "stdafx.h"
#include "MyGame.h"

int power = 0;
int direction = 0;
int currentState = 0;
int swings = 0;
int windValue = 0;
int ballDistance = 0;
int holeStartX;
string currentStateText = "Press space to start.";

int angularLimit = 90;

CMyGame::CMyGame(void)
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	//Putting ball in hole
	if(ball->HitTest(hole) && ball->GetSpeed() < 300 && !ball->inHole)
	{
		ball->inHole = true;
		currentState = 5;
		ball->SetSpeed(0);
	}

	//Set up angular limit
	if (ball->reachedCentre)
	{
		angularLimit = 180;
	}
	else
	{
		angularLimit = 90;
	}

	//Setting up arrow position
	arrow.SetRotation(-direction);
	arrow.SetX(ball->GetX());

	//Setting up wind arrow
	windArrow.SetX(512);
	windArrow.SetSize(windValue*10, windArrow.GetHeight());

	//Define distance
	ballDistance = ((ball->GetX() - 40) + (holeStartX - hole->GetX()))/50;

	long t = GetTime();

	//Update Ball
	ball->Update(t); CVector ballV = ball->GetVelocity(); float ballXV = ballV.X();

	if (ball->getBeenHit() && ball->GetY() > 16)
	{
		ball->Accelerate(windValue/2,0);
	}

	if (ball->reachedCentre == true)
	{
		hole->SetVelocity(-ballXV, 0);
		grass1.SetVelocity(-ballXV, 0);
		grass2.SetVelocity(-ballXV, 0);

		float cloudV = -(ballXV/60) + windValue;
		cloud1.SetVelocity(cloudV, 0);
		cloud2.SetVelocity(cloudV, 0);
		cloud3.SetVelocity(cloudV, 0);
		cloud4.SetVelocity(cloudV, 0);

		float treeV = -(ballXV/3);
		tree1.SetVelocity(treeV, 0);
		tree2.SetVelocity(treeV, 0);
		tree3.SetVelocity(treeV, 0);
		tree4.SetVelocity(treeV, 0);
		tree5.SetVelocity(treeV, 0);

		float hedgeV = -(ballXV/4);
		hedge1.SetVelocity(hedgeV, 0);
		hedge2.SetVelocity(hedgeV, 0);

		float cityV = -(ballXV/55);
		city1.SetVelocity(cityV, 0);
		city2.SetVelocity(cityV, 0);

		ball->SetX(512);

		//Parallax
		parallaxScroll();
	}
	else
	{
		cloud1.SetVelocity(windValue, 0);
		cloud2.SetVelocity(windValue, 0);
		cloud3.SetVelocity(windValue, 0);
		cloud4.SetVelocity(windValue, 0);
	}

	//Resetting
	if (ball->GetSpeed() == 0 && currentState == 4)
	{
		ball->SetPosition(ball->GetX(), 15);
		ball->setBeenHit(false);
		currentState = 1;

		if (ball->GetX() - hole->GetX() < 0)
		{
			direction = 0;
		}
		else
		{
			direction = 180;
		}

		ball->SetDirection(0);
		power = 0;
		windValue = (rand() % 21) - 10;
	}

	//Updating
	hole->Update(t);
	cloud1.Update(t); cloud2.Update(t); cloud3.Update(t); cloud4.Update(t);
	tree1.Update(t); tree2.Update(t); tree3.Update(t); tree4.Update(t); tree5.Update(t);
	hedge1.Update(t); hedge2.Update(t); grass1.Update(t); grass2.Update(t);
	city1.Update(t); city2.Update(t); background.Update(t);

	//Controls
	controls();
}

void CMyGame::OnDraw(CGraphics* g)
{
	background.Draw(g);	cloud1.Draw(g);	cloud2.Draw(g);	cloud3.Draw(g); cloud4.Draw(g);
	city1.Draw(g); city2.Draw(g);
	hedge1.Draw(g);	hedge2.Draw(g);
	tree1.Draw(g); tree2.Draw(g); tree3.Draw(g); tree4.Draw(g); tree5.Draw(g);	
	grass1.Draw(g); grass2.Draw(g);	hole->Draw(g);

	windArrow.Draw(g);
	
	if (currentState == 1 || currentState == 2)
	{
		arrow.Draw(g);
	}

	powerBar.Draw(g); powerBarInside.Draw(g); powerBarInside.SetSize(18, power-2); powerBarInside.SetPosition(12, 2+(power/2));
	
	if (!ball->inHole)
	{
		ball->Draw(g); 
	}
	
	*g << centre << "Wind strength:" << endl;

	*g << top << left << "Hole is at: " << holeStartX/50 << "m" << endl;
	*g << "Distance: " << ballDistance << "m" << endl;

	if (currentState != 5)
	{
		*g << centre << vcentre << currentStateText << endl;
	}
	else
	{
		*g << centre << vcentre << currentStateText << swings << " swings!" << endl;
	}

	*g << top << right << "Swings: " << swings << endl;	
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	background.SetImageFromFile("images/sky.bmp"); background.SetPosition(512, 384);
	hole = new SpriteHole(20000, 53, GetTime()); holeStartX = hole->GetX();
	ball = new SpriteBall(40, 15, GetTime());
	arrow.SetImageFromFile("images/arrow.gif"); arrow.SetPosition(115, 15); arrow.SetPivot(40, 15);
	windArrow.SetImageFromFile("images/arrow.gif"); windArrow.SetPosition(512, 735); //windArrow.SetPivot(512, windArrow.GetY());
	powerBar.SetImageFromFile("images/powerBar.gif"); powerBar.SetPosition(12, 52);
	powerBarInside.SetImageFromFile("images/power.bmp"); powerBarInside.SetPosition(12, 52);

	cloud1.SetImageFromFile("images/cloud.gif");	cloud1.SetPosition(512, 675);
	cloud2.SetImageFromFile("images/cloud2.gif");	cloud2.SetPosition(128, 575);
	cloud3.SetImageFromFile("images/cloud2.gif");	cloud3.SetPosition(896, 575);
	cloud4.SetImageFromFile("images/cloud3.gif");  cloud4.SetPosition(1290, 675);

	tree1.SetImageFromFile("images/tree.gif");		tree1.SetPosition(0, (tree1.GetHeight()/2) + 15);
	tree2.SetImageFromFile("images/tree.gif");		tree2.SetPosition(256, (tree2.GetHeight()/2) + 15);
	tree3.SetImageFromFile("images/tree.gif");		tree3.SetPosition(512, (tree3.GetHeight()/2) + 15);
	tree4.SetImageFromFile("images/tree.gif");		tree4.SetPosition(768, (tree4.GetHeight()/2) + 15);
	tree5.SetImageFromFile("images/tree.gif");		tree5.SetPosition(1024, (tree5.GetHeight()/2) + 15);

	hedge1.SetImageFromFile("images/hedge.bmp");	hedge1.SetPosition(512,38);
	hedge2.SetImageFromFile("images/hedge.bmp");	hedge2.SetPosition(1536,38);

	grass1.SetImageFromFile("images/grass.gif");	grass1.SetPosition(512, grass1.GetHeight()/2);
	grass2.SetImageFromFile("images/grass.gif");	grass2.SetPosition(1536, grass2.GetHeight()/2);

	city1.SetImageFromFile("images/city.gif");		city1.SetPosition(512, (city1.GetHeight()/2) + 65);
	city2.SetImageFromFile("images/city.gif");		city2.SetPosition(city1.GetX() + city2.GetWidth(), (city2.GetHeight()/2) + 65);

	srand(time(NULL)); windValue = (rand() % 21) - 10;
}
// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{

}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	//if (sym == SDLK_SPACE)
	//	PauseGame();
	if (sym == SDLK_F2)
		NewGame();

	if (sym == SDLK_SPACE)
	{
		if (currentState == 0)
		{
			currentState = 1;
		}
		else if (currentState == 1)
		{
			int d = (-direction + 90);
			ball->SetDirection(d);
			currentState = 2;
		}
		else if (currentState == 2)
		{
			currentState = 3;
		}
		else if (currentState == 3)
		{
			ball->hitBall(power);
			swings++;
			currentState = 4;
		}
	}
	if (sym == SDLK_BACKSPACE)
	{
		if (currentState == 1)
		{
			currentState = 0;
		}
		else if (currentState == 2)
		{
			currentState = 1;
		}
		else if (currentState == 3)
		{
			currentState = 2;
		}
	}
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::parallaxScroll()
{
	//Cloud Scrolling
	if ((cloud1.GetX() + cloud1.GetWidth()/2) < 0 && cloud1.GetVelocity().X() < 0)
	{
		cloud1.SetX(cloud2.GetX() + 384);
	}
	else if ((cloud1.GetX() - cloud1.GetWidth()/2) > 1024 && cloud1.GetVelocity().X() > 0)
	{
		cloud1.SetX(cloud3.GetX() - 384);
	}

	if ((cloud2.GetX() + cloud2.GetWidth()/2) < 0 && cloud2.GetVelocity().X() < 0)
	{
		cloud2.SetX(cloud4.GetX() + 384);
	}
	else if ((cloud2.GetX() - cloud2.GetWidth()/2) > 1024 && cloud2.GetVelocity().X() > 0)
	{
		cloud2.SetX(cloud1.GetX() - 384);
	}

	if ((cloud3.GetX() + cloud3.GetWidth()/2) < 0 && cloud3.GetVelocity().X() < 0)
	{
		cloud3.SetX(cloud1.GetX() + 384);
	}
	else if ((cloud3.GetX() - cloud3.GetWidth()/2) > 1024 && cloud3.GetVelocity().X() > 0)
	{
		cloud3.SetX(cloud4.GetX() - 384);
	}

	if ((cloud4.GetX() + cloud4.GetWidth()/2) < 0 && cloud4.GetVelocity().X() < 0)
	{
		cloud4.SetX(cloud3.GetX() + 384);
	}
	else if ((cloud4.GetX() - cloud4.GetWidth()/2) > 1024 && cloud4.GetVelocity().X() > 0)
	{
		cloud4.SetX(cloud2.GetX() - 384);
	}
	//Tree Scrolling
	if (tree1.GetX() + 104.5 < 0 && tree1.GetVelocity().X() < 0)
	{
		tree1.SetPosition(tree5.GetX() + 256, tree1.GetY());
	}
	else if (tree1.GetX() - 104.5 > 1024 && tree1.GetVelocity().X() > 0)
	{
		tree1.SetPosition(tree2.GetX() - 256, tree1.GetY());
	}

	if (tree2.GetX() + 104.5 < 0 && tree2.GetVelocity().X() < 0)
	{
		tree2.SetPosition(tree1.GetX() + 256, tree2.GetY());
	}
	else if (tree2.GetX() - 104.5 > 1024 && tree2.GetVelocity().X() > 0)
	{
		tree2.SetPosition(tree3.GetX() - 256, tree2.GetY());
	}

	if (tree3.GetX() + 104.5 < 0 && tree3.GetVelocity().X() < 0)
	{
		tree3.SetPosition(tree2.GetX() + 256, tree3.GetY());
	}
	else if (tree3.GetX() - 104.5 > 1024 && tree3.GetVelocity().X() > 0)
	{
		tree3.SetPosition(tree4.GetX() - 256, tree3.GetY());
	}

	if (tree4.GetX() + 104.5 < 0 && tree4.GetVelocity().X() < 0)
	{
		tree4.SetPosition(tree3.GetX() + 256, tree4.GetY());
	}
	else if (tree4.GetX() - 104.5 > 1024 && tree4.GetVelocity().X() > 0)
	{
		tree4.SetPosition(tree5.GetX() - 256, tree4.GetY());
	}

	if (tree5.GetX() + 104.5 < 0 && tree5.GetVelocity().X() < 0)
	{
		tree5.SetPosition(tree4.GetX() + 256, tree5.GetY());
	}
	else if (tree5.GetX() - 104.5 > 1024 && tree5.GetVelocity().X() > 0)
	{
		tree5.SetPosition(tree1.GetX() - 256, tree5.GetY());
	}

	//Hedge Scrolling
	if (hedge1.GetX() + 512 < 0 && hedge1.GetVelocity().X() < 0)
	{
		hedge1.SetPosition(hedge2.GetX() + 1024, hedge1.GetY());
	}
	else if (hedge1.GetX() - 512 > 1024 && hedge1.GetVelocity().X() > 0)
	{
		hedge1.SetPosition(hedge2.GetX() - 1024, hedge1.GetY());
	}

	if (hedge2.GetX() + 512 < 0 && hedge2.GetVelocity().X() < 0)
	{
		hedge2.SetPosition(hedge1.GetX() + 1024, hedge2.GetY());
	}
	else if (hedge2.GetX() - 512 > 1024 && hedge2.GetVelocity().X() > 0)
	{
		hedge2.SetPosition(hedge1.GetX() - 1024, hedge2.GetY());
	}

	//Grass Scrolling
	if (grass1.GetX() + 512 < 0 && grass1.GetVelocity().X() < 0)
	{
		grass1.SetPosition(grass2.GetX() + 1024, grass1.GetY());
	}
	else if (grass1.GetX() - 512 > 1024 && grass1.GetVelocity().X() > 0)
	{
		grass1.SetPosition(grass2.GetX() - 1024, grass1.GetY());
	}

	if (grass2.GetX() + 512 < 0 && grass2.GetVelocity().X() < 0)
	{
		grass2.SetPosition(grass1.GetX() + 1024, grass2.GetY());
	}
	else if (grass2.GetX() - 512 > 1024 && grass2.GetVelocity().X() > 0)
	{
		grass2.SetPosition(grass1.GetX() - 1024, grass2.GetY());
	}

	//City Scrolling
	if (city1.GetX() + city1.GetWidth()/2 < 0 && city1.GetVelocity().X() < 0)
	{
		city1.SetPosition(city2.GetX() + city1.GetWidth(), city1.GetY());
	}
	else if (city1.GetX() - city1.GetWidth()/2 > 1024 && city1.GetVelocity().X() > 0)
	{
		city1.SetPosition(city2.GetX() - city1.GetWidth(), city1.GetY());
	}

	if (city2.GetX() + city2.GetWidth()/2 < 0 && city2.GetVelocity().X() < 0)
	{
		city2.SetPosition(city1.GetX() + city2.GetWidth(), city2.GetY());
	}
	else if (city2.GetX() - city2.GetWidth()/2 > 1024 && city2.GetVelocity().X() > 0)
	{
		city2.SetPosition(city1.GetX() - city2.GetWidth(), city2.GetY());
	}
}

void CMyGame::controls()
{
	if (CMyGame::IsKeyDown(SDLK_LEFT) && direction < angularLimit)
	{
		if (currentState == 1)
		{
			direction++;
		}
	}	
	else if (CMyGame::IsKeyDown(SDLK_RIGHT) && direction > 0)
	{
		if (currentState == 1)
		{		
			direction--;
		}
	}

	if (CMyGame::IsKeyDown(SDLK_UP) && power < 100)
	{
		if (currentState == 2)
		{
			power++;
		}
	}	
	else if (CMyGame::IsKeyDown(SDLK_DOWN) && power > 0)
	{
		if (currentState == 2)
		{		
			power--;
		}
	}

  	if (currentState == 0)
	{
		currentStateText = "Press space to start.";
	}
	else if (currentState == 1)
	{
		currentStateText = "Adjust direction with left and right.";
	}
	else if (currentState == 2)
	{
		currentStateText = "Adjust power with up and down.";
	}
	else if (currentState == 3)
	{
		currentStateText = "Press space to swing!";
	}
	else if (currentState == 4)
	{
		currentStateText = "";
	}
	else if (currentState == 5)
	{
		currentStateText = "Congratulations! You won in ";
	}
}