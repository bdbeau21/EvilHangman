// Include files                                                                                                                                                                                                                                                                                                                              
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

// Structure for my string                                                                                                                                                                                                                                                                                                                    
struct my_string
{
  int size;
  int capacity;
  char* data;
};
typedef struct my_string My_String;

// Sets Defaults                                                                                                                                                                                                                                                                                                                              
MY_STRING my_string_init_default()
{
  My_String* pMy_string;

  // Allocates space                                                                                                                                                                                                                                                                                                                          
  pMy_string = (My_String*)malloc(sizeof(My_String));

  // If pointer is not NULL Initiliaze                                                                                                                                                                                                                                                                                                        
  if(pMy_string != NULL){
    pMy_string->size=0;
    pMy_string->capacity=7;
    // Allocates space for data                                                                                                                                                                                                                                                                                                               
    pMy_string->data=(char*)(malloc(sizeof(char)*pMy_string->capacity));

    // Checks if data is NULL                                                                                                                                                                                                                                                                                                                 
    if(pMy_string->data == NULL){
      free(pMy_string);  // Frees space                                                                                                                                                                                                                                                                                                       
      pMy_string = NULL;
    }
    pMy_string->data[0] = '\0';
  }
  return pMy_string;
}

// Memory is freed                                                                                                                                                                                                                                                                                                                            
/*void my_string_destroy(MY_STRING* phMy_string)                                                                                                                                                                                                                                                                                              
{                                                                                                                                                                                                                                                                                                                                             
  My_String* temp = (My_String*) *phMy_string;                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                              
  // If pointer is full                                                                                                                                                                                                                                                                                                                       
  if(temp != NULL){                                                                                                                                                                                                                                                                                                                           
    // If char pointer is full                                                                                                                                                                                                                                                                                                                
    if(temp->data != NULL){                                                                                                                                                                                                                                                                                                                   
      free(temp->data); // Frees data                                                                                                                                                                                                                                                                                                         
      free(temp); // free pointer                                                                                                                                                                                                                                                                                                             
    }                                                                                                                                                                                                                                                                                                                                         
  }                                                                                                                                                                                                                                                                                                                                           
  *phMy_string = NULL;                                                                                                                                                                                                                                                                                                                        
}*/


 // New destroy function                                                                                                                                                                                                                                                                                                                      
void my_string_destroy(Item* pItem){
  My_String* pString=(My_String*)* pItem;
  free(pString->data);
  free(pString);
  *pItem = NULL;
}

// Space for string object is allocated                                                                                                                                                                                                                                                                                                       
MY_STRING my_string_init_c_string(const char* c_string)
{
  // Intiliaize values                                                                                                                                                                                                                                                                                                                        
  int i =0, size =0, capacity =9;

  My_String* phMy_string= NULL;

  //Allocate space for void pointer                                                                                                                                                                                                                                                                                                           
  phMy_string = (My_String*)malloc(sizeof(My_String));

  // Checks for size of c_string                                                                                                                                                                                                                                                                                                              
  while(c_string[size] != '\0'){
    size++;
  }

  // Iterates up until size is equal to capacity                                                                                                                                                                                                                                                                                              
  for(i=1; size > capacity; i++)
  {
    capacity *= i;
  }

  // Pointer is full                                                                                                                                                                                                                                                                                                                          
  if(phMy_string != NULL){
    phMy_string->size = size;
    phMy_string->capacity = capacity;

    // Allocates space for data                                                                                                                                                                                                                                                                                                               
    phMy_string->data = (char*)malloc(sizeof(char) *phMy_string-> capacity);

    // Verifys char pointer is full                                                                                                                                                                                                                                                                                                           
    if(phMy_string->data ==NULL){
      free(phMy_string);  // Frees space                                                                                                                                                                                                                                                                                                      
      phMy_string = NULL;
    }

    // Data filled with c string                                                                                                                                                                                                                                                                                                              
    for(i=0;i<size;i++){
        phMy_string->data[i] =c_string[i];
    }
  }
  return (MY_STRING)phMy_string;
}

// Function to get capacity                                                                                                                                                                                                                                                                                                                   
int my_string_get_capacity(MY_STRING hMy_string)
{
  My_String* pString = (My_String*)hMy_string;
  int capacity =-1; // Initliaze capacity                                                                                                                                                                                                                                                                                                     

  // Checks if null                                                                                                                                                                                                                                                                                                                           
  if(pString != NULL){
    capacity = pString->capacity; // Sets numeric value to capacity                                                                                                                                                                                                                                                                           
  }
  return capacity;
}

// Function to get size                                                                                                                                                                                                                                                                                                                       
int my_string_get_size(MY_STRING hMy_string)
{
    My_String* hold = (My_String*)hMy_string;
    int size =-1; // Initliaze capacity                                                                                                                                                                                                                                                                                                       

    // Checks if null                                                                                                                                                                                                                                                                                                                         
    if(hold != NULL){
    size = hold->size; // Sets numeric value to size                                                                                                                                                                                                                                                                                          
  }
  return size;
}

