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
#include "AStarCustomClass.hpp"
#include "BinaryHeap.hpp"

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

void aStarDealNeighborNode(
                           const std::vector<std::vector<AStarDataNode>> &astarData,
                           BinaryHeap<AStarNode *> &openList,
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
