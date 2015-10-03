#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__


#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
protected:
    CIw2DImage*     checkBoxUnChecked;
    CIw2DImage*     GameBG;
	CIw2DImage*     checkedBox;
	CIw2DImage*     passivHouse;
	CIw2DImage*     iButtonImg;
	CIw2DImage*     back;
	CIw2DImage*     uValue;
	CIw2DImage*		textBox;
	CIw2DImage*		resetImage;

	CIw2DImage*		infoTextImage;

	CIw2DImage*		transparent;
	CIw2DImage*		resultBoxImage;

	CIw2DImage*		downButtonImage;

	CIw2DImage*		upButtonImage;

	CIw2DImage*		infoButtonIcon;

	CIw2DImage*		eraseButtonImage;

    CIw2DFont*      Font;
	CIw2DFont*      FontB;

public:
	CIw2DImage*     getCheckBox()                    { return checkBoxUnChecked; }
    CIw2DImage*     getGameBG()                 { return GameBG; }
	CIw2DImage*     getGameBGB()                 { return GameBG; }
	CIw2DImage*     getChecked()              { return checkedBox; }
	CIw2DImage*     getPassivHouse()              { return passivHouse; }
	CIw2DImage*     getIButton()              { return iButtonImg; }
	CIw2DImage*     getUValue()              { return uValue; }
	CIw2DImage*     getBackButton()              { return back; }
	CIw2DImage*     getResetImage()              { return resetImage; }
	CIw2DFont*      getFont(int w)                  { 
														{ return Font; }

													}
	CIw2DImage*      getTextBox()                   { return textBox; }
	CIw2DImage*      getTrans()                   { return transparent; }
	CIw2DImage*      getResultBox()                   { return resultBoxImage; }

	CIw2DImage*      getDownButton()                   { return downButtonImage; }


	CIw2DImage*      getUpButton()                   { return upButtonImage; }


	CIw2DImage*      getInfoButton()                   { return infoButtonIcon; }


	CIw2DImage*      getInfoText()                   { return infoTextImage; }


	CIw2DImage*      getEraseButton()                   { return eraseButtonImage; }


public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


