#if !defined(__ROCK_H)
#define __ROCK_H

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


/**
* @class Gem
*
* @brief A game gem.
*
* The game grid consists of a collection of Gems. Each gem has its own type and sprite node associated with it
*/
class Rock : public CSprite
{
protected:
	bool hit;
	bool coin;
public:
	
public:
	Rock() : hit(false) {}

	~Rock();
	void init(float x, float y);
	void hitRock();
	bool getHit() { return hit; }
	void reset() { hit = false; }
	void isCoin(bool c) { coin = c; }
	bool getCoin() { return coin; }
};

#endif  // __GEM_H
