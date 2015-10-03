#if !defined(__OPTIONSMENU_H__)
#define __OPTIONSMENU_H__

#include "scene.h"

class OptionsMenu : public Scene
{
protected:
	int highScore;
	bool runBefore;
    // UI components
	CLabel*		highScoreLabel;
    CSprite*    playButton;
    CSprite*    playText;
	CSprite*	PlayGameButton;
	CSprite*	OptionsButton;
	CSprite*	backtoMainMenu;

public:
	OptionsMenu() {}
    ~OptionsMenu();

    // initialise the menu
    void            Init();

	void			Render();

    // Update the menu
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
};

#endif  // __MAINEMENU_H__


