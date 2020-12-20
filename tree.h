#ifndef TREE_H
#define TREE_H

#include "gVector.h"
#include "my_string.h"

typedef struct Node tNode;

// AVL TREE                                                                                                                                                                                                     
struct Node{
    MY_STRING key;  // String data                                                                                                                                                                              
    GVECTOR words;  // Vector words                                                                                                                                                                             
    tNode* lChild;  // Left Child                                                                                                                                                                               
    tNode* rChild;  // Right Child                                                                                                                                                                              
    int nodeHeight; // Height of specific node                                                                                                                                                                  
};

tNode* insertNodes(tNode* node, MY_STRING key, MY_STRING word);
tNode* createNode(MY_STRING key);
int getHeight(tNode* node);
int getBalancefactor(tNode* node);
int findmax(int x, int y);
tNode* rightRotation(tNode* root);
tNode* leftRotation(tNode *x);
GVECTOR lookup_by_key(tNode* node, MY_STRING key);
void preorderTransversal(tNode* node);
void inorderTraversal(tNode* root);
void destroy(tNode** node);

#endif
