#include "PauseMenu.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "game.h"
#include "scene.h"

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if ((m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched) || (s3eKeyboardGetState(s3eKeyBack) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyBack) & S3E_KEY_STATE_PRESSED))
	{
		g_pInput->Reset();

			// Switch to game scene
			Game* game = (Game*)g_pSceneManager->Find("game");
			g_pSceneManager->SwitchTo(game);

			// Resume game
			game->resumeGame();
			// Restore button alpha state
			//PauseMenu* menu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
	}

}

void PauseMenu::Render()
{
	Scene::Render();
}

void PauseMenu::resume()
{
}
void PauseMenu::Init()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	add = false;
	int width = IwGxGetScreenWidth();
	int height = IwGxGetScreenHeight();
	// Create menu background
	CSprite* background = new CSprite();
	background->m_X = (float) width / 2;
	background->m_Y = (float) height / 2;
	background->SetImage(g_pResources->getGameBGB());
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)width / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)height / background->GetImage()->GetHeight();
	AddChild(background);

	shown = false;

	// Create New  Game button
	infoButton = new CSprite();
	infoButton->SetImage(g_pResources->getInfoButton());
	infoButton->m_X = (float)(width * 0.15) + (width / (1.5 * 2));
	infoButton->m_Y = (float)height / 50;
	infoButton->m_W = infoButton->GetImage()->GetWidth();
	infoButton->m_H = infoButton->GetImage()->GetHeight();
	infoButton->m_AnchorX = 0.5f;
	infoButton->m_AnchorY = 0;
	infoButton->m_ScaleX = (float)width / infoButton->GetImage()->GetWidth() / 1.5;
	infoButton->m_ScaleY = infoButton->m_ScaleX;
	AddChild(infoButton);



	// Create New  Game button
	infoText = new CSprite();
	infoText->SetImage(g_pResources->getInfoText());
	infoText->m_X = (float)(width * 0.15) + ((width / (1.4 * 2)));
	infoText->m_W = infoText->GetImage()->GetWidth();
	infoText->m_H = infoText->GetImage()->GetHeight();
	infoText->m_AnchorX = 0.5f;
	infoText->m_AnchorY = 0.5f;
	infoText->m_ScaleX = (float)(width / infoText->GetImage()->GetWidth()) / 1.4;
	infoText->m_ScaleY = infoText->m_ScaleX;
	infoText->m_Y = (float)(infoText->GetImage()->GetHeight() * infoText->m_ScaleX)/ 2 + (height / 6);
	AddChild(infoText);
}

