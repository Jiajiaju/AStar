//
//  AStarScene.cpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/14.
//
//

#include "AStarScene.hpp"
#include "AStarLayer.hpp"

USING_NS_CC;

AStarScene *AStarScene::createAStarScene(){
    AStarScene *astarScene = new (std::nothrow) AStarScene();
    if (astarScene && astarScene->init()){
        astarScene->autorelease();
        return astarScene;
    }
    
    delete astarScene;
    astarScene = nullptr;
    return nullptr;
}

bool AStarScene::init(){
    if (!Scene::init()){
        return false;
    }
    
    _astarLayer = AStarLayer::createAStarLayer();
    this->addChild(_astarLayer, 1);
    
    return true;
}


