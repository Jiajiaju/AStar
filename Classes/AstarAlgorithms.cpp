//
//  AstarAlgorithms.cpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/16.
//
//

#include "AstarAlgorithms.hpp"
#include <algorithm>
#include <math.h>

int calculateGValue(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode){
    if (currentNode->row == row || currentNode->column == column){
        return 10;
    }else {
        return 14;
    }
}

int calculateHValueZero(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode){
    return 0;
}

int calculateHValueManhattan(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode){
    return (abs(static_cast<int>(targetNode.column - column)) + abs(static_cast<int>(targetNode.row - row))) * 10;
}

int calculateHValueDiagonal(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode){
    int nOfDiagonal = MIN(abs(column - targetNode.column), abs(row - targetNode.row));
    int nOfStraight = abs(static_cast<int>(targetNode.column - column)) + abs(static_cast<int>(targetNode.row - row));
    int FVaule = nOfDiagonal * 14 + (nOfStraight - 2 * nOfDiagonal) * 10;
    return FVaule;
}
int calculateHValueEuclid(int column, int row, AStarNode *currentNode, const AStarDataNode &beginNode, const AStarDataNode &targetNode){
    int distance = static_cast<int>(sqrt((column - targetNode.column)*(column - targetNode.column) + (row - targetNode.row)*(row - targetNode.row)));
    return distance * 10;
}

void aStarDealNeighborNode(
                           const std::vector<std::vector<AStarDataNode>> &astarData,
                           std::vector<AStarNode *> &openList,
                           std::vector<AStarNode *> &closeList,
                           AStarNode *currentNode,
                           const AStarDataNode &beginNode,
                           const AStarDataNode &targetNode
                           )
{
    int maxColumn = static_cast<int>(astarData.size());
    int maxRow = static_cast<int>(astarData[0].size());
    
    for (int column = currentNode->column - 1; column < currentNode->column + 2; ++column){
        for (int row = currentNode->row - 1; row < currentNode->row + 2; ++row){
//            printf("(%d, %d)", column, row);
            if (column < 0 || column >= maxColumn || row < 0 || row >= maxRow){
                continue;
            }
            
            if (!astarData[column][row].walkable){
                continue;
            }
            
            bool isInCloseList = false;
            for (std::vector<AStarNode *>::iterator iter = closeList.begin(); iter != closeList.end(); ++iter){
                if (column == (*iter)->column && row == (*iter)->row){
                    isInCloseList = true;
                    break;
                }
            }
            if (isInCloseList){
                continue;
            }
            
            cocos2d::EventCustom event("AddCheckNode");
            AStarDataNode *testUserData = new (std::nothrow) AStarDataNode(column, row, true);
            event.setUserData(testUserData);
            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
            
            bool isInOpenList = false;
            AStarNode *nodeInOpenList;
            for (std::vector<AStarNode *>::iterator iter = openList.begin(); iter != openList.end(); ++iter){
                if (column == (*iter)->column && row == (*iter)->row){
                    isInOpenList = true;
                    nodeInOpenList = (*iter);
                    break;
                }
            }
            int GValue = currentNode->GValue + calculateGValue(column, row, currentNode, beginNode, targetNode);
            int HValue = calculateHValueZero(column, row, currentNode, beginNode, targetNode);
//            int HValue = calculateHValueManhattan(column, row, currentNode, beginNode, targetNode);
//            int HValue = calculateHValueDiagonal(column, row, currentNode, beginNode, targetNode);
//            int HValue = calculateHValueEuclid(column, row, currentNode, beginNode, targetNode);
            int FValue = GValue + HValue;
            if (isInOpenList){
                if (FValue < nodeInOpenList->FValue){
                    nodeInOpenList->GValue = GValue;
                    nodeInOpenList->HValue = HValue;
                    nodeInOpenList->FValue = FValue;
                    nodeInOpenList->parentNode = currentNode;
                }
            }else {
                AStarNode *newNode = new (std::nothrow) AStarNode(column, row, FValue, GValue, HValue, currentNode);
                openList.push_back(newNode);
            }
        }
    }
}

std::vector<AStarDataNode> aStar(
                                 const std::vector<std::vector<AStarDataNode>> &astarData,
                                 const AStarDataNode &beginNode,
                                 const AStarDataNode &targetNode
                                 )
{
    
    std::vector<AStarNode *> openList;
    std::vector<AStarNode *> closeList;
    
    AStarNode *beginAStarNode = new (std::nothrow) AStarNode(beginNode.column, beginNode.row, 0, 0, 0, nullptr);
    AStarNode *currentAStarNode;
    openList.push_back(beginAStarNode);
    
    while (!openList.empty()){
        
        currentAStarNode = openList[0];
//        printf("Find Min\n");
        for (std::vector<AStarNode *>::iterator iter = openList.begin(); iter != openList.end(); ++iter){
//            (*iter)->print();
            if (currentAStarNode->FValue > (*iter)->FValue){
                currentAStarNode = (*iter);
            }
        }
        
        for (std::vector<AStarNode *>::iterator iter = openList.begin(); iter != openList.end(); ++iter){
            if (currentAStarNode->column == (*iter)->column && currentAStarNode->row == (*iter)->row){
                openList.erase(iter);
                break;
            }
        }
        
        if (currentAStarNode->column == targetNode.column && currentAStarNode->row == targetNode.row){
            std::vector<AStarDataNode> path;
            while (currentAStarNode) {
                AStarDataNode astarDataNode = AStarDataNode(currentAStarNode->column, currentAStarNode->row, true);
                path.push_back(astarDataNode);
                currentAStarNode = currentAStarNode->parentNode;
            }
            return path;
        }
        
        closeList.push_back(currentAStarNode);
        
//        printf("CurrentNode: ");
//        currentAStarNode->print();
//
        aStarDealNeighborNode(astarData, openList, closeList, currentAStarNode, beginNode, targetNode);
        
//        printf("VectorSize:(%d, %d)\n", static_cast<int>(openList.size()), static_cast<int>(closeList.size()));
        
    }
    
    std::vector<AStarDataNode> emptyPath;
    return emptyPath;
    
}