#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//glider gun
// 12 4 12 5 13 4 13 5 12 14 13 14 14 14 11 15 15 15 10 16 16 16 10 17 16 17 13 18 11 19 15 19 12 20 13 20 14 20 13 21 10 24 11 24 12 24 10 25 11 25 12 25 9 26 13 26 8 28 9 28 13 28 14 28 10 38 11 38 10 39 11 39

//Program Designed by Rhett Applestone 2024


void printBoard(char* board, int numCols){

	for(size_t i = 0; i < strlen(board); i++){
		if (board[i] == '1'){
			printf("%s", "\U00002B1C");	
		}else {
			printf("%s", "\U00002B1B");
		}
		
		if(((i+1) % numCols) == 0){
			printf("\n");
		}
	}
}

void changeChar(char* board, int userRow, int userCol, int numCols){

	board[(numCols*(userRow -1)) + (userCol-1)] = '1';
	
}

void invalidRowCol(int * userRow, int * userCol, int numRows, int numCols){
	printf("Invalid Row or Col num, Please enter new ones: \n");
	scanf("%d%d", userRow, userCol);

	if(*userRow > numRows || *userCol > numCols || *userRow == 0 || *userCol == 0){
		invalidRowCol(&*userRow, &*userCol, numRows, numCols);		
	}
	
}

int topThree(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i-numCols)-1] == '1'){
		neighbors++;
	}
	if (board[(i-numCols)] == '1'){
		neighbors++;
	}
	if (board[(i-numCols)+1] == '1'){
		neighbors++;
	}
	
	return neighbors;
}
int bottomThree(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i+numCols)-1] == '1'){
		neighbors++;
	}
	if (board[(i+numCols)] == '1'){
		neighbors++;
	}
	if (board[(i+numCols)+1] == '1'){
		neighbors++;
	}
	
	return neighbors;
	
}


int north(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i-numCols)] == '1'){
		neighbors++;
	}
	return neighbors;
	
}

int west(char* board, int i){
	int neighbors = 0;
	if (board[i-1] == '1'){
		neighbors++;
	}
	return neighbors;
	
}
int east(char* board, int i){
	int neighbors = 0;
	if (board[i+1] == '1'){
		neighbors++;
	}
	return neighbors;
	
}
int south(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i+numCols)] == '1'){
		neighbors++;
	}
	return neighbors;
	
}

int nw(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i-numCols)-1] == '1'){
		neighbors++;
	}
	return neighbors;
	
}
int ne(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i-numCols)+1] == '1'){
		neighbors++;
	}
	return neighbors;
	
}

int sw(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i+numCols)-1] == '1'){
		neighbors++;
	}
	return neighbors;
	
}
int se(char* board, int numCols, int i){
	int neighbors = 0;
	if (board[(i+numCols)+1] == '1'){
		neighbors++;
	}
	return neighbors;
	
}

int countNeighbors(char* board, int numRows, int numCols, int i){
	int neighbors = 0;

	// left upper corner case
	if(i == 0){

		neighbors+=east(board, i);
		neighbors+=south(board, numCols, i);
		neighbors+=se(board, numCols, i);

		return neighbors;
	}

	
	// right upper coner case

	if(i == (numCols-1)){

		neighbors+=west(board, i);
		neighbors+=sw(board, numCols, i);
		neighbors+=south(board, numCols, i);

		return neighbors;
	}

	// bottom left corner case

	if(i == ((numCols*numRows)-numCols)){

		neighbors+=north(board, numCols, i);
		neighbors+=nw(board, numCols, i);
		neighbors+=east(board, i);
		return neighbors;
	}


	// bottom right corner case
	
	if(i == ((numCols*numRows)-1)){

		neighbors+=nw(board, numCols, i);
		neighbors+=north(board, numCols, i);
		neighbors+=west(board, i);

		return neighbors;
	}

	// top edge case

	if(i < numCols){
		neighbors+=west(board, i);
		neighbors+=east(board, i);
		neighbors+=bottomThree(board, numCols, i);
		
		return neighbors;
	}


	
	// left edge case

	if((i % numCols) == 0){

		neighbors+=north(board, numCols, i);
		neighbors+=ne(board, numCols, i);
		neighbors+=east(board, i);
		neighbors+=south(board, numCols, i);
		neighbors+=se(board, numCols, i);
		
		return neighbors;
	}

	
	// right edge case
	if(((i+1) % numCols) == 0){

		neighbors+=north(board, numCols, i);
		neighbors+=nw(board, numCols, i);
		neighbors+=west(board, i);
		neighbors+=sw(board, numCols, i);
		neighbors+=south(board, numCols, i);
		
		return neighbors;
	}


	
	// bottom edge case
	if(i > ((numCols*numRows)-numCols)){

		neighbors+=topThree(board, numCols, i);
		neighbors+=west(board, i);
		neighbors+=east(board, i);
		
		return neighbors;
	}

	//general case
	
	neighbors+=topThree(board, numCols, i);
	neighbors+=west(board, i);
	neighbors+=east(board, i);
	neighbors+=bottomThree(board, numCols, i);



	return neighbors;
}

void playGame(char* board, int numRows, int numCols){

	char* newBoard = malloc(numRows*numCols*sizeof(char));
	
	// set new board all to 0s
	
	for(int i = 0; i< (numCols * numRows); i++){
		newBoard[i] = '0';
	}


	
// make new board into next itteration

	for(int i = 0; i < (numRows*numCols); i++){

		if(board[i] == '1'){

			if (countNeighbors(board, numRows, numCols, i) == 2 || countNeighbors(board, numRows, numCols, i) == 3){
				newBoard[i] = '1';
			}
						
		} else {
			if (countNeighbors(board, numRows, numCols, i) == 3){
				newBoard[i] = '1';
			}
			
		}
	
	}

	strcpy(board, newBoard);

	printBoard(board, numCols);

	free(newBoard);

	printf("\e[2J\e[H");

	usleep(125000);

	
}

int main(){
	
	int numRows;
	int numCols;



	printf("Enter the size of board you want: ");

	scanf("%d", &numRows);

	numCols = numRows;

	char* board = malloc(numRows*numCols*sizeof(char));

	for(int i = 0; i< (numCols * numRows); i++){
		board[i] = '0';
	}
	
	char* zeroes = malloc(numRows*numCols*sizeof(char));

	for(int i = 0; i< (numCols * numRows); i++){
		zeroes[i] = '0';
	}


	printBoard(board, numCols);

	printf("\n\n");

	int userRow;
	int userCol;

	printf("Enter the ROW and COL you want to be alive, ie <rows down> <cols right> (can be multiple): ");

	while(scanf("%d%d", &userRow, &userCol) == 2){
		if(userRow > numRows || userCol > numCols || userRow == 0 || userCol == 0){
			invalidRowCol(&userRow, &userCol, numRows, numCols);
		}
		
		changeChar(board, userRow, userCol, numCols);
		printBoard(board, numCols);
		printf("\n\n");
	}


	int stage = 0;
	
	while(strcmp(board, zeroes) != 0){
		playGame(board, numRows, numCols);
		stage ++;
	}

	
	free(board);
	printf("Pattern has %d stages\n", stage);
	
	return 0;
}
