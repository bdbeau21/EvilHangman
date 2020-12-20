#include <stdlib.h>
#include <stdio.h>
#include "status.h"
#include "my_string.h"
#include "gVector.h"
#include "tree.h"

// Create node with NULL left and right children                                                                                                                                                                                                                                                                                              
tNode* createNode(MY_STRING key){
    tNode* node = (tNode*) malloc(sizeof(tNode));

    // If Node is properly allocated                                                                                                                                                                                                                                                                                                          
    if(node != NULL){
        // Intialize Node                                                                                                                                                                                                                                                                                                                     
        node->key = my_string_init_c_string(my_string_c_str(key));
        node->lChild = NULL;
        node->rChild = NULL;
        node->nodeHeight = 1;

        // If MY_String is properly allocated                                                                                                                                                                                                                                                                                                 
        if(node->key == NULL){
            free(node);
            return NULL;
        }

        // Initliaze GVECTOR                                                                                                                                                                                                                                                                                                                  
        node->words = generic_vector_init_default(my_string_assignment, my_string_destroy);

        // GVECTOR is not properly allocated                                                                                                                                                                                                                                                                                                  
        if(node->words == NULL){
            free(node->key);
            free(node);
            return NULL;
        }
    }
    return node;
}

// Insert node into root of subtree and return new root                                                                                                                                                                                                                                                                                       
tNode* insertNodes(tNode* node, MY_STRING key, MY_STRING word){
    // Failed Allocation                                                                                                                                                                                                                                                                                                                      
    if (node == NULL){
        tNode* newNode = createNode(key);
        generic_vector_push_back(newNode->words, word);
        return newNode;
    }

    // Add string                                                                                                                                                                                                                                                                                                                             
    if(my_string_compare(key, node->key) == 0){
        generic_vector_push_back(node->words, word);
        return node;
    }

    // Insert left child                                                                                                                                                                                                                                                                                                                      
    if (my_string_compare(key, node->key) < 0)
        node->lChild  = insertNodes(node->lChild, key, word);

    // Insert right child                                                                                                                                                                                                                                                                                                                     
    else if (my_string_compare(key, node->key) > 0)
        node->rChild = insertNodes(node->rChild, key, word);


    // Height is increased                                                                                                                                                                                                                                                                                                                    
    node->nodeHeight = 1 + findmax(getHeight(node->lChild),getHeight(node->rChild));


    // Calculate balance factor                                                                                                                                                                                                                                                                                                               
    int balance = getBalancefactor(node);

    // Left Left Case                                                                                                                                                                                                                                                                                                                         
    if (balance > 1 && key < node->lChild->key){
        return rightRotation(node);
    }

    // Right Right Case                                                                                                                                                                                                                                                                                                                       
    if (balance < -1 && key > node->rChild->key){
        return leftRotation(node);
    }

    // Left Right Case                                                                                                                                                                                                                                                                                                                        
    if (balance > 1 && key > node->lChild->key){
        node->lChild =  leftRotation(node->lChild);
        return rightRotation(node);
    }

    // Right Left Case                                                                                                                                                                                                                                                                                                                        
    if (balance < -1 && key < node->rChild->key){
        node->rChild = rightRotation(node->rChild);
        return leftRotation(node);
    }
    return node;
}

// Look Up Key Function                                                                                                                                                                                                                                                                                                                       
GVECTOR lookup_by_key(tNode* node, MY_STRING key){
    // Node is NULL                                                                                                                                                                                                                                                                                                                           
    if(node == NULL){
        return NULL;
    }

    // Left String Compare                                                                                                                                                                                                                                                                                                                    
    if(my_string_compare(node->key, key) < 0){
        return lookup_by_key(node->lChild, key);
    }

    // Right String Compare                                                                                                                                                                                                                                                                                                                   
    if(my_string_compare(node->key, key) > 0){
        return lookup_by_key(node->rChild, key);
    }
    else{
        return node->words;
    }
}

// Rotate tree right                                                                                                                                                                                                                                                                                                                          
tNode* rightRotation(tNode* root){
    tNode *node = root->lChild;

    // If there is a left child                                                                                                                                                                                                                                                                                                               
    if(node != NULL){
    tNode* right = node->rChild;

    // Rotate nodes right                                                                                                                                                                                                                                                                                                                     
    node->rChild = root;
    root->lChild = right;

    // Height is increased                                                                                                                                                                                                                                                                                                                    
    root->nodeHeight = findmax(getHeight(root->lChild), getHeight(root->rChild))+1;
    node->nodeHeight = findmax(getHeight(node->lChild), getHeight(node->rChild))+1;
    }
    return node;
}

tNode* leftRotation(tNode* root){
    tNode *node = root->rChild;

    // There is a right child                                                                                                                                                                                                                                                                 
    if(node != NULL){
        tNode *lChild = node->lChild;

        // Rotates nodes left                                                                                                                                                                                                                                                                 
        node->lChild = root;
        root->rChild = lChild;

        // Height is increased                                                                                                                                                                                                                                                                
        root->nodeHeight = findmax(getHeight(root->lChild), getHeight(root->rChild))+1;
	node->nodeHeight = findmax(getHeight(node->lChild), getHeight(node->rChild))+1;
    }
    return node;
}

// Return the largest value                                                                                                                                                                                                                                                                   
int findmax(int x, int y){
    return (x > y)? x : y;
}

// Gets height of node                                                                                                                                                                                                                                                                        
int getHeight(tNode* node){
    // If node is a leaf                                                                                                                                                                                                                                                                      
    if (node == NULL){
      return 0;
    }
    return node->nodeHeight;
}

// Get Balance factor of node                                                                                                                                                                                                                                                                 
int getBalancefactor(tNode* node){
    // If node is a leaf                                                                                                                                                                                                                                                                      
    if (node == NULL){
        return 0;
    }
    return getHeight(node->lChild) - getHeight(node->rChild);
}

// Tree transversal with root first                                                                                                                                                                                                                                                           
void preorderTransversal(tNode *node){
    // Root is existent                                                                                                                                                                                                                                                                       
    if(node != NULL)
    {
        printf("%s %d\n", my_string_c_str(node->key),generic_vector_get_size(node->words));
        preorderTransversal(node->lChild);
        preorderTransversal(node->rChild);
    }
}

// Tree transversal in order                                                                                                                                                                                                                                                                  
void inorderTraversal(tNode *root)
{
    // Root is existent                                                                                                                                                                                                                                                                       
    if(root != NULL)
    {
        inorderTraversal(root->lChild);
        printf("%s %d\n", my_string_c_str(root->key),generic_vector_get_size(root->words));
        inorderTraversal(root->rChild);
    }
}

// Free memory of node                                                                                                                                                                                                                                                                        
void destroy(tNode** node){
    // Free memory                                                                                                                                                                                                                                                                            
    if(*node != NULL){
        destroy(&(*node)->lChild);
        destroy(&(*node)->rChild);
        free(*node);
        *node = NULL;
    }
}
