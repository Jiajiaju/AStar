//
//  BinaryHeap.hpp
//  AStar
//
//  Created by 贾佳菊 on 16/2/20.
//
//

#ifndef BinaryHeap_hpp
#define BinaryHeap_hpp

#include <stdio.h>
#include <vector>
#include "AStarCustomClass.hpp"

template <typename BinaryHeapNode>
class BinaryHeap {
public:
    BinaryHeap();
    
    bool empty();
    BinaryHeapNode getMin();
    BinaryHeapNode isIn(const BinaryHeapNode &node);
    void insert(const BinaryHeapNode &node);
    void deleteMin();
    
private:
    int _currentSize;
    std::vector<BinaryHeapNode> _array;
    
    void _percolateUp(int hole);
    void _percolateDown(int hole);
};


/**
 ** implementation
 */

template <typename BinaryHeapNode>
BinaryHeap<BinaryHeapNode>::BinaryHeap(){
    _currentSize = 0;
    _array.resize(100);
}

template <typename BinaryHeapNode>
bool BinaryHeap<BinaryHeapNode>::empty(){
    if (_currentSize == 0){
        return true;
    }
    return false;
}

template <typename BinaryHeapNode>
BinaryHeapNode BinaryHeap<BinaryHeapNode>::isIn(const BinaryHeapNode &node){
    for (int index = 1; index <= _currentSize; ++index){
        if ((*node) == _array[index]){
            return _array[index];
        }
    }
    
    return nullptr;
}

template <typename BinaryHeapNode>
BinaryHeapNode BinaryHeap<BinaryHeapNode>::getMin(){
    BinaryHeapNode min = _array[1];
    deleteMin();
    return min;
}

template <typename BinaryHeapNode>
void BinaryHeap<BinaryHeapNode>::insert(const BinaryHeapNode &node){
    
    int hole = ++_currentSize;
    if (_array.size() - 1 <= _currentSize){
        _array.resize(_currentSize * 2);
    }
    _array[_currentSize] = node;
    _percolateUp(hole);
}

template <typename BinaryHeapNode>
void BinaryHeap<BinaryHeapNode>::deleteMin(){
    
//    std::cout << __func__ << std::endl;
//    for (int index = 1; index <= _currentSize; ++index){
//        std::cout << index << ":";
//        _array[index]->print();
//    }
    
    _array[1] = _array[_currentSize--];
    _percolateDown(1);
}

template <typename BinaryHeapNode>
void BinaryHeap<BinaryHeapNode>::_percolateDown(int hole){
    int child;
    BinaryHeapNode temp = _array[hole];
    
    for (; hole * 2 <= _currentSize; hole = child){
        child = hole * 2;
        if (child != _currentSize && (*_array[child + 1]) < _array[child]){
            ++child;
        }
        
        if ((*_array[child]) < temp){
            _array[hole] = _array[child];
        }else {
            break;
        }
    }
    
    _array[hole] = temp;
}

template <typename BinaryHeapNode>
void BinaryHeap<BinaryHeapNode>::_percolateUp(int hole){
    for (; hole > 1 && (*_array[hole]) < _array[hole / 2]; hole /= 2){
        BinaryHeapNode tempNode = _array[hole];
        _array[hole] = _array[hole / 2];
        _array[hole / 2] = tempNode;
    }
}

#endif /* BinaryHeap_hpp */
