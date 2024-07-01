#pragma once
#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

enum Color { RED, BLACK };

struct RBTreeNode {
    int key;
    Color color;
    RBTreeNode *left, *right, *parent;
};

//Funções principais da árvore
RBTreeNode* createNode(int key);
void insertRBTree(RBTreeNode *&root, int key);
RBTreeNode* searchRBTree(RBTreeNode* node, int key);
RBTreeNode* minimumRBTree(RBTreeNode* node);
RBTreeNode* maximumRBTree(RBTreeNode* node);
int heightRBTree(RBTreeNode* node);
void deleteRBTree(RBTreeNode* node);

//Funções auxiliares
void rotateLeft(RBTreeNode *&root, RBTreeNode *&node);
void rotateRight(RBTreeNode *&root, RBTreeNode *&node);
void fixInsertRBTree(RBTreeNode *&root, RBTreeNode *&node);
void inorderHelper(RBTreeNode *node,bool verbose);

#endif 

#include "RBT.cpp"

