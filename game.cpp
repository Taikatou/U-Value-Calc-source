#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "input.h"
#include "audio.h"
#include "PauseMenu.h"
#include "resources.h"
#include "s3eKeyboard.h"
#include "s3eOSReadString.h"
#include "s3eOSExec.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;


#define numBoxes 5
#define FONT_HEIGHT             15
#define FONT_DESIGN_WIDTH       320
#define GRAPHIC_DESIGN_WIDTH    768
#define maxCount 10

Game::~Game()
{
	if (checkBoxes != 0)
	{
		delete[] checkBoxes;
	}
	if (checkBoxText != 0)
	{
		delete[] checkBoxText;
	}
	if (textBoxes != 0)
	{
		delete[] textBoxes;
	}
	if (textFeildText != 0)
	{
		delete[] textFeildText;
	}
	if (stringValues != 0)
	{
		delete[] stringValues;
	}
	if (checkBoxesChecked != 0)
	{
		delete[] checkBoxesChecked;
	}
	if (eraseButton != 0)
	{
		delete[] eraseButton;
	}
}


/*void Game::pauseGame()
{
// Switch to pause menu scene
g_pSceneManager->SwitchTo(g_pSceneManager->Find("pausemenu"));
}*/
float	inputConverted[15 + (3 * maxCount)];

void Game::resumeGame()
{
}

void Game::newGame()
{
	// Reset score
}

void Game::swap(bool ch, int i)
{
	//ch false if unchecked

	if (!ch)
	{
		checkBoxesChecked[i]->m_X = checkBoxes[i]->m_X;
		checkBoxes[i]->m_X = width * 2;
	}

	else
	{
		checkBoxes[i]->m_X = checkBoxesChecked[i]->m_X;
		checkBoxesChecked[i]->m_X = width * 2;
	}
}

void Game::Move(int upDown)
{
	int tempCounter = counter + upDown;

	if (tempCounter >= 0 && tempCounter <= maxCount)
	{
		if (tempCounter == 0)
		{
			if (eraseButton[0]->m_X > width)
			{
				eraseButton[0]->m_X = upButton->m_X;
				upButton->m_X = width * 2;
			}
		}
		else
		{
			if (eraseButton[0]->m_X < width)
			{
				upButton->m_X = eraseButton[0]->m_X;
				eraseButton[0]->m_X = width * 2;
			}

			if (tempCounter == maxCount)
			{
				if (eraseButton[4]->m_X > width)
				{
					eraseButton[4]->m_X = downButton->m_X;
					downButton->m_X = width * 2;
				}
			}
			else
			{
				if (eraseButton[4]->m_X < width)
				{
					downButton->m_X = eraseButton[4]->m_X;
					eraseButton[4]->m_X = width * 2;
				}
			}
		}
		counter = tempCounter;


		for (int q = 3; q < 18; q++)
		{
			textFeildText[q]->m_Text = stringValues[(q - 3) + (tempCounter * 3)]->m_Text;
		}
	}
}


