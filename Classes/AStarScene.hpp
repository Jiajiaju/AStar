//
//  AStarScene.hpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/14.
//
//

#ifndef AStarScene_hpp
#define AStarScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class AStarLayer;

class AStarScene: public cocos2d::Scene{
public:
    static AStarScene *createAStarScene();
    
    virtual bool init();
    
private:
    
    AStarLayer *_astarLayer;
    
};


#endif /* AStarScene_hpp */
