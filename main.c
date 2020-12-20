#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
#include "gVector.h"
#include "my_string.h"

// Function Section                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
// Checks to see if word length is available                                                                                                                                                                                                                                                                                                                                                                                                                                                              
Boolean possible_length(int word_length);

// Makes sure multiple letters are not guessed more than once                                                                                                                                                                                                                                                                                                                                                                                                                                             
Boolean previousGuess(MY_STRING guessed_letters, char guess);

// User wins the game                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
Boolean correctGuess(MY_STRING key);

// Return Maxium height comparing left and right heights                                                                                                                                                                                                                                                                                                                                                                                                                                                  
int heightMax(tNode* tree);

// Input for number of guesses chosen by user                                                                                                                                                                                                                                                                                                                                                                                                                                                             
int get_number_of_guesses(void);

// Input for length of word chosen by the user                                                                                                                                                                                                                                                                                                                                                                                                                                                            
int get_number_for_length(void);

// Fill tree with similar length words                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
Status tree_filling(tNode** tree, GVECTOR words,  MY_STRING key, char guess);

// Fill vector with all dictionary words                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
Status vector_filling(GVECTOR hVector, int length);

// Return the largest vector family with most words                                                                                                                                                                                                                                                                                                                                                                                                                                                       
void largest_family(GVECTOR *generic, tNode* tree, MY_STRING* newKey, int size);

// Clear keyboard buffer after input                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
void clear_keyboard(void);

//void destroy_everything(tNode* tree, GVECTOR words, MY_STRING key, MY_STRING letters);                                                                                                                                                                                                                                                                                                                                                                                                                  

// Main Program                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
int main(void){
    Boolean reRun = FALSE;

    // While the user choses to rerun the program                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    do{
        tNode *tree = NULL;
        GVECTOR words = generic_vector_init_default(my_string_assignment, my_string_destroy);
        MY_STRING key = my_string_init_default();
        MY_STRING guessed_letters = my_string_init_default();
        char guess = '\0';
        Boolean guessed = FALSE;
        int length = 0;
        int guesses = 0;
        int guessingStatus = 0;

        printf("Evil Hangman Game!\n");

        while(!possible_length(length)){
            length= get_number_for_length();
        }

        // Create key of dashes                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        for(int i = 0; i < length; i++)
            my_string_push_back(key, '-');

        length = my_string_get_size(key);

        guesses= get_number_of_guesses();

        //Fill the vector of words                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        vector_filling(words, length);

        // While there are remaining guess left                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        while(guesses > 0){
            printf("You have %d guesses left.\n", guesses);

            guessingStatus = 0;
            do{
                printf("Guess a letter: ");
                guessingStatus = scanf("%c", &guess);
                clear_keyboard();

                // Changes to lower case value                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                if (isalpha(guess))
                {
                    if (isupper(guess))
                    {
                        guess = tolower(guess);
                    }
                }
            }
            // While letter hasn't been guessed                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            while(previousGuess(guessed_letters, guess) || guessingStatus == 0);

            my_string_push_back(guessed_letters, guess);

            tree_filling(&tree, words, key, guess);

            generic_vector_destroy(&words);

            preorderTransversal(tree);

            printf("Used Letters: %s\n", my_string_c_str(guessed_letters));
            printf("Word: %s \n", my_string_c_str(key));
            printf("Letter guessed: %c\n", guess);

            int biggest_family = heightMax(tree);

            largest_family(&words, tree, &key, biggest_family);
            guesses--;
            destroy(&tree);

            // If user guess the correct word                                                                                                                                                                                                                                                                                                                                                                                                                                                             
            if(correctGuess(key)){
                guessed = TRUE;
                printf("YOU HAVE WON! The word was: %s\n", my_string_c_str(key));
                break;
            }
        }

        // User runs out of attempts                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
        if(!guessed)
            printf("You Lost! The word was: %s\n", my_string_c_str(generic_vector_at(words, 0)));

        // Free all memory                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        my_string_destroy(&key);
        my_string_destroy(&guessed_letters);
        destroy(&tree);
        generic_vector_destroy(&words);

        //destroy_everything(tree,words,key,guessed_letters);                                                                                                                                                                                                                                                                                                                                                                                                                                             

        int play_status = 0;
        char again = '\0';
        do{
            printf("Do you want to play again? (y/n): ");
            play_status = scanf("%c", &again);
            clear_keyboard();
            // Changes to lower case value                                                                                                                                                                                                                                                                                                                                                                                                                                                                
            if (isalpha(again))
            {
                if (isupper(again))
                {
                    again = tolower(again);
                }
            }
        }while(play_status == 0);

        // If User choices to play again                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        if(again == 'y'){
            reRun = TRUE;
        }
        // If user neglects to play again                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
        else{
            reRun = FALSE;
        }

    }while(reRun);
   return 0;
}

