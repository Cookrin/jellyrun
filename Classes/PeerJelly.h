//
//  PeerJelly.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/30.
//
//

#ifndef __jellyrun__PeerJelly__
#define __jellyrun__PeerJelly__

#include "cocos2d.h"
#include "JSONPacker.h"

class PeerJelly : public cocos2d::Sprite
{
public:
    CREATE_FUNC(PeerJelly);

private:
    bool init() override;
    cocos2d::RepeatForever *moving();
};

#endif /* defined(__jellyrun__PeerJelly__) */
