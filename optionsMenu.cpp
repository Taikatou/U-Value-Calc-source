#include "OptionsMenu.h"
#include "MainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "s3eFile.h"
#include "pauseMenu.h"

using namespace std;


OptionsMenu::~OptionsMenu()
{


}


void OptionsMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this)
	{

		if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{

			g_pInput->Reset();
			if (PlayGameButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				MainMenu * main = (MainMenu*)g_pSceneManager->Find("MainMenu");
				main->setHeightScore(0);
				char str [1];
				snprintf(str, 1, "%d", (int)0);
				main->setHeightScore(0);
				main->changeText(str);
				main->save();
				PlayGameButton->SetImage(g_pResources->getHighScoresReset());
				
			}
			else if (OptionsButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pSceneManager->SwitchTo(g_pSceneManager->Find("pause"));
			}
			else if (backtoMainMenu->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pSceneManager->SwitchTo(g_pSceneManager->Find("MainMenu"));
			}

		}

	}

}

void OptionsMenu::Render()
{

    Scene::Render();

}

void OptionsMenu::Init()
{

    Scene::Init();



    // Create menu background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getWhite());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);

	PlayGameButton = new CSprite();
	PlayGameButton->m_X = background->m_X;
	PlayGameButton->m_Y = background->m_Y / 3;
	PlayGameButton->SetImage(Iw2DCreateImage("textures/resetHighScoresButton.png"));
	PlayGameButton->m_AnchorX = 0.5;
	PlayGameButton->m_AnchorY = 0.5;
	// Fit background to screen size

	PlayGameButton->m_ScaleX = (float)background->m_X / PlayGameButton->GetImage()->GetWidth() * .6;
	PlayGameButton->m_ScaleY = PlayGameButton->m_ScaleX;
	AddChild(PlayGameButton);

	OptionsButton = new CSprite();
	OptionsButton->m_X = background->m_X;
	OptionsButton->m_Y = PlayGameButton->m_Y * 2;
	OptionsButton->SetImage(Iw2DCreateImage("textures/HowToPlay.png"));
	OptionsButton->m_AnchorX = 0.5;
	OptionsButton->m_AnchorY = 0.5;
	// Fit background to screen size

	OptionsButton->m_ScaleX = PlayGameButton->m_ScaleX;
	OptionsButton->m_ScaleY = PlayGameButton->m_ScaleX;
	AddChild(OptionsButton);


	backtoMainMenu = new CSprite();
	backtoMainMenu->m_X = background->m_X;
	backtoMainMenu->m_Y = PlayGameButton->m_Y * 3;
	backtoMainMenu->SetImage(Iw2DCreateImage("textures/backToMain.png"));
	backtoMainMenu->m_AnchorX = 0.5;
	backtoMainMenu->m_AnchorY = 0.5;
	// Fit background to screen size

	backtoMainMenu->m_ScaleX = PlayGameButton->m_ScaleX;
	backtoMainMenu->m_ScaleY = PlayGameButton->m_ScaleX;
	AddChild(backtoMainMenu);

}