// Clears the keyboard after input                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
void clear_keyboard(void){
    char c;
    while((c = getchar()) && (c != '\n') && (c != EOF));
}

// Function to input the number of guesses                                                                                                                                                                                                                                                                                                                                                                                                                                                                
int get_number_of_guesses(void)
{
    int number_of_guesses;
    printf("How many guesses would you like to have: ");
    scanf("%d", &number_of_guesses);
    clear_keyboard();

    // Make sure the input is great than                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    if (number_of_guesses <= 0)
    {
        printf("I'm sorry, but you need to choose a positive integer!\n");
        number_of_guesses = get_number_of_guesses();
    }
    return number_of_guesses;
}

// Function to input the length of word                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
int get_number_for_length(void)
{
    int length;
    printf("How many characters long is the word: ");
    scanf("%d", &length);
    clear_keyboard();

    if (length <= 0)
    {
        printf("I'm sorry, but you need to choose a positive integer!\n");
        length = get_number_for_length();
    }
    return length;
}

// Checks if word length is available                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
Boolean possible_length(int word_length){
    int size = 0;
    if(word_length <= 0 || word_length > 29){
        return FALSE;
    }

    MY_STRING string = my_string_init_default();

    FILE *fp  = fopen("dictionary.txt","r");
    FILE *null = fopen("null", "w");
    if(fp == NULL|| null == NULL){
        printf("Fatal Error: Dictionary file not found...\n");
        exit(1);
    }

    // Extract string from dictionary                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
    while(my_string_extraction(string, fp)){
        // Determine the size                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
        size = my_string_get_size(string);
        my_string_insertion(string, null);

        // Dictionary has available size                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        if(size == word_length)
            return TRUE;
    }
    return FALSE;
}

//                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
Status tree_filling(tNode** tree, GVECTOR words, MY_STRING key, char guess){
    // Iterate through vector size                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    for(int i = 0; i < generic_vector_get_size(words); i++){
        MY_STRING oldKey = NULL;
        MY_STRING newKey = my_string_init_default();

        my_string_assignment(&oldKey, key);

        // Makes sure new key has value                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        if(newKey == NULL){
            return FAILURE;
        }

        // Assign string at index                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
        MY_STRING word = generic_vector_at(words, i);

        // Update key                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
        get_word_key_value(oldKey, newKey, word, guess);

        // Insert word                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
        *tree = insertNodes(*tree, newKey, word);
    }
    return SUCCESS;
}

Status vector_filling(GVECTOR hVector, int length){
    MY_STRING word = my_string_init_default();
    if(word == NULL){
        return FAILURE;
    }

    FILE *dictionary = fopen("dictionary.txt", "r");
    FILE *null = fopen("null", "w");
    if(dictionary == NULL || null == NULL){
        printf("Failed to open dictionary!\n");
        exit(-1);
    }

    // Extract word from dictionary                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    while(my_string_extraction(word, dictionary)){

        // Check size of string                                                                                                                                                                                                                                                                                                                                                                                                                                                             
        if(my_string_get_size(word) == length)
            // Push string onto vector                                                                                                                                                                                                                                                                                                                                                                                                                                                      
            generic_vector_push_back(hVector, word);
        my_string_insertion(word, null);
    }
    return SUCCESS;
}

