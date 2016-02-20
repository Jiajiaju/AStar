//
//  AstarAlgorithms.hpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/16.
//
//

#ifndef AstarAlgorithms_hpp
#define AstarAlgorithms_hpp

#include <stdio.h>
#include "cocos2d.h"

class AStarDataNode{
public:
    int column = 0;
    int row    = 0;
    bool walkable = 0;
    
    AStarDataNode(){}
    
    AStarDataNode(int argumentColumn, int argumentRow, bool argumentWalkable):
    column(argumentColumn), row(argumentRow), walkable(argumentWalkable) {}
    
    void print(){
        printf("(Col:%d, Row:%d, Wal:%d)\n", column, row, walkable);
    }
};

class AStarNode{
public:
    int column = 0;
    int row    = 0;
    
    int FValue = 0;
    int GValue = 0;
    int HValue = 0;
    
    AStarNode *parentNode = nullptr;
    
    AStarNode(int argumentColumn, int argumentRow, int argumentF, int argumentG, int argumentH, AStarNode *argumentParent):
    column(argumentColumn), row(argumentRow), FValue(argumentF), GValue(argumentG), HValue(argumentH), parentNode(argumentParent) {}
    
    void print(){
        if (parentNode){
            printf("(Col:%d, Row:%d, F:%d, G:%d, H:%d, parent:(Col:%d, Row:%d))\n", column, row, FValue, GValue, HValue, parentNode->column, parentNode->row);
        }else {
            printf("(Col:%d, Row:%d, F:%d, G:%d, H:%d, parent:nullptr)\n", column, row, FValue, GValue, HValue);
        }
        
    }
};

std::vector<AStarDataNode> aStar(
                                 const std::vector<std::vector<AStarDataNode>> &astarData,
                                 const AStarDataNode &beginNode,
                                 const AStarDataNode &targetNode
                                 );

void aStarDealNeighborNode(
                           const std::vector<std::vector<AStarDataNode>> &astarData,
                           std::vector<AStarNode *> &openList,
                           std::vector<AStarNode *> &closeList,
                           AStarNode *currentNode,
                           const AStarDataNode &beginNode,
                           const AStarDataNode &targetNode
                           );

int calculateGValue(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode);

int calculateHValueZero(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode);
int calculateHValueManhattan(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode);
int calculateHValueDiagonal(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode);
int calculateHValueEuclid(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode);

#endif /* AstarAlgorithms_hpp */
