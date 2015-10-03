#include "rock.h"
#include "game.h"
#include "resources.h"


Rock::~Rock()
{
}

void Rock::init(float x, float y)
{
	m_X = x;
	m_Y = y;
	hit = false;
}

// Explode gem
void Rock::hitRock()
{
	if (!hit)
	{
		hit = true;
		if (coin)
		{
			this->SetImage(g_pResources->getTrans());
		}
		else
		{
			this->SetImage(g_pResources->getRockImage(hit));
		}
	}
}




