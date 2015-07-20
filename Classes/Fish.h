//
//  Fish.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/17.
//
//

#ifndef __jellyrun__Fish__
#define __jellyrun__Fish__


#include "cocos2d.h"

class Fish : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Fish);
    
protected:
    bool init() override;
    
};

#endif /* defined(__jellyrun__Fish__) */