void Game::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	activeEvent = false;
	// Update base scene
	Scene::Update(deltaTime, alphaMul);

	if ((s3eKeyboardGetState(s3eKeyBack) & S3E_KEY_STATE_DOWN) || (s3eKeyboardGetState(s3eKeyBack) & S3E_KEY_STATE_PRESSED))
	{
		s3eDeviceRequestQuit();
	}
	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();

		if (iButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			PauseMenu* pause = new PauseMenu();
			pause->SetName("pausemenu");
			pause->Init();
			g_pSceneManager->Add(pause);
			g_pSceneManager->SwitchTo(g_pSceneManager->Find("pausemenu"));
			activeEvent = true;
		}

		else if (reset->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			if (checkBoxes != 0)
			{
				delete[] checkBoxes;
			}
			if (checkBoxText != 0)
			{
				delete[] checkBoxText;
			}
			if (textBoxes != 0)
			{
				delete[] textBoxes;
			}
			if (textFeildText != 0)
			{
				delete[] textFeildText;
			}
			if (stringValues != 0)
			{
				delete[] stringValues;
			}
			if (checkBoxesChecked != 0)
			{
				delete[] checkBoxesChecked;
			}
			if(eraseButton != 0)
			{
				delete[] eraseButton;
			}
			
			largestInput = 0;
			Init();
			activeEvent = true;
		}
		else if (teachPassiv->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			if (s3eOSExecAvailable())
			{
				s3eOSExecExecute("http://teachpassiv.com", S3E_FALSE);
			}
			activeEvent = true;
		}
		else if (upButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			Move(-1);
			activeEvent = true;
		}
		else if (downButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			Move(1);
			activeEvent = true;
		}

		else if (!heated)
		{
			if (heatedButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				if (!checked[0])
				{
					heated = !heated;

					heatSpriteChecked->m_X = heatedButton->m_X;
					heatedButton->m_X = width * 2;
					if (largestInput >= 2)
					{
						if (largestInput % 3 == 1)
						{
							largestInput -= 2;
						}
						else if (largestInput % 3 == 0)
						{
							largestInput--;
						}
						Calculate();
					}
				}
				activeEvent = true;
			}
		}
		else
		{
			if (heatSpriteChecked->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				if (!checked[0])
				{
					heated = !heated;
					heatedButton->m_X = heatSpriteChecked->m_X;
					heatSpriteChecked->m_X = width * 2;
					Calculate();
				}
				activeEvent = true;
			}
		}

		if (activeEvent == false)
		{
			for (int i = 0; i < numBoxes; i++)
			{
				//up to here ok
				if (!checked[i])
				{

					if (checkBoxes[i]->HitTest(g_pInput->m_X, g_pInput->m_Y))
					{

						swap(checked[i], i);
						checked[i] = !checked[i];
						activeEvent = true;


						if (i == 1)
						{
							checkBoxText[4]->m_X = checkBoxLabelStorage;
							checkBoxes[4]->m_X = checkBoxStorage;
						}
						else if (i != 4)
						{
							if (checked[4])
							{
								swap(checked[4], 4);

								checked[4] = !checked[4];
							}
							checkBoxesChecked[4]->m_X = width * 2;
							checkBoxText[4]->m_X = width * 2;
							checkBoxes[4]->m_X = width * 2;
							if (checked[4])
							{
								swap(checked[4], 4);
							}
						}

						if (i == 0)
						{
							heatedText->m_X = width * 2;
							heatedTextB->m_X = width * 2;

							heatedButton->m_X = width * 2;

							heatSpriteChecked->m_X = width * 2;

							if (heated)
							{
								heated = !heated;
							}

						}

						else
						{
							if (heatedText->m_X = width * 2)
							{
								heatedText->m_X = heatedTextStorage;
								heatedTextB->m_X = heatedTextStorage;

								heatedButton->m_X = heatedSpriteStorage;

								heatSpriteChecked->m_X = width * 2;
								if (heated)
								{
									heated = !heated;
								}
							}
						}
						//up to here working
						if (i != 4)
						{

							for (int k = 0; k < numBoxes - 1; k++)
							{

								if (k != i && checked[k])
								{

									//to uncheck pass in false
									swap(checked[k], k);

									checked[k] = !checked[k];

								}

							}

							if (i == 0 && heated)
							{
								heated = !heated;
								heatedButton->m_X = heatSpriteChecked->m_X;
								heatSpriteChecked->m_X = width * 2;
							}
						}
						Calculate();
						break;
					}

				}

				else
				{

					if (checkBoxesChecked[i]->HitTest(g_pInput->m_X, g_pInput->m_Y))
					{

						if (i == 1)
						{
							if (checked[4])
							{
								swap(checked[4], 4);
							}

							checkBoxesChecked[4]->m_X = width * 2;
							checkBoxText[4]->m_X = width * 2;
							checkBoxes[4]->m_X = width * 2;
						}

						else if (i == 0)
						{
							if (heatedText->m_X = width * 2)
							{
								heatedText->m_X = heatedTextStorage;
								heatedTextB->m_X = heatedTextStorage;

								heatedButton->m_X = heatedSpriteStorage;

								heatSpriteChecked->m_X = width * 2;
							}
						}
						swap(checked[i], i);
						activeEvent = true;
						checked[i] = !checked[i];
						Calculate();
						break;

					}

				}


			}

			if (!activeEvent)
			{
				for (int eraseCheck = 0; eraseCheck < 5; eraseCheck++)
				{
					if (eraseButton[eraseCheck]->HitTest(g_pInput->m_X, g_pInput->m_Y))
					{
						//delete text
						for (int l = 0; l < 3; l++)
						{
							textFeildText[(eraseCheck * 3) + 3 + l]->m_Text = "";
							stringValues[(eraseCheck * 3) + l + (counter * 3)]->m_Text = "";
						}

						inputConverted[(eraseCheck * 3) + 1 + (counter * 3)] = 0.0;
						inputConverted[(eraseCheck * 3) + 2 + (counter * 3)] = 0.0;
						activeEvent = true;
						int index = 1;
						largestInput = 0;
						while (inputConverted[index] > 0 || index % 3 == 0)
						{

							if (index % 3 != 0)
							{
								largestInput++;
							}
							if (index % 3 == 1)
							{
								largestInput++;
							}
							index++;

						}


						//everything up to here working
						if (largestInput >= 2)
						{
							if (largestInput % 3 == 1)
							{
								largestInput -= 2;
							}
							else if (largestInput % 3 == 0)
							{
								largestInput--;
							}
							Calculate();
						}
						else
						{
							resultLabel->m_Text = "";
							RSELabel->m_Text = "";
							RSILabel->m_Text = "";
						}
					}
				}
			}

			if (!activeEvent)
			{
				for (int k = 3; k < 18; k++)
				{
					if (textBoxes[k]->HitTest(g_pInput->m_X, g_pInput->m_Y))
					{
						const char* text;
						if (k % 3 == 0)
						{
							text = "Material";
						}
						else
						{
							if (k % 3 == 1)
							{
								text = "Thickness";
							}
							else
							{
								text = "Conductivity";
							}
						}


						const char *inputed = s3eOSReadStringUTF8WithDefault(text, stringValues[k - 3 + (counter * 3)]->m_Text.c_str(), 0);

						if (inputed != NULL)
						{
							std::string textA = inputed;

							std::string textB;

							if (inputed == NULL)
							{
								inputed = "";
								textB = inputed;
								textA = textB;
							}

							else
							{
								textA = inputed;
								if (textA.length() > 13)
								{
									textB = "";
									for (int o = 0; o < 10; o++)
									{
										textB += textA[o];
									}

									for (int y = 0; y < 3; y++)
									{
										textB += '.';
									}
								}
								else
								{
									textB = textA;
								}
							}
							stringValues[k - 3 + (counter * 3)]->m_Text = textA;
							textFeildText[k]->m_Text = textB;


							//if it is not text input
							if (k % 3 != 0)
							{
								//take in user input into the float array
								inputConverted[k - 3 + (3 * counter)] = ::atof(inputed);
								//if there is at least one input do the calculations
								largestInput = -1;

								int index = 1;
								while (inputConverted[index] != 0 || index % 3 == 0)
								{

									if (index % 3 != 0)
									{
										largestInput++;
									}
									if (index % 3 == 1)
									{
										largestInput++;
									}
									index++;

								}

								int counter = 0;
								int l;

								for (l = counter * 3; l < largestInput && counter < 5; l++)
								{
									counter++;
								}

								while (counter < 5)
								{
									counter++;
								}

								//everything up to here working
								if (largestInput >= 2)
								{
									if (largestInput % 3 == 1)
									{
										largestInput -= 2;
									}
									else if (largestInput % 3 == 0)
									{
										largestInput--;
									}
									Calculate();
								}
							}
						}
						break;
					}
				}
			}
		}
	}
	if (counterAd > 0)
	{
		counterAd++;
		if (counterAd % 100 == 0)
		{
			if (adId)
			{
				s3eAmazonAdsDestroyAd(adId);
				adId;
			}
			counterAd = 0;
		}
	}
	s3eDeviceYield(0);
}


