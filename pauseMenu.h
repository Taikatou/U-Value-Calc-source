#if !defined(__PAUSEMENU_H__)
#define __PAUSEMENU_H__

#include "scene.h"
#include "Iw2D.h"
#include "s3eAmazonAds.h"

class PauseMenu : public Scene
{
protected:
    // UI components
    CSprite*    backButton;
	CSprite*	infoButton;
	CSprite*	infoText;

	s3eAmazonAdsId adId;

	bool add;

	bool shown;


public:
    CSprite*    getBackButton()     { return backButton; }

	CIw2DFont* pFont2D;

public:
    PauseMenu() {}
    ~PauseMenu();

	void resume();

    // initialise the menu
    void            Init();
    // Update the menu
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the menu
    void            Render();

};

#endif  // __PAUSEMENU_H__


