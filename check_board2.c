///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2022
// Instructor:       deppeler
//
// Author:           Bill Lee
// Email:            blee266@wisc.edu
// CS Login:         billl
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including Peer Mentors, Instructors, and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 */
void get_board_size(FILE *fptr, int *size) {      
    char *line1 = NULL;
    size_t len = 0;

    if ( getline(&line1, &len, fptr) == -1 ) {
        printf("Error reading the input file.\n");
        exit(1);
    }

    char *size_chars = NULL;
    size_chars = strtok(line1, DELIM);
    *size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}



/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {
	if(size>9){
		return 0;
	}
	for(int i = 0; i < size; i++){
	for(int j = 0; j < size; j++){
	for(int k = 0; k < size; k++){
	if(*(*(board + i) + j)>size || *(*(board + i) + j)<1){
		return 0;
	}
	if(*(*(board + i) + j) != 0){

	if(j != k){
	if(*(*(board + i) + j) == *(*(board + i) + k)){
		return 0;
	}
	}

	if(i != k){
	if(*(*(board + i) + j) == *(*(board + k) + j)){
		return 0;
	}
	}

	}
	}
	}
	}



		return 1;   
	}    
  
 
   
/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA which is the name of the file that contains board data 
 * is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 */
int main( int argc, char **argv ) {              
     
    // TODO: Check if number of command-line arguments is correct.
	if(argc != 2){
	printf("Invalid input");
	}

    // Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    // Declare local variables.
    int size;

    // TODO: Call get_board_size to read first line of file as the board size.
	get_board_size(fp, &size);
	int **board=(int**)malloc(size*sizeof(int*));
	for (int i=0; i < size; i++){
		*(board + i) = (int*)malloc(size*sizeof(int));
	}
    // TODO: Dynamically allocate a 2D array for given board size.
    // Read the rest of the file line by line.
    // Tokenize each line wrt the delimiter character 
    // and store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading line %i of the file.\n", i+2);
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            // TODO: Complete the line of code below
            // to initialize your 2D array.
	 for (int i = 0; i < size; i++) {
            *(*(board + i) + j) = atoi(token);
            token = strtok(NULL, DELIM);
		}
        }
    }

    // TODO: Call the function valid_board and print the appropriate
    //       output depending on the function's return value.
		if(valid_board(board, size)){
		printf("Valid");
		}
		else{
		printf("Invalid");
		}


    // TODO: Free all dynamically allocated memory.
    for(int i = 0; i < 2; i++){
       free(*(board + i));
    }
       free(*board);
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       






// s22

