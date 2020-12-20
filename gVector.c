include <stdio.h>
#include <stdlib.h>
#include "gVector.h"

// Generic Vector                                                                                                                                                                                                                                                                                     
struct vector
{
    Status(*item_assignment)(Item*, Item);
    void(*item_destroy)(Item*);
    int size;
    int capacity;
    Item* data;
};
typedef struct vector Vector;

// Generic default vector function                                                                                                                                                                                                                                                                    
GVECTOR generic_vector_init_default(Status(*item_assignment)(Item*, Item),void(*item_destroy)(Item*))
{
    Vector* pVector = (Vector*) malloc(sizeof(Vector));

    // If allocation is successful                                                                                                                                                                                                                                                                    
    if (pVector != NULL)
    {
        pVector->item_assignment = item_assignment;
        pVector->item_destroy = item_destroy;
        pVector->size = 0;
        pVector->capacity = 1;
        pVector->data = (Item*) malloc(sizeof(Item) * pVector->capacity);

        // If failed allocation                                                                                                                                                                                                                                                                       
        if (pVector->data == NULL)
        {
            free(pVector);
            pVector = NULL;
        }
        // If allocation is succesful                                                                                                                                                                                                                                                                 
        else
        {
            // Fill vector with NULL values                                                                                                                                                                                                                                                           
            for (int i = 0; i < pVector->capacity; i++)
            {
                pVector->data[i] = NULL;
            }
        }
    }
    return pVector;
}

// Free and destroy generic vector                                                                                                                                                                                                                                                                    
void generic_vector_destroy(GVECTOR* phVector){
    Vector* pVector = (Vector*)*phVector;

    // While vector is full                                                                                                                                                                                                                                                                           
    if(pVector != NULL){
        // Free data                                                                                                                                                                                                                                                                                  
        if(pVector->data!=NULL){
            free(pVector->data);
            free(pVector);
        }
    }
    *phVector = NULL;
}

// Function to get capacity                                                                                                                                                                                                                                                                           
int generic_vector_get_capacity(GVECTOR hVector)
{
  Vector* pVector = (Vector*)hVector;
  int capacity =-1; // Initliaze capacity                                                                                                                                                                                                                                                             

  // Checks if full                                                                                                                                                                                                                                                                                   
  if(pVector != NULL){
    capacity = pVector->capacity; // Sets numeric value to capacity                                                                                                                                                                                                                                   
  }
  return capacity;
}

// Function to get size                                                                                                                                                                                                                                                                               
int generic_vector_get_size(GVECTOR hVector)
{
  Vector* pVector = (Vector*)hVector;
  int size=-1; // Initliaze size                                                                                                                                                                                                                                                                      

  // Checks if full                                                                                                                                                                                                                                                                                   
  if(pVector != NULL){
    size= pVector->size; // Sets numeric value to size                                                                                                                                                                                                                                                
  }
  return size;
}

// Function to get size                                                                                                                                                                                                                                                                               
int generic_vector_get_size(GVECTOR hVector)
{
  Vector* pVector = (Vector*)hVector;
  int size=-1; // Initliaze size                                                                                                                                                                                                                                                                      

  // Checks if full                                                                                                                                                                                                                                                                                   
  if(pVector != NULL){
    size= pVector->size; // Sets numeric value to size                                                                                                                                                                                                                                                
  }
  return size;
}

// Push on top of stack                                                                                                                                                                                                                                                                               
Status generic_vector_push_back(GVECTOR hVector, Item item)
{
    Vector* pVector = (Vector*) hVector;
    Item* temp;
    int i;
    Status status;

    // If vector size is greater than capacity                                                                                                                                                                                                                                                        
    if (pVector->size >= pVector->capacity) //there is not enough room...make room                                                                                                                                                                                                                    
    {
        temp = (Item*) malloc(sizeof(Item) * pVector->capacity * 2);

        // Failed allocation                                                                                                                                                                                                                                                                          
        if (temp == NULL)
        {
            return FAILURE;
        }

        // Fill temp with data                                                                                                                                                                                                                                                                        
        for (i = 0; i < pVector->size; i++)
        {
            temp[i] = pVector->data[i];
        }

        // Fill remainder of temp with null value                                                                                                                                                                                                                                                     
        for (i = pVector->size; i < pVector->capacity * 2; i++)
        {
            temp[i] = NULL;
        }

        // Free Vector data                                                                                                                                                                                                                                                                           
        free(pVector->data);
        pVector->data = temp;
        pVector->capacity *= 2; // Double capacity                                                                                                                                                                                                                                                    
    }

    // Status equals vector assignment status                                                                                                                                                                                                                                                         
    status = pVector->item_assignment(&(pVector->data[pVector->size]), item);

    // Status was set to fail                                                                                                                                                                                                                                                                         
    if (status == FAILURE)
    {
        return FAILURE;
    }
    pVector->size++;    // Size is incremented                                                                                                                                                                                                                                                        
    return SUCCESS;
}

// Pop from top                                                                                                                                                                                                                                                                                       
Status generic_vector_pop_back(GVECTOR hVector){
  Vector* point=(Vector*)hVector;

  // Point has 0 elements or none                                                                                                                                                                                                                                                                     
  if(point->size<=0){
    return FAILURE;
  }
  point->size--; // Decrease                                                                                                                                                                                                                                                                          
  return SUCCESS;
}

// Return item at vector data index                                                                                                                                                                                                                                                                   
Item generic_vector_at(GVECTOR hVector, unsigned int index)
{
    Vector* pVector = (Vector*)hVector;

    // Index greater or equal to vector size                                                                                                                                                                                                                                                          
    if (index >= pVector->size)
    {
        printf("Index is invalid!\n");
        return NULL;
    }

    return (pVector->data[index]);
}

// Checks size of vector                                                                                                                                                                                                                                                                              
Boolean generic_vector_empty(GVECTOR hVector){
  Vector* point = (Vector*)hVector;

  // Size is has value nonnegative or zero                                                                                                                                                                                                                                                            
  if(point->size <0){
    return TRUE;
  }
  return FALSE; // Vector is empty                                                                                                                                                                                                                                                                    
}
