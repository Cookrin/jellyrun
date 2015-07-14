//
//  SceneManager.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#ifndef __jellyrun__SceneManager__
#define __jellyrun__SceneManager__

#include "cocos2d.h"

class SceneManager {
public:
    static SceneManager *getInstance();
    
    void enterGameScene(bool networked);
    
    void enterLobby();
    
private:
    SceneManager();
    ~SceneManager();
};

#endif /* defined(__jellyrun__SceneManager__) */