void Game::Calculate()
{
	float results = 0.0;
	float delt;
	int p;
	for (p = 0; p <= largestInput; p++)
	{
		switch (p % 3)
		{
			case 1:
				delt = (float)inputConverted[p] / 1000;
				break;
			case 2:
				results += ((float)delt / inputConverted[p]);
				break;
		}
	}

	float RSE = 0.0;
	bool found = false;
	float RSI = 0.0;
	for (int n = 0; n < numBoxes; n++)
	{

		if (checked[n])
		{
			found = true;
			switch (n)
			{
			case 0:
				RSI = 0.17;
				break;

			case 1:
				RSI = 0.13;
				RSE = 0.04;
				break;

			case 2:
				RSI = 0.1;
				RSE = 0.04;
				break;

			case 3:
				RSI = 0.17;
				//RSE = 0.17 as it is not going outside
				RSE = 0.17;
				break;

			}

			if (heated)
			{
				RSE = RSI;
			}

			if (checked[4])
			{
				RSE = 0.0;
			}
			break;

		}

	}

	int scale[3] = { 3, 4, 4 };
	if (found && largestInput >= 2)
	{

		results = 1 / (RSE + results + RSI);
		std::ostringstream ss;
		ss << results;
		resultLabel->m_Text = "Uvalue = " + ss.str();

		resultLabel->m_Text += " W/(m2K)";

		ss.str(std::string());
		ss << RSE;

		RSELabel->m_Text = "RSE = " + ss.str();

		ss.str(std::string());
		ss << RSI;

		RSILabel->m_Text = "RSI = " + ss.str();

	}
	else
	{
		if (!found && largestInput >= 2)
		{
			RSILabel->m_Text = "Please tick a box above";
			RSELabel->m_Text = "";
		}
		else
		{

			RSILabel->m_Text = "";
			RSELabel->m_Text = "";
		}
		resultLabel->m_Text = "";
	}

}


