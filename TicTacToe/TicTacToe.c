#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printBoard(char* board);
int validate(board, userInput);
void reset(char* board);
int winCheck(char* board);
void playVsHuman();
void playVsComputer();
void instruction();


int main() {

	int play = 1;
	int userInput = -1;
	while (play) {
		printf("\nHi, Welcome to TicTac Toe game. Please press: \n");
		printf("\n1 for play Vs Human");
		printf("\n2 for play Vs computer");
		printf("\n3 for Instruction");
		printf("\n4 for Exit\n");
		printf("\nUser's choice: ");
		scanf_s("%d", &userInput);
		if (userInput == 1) {
			playVsHuman();
		}
		else if (userInput == 2) {
			playVsComputer();
		}
		else if (userInput == 3) {
			instruction();
		}
		else if (userInput == 4) {
			play = 0;
		}
		else {
			printf("Please try again.");
		}
	}


	return 0;
}



void instruction() {
	int userAnswer = 0;
	char doesUserUnderstand[10];
	printf("\nRules for Tic-Tac-Toe\n");
	printf("\n1. The game is played on a grid that's 3 squares by 3 squares.");
	printf("\n2. The red player is  X, the blue player (or the computer) is O.");
	printf("\n3. The first player to get 3 marks in a row (up, down, across, or diagonally) is the winner.");
	printf("\n4. When all 9 squares are full, the game is over and start again.");
	printf("\n5. If you want to restart after the game end, you can press 1 to restart.");
	printf("\n6. You can press -1 to reset.\n");
	printf("\nIf you understood, press 'y': ");
	scanf_s("%s", doesUserUnderstand, (unsigned)_countof(doesUserUnderstand));
	if (strcmp(doesUserUnderstand, "y") == 0) {
		printf("\nOK\n");
	}
	else {
		printf("\nI'll tell you again.\n");
		instruction();
	}
	return 0;
}



void playVsHuman() {
	int validateResult = 0;
	char userInput[100] = "";
	int userInputNumber = 999999;
	char board[9] = { '0','1','2','3','4','5','6','7','8' };
	int isRedPlayer = 1;

	printBoard(board);
	printf("\n");


	while (1) {
		if (isRedPlayer == 1) {
			printf("--------------------\n");
			printf("|");
			printf("System:| Red turn |\n");
			printf("--------------------");

		}
		else {
			printf("\n\n----------------------\n");
			printf("| ");
			printf("System:| Blue turn |\n");
			printf("----------------------");
		}
		printf("\n\n\nWhich number do u want to click?(type -1 for reset): ");
		scanf_s("%s", &userInput, (unsigned int)sizeof(userInput));

		userInputNumber = atoi(userInput); //"4" -> 4
		if (userInputNumber == -1) {

			return;
		}

		if (userInputNumber >= 0 && userInputNumber <= 8) {
			validateResult = validate(board, userInputNumber);
			if (validateResult == 1) {
				if (isRedPlayer == 1) {
					board[userInputNumber] = 'X';
					isRedPlayer = 0;
				}

				else {
					board[userInputNumber] = 'O';
					isRedPlayer = 1;
				}

				printf("System: The spot you have clicked is %d \n", userInputNumber);
				if (winCheck(board) == 1) {
					char continueGame[100];
					printf("The game has ended. Do you want to play again? \nIf you do, please press 1, or 0 to exit: ");
					scanf_s("%s", &continueGame, (unsigned int)sizeof(continueGame));

					if (strcmp(continueGame, "1") == 0) {
						reset(board);
					}
					else {
						printf("See you next time.");
						return 0;
					}
				}
			}
			else {
				printf("System: This spot is already occupied. Try again");
			}

		}

		printBoard(board);
	}
	return 0;
}


void printBoard(char* board) {
	int col = 3;
	int row = 3;

	int num = 0;
	printf("\n------------\n");
	for (int i = 0; i < row; i++) {
		printf("|");
		for (int j = 0; j < col; j++) {
			printf("%c | ", board[num]);
			num++;
		}
		printf("\n------------\n");

	}
}

int validate(char* board, int userInput) {
	int counter = 0;
	int boardLength = 9;

	if (board[userInput] == 'X' || board[userInput] == 'O') {
		return 0;//something is already there
	}
	else {
		return 1;//empty
	}
}


void reset(char* board) {
	int counter = 0;
	while (counter < 9) {
		board[counter] = (char)(counter + 48);
		counter++;
	}
	printf("The game started again. Good luck!");
}


int winCheck(char* board) {
	char* winCases[8] = { "012","345","678","036","147","258","048","246" };
	char redPlayer[100] = { '0' };
	char bluePlayer[100] = { '0' };
	char str[1];
	int redIndex = 0;
	int blueIndex = 0;
	int counter = 0;

	while (counter < 9) {
		if (board[counter] == 'X') {
			redPlayer[redIndex] = (char)(counter + 48);
			redIndex++;
		}
		else if (board[counter] == 'O') {
			bluePlayer[blueIndex] = (char)(counter + 48);
			blueIndex++;
		}
		counter++;
	}

	printf("\n");
	printf("-----------------\n");
	printf("|");
	printf("Red Status : ");

	for (int i = 0; i < redIndex; i++) {
		if (redPlayer[i] == '\0') {
			break;
		}
		printf("%c ", redPlayer[i]);
	}
	printf(" \n");
	printf("-----------------");

	printf("\n");
	printf("-----------------\n");
	printf("|");
	printf("Blue Status: ");

	for (int i = 0; i < blueIndex; i++) {
		if (bluePlayer[i] == '\0') {
			break;
		}
		printf("%c ", bluePlayer[i]);
	}
	printf("\n");
	printf("-----------------\n\n");

	counter = 0;
	while (counter < 8) {
		if (strcmp(redPlayer, winCases[counter]) == 0) {

			printf("\nCongrtualtion! Red won.\n");
			return 1;
		}
		else if (strcmp(bluePlayer, winCases[counter]) == 0) {
			printf("\nCongratualation! Blue won.\n");
			return 1;
		}
		counter++;
	}

	counter = 0;
	int redCount = 0;
	int blueCount = 0;
	while (counter < 9) {

		if (board[counter] == 'X') {
			redCount++;
		}
		else if (board[counter] == 'O') {
			blueCount++;
		}

		if (blueCount + redCount == 9) {
			printf("\nDraw. Play the game again ");
			reset(board);
		}
		counter++;
	}

	return 0;
}