// Compare two strings                                                                                                                                                                                                                                                                                                                        
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string){
    My_String* plString = (My_String*) hLeft_string;
    My_String* prString = (My_String*) hRight_string;
    int size = 0;

    char* leftData = plString->data;
    char* rightData = prString->data;

    // Checks full string                                                                                                                                                                                                                                                                                                                     
    while(leftData[size] != '\0' && rightData[size] != '\0'){
        // If left string is greater than right                                                                                                                                                                                                                                                                                               
        if(leftData[size] >  rightData[size]){
            return 1;
        }
        // If right string is greater than left                                                                                                                                                                                                                                                                                               
        else if(leftData[size] < rightData[size]){
            return -1;
        }
        size++;
    }

    // If strings are equal                                                                                                                                                                                                                                                                                                                   
    if(leftData[size] == '\0' && rightData[size] == '\0'){
        return 0;
    }
    // If left data is empty                                                                                                                                                                                                                                                                                                                  
    else if(leftData[size] == '\0'){
        return -1;
    }
    else{
        return 1;
    }
}


// Extracts string from file                                                                                                                                                                                                                                                                                                                  
Status my_string_extraction(MY_STRING hMy_string, FILE* fp){
    My_String* pMy_String = (My_String*) hMy_string;

    // If string and file can be accessed                                                                                                                                                                                                                                                                                                     
    if(pMy_String == NULL || fp == NULL){
        return FAILURE;
    }
    char endline = '\0';
    int status = fscanf(fp,"%c", &endline);

    // File output                                                                                                                                                                                                                                                                                                                            
    if(status){
        pMy_String->size = 0;

        // While character is read                                                                                                                                                                                                                                                                                                            
        while(status){

            // Resize/double capacity                                                                                                                                                                                                                                                                                                         
            if(pMy_String->capacity == pMy_String->size){
                char* newChar = (char*) malloc(sizeof(char) * pMy_String->capacity * 2);

                // If allocation fails                                                                                                                                                                                                                                                                                                        
                if(newChar == NULL){
                    return FAILURE;
                }

                // Fill string values into new string                                                                                                                                                                                                                                                                                         
                for(int i = 0; i<pMy_String->size; i++){
                    newChar[i] = pMy_String->data[i];
                }

                // Free former string                                                                                                                                                                                                                                                                                                         
                free(pMy_String->data);
                pMy_String->data = newChar;
                pMy_String->capacity *= 2;
            }

            // Exit loop                                                                                                                                                                                                                                                                                                                      
            if(endline == EOF || endline == '\n' || endline == '\0'){
                break;
            }

            // If there is a space                                                                                                                                                                                                                                                                                                            
            if(endline == ' '){
                ungetc(endline, fp);    // Ignore space                                                                                                                                                                                                                                                                                       
                endline = '\0';
                break;
            }
            pMy_String->data[pMy_String->size++] = endline;
            status = fscanf(fp,"%c", &endline);
        }
    }

    // Failed to read strings                                                                                                                                                                                                                                                                                                                 
    if(status != 1 && endline == '\0'){
        return FAILURE;
    }

    return SUCCESS;
}

// Writes characters to file                                                                                                                                                                                                                                                                                                                  
Status my_string_insertion(MY_STRING hMy_string,FILE *fp)
{
  My_String* point= (My_String*)hMy_string;
  // For loop to print charcters                                                                                                                                                                                                                                                                                                              
  int count =0;

  if(point->size==0 || point == NULL){
    return FAILURE;
  }
  while(count<point->size){
    fputc(point->data[count],fp);
    count++;
  }
  return SUCCESS;
}
// Push onto top of stack                                                                                                                                                                                                                                                                                                                     
Status my_string_push_back(MY_STRING hMy_string, char item){
  My_String* point = (My_String*)hMy_string;

  // If string is NULL                                                                                                                                                                                                                                                                                                                        
  if(point != NULL){
    // Increase capacity if size is greater                                                                                                                                                                                                                                                                                                   
    if(point->size >= point-> capacity){
      char *tempData;
      point->capacity= point->capacity*2;
      tempData = (char*)malloc(sizeof(char)*point->capacity);

      // Return FAILURE                                                                                                                                                                                                                                                                                                                       
      if(tempData){
        point->capacity= point->capacity /2;
        return FAILURE;
      }

      // Fill tempData                                                                                                                                                                                                                                                                                                                        
      for(int i=0; i<point->size;i++){
        tempData[i]=point->data[i];
      }

      free(point->data);
      point->data = tempData;
    }

    point->data[point->size] = item; // Assign item value                                                                                                                                                                                                                                                                                     
    point->size++; // Points to next item                                                                                                                                                                                                                                                                                                     

    return SUCCESS;
  }

  return FAILURE;
}

// Pop from top                                                                                                                                                                                                                                                                                                                               
Status my_string_pop_back(MY_STRING hMy_string){
  My_String* point=(My_String*)hMy_string;

  // Point has 0 eleemtn or none                                                                                                                                                                                                                                                                                                              
  if(point->size<=0){
    return FAILURE;
  }
  point->size--; // Decrease                                                                                                                                                                                                                                                                                                                  
  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index){
    My_String* pMy_String = (My_String*) hMy_string;

    if((index < 0) || (index > pMy_String->size))
        return NULL;

    return (char*) pMy_String->data + index;
}

