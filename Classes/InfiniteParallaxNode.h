//
//  InfiniteParallaxNode.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/23.
//
//

#ifndef __jellyrun__InfiniteParallaxNode__
#define __jellyrun__InfiniteParallaxNode__

#include "cocos2d.h"

using namespace cocos2d;

class InfiniteParallaxNode : public ParallaxNode
{
public:
    static InfiniteParallaxNode* create();
    void updatePosition();
};


#endif /* defined(__jellyrun__InfiniteParallaxNode__) */
