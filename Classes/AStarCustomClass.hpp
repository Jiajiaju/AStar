//
//  AStarCustomClass.hpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/21.
//
//

#ifndef AStarCustomClass_hpp
#define AStarCustomClass_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>

class AStarException {
public:
    AStarException(const std::string &exceptionMessage):
    _exceptionMessage(exceptionMessage) {
        std::cout << "AStarException" <<std::endl;
    }
    
private:
    std::string _exceptionMessage;
};

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
    
    bool operator==(const AStarNode &rhs){
        
        if (this == &rhs || (this->column == rhs.column && this->row == rhs.row)){
            return true;
        }
        return false;
//        try {
//            if (this == &rhs || (this->column == rhs.column && this->row == rhs.row)){
//                throw AStarException("Try To Compare Two Same Object");
//            }
//            
//            return this->FValue == rhs.FValue;
//        }catch(AStarException &exception){
//            return true;
//        }
    }
    
    bool operator==(const AStarNode *rhs){
        if (this == rhs || (this->column == rhs->column && this->row == rhs->row)){
            return true;
        }
        return false;
//        try {
//            if (this == rhs || (this->column == rhs->column && this->row == rhs->row)){
//                throw AStarException("Try To Compare Two Same Object");
//            }
//            
//            return this->FValue == rhs->FValue;
//        } catch (AStarException &exception) {
//            return false;
//        }
    }
    
    bool operator!=(const AStarNode &rhs){
        try {
            if (this == &rhs || (this->column == rhs.column && this->row == rhs.row)){
                throw AStarException("Try To Compare Two Same Object");
            }
            
            return this->FValue != rhs.FValue;
        }catch(AStarException &exception){
            return false;
        }
    }
    
    bool operator!=(const AStarNode *rhs){
        try {
            if (this == rhs || (this->column == rhs->column && this->row == rhs->row)){
                throw AStarException("Try To Compare Two Same Object");
            }
            
            return this->FValue != rhs->FValue;
        } catch (AStarException &exception) {
            return false;
        }
    }
    
    bool operator>(const AStarNode &rhs){
        try {
            if (this == &rhs || (this->column == rhs.column && this->row == rhs.row)){
                throw AStarException("Try To Compare Two Same Object");
            }
            
            return this->FValue > rhs.FValue;
        }catch(AStarException &exception){
            return false;
        }
    }
    
    bool operator>(const AStarNode *rhs){
        try {
            if (this == rhs || (this->column == rhs->column && this->row == rhs->row)){
                throw AStarException("Try To Compare Two Same Object");
            }
            
            return this->FValue > rhs->FValue;
        } catch (AStarException &exception) {
            return false;
        }
    }
    
    bool operator<(const AStarNode &rhs){
        try {
            if (this == &rhs || (this->column == rhs.column && this->row == rhs.row)){
                throw AStarException("Try To Compare Two Same Object");
            }
            
//            printf("%d < %d ? %d", this->FValue, rhs.FValue, this->FValue < rhs.FValue);
            
            return this->FValue < rhs.FValue;
        }catch(AStarException &exception){
            return false;
        }
    }
    
    bool operator<(const AStarNode *rhs){
        try {
            if (this == rhs || (this->column == rhs->column && this->row == rhs->row)){
                throw AStarException("Try To Compare Two Same Object");
            }
            
//            printf("%d < %d ? %d", this->FValue, rhs->FValue, this->FValue < rhs->FValue);
            
            return this->FValue < rhs->FValue;
        } catch (AStarException &exception) {
            return false;
        }
    }
};

#endif /* AStarCustomClass_hpp */
