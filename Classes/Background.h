//
//  Background.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/04.
//
//

#ifndef __jellyrun__Background__
#define __jellyrun__Background__

#include "cocos2d.h"
#include "InfiniteParallaxNode.h"

using namespace cocos2d;

class Background : public InfiniteParallaxNode
{
public:
    CREATE_FUNC(Background);
    Sprite *shipwreckBG1;
    Sprite *shipwreckBG2;
    Sprite *underwaterBG1;
    Sprite *underwaterBG2;
    Sprite *rockBG1;
    Sprite *rockBG2;
    Sprite *aquaticBG1;
    Sprite *aquaticBG2;
    Sprite *coralBG1;
    Sprite *coralBG2;

    void setBackgroundToMove();

protected:
    bool init() override;

};

#endif /* defined(__jellyrun__Background__) */