// Find largest word family                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
void largest_family(GVECTOR *generic, tNode* tree, MY_STRING* newKey, int size){
    // If vector is null assign initlizing function                                                                                                                                                                                                                                                                                                                                                                                                                                         
    if(*generic == NULL){
        *generic = generic_vector_init_default(my_string_assignment, my_string_destroy);
    }

    // If Node has value                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    if(tree != NULL){
        // Get the size                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
        if(generic_vector_get_size(tree->words) == size){
            my_string_destroy(newKey);
            *newKey = my_string_init_c_string(my_string_c_str(tree->key));

            // Iterate till vector size                                                                                                                                                                                                                                                                                                                                                                                                                                                     
            for(int i = 0; i < generic_vector_get_size(tree->words); i++){
                MY_STRING currentWord = generic_vector_at(tree->words, i);

                // Push string onto stack                                                                                                                                                                                                                                                                                                                                                                                                                                                   
                generic_vector_push_back(*generic,my_string_init_c_string(my_string_c_str(currentWord)));
            }
        }
        // Recursive actions for children                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        largest_family(generic, tree->lChild, newKey, size);
        largest_family(generic, tree->rChild, newKey, size);
    }
}

int heightMax(tNode* tree){
    int rightTree= -2;
    int leftTree= -2;

    // Confrim Node is not empty                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    if (tree == NULL){
        printf("EMPTY NODE!\n");
        return -3.14159;    // return noticeable value to confrim error                                                                                                                                                                                                                                                                                                                                                                                                                     
    }

    // Node is a leaf                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    if (tree->lChild == NULL && tree->rChild == NULL)
        return generic_vector_get_size(tree->words);

    // Iterate throught tree to determine left tree height                                                                                                                                                                                                                                                                                                                                                                                                                                  
    if (tree->lChild != NULL){
        leftTree = heightMax(tree->lChild);
    }

    // Iterate through tree to determine right height                                                                                                                                                                                                                                                                                                                                                                                                                                       
    if (tree->rChild != NULL){
        rightTree = heightMax(tree->rChild);
    }

    // Return bigger right tree                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    if (rightTree >= generic_vector_get_size(tree->words) && rightTree >= leftTree){
        return rightTree;
    }

    // Return bigger left tree                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    if (leftTree >= generic_vector_get_size(tree->words) && leftTree >= rightTree){
        return leftTree;
    }

    // Current node is biggest                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    return generic_vector_get_size(tree->words);
}

// Confrims the character was not already chosen                                                                                                                                                                                                                                                                                                                                                                                                                                            
Boolean previousGuess(MY_STRING guessed_letters, char guess){
    // Iterate through guessed letter                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    for(int i = 0; i < my_string_get_size(guessed_letters); i++){
        // Guesss matches a previous guess                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        if(guess == *my_string_at(guessed_letters, i)){
            printf("LETTER WAS ALREADY GUESSED!\n");
            return TRUE;
        }
    }
    return FALSE;   // New letter guessed                                                                                                                                                                                                                                                                                                                                                                                                                                                   
}

// Confirms if guess is correct                                                                                                                                                                                                                                                                                                                                                                                                                                                             
Boolean correctGuess(MY_STRING key){
    // Iterate through string                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    for(int i = 0; i < my_string_get_size(key); i++){
        // Confirms no more dashes/un-guessed lettersleft in string                                                                                                                                                                                                                                                                                                                                                                                                                         
        if(*my_string_at(key, i) == '-'){
            printf("Keep Trying!\n");
            return FALSE;
        }
    }
    return TRUE;
}

// Function to free all memory                                                                                                                                                                                                                                                                                                                                                                                                                                                              
void destroy_everything(tNode* tree, GVECTOR words, MY_STRING key, MY_STRING letters){
    destroy(&tree);
    generic_vector_destroy(&words);
    my_string_destroy(&key);
    my_string_destroy(&letters);
}