void playVsComputer() {
	int validateResult = 0;
	char userInput[100] = "";
	int userInputNumber = 999999;
	char board[9] = { '0','1','2','3','4','5','6','7','8' };
	int isPlayer = 1;
	char result[10] = "";
	char computerChoice = "";
	char comNumber[9];
	char comChoice = "";
	int counter = 0;
	int userChoice = 0;
	int resultExists = 1;
	int isSmallNum = 1;

	printBoard(board);
	printf("\n");

	while (1) {
		if (isPlayer == 1) {
			printf("--------------------");
			printf("\nSystem:| Red turn |\n");
			printf("--------------------");
			printf("\n\n\nWhich number do u want to click?(type -1 for reset): ");
			scanf_s("%s", &userInput, (unsigned int)sizeof(userInput));
			userInputNumber = atoi(userInput);

			if (userInputNumber == -1) {
				return;
			}

			if (userInputNumber >= 0 && userInputNumber <= 8) {
				validateResult = validate(board, userInputNumber);
				if (validateResult == 1) {
					if (isPlayer == 1) {
						board[userInputNumber] = 'X';
						isPlayer = 0;
					}
					printBoard(board);
				}
				else {
					printf("That's invalid. Try again.");
				}

			}
			else {
				printf("That's out of range. Try again.");
			}
		}
		else { //computer turn
			printf("\n\n---------------------------\n");
			printf("| ");
			printf("System:| Computer turn |\n");
			printf("---------------------------");

			int isForward = 1;

			if (userInputNumber >= 0 && userInputNumber <= 4) {
				isForward = 1;
			}
			else if (userInputNumber >= 5 && userInputNumber <= 8) {
				isForward = 0;
			}


			if (isForward == 1) {
				for (int i = 0; i < 9; i++) {
					if (board[i] != 'X' && board[i] != 'O') {
						board[i] = 'O';
						break;
					}
				}
			}

			else {
				for (int i = 8; i >= 0; i--) {
					if (board[i] != 'X' && board[i] != 'O') {
						board[i] = 'O';
						break;
					}
				}
			}

			isPlayer = 1;
			printBoard(board);

		}

		if (winCheckVsComputer(board) == 1) {
			char continueGame[100];
			printf("The game has ended. Do you want to play again? \nIf you do, please press 1, or 0 to exit: ");
			scanf_s("%s", &continueGame, (unsigned int)sizeof(continueGame));

			if (strcmp(continueGame, "1") == 0) {
				reset(board);
			}
			else {
				printf("See you next time.");
				return 0;
			}
		}

		printf("\n");
	}
}

int winCheckVsComputer(char* board) {
	char* winCases[8] = { "012","345","678","036","147","258","048","246" };
	char redPlayer[100] = { '0' };
	char computer[100] = { '0' };
	char str[1];
	int redIndex = 0;
	int computerIndex = 0;
	int counter = 0;

	while (counter < 9) {
		if (board[counter] == 'X') {
			redPlayer[redIndex] = (char)(counter + 48);
			redIndex++;
		}
		else if (board[counter] == 'O') {
			computer[computerIndex] = (char)(counter + 48);
			computerIndex++;
		}
		counter++;
	}

	printf("\n");
	printf("-----------------\n");
	printf("|");
	printf("Red Status : ");

	for (int i = 0; i < redIndex; i++) {
		if (redPlayer[i] == '\0') {
			break;
		}
		printf("%c ", redPlayer[i]);
	}
	printf(" \n");
	printf("-----------------");

	printf("\n");
	printf("----------------------\n");
	printf("|");
	printf("Computer Status: ");
	

	for (int i = 0; i < computerIndex; i++) {
		if (computer[i] == '\0') {
			break;
		}
		printf("%c ", computer[i]);
	}
	printf("\n");
	printf("----------------------\n\n");

	counter = 0;
	while (counter < 8) {
		if (strcmp(redPlayer, winCases[counter]) == 0) {

			printf("\nCongrtualtion! Red won.\n");
			return 1;
		}
		else if (strcmp(computer, winCases[counter]) == 0) {
			printf("\nComputer won.\n");
			return 1;
		}
		counter++;
	}

	counter = 0;
	int redCount = 0;
	int computerCount = 0;
	while (counter < 9) {

		if (board[counter] == 'X') {
			redCount++;
		}
		else if (board[counter] == 'O') {
			computerCount++;
		}

		if (computerCount + redCount == 9) {
			printf("\nDraw. Play the game again ");
			reset(board);
		}
		counter++;
	}

	return 0;
}

