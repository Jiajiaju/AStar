//
//  AStarLayer.hpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/14.
//
//

#ifndef AStarLayer_hpp
#define AStarLayer_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include "cocos2d.h"

#include "AstarAlgorithms.hpp"

class AStarLayer: public cocos2d::Layer{
public:
    
    static AStarLayer *createAStarLayer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::Size tileSize;
    cocos2d::Size mapSize;
    std::vector<std::vector<AStarDataNode>> astarData;
    
private:
    
    cocos2d::TMXTiledMap *_tiledMap;
    cocos2d::TMXLayer *_walkableLayer;
    
    cocos2d::EventListenerCustom *_addCheckNodeListener;
    
    void _makeWableableData();
    clock_t startTime;
    clock_t finishTime;
    
    void _calculateAStarTime();
    
};

#endif /* AStarLayer_hpp */
