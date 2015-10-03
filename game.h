#if !defined(__GAME_H__)
#define __GAME_H__

#include "scene.h"
#include "s3eAmazonAds.h"

class Game : public Scene
{
protected:
    int                 currentRoundScore;              // Current round score

	int counterAd;
	s3eAmazonAdsId adId;
    // UI components
    CLabel*             scoreLabel;
	CLabel*				RSILabel;
	CLabel*				RSELabel;
	CLabel*             resultLabel;
    CSprite*            pauseSprite;
	CSprite*			teachPassiv;
	CSprite*			uValue;
	CSprite*			iButton;
	CSprite*			upButton;
	CSprite*			downButton;
    CSprite**            checkBoxes;

	CSprite**			checkBoxesChecked;

	CSprite**            textBoxes;

	CLabel**			checkBoxText;

	CLabel**			stringValues;

	CLabel**			textFeildText;

	CLabel*			left;

	CLabel*			middle;

	CLabel*				right;

	CSprite**		eraseButton;
	CSprite*	heatedButton;

	CSprite*    heatSpriteChecked;

	CSprite*	reset;


	CLabel*		heatedText;

	CLabel*		heatedTextB;


	char**				input;

	int counter;

private:
    void            initUI();
	void			Calculate();
public:
    Game() {}
    ~Game();

    // initialise the game
    void            Init();

    // Update the game
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the game
    void            Render();

	void			Move(int updown);

    void            switchToScene(const char* scene_name);
    void            addToRoundScore(int score);
    void            pauseGame();
    void            resumeGame();
    void            newGame();
	void			makeTextBox();
	const char*		showOnScreenKeyboard(const char* prompt, int flags, const char* default_text);

	bool			checked[6];

	void			swap(bool ch, int i);
	int totalOver;
	int				height;

	int				width;

	bool			pressed2;

	bool			KeysAvailable;

	bool			OSKeyboardAvailable;

	bool			activeEvent;

	int				numTextBoxes;


	int		largestInput;

	bool heated;

	int checkBoxLabelStorage;
	int			checkBoxStorage;

	int heatedTextStorage;

	int heatedSpriteStorage;

};

#endif  // __GAME_H__