void Game::Render()
{
	Scene::Render();
}

// Initialise the games user interface
void Game::initUI()
{

	width = IwGxGetScreenWidth();
	height = IwGxGetScreenHeight();
	// Create background
	CSprite* background = new CSprite();
	background->m_X = (float)width / 2;
	background->m_Y = (float)height / 2;
	background->SetImage(g_pResources->getGameBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size

	background->m_ScaleX = (float)width / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)height / background->GetImage()->GetHeight();
	AddChild(background);



}


void Game::Init()
{

	Scene::Init();

	// Check to see if the device that we are running on supports the keyboard
	KeysAvailable = (s3eKeyboardGetInt(S3E_KEYBOARD_HAS_KEYPAD) || s3eKeyboardGetInt(S3E_KEYBOARD_HAS_ALPHA));

	int fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;

	// Check to see if the device that we are running on supports the on screen keyboard
	OSKeyboardAvailable = s3eOSReadStringAvailable() == S3E_TRUE;

	// Initialise UI
	initUI();

	for (int h = 0; h < 15; h++)
	{
		inputConverted[h] = 0;
	}
	checkBoxes = new CSprite*[numBoxes];

	checkBoxesChecked = new CSprite*[numBoxes];

	teachPassiv = new CSprite();
	teachPassiv->SetImage(g_pResources->getPassivHouse());
	teachPassiv->m_X = (float)width - width / 4;
	teachPassiv->m_Y = (float)height - (teachPassiv->GetImage()->GetHeight() * (float)width / teachPassiv->GetImage()->GetWidth() / 2);
	teachPassiv->m_W = teachPassiv->GetImage()->GetWidth();
	teachPassiv->m_H = teachPassiv->GetImage()->GetHeight();
	teachPassiv->m_AnchorX = 0.5;
	teachPassiv->m_AnchorY = 0.5;

	teachPassiv->m_ScaleX = ((float)width / teachPassiv->GetImage()->GetWidth() / 2);
	teachPassiv->m_ScaleY = (float)width / teachPassiv->GetImage()->GetWidth() / 2;
	AddChild(teachPassiv);

	reset = new CSprite();
	reset->SetImage(g_pResources->getResetImage());
	reset->m_X = (float)(width * 0.15) + (width / 10);
	reset->m_Y = (float)height - (teachPassiv->GetImage()->GetHeight() * (float)width / teachPassiv->GetImage()->GetWidth() / 2);
	reset->m_W = reset->GetImage()->GetWidth();
	reset->m_H = reset->GetImage()->GetHeight();
	reset->m_AnchorX = 0.5;
	reset->m_AnchorY = 0.5;

	reset->m_ScaleX = ((float)width / reset->GetImage()->GetWidth() / 5);
	reset->m_ScaleY = (float)width / reset->GetImage()->GetWidth() / 5;
	AddChild(reset);

	iButton = new CSprite();
	iButton->SetImage(g_pResources->getIButton());
	iButton->m_X = (float)width - width / 15;
	iButton->m_Y = (float)width / 15;
	iButton->m_W = iButton->GetImage()->GetWidth();
	iButton->m_H = iButton->GetImage()->GetHeight();
	iButton->m_AnchorX = 0.5;
	iButton->m_AnchorY = 0.5;

	iButton->m_ScaleX = ((float)width / iButton->GetImage()->GetWidth() / 13);
	iButton->m_ScaleY = iButton->m_ScaleX;
	AddChild(iButton);

	uValue = new CSprite();
	uValue->SetImage(g_pResources->getUValue());
	uValue->m_X = (float)(width * 0.15) + (width / (2.5 * 2));
	uValue->m_Y = (float)height / 50;
	uValue->m_W = uValue->GetImage()->GetWidth();
	uValue->m_H = uValue->GetImage()->GetHeight();
	uValue->m_AnchorX = 0.5;

	uValue->m_ScaleX = ((float)width / uValue->GetImage()->GetWidth() / 2.5);
	uValue->m_ScaleY = (float)width / uValue->GetImage()->GetWidth() / 2.5;
	AddChild(uValue);

	checkBoxText = new CLabel*[numBoxes];

	stringValues = new CLabel*[15 + (maxCount * 3)];

	for (int l = 0; l < 15 + (maxCount * 3); l++)
	{
		stringValues[l] = new CLabel();
		stringValues[l]->m_Text = "";
		stringValues[l]->m_X = 0;
		stringValues[l]->m_Y = 0;
		stringValues[l]->m_W = 0;
		stringValues[l]->m_Color = CColor(0x00, 0x00, 0x00, 0x00);
		AddChild(stringValues[l]);
		stringValues[l]->m_Text = "";
	}

	int current;
	float firstDown = (float)uValue->m_ScaleY * uValue->m_H + (height / 100);
	// Create a gem
	for (int h = 0; h < 2; h++)
	{
		for (int i = 0; i < 3; i++)
		{
			current = i + (h * 3);
			checked[current] = false;
			checkBoxes[current] = new CSprite();
			checkBoxes[current]->SetImage(g_pResources->getCheckBox());
			checkBoxes[current]->m_X = (float)width / 36 + (width * 0.15) + ((width / 3) * i);
			checkBoxes[current]->m_Y = (float)firstDown + 20 + (h * (height / 17));
			checkBoxes[current]->m_W = checkBoxes[current]->GetImage()->GetWidth();
			checkBoxes[current]->m_ScaleX = ((float)width / checkBoxes[current]->GetImage()->GetWidth() / 13);
			checkBoxes[current]->m_ScaleY = (float)width / checkBoxes[current]->GetImage()->GetWidth() / 13;
			checkBoxes[current]->m_H = checkBoxes[i]->GetImage()->GetHeight();
			checkBoxes[current]->m_AnchorX = 0.5;
			AddChild(checkBoxes[current]);


			checked[current] = false;
			checkBoxesChecked[current] = new CSprite();
			checkBoxesChecked[current]->SetImage(g_pResources->getChecked());
			checkBoxesChecked[current]->m_X = (width * 2);
			checkBoxesChecked[current]->m_Y = checkBoxes[current]->m_Y;
			checkBoxesChecked[current]->m_W = checkBoxesChecked[current]->GetImage()->GetWidth();
			checkBoxesChecked[current]->m_ScaleX = ((float)width / checkBoxesChecked[current]->GetImage()->GetWidth() / 13);
			checkBoxesChecked[current]->m_ScaleY = (float)width / checkBoxesChecked[current]->GetImage()->GetWidth() / 13;
			checkBoxesChecked[current]->m_H = checkBoxesChecked[i]->GetImage()->GetHeight();
			checkBoxesChecked[current]->m_AnchorX = 0.5;
			AddChild(checkBoxesChecked[current]);

			// Create score label text
			checkBoxText[current] = new CLabel();
			checkBoxText[current]->m_X = (float)width / 36 + (width * 0.15) + (((width / 3) * (i))) + width / 18;
			checkBoxText[current]->m_Y = (float)checkBoxes[current]->m_Y;
			checkBoxText[current]->m_W = (float)width;
			if (width < 800)
			{
				checkBoxText[current]->m_H = 9 * (width / 800);
			}
			else
			{
				checkBoxText[current]->m_H = 9;
			}
			checkBoxText[current]->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
			checkBoxText[current]->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
			checkBoxText[current]->m_Font = g_pResources->getFont(height);
			checkBoxText[current]->m_W = FONT_DESIGN_WIDTH;
			checkBoxText[current]->m_ScaleX = fontScale;
			checkBoxText[current]->m_ScaleY = fontScale;
			checkBoxText[current]->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
			AddChild(checkBoxText[current]);

			if (current == 4)
			{
				break;
			}
		}
	}

	checkBoxStorage = checkBoxes[4]->m_X;

	checkBoxLabelStorage = checkBoxText[4]->m_X;

	checkBoxes[4]->m_X = width * 2;

	checkBoxesChecked[4]->m_X = width * 2;

	checkBoxText[4]->m_X = width * 2;


	textBoxes = new CSprite*[18];
	eraseButton = new CSprite*[5];
	textFeildText = new CLabel*[18];
	int scale[3] = { 3, 4, 4 };
	for (int l = 0; l < 6; l++)
	{

		totalOver = 0;
		if (l != 0)
		{

			eraseButton[l - 1] = new CSprite();
			eraseButton[l - 1]->SetImage(g_pResources->getEraseButton());
			eraseButton[l - 1]->m_X = width - (width / 24);
			eraseButton[l - 1]->m_Y = (float)firstDown + ((3 + l) * (height / 14)) + (height / 40);
			eraseButton[l - 1]->m_W = g_pResources->getEraseButton()->GetWidth();
			eraseButton[l - 1]->m_ScaleY = (float)(height / textBoxes[current]->GetImage()->GetHeight()) / 16;
			eraseButton[l - 1]->m_ScaleX = eraseButton[l - 1]->m_ScaleY;
			eraseButton[l - 1]->m_H = g_pResources->getEraseButton()->GetHeight();
			eraseButton[l - 1]->m_AnchorX = 0.5;
			AddChild(eraseButton[l - 1]);

		}

		for (int q = 0; q < 3; q++)
		{

			current = q + (l * 3);
			textBoxes[current] = new CSprite();
			textBoxes[current]->SetImage(g_pResources->getTextBox());
			textBoxes[current]->m_X = (float)(width / (scale[q] * 2)) + (width * 0.15) + totalOver;
			textBoxes[current]->m_Y = (float)firstDown + ((3 + l) * (height / 14));
			textBoxes[current]->m_W = textBoxes[current]->GetImage()->GetWidth();
			textBoxes[current]->m_ScaleX = ((float)width / textBoxes[current]->GetImage()->GetWidth() / scale[q]);
			textBoxes[current]->m_ScaleY = (float)(height / textBoxes[current]->GetImage()->GetHeight()) / 12;
			textBoxes[current]->m_H = textBoxes[current]->GetImage()->GetHeight();
			textBoxes[current]->m_AnchorX = 0.5;
			AddChild(textBoxes[current]);

			// Create score label text
			textFeildText[current] = new CLabel();
			textFeildText[current]->m_X = (float)(width / (scale[q] * 4)) + (width * 0.15) + totalOver - (width / 18);
			textFeildText[current]->m_Y = (float)firstDown + ((3 + l) * (height / 14)) + (height / 90);
			textFeildText[current]->m_W = (float)width;
			if (width < 800)
			{
				textFeildText[current]->m_H = 9 * (width / 800);
			}
			else
			{
				textFeildText[current]->m_H = 9;
			}
			textFeildText[current]->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
			textFeildText[current]->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
			textFeildText[current]->m_Font = g_pResources->getFont(height);
			textFeildText[current]->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
			textFeildText[current]->m_Text = "";
			textFeildText[current]->m_W = FONT_DESIGN_WIDTH;
			textFeildText[current]->m_ScaleX = fontScale;
			textFeildText[current]->m_ScaleY = fontScale;
			AddChild(textFeildText[current]);

			totalOver += width / scale[q];
		}
	}

	checkBoxText[0]->m_Text = "Ground slab";
	checkBoxText[1]->m_Text = "Wall";
	checkBoxText[2]->m_Text = "Roof";
	checkBoxText[3]->m_Text = "Ceiling";
	checkBoxText[4]->m_Text = "Underground";

	textFeildText[0]->m_Text = "Eg Mineral wool";
	textFeildText[1]->m_Text = "300 (in mm)";
	textFeildText[2]->m_Text = "0.035 W/mk";


	eraseButton[4]->m_X = width * 2;

	totalOver = 0;
	left = new CLabel();
	left->m_X = (float)(width / (scale[0] * 4)) + (width * 0.15) + totalOver - (width / 18);
	left->m_Y = (float)firstDown - (height / 20) + ((3) * (height / 14));
	left->m_W = (float)width;
	left->m_H = 11;
	left->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	left->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	left->m_Font = g_pResources->getFont(height);

	left->m_W = FONT_DESIGN_WIDTH;
	left->m_ScaleX = fontScale;
	left->m_ScaleY = fontScale;
	left->m_Color = CColor(0x00, 0x00, 0x00, 0xff);

	left->m_Text = "Material";

	AddChild(left);
	totalOver = width / scale[0];


	middle = new CLabel();
	middle->m_X = (float)(width / (scale[1] * 4)) + (width * 0.15) + totalOver - (width / 18);
	middle->m_Y = (float)(float)firstDown - (height / 20) + ((3) * (height / 14));
	middle->m_W = (float)width;
	middle->m_H = 11;
	middle->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	middle->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	middle->m_Font = g_pResources->getFont(height);
	middle->m_Color = CColor(0x00, 0x00, 0x00, 0xff);

	middle->m_Text = "Thickness";

	middle->m_W = FONT_DESIGN_WIDTH;
	middle->m_ScaleX = fontScale;
	middle->m_ScaleY = fontScale;

	AddChild(middle);

	totalOver += width / scale[1];

	right = new CLabel();
	right->m_X = (float)(width / (scale[2] * 4)) + (width * 0.15) + totalOver - (width / 18);
	right->m_Y = (float)(float)firstDown - (height / 20) + ((3) * (height / 14));
	right->m_W = (float)width;
	right->m_H = 11;
	right->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	right->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	right->m_Font = g_pResources->getFont(height);
	right->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	right->m_Text = "Conductivity";

	right->m_W = FONT_DESIGN_WIDTH;
	right->m_ScaleX = fontScale;
	right->m_ScaleY = fontScale;
	AddChild(right);




	downButton = new CSprite();
	downButton->SetImage(g_pResources->getDownButton());
	downButton->m_X = width - (width / 24);
	downButton->m_Y = textBoxes[17]->m_Y + height / 50;
	downButton->m_W = g_pResources->getDownButton()->GetWidth();
	downButton->m_ScaleX = ((float)width / g_pResources->getDownButton()->GetWidth() / 9);
	downButton->m_ScaleY = (float)(height / downButton->GetImage()->GetHeight()) / 17;
	downButton->m_H = g_pResources->getDownButton()->GetHeight();
	downButton->m_AnchorX = 0.5;
	AddChild(downButton);

	largestInput = 0;


	upButton = new CSprite();
	upButton->SetImage(g_pResources->getUpButton());
	upButton->m_X = width * 2;
	upButton->m_Y = textBoxes[5]->m_Y + height / 50;
	upButton->m_W = g_pResources->getUpButton()->GetWidth();
	upButton->m_ScaleX = downButton->m_ScaleX;
	upButton->m_ScaleY = (float)(height / upButton->GetImage()->GetHeight()) / 17;
	upButton->m_H = g_pResources->getUpButton()->GetHeight();
	upButton->m_AnchorX = 0.5;
	AddChild(upButton);


	resultLabel = new CLabel();
	resultLabel->m_X = textFeildText[1]->m_X - (width / 15);
	resultLabel->m_Y = height * 0.75;
	resultLabel->m_W = (float)width;
	resultLabel->m_H = 11;
	resultLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	resultLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	resultLabel->m_Font = g_pResources->getFont(height);
	resultLabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	resultLabel->m_Text = "";

	AddChild(resultLabel);


	resultLabel->m_W = FONT_DESIGN_WIDTH;
	resultLabel->m_ScaleX = fontScale;
	resultLabel->m_ScaleY = fontScale;


	RSELabel = new CLabel();
	RSELabel->m_X = textFeildText[0]->m_X;
	RSELabel->m_Y = height * 0.75;
	RSELabel->m_W = (float)width;
	RSELabel->m_H = 11;
	RSELabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	RSELabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	RSELabel->m_Font = g_pResources->getFont(height);
	RSELabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	RSELabel->m_Text = "";

	RSELabel->m_W = FONT_DESIGN_WIDTH;
	RSELabel->m_ScaleX = fontScale;

	RSELabel->m_ScaleY = fontScale;
	AddChild(RSELabel);


	RSILabel = new CLabel();
	RSILabel->m_X = textFeildText[0]->m_X;
	RSILabel->m_Y = height * 0.79;
	RSILabel->m_W = (float)width;
	RSILabel->m_H = 11;
	RSILabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	RSILabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	RSILabel->m_Font = g_pResources->getFont(height);
	RSILabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	RSILabel->m_Text = "";

	RSILabel->m_W = FONT_DESIGN_WIDTH;
	RSILabel->m_ScaleX = fontScale;

	RSILabel->m_ScaleY = fontScale;

	AddChild(RSILabel);


	heatedButton = new CSprite();
	heatedButton->SetImage(g_pResources->getCheckBox());
	heatedButton->m_X = (float)(width * 0.18);
	heatedButton->m_Y = (float)height * 0.83;
	heatedButton->m_W = heatedButton->GetImage()->GetWidth();
	heatedButton->m_H = heatedButton->GetImage()->GetHeight();
	heatedButton->m_AnchorX = 0.5f;
	heatedButton->m_AnchorY = 0;
	heatedButton->m_ScaleX = (float)width / heatedButton->GetImage()->GetWidth() / 13;
	heatedButton->m_ScaleY = (float)width / heatedButton->GetImage()->GetHeight() / 13;
	AddChild(heatedButton);


	heatedText = new CLabel();
	heatedText->m_X = (float)(width * 0.16) + width / 15;
	heatedText->m_Y = (float)height * 0.83;
	heatedText->m_W = (float)width;
	heatedText->m_H = 11;
	heatedText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	heatedText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	heatedText->m_Font = g_pResources->getFont(height);
	heatedText->m_Color = CColor(0x00, 0x00, 0x00, 0xff);

	heatedText->m_W = FONT_DESIGN_WIDTH;
	heatedText->m_ScaleX = fontScale;

	heatedText->m_ScaleY = fontScale;
	heatedText->m_Text = "Check if space is unheated";

	heatedTextB = new CLabel();
	heatedTextB->m_X = (float)(width * 0.16) + width / 15;
	heatedTextB->m_Y = (float)height * 0.85;
	heatedTextB->m_W = (float)width;
	heatedTextB->m_H = 11;
	heatedTextB->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	heatedTextB->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	heatedTextB->m_Font = g_pResources->getFont(height);
	heatedTextB->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	heatedTextB->m_W = FONT_DESIGN_WIDTH;
	heatedTextB->m_ScaleX = fontScale;

	heatedTextB->m_ScaleY = fontScale;
	heatedTextB->m_Text = "Or a cold roof or a rainscreen.";

	heatedTextStorage = heatedText->m_X;
	AddChild(heatedText);

	AddChild(heatedTextB);

	heated = false;

	heatSpriteChecked = new CSprite();
	heatSpriteChecked->SetImage(g_pResources->getChecked());
	heatSpriteChecked->m_X = width * 2;
	heatSpriteChecked->m_Y = (float)height * 0.83;
	heatSpriteChecked->m_W = heatSpriteChecked->GetImage()->GetWidth();
	heatSpriteChecked->m_H = heatSpriteChecked->GetImage()->GetHeight();
	heatSpriteChecked->m_AnchorX = 0.5f;
	heatSpriteChecked->m_AnchorY = 0;
	heatSpriteChecked->m_ScaleX = (float)width / heatSpriteChecked->GetImage()->GetWidth() / 13;
	heatSpriteChecked->m_ScaleY = (float)width / heatSpriteChecked->GetImage()->GetHeight() / 13;
	AddChild(heatSpriteChecked);


	heatedSpriteStorage = heatedButton->m_X;
	counter = 0;



}