char* my_string_c_str(MY_STRING hMy_string){
    My_String* pMy_String = (My_String*) hMy_string;

    return (char*) pMy_String->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend){
  My_String* outcome = (My_String*)hResult;
  My_String* add = (My_String*)hAppend;
  char* string1 = outcome->data;
  char* string2 = add->data;
  char* temp;
  int i;
  // Allocate Space for temp                                                                                                                                                                                                                                                                                                                  
  temp = (char*)malloc(sizeof(char) * (outcome->capacity - 1) + (add->capacity - 1) + 1\
);
  // Failed Allocation                                                                                                                                                                                                                                                                                                                        
  if (temp == NULL) {
    free(temp);
    printf("Failed Allocation");
    return FAILURE;
  }

  // Assign first string values to temp string                                                                                                                                                                                                                                                                                                
  for (i = 0; i < outcome->size; i++) {
    temp[i] = string1[i];
  }

  // Assign second string values to temp string                                                                                                                                                                                                                                                                                               
  for (int j = 0; i < (outcome->size) + (add->size); j++, i++) {
    temp[i] = string2[j];
  }
  free(outcome->data);   // Free unused data                                                                                                                                                                                                                                                                                                  
  outcome->data = temp;  // Set data equal to outocme string                                                                                                                                                                                                                                                                                  
  // Adjust capacity accordingly                                                                                                                                                                                                                                                                                                              
  outcome->capacity = (outcome->capacity - 1) + (add->capacity - 1) + 1;
  outcome->size = i; // Size is calculated by number of terminations                                                                                                                                                                                                                                                                          
  return SUCCESS;
}

// Checks size of string                                                                                                                                                                                                                                                                                                                      
Boolean my_string_empty(MY_STRING hMy_string)
{
  My_String* point = (My_String*)hMy_string;

  // Size is has value nonnegative or zero                                                                                                                                                                                                                                                                                                    
  if(point->size <=0){
    return TRUE;
  }
  return FALSE; // String is empty                                                                                                                                                                                                                                                                                                            
}

// Assignment string function                                                                                                                                                                                                                                                                                                                 
Status my_string_assignment(Item* pLeft, Item Right){
    My_String *leftString = (My_String*) *pLeft;
    My_String *rightString = (My_String*) Right;

    // If Left string capacity is greater than right size                                                                                                                                                                                                                                                                                     
    if(leftString != NULL && leftString->capacity < rightString->size){
        my_string_destroy(pLeft); leftString = NULL;
    }

    // If String must be null                                                                                                                                                                                                                                                                                                                 
    if(leftString == NULL){
        leftString = (My_String*) malloc(sizeof(My_String));

        // Checks for failed allocation                                                                                                                                                                                                                                                                                                       
        if(leftString !=  NULL){
            leftString->capacity = rightString->capacity;

            // Allocate space for data                                                                                                                                                                                                                                                                                                        
            leftString->data = (char*) malloc(sizeof(char) * rightString->capacity);

            // Checks for faulty allocation                                                                                                                                                                                                                                                                                                   
            if(leftString->data == NULL){
                free(leftString); leftString = NULL;
                return FAILURE;
            }
            leftString->data[0] = '\0';
        }
        else return FAILURE;
    }

    // For loop to fill left string values with right                                                                                                                                                                                                                                                                                         
    for(int i = 0; i < rightString->size; i++){
        leftString->data[i] = rightString->data[i];
    }
    leftString->data[rightString->size] = '\0';

    leftString->size = rightString->size; // Set left string equal to right                                                                                                                                                                                                                                                                   

    *pLeft = leftString;

    return SUCCESS;
}

// Places string in new key                                                                                                                                                                                                                                                                                                                   
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess){
    My_String* key = (My_String*)new_key;
    int size = my_string_get_size(word);
    char dict[size + 1];
    char *hold;

    // Iterate through string                                                                                                                                                                                                                                                                                                                 
    for(int i = 0; i <= size; i++)
        dict[i] = *my_string_at(current_word_family, i);

    // If guess is correct                                                                                                                                                                                                                                                                                                                    
    for(int i = 0; i < size; i++){
        hold = my_string_at(word, i);

        // Change capitalization                                                                                                                                                                                                                                                                                                              
        if(*hold == guess)
            dict[i] = tolower(guess);
    }

    // If capacity is less than size                                                                                                                                                                                                                                                                                                          
    if(key->capacity < size + 1){
        char* temp = (char *) malloc((size + 1) * sizeof(char));

        // Failed allocatiom                                                                                                                                                                                                                                                                                                                  
        if(temp == NULL){
            return FAILURE;
        }
        free(key->data);
        key->data = temp;
    }

    // Fill key data with value                                                                                                                                                                                                                                                                                                               
    for(int i = 0; i <= size; i++){
        key->data[i] = dict[i];
    }
    return SUCCESS;
}
