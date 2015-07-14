//
//  Jellyfish.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/14.
//
//

#ifndef __jellyrun__Jellyfish__
#define __jellyrun__Jellyfish__

#include "cocos2d.h"

class Jellyfish : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Jellyfish);
    
protected:
    bool init() override;
    
};

#endif /* defined(__jellyrun__Jellyfish__) */
