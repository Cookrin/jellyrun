//
//  BarrierLayer.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/13.
//
//

#ifndef __jellyrun__BarrierLayer__
#define __jellyrun__BarrierLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class BarrierLayer : public Layer
{
public:
    BarrierLayer();
    ~BarrierLayer();
    bool init();
    CREATE_FUNC(BarrierLayer);
};

#endif /* defined(__jellyrun__BarrierLayer__) */
