//
//  AStarLayer.cpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/14.
//
//

#include "AStarLayer.hpp"

USING_NS_CC;

AStarLayer *AStarLayer::createAStarLayer(){
    AStarLayer *astarLayer = new (std::nothrow) AStarLayer();
    if (astarLayer && astarLayer->init()){
        astarLayer->autorelease();
        return astarLayer;
    }
    
    delete astarLayer;
    astarLayer = nullptr;
    return nullptr;
}

void AStarLayer::onEnter(){
    Layer::onEnter();
    
    _addCheckNodeListener = EventListenerCustom::create("AddCheckNode", [&](EventCustom *eventCustom){
        
        AStarDataNode *userData = static_cast<AStarDataNode *>(eventCustom->getUserData());
        Sprite *checkNode = Sprite::create("res/astar_check.png");
        checkNode->setAnchorPoint(Vec2(0, 0));
        checkNode->setPosition(userData->column * 20, userData->row * 20);
        this->addChild(checkNode, 5);
        
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_addCheckNodeListener, this);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    AStarDataNode beginNode = AStarDataNode(5, 5, true);
    AStarDataNode targetNode = AStarDataNode(90, 50, true);
    
    Sprite *beginNodeSprite = Sprite::create("res/astar_pathfinder.png");
    beginNodeSprite->setAnchorPoint(Vec2(0, 0));
    beginNodeSprite->setPosition(beginNode.column * 20, beginNode.row * 20);
    this->addChild(beginNodeSprite, 5);
    Sprite *targetNodeSprite = Sprite::create("res/astar_pathfinder.png");
    targetNodeSprite->setAnchorPoint(Vec2(0, 0));
    targetNodeSprite->setPosition(targetNode.column * 20, targetNode.row * 20);
    this->addChild(targetNodeSprite, 10);
    
    Label *starFindPathMenuItemLabel = Label::createWithSystemFont("开始", "Arial", 50);
    starFindPathMenuItemLabel->setColor(Color3B(0, 0, 0));
    MenuItemLabel *starFindPathMenuItem = MenuItemLabel::create(starFindPathMenuItemLabel, [&, beginNode, targetNode](Ref *sender){
        CCLOG("开始寻路");
        
        startTime = clock();
        
        std::vector<AStarDataNode> path = aStar(astarData, beginNode, targetNode);
        
        _calculateAStarTime();
        
        
        
        CCLOG("Path: %d", static_cast<int>(path.size()));
        for (std::vector<AStarDataNode>::iterator iter = path.begin(); iter != path.end(); ++iter){
            //        CCLOG("(%d, %d)", static_cast<int>(iter->column), static_cast<int>(iter->row));
            Sprite *path = Sprite::create("res/astar_pathfinder.png");
            path->setAnchorPoint(Vec2(0, 0));
            path->setPosition(iter->column * 20, iter->row * 20);
            this->addChild(path, 5);
        }
        
    });
    Menu *starFindPathMenu = Menu::create(starFindPathMenuItem, NULL);
    starFindPathMenu->setPosition(visibleSize.width - 100, 50);
    this->addChild(starFindPathMenu, 100);
    
}

void AStarLayer::onExit(){
    Layer::onExit();
    
    if (_addCheckNodeListener){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_addCheckNodeListener);
    }
}

bool AStarLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    LayerColor *backgroundColorLayer = LayerColor::create(Color4B(255, 255, 255, 255), visibleSize.width, visibleSize.height);
    this->addChild(backgroundColorLayer, 0);
    
    _tiledMap = TMXTiledMap::create("res/astar.tmx");
    _walkableLayer = _tiledMap->getLayer("walkable");
//    Size mapSize = _tiledMap->getMapSize();
//    Size tileSize = _tiledMap->getTileSize();
//    
//    CCLOG("MapSize:(%f, %f), TileSize:(%f, %f)", mapSize.width, mapSize.height, tileSize.width, tileSize.height);
    Size layerSize = _walkableLayer->getLayerSize();
    Size layerTileSize = _walkableLayer->getMapTileSize();
    tileSize = layerTileSize;
    mapSize = layerSize;
//    CCLOG("LayerSize:(%f, %f), LayerTileSize:(%f, %f)", layerSize.width, layerSize.height, layerTileSize.width, layerTileSize.height);
    
    _walkableLayer->setAnchorPoint(Vec2(0, 0));
    _walkableLayer->setPosition(0, 0);
    this->addChild(_walkableLayer, 1);
    
    _makeWableableData();
    
    return true;
}

void AStarLayer::_calculateAStarTime(){
    finishTime = clock();
    std::cout << "AstarTime:" << static_cast<double>(finishTime - startTime) / CLOCKS_PER_SEC << std::endl;
}

void AStarLayer::_makeWableableData(){
    
    AStarDataNode astarDataArray[100][60];
    
    for (int column = 0; column < mapSize.width; ++column){
        for (int row = 0; row < mapSize.height; ++row){
            Vec2 tileCoord = Vec2(static_cast<int>(column), static_cast<int>(mapSize.height - row - 1));
            int tileGID = _walkableLayer->getTileGIDAt(tileCoord);
//            CCLOG("TileGID:%d, Coord:(%f, %f)", tileGID, tileCoord.x, tileCoord.y);
            if (tileGID > 0){
                
                Value value = _tiledMap->getPropertiesForGID(tileGID);
                ValueMap valueMap = value.asValueMap();
                int isWalkable = valueMap["walkable"].asInt();
                
//                CCLOG("TileGID:%d, Coord:(%f, %f), IsWalkable:%d", tileGID, tileCoord.x, tileCoord.y, isWalkable);
                int x = static_cast<int>(tileCoord.x);
                int y = 59 - static_cast<int>(tileCoord.y);
                
                astarDataArray[x][y].column = x;
                astarDataArray[x][y].row = y;
                astarDataArray[x][y].walkable = isWalkable;
                
            }
            
        }
    }
    
//    CCLOG("AStarDataNodeArray:");
    for (int i = 0; i < 100; ++i){
        std::vector<AStarDataNode> oneList;
        for (int j = 0; j < 60; ++j){
//            printf("%d", astarDataArray[i][j].walkable);
//            printf("(%d, %d, %d)", astarDataArray[i][j].column, astarDataArray[i][j].row, astarDataArray[i][j].walkable);
            
            AStarDataNode astarDataNode = AStarDataNode(i, j, astarDataArray[i][j].walkable);
            oneList.push_back(astarDataNode);
        }
        astarData.push_back(oneList);
//        printf("\n");
    }
    
//    CCLOG("AstarDataNodeVector:");
//    for (int i = 0; i < 100; ++i){
//        for (int j = 0; j < 60; ++j){
//            printf("%d", astarData[i][j].walkable);
////            printf("i:%d, Col:%d j:%d, Row:%d\n", i, astarData[i][j].column, j, astarData[i][j].row);
//        }
//        printf("\n");
//    }
    
}

