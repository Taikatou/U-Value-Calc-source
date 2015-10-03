#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
    // Load images
	checkBoxUnChecked = Iw2DCreateImage("textures/checkBox.png");
    GameBG = Iw2DCreateImage("textures/spiral.jpg");
	checkedBox = Iw2DCreateImage("textures/checkBoxMarked.png");
	back = Iw2DCreateImage("textures/backButton.png");
	resetImage = Iw2DCreateImage("textures/reset.png");
	iButtonImg = Iw2DCreateImage("textures/iButton.png");


	eraseButtonImage = Iw2DCreateImage("textures/newclose.png");

	passivHouse = Iw2DCreateImage("textures/teachPassivTrans.png");
	uValue = Iw2DCreateImage("textures/UValueTrans.png");
	textBox = Iw2DCreateImage("textures/textBox.png");

	downButtonImage = Iw2DCreateImage("textures/downButton.png");
	upButtonImage = Iw2DCreateImage("textures/upButton.png");



	transparent = Iw2DCreateImage("textures/transparent.png");
	resultBoxImage = Iw2DCreateImage("textures/resultBox.png");
    // Load fonts
    Font = Iw2DCreateFont("fonts/arial8.gxfont");
	FontB = Iw2DCreateFont("fonts/arial14.gxfont");

	infoButtonIcon = Iw2DCreateImage("textures/info.png");
	infoTextImage = Iw2DCreateImage("textures/information_text.png");
}

Resources::~Resources()
{
	delete checkBoxUnChecked;

    delete GameBG;
    delete Font;
	delete checkedBox;
	delete FontB;
	delete passivHouse;
	delete uValue;
	delete iButtonImg;
	delete back;
	delete resetImage;
	delete textBox;
	delete transparent;
	delete resultBoxImage;
	delete downButtonImage;
	delete upButtonImage;
	delete infoButtonIcon;
	delete infoTextImage;
	delete eraseButtonImage;
}

// Global resources
Resources* g_pResources = 0;